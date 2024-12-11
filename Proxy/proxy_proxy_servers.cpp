#include<bits/stdc++.h>
using namespace std;


class Server{
    private:
    string ip;
    string response="";
    public:
    string url;
    Server(string url,string ip, string response){
        cout<<"\033[92m"<<endl;
        cout<<"Creating Server..."<<endl;
        cout<<"\033[0m"<<endl;
        this->ip=ip;
        this->url=url;
        this->response=response;
    }
    string sendResponse(){
        return response;
    }
};

class ProxyServer{
    public:
    string proxy_ip;
    string proxy_response;
    Server *server;
    ProxyServer(){}
    ProxyServer(string proxy_ip,Server *server){
        this->proxy_ip=proxy_ip;
        this->server=server;
    }
    string sendResponse(){
        return server->sendResponse();
    }
};


class DNSServer{
    private:
    unordered_map<string,string> dns;
    public:
    void setMapping(string url,string ip){
        dns[url]=ip;
    }
    string resolve(string url)
    {
        return dns[url];
    }
};

class Internet{
    private:
    unordered_map<string,ProxyServer> ServerMap;
    public:
    void setMapping(string ip, ProxyServer proxy_server){
        ServerMap[ip]=proxy_server;
    }
    ProxyServer getServer(string ip){
        return ServerMap[ip];
    }
};

class Client{
    public:
    string request(string url,DNSServer dns_server,Internet internet){
        string server_ip=dns_server.resolve(url);
        return internet.getServer(server_ip).sendResponse();
    }
};

int main(){
    Internet internet;
    DNSServer dns_server;

    string url;
    string ip;
    string content;
    string proxy_ip;

    cout<<"\033[92m"<<endl;
    cout<<"Set up proxies..."<<endl;
    cout<<"\033[0m"<<endl;
    cout<<"Enter the url: ";
    cin>>url;
    cout<<"Enter the ip: ";
    cin>>ip;
    cin.ignore();
    cout<<"Enter the content: ";
    getline(cin,content);
    cout<<"Enter the proxy ip: ";
    cin>>proxy_ip;

    Server google(url,ip,content);
    ProxyServer google_proxy(proxy_ip,&google);
    internet.setMapping(google_proxy.proxy_ip,google_proxy);
    dns_server.setMapping(google.url,google_proxy.proxy_ip);

    Client client;
    cout<<client.request("www.google.com",dns_server,internet)<<endl;
    return 0;
}