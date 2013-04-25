#include <utility>
#include <iostream>

#include "Socket.hpp"

namespace ntw {
int Socket::max_id = 0;

Socket::Socket(Socket::Dommaine dommaine,Socket::Type type,int protocole)
{
    //déclaration de la socket
    if((sock = socket(dommaine,type,protocole)) == INVALID_SOCKET)
    {
        perror("socket()");
        throw SocketExeption("Invalid socket");
    }

     max_id = (sock>max_id)?sock:max_id;

    //sin_family = Dommaine
    sock_cfg.sin_family = dommaine;
};

Socket::~Socket()
{
    _close();
};

void Socket::Connect(std::string host,int port)
{
    
    /*if(host.size() == 0)
        sock_cfg.sin_addr.s_addr = htonl(INADDR_ANY); //IP automatiquement chopée utiliser inet_addr("127.0.0.1") pour présiser
    else
        sock_cfg.sin_addr.s_addr= inet_addr(host.c_str());
    */

   struct hostent *hostinfo = gethostbyname(host.c_str());
   sock_cfg.sin_addr = *(IN_ADDR*)hostinfo->h_addr;
   
    //sin_port = port à utiliser
    sock_cfg.sin_port = htons(port);

     if(connect(sock, (SOCKADDR*)&sock_cfg, sizeof(sock_cfg)) != SOCKET_ERROR)
            std::cout<<"<id:"<<sock<<">Connexion à "<<inet_ntoa(sock_cfg.sin_addr)<<" sur le port "<<htons(sock_cfg.sin_port)<<std::endl;
        else
            std::cout<<"<id:"<<sock<<">Impossible de se connecter"<<std::endl;;
};

void Socket::Bind()
{
    if(bind(sock,(SOCKADDR*)&sock_cfg,sizeof(sock_cfg)) == SOCKET_ERROR)
    {
        perror("bind()");
        throw SocketExeption("Ennable to bind soket");
    }
}

void Socket::Listen(const int max_connexion)
{
    if(listen(sock,max_connexion) == SOCKET_ERROR)
    {
        perror("listen()");
        throw SocketExeption("Ennable to listen");
    }
}

void Socket::ServeurMode(const int max_connexion,std::string host,int port)
{
    //sin_addr.s_addr = adresse IP à utiliser
    //IP automatiquement chopée
    if(host.size() == 0)
        sock_cfg.sin_addr.s_addr = htonl(INADDR_ANY);
    else
        sock_cfg.sin_addr.s_addr= inet_addr(host.c_str());

    //sin_port = port à utiliser
    sock_cfg.sin_port = htons(port);

    Bind();
    Listen(max_connexion);

};

Socket Socket::Accept()
{
    Socket client;
    Accept(client);
    return client;
};

void Socket::Accept(Socket& client)
{
    socklen_t size = sizeof(SOCKADDR_IN);
    std::cout<<"<id:"<<sock<<">Patientez pendant que le client se connecte sur le port "<<htons(sock_cfg.sin_port)<<std::endl;
    client.sock = accept(sock,(SOCKADDR*) &client.sock_cfg, &size);
    if (client.sock == INVALID_SOCKET)
    {
        perror("accept()");
        throw SocketExeption("Invalid socket get");
    }
    std::cout<<"<id:"<<sock<<">Un client se connecte avec la socket <id:"<<client.sock<<"> de "<<inet_ntoa(client.sock_cfg.sin_addr)<<":"<<htons(client.sock_cfg.sin_port)<<std::endl;
};

void Socket::Shutdown(Socket::Down mode)
{
    if (shutdown(sock,mode) == -1)
    {
        perror("shutdown()");
        throw SocketExeption("Can't shutdown socket");
    }
};

};

