#include<bits/stdc++.h>
using namespace std;

enum class ServerStatus{ONLINE,OFFLINE};

struct Server{
    string ip;
    int port;
    ServerStatus status;
};

class LoadBalancer
{
private:
    vector<Server> servers;
    unordered_map<string,Server> serverMap;
    queue<Server> requestQueue;
    int currentIndex;
public:
    LoadBalancer():currentIndex(0){};

    void addServer(const string& ip,int port)
    {
        Server newServer{ip,port, ServerStatus::ONLINE};
        servers.push_back(newServer);
        serverMap[ip]=newServer;
    }
    
    void removeServer(const string& ip) {
        if (serverMap.count(ip)) { 
            serverMap[ip].status = ServerStatus::OFFLINE;
        }
    }

    Server getServer() {
        while (true) {
            currentIndex = (currentIndex + 1) % servers.size();
            Server server = servers[currentIndex];  // Return a copy of the server
            if (server.status == ServerStatus::ONLINE) { 
                return server; 
            }
        }
    }

    void processRequest(const string& clientIP, int clientPort) {
        Server server = getServer(); 
        cout << "Routing request from client " << clientIP << ":" << clientPort << " to server " << server.ip << ":" << server.port << endl;
    }

    void addRequest(const string& clientIP, int clientPort) {
        requestQueue.push({ clientIP, clientPort, ServerStatus::ONLINE }); 
    }

    void handleRequests() {
        while (!requestQueue.empty()) { 
            Server server = getServer(); // Return a copy of the server
            Server request = requestQueue.front(); 
            requestQueue.pop(); 
            cout << "Routing queued request from client " << request.ip << ":" << request.port << " to server " << server.ip << ":" << server.port << endl;
        }
    }
};

int main() {
    LoadBalancer lb; 

    lb.addServer("192.168.1.1", 8080);
    lb.addServer("192.168.1.2", 8080);
    lb.addServer("192.168.1.3", 8080);

    lb.addRequest("10.0.0.1", 1234);
    lb.addRequest("10.0.0.2", 2345);
    lb.addRequest("10.0.0.3", 3456);

    lb.processRequest("10.0.0.4", 4567);

    lb.handleRequests();

    return 0;
}
