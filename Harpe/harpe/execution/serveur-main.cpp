#include "serveur.hpp"

#include <iostream>
#include <chrono>

/*class Test
{
    public:
        int i1;
        int i2;
        double d1;
        
        friend ntw::Serializer& operator<<(ntw::Serializer& output,const Test& self)
        {
            output<<self.i1<<self.i2<<self.d1;
            return output;
        };
};

ntw::SelectManager clientSelector;

void newclient(ntw::SelectManager& selector,ntw::Socket& sock)
{
    ntw::SocketSerialized* clientSock = new ntw::SocketSerialized(sock.accept());
    std::cout<<"Envoi du message: <hello!> à la soket "<<clientSock->id()<<std::endl;
    *clientSock<<"hello!";
    clientSock->send();

    //clientSock->Shutdown(ntw::Socket::Down::SEND);
    clientSelector.add(clientSock);
};

void reply(ntw::SelectManager& selector,ntw::Socket& sock)
{
    ntw::SocketSerialized& clientSock = *(ntw::SocketSerialized*)&sock;
    std::cout<<"Répond à "<<clientSock.id()<<std::endl;
    if(clientSock.receive() >0)
    {
        char* c=0;
        clientSock>>c;
        std::cout<<"[serveur] recu char*: <"<<c<<">"<<std::endl;
        clientSock.clear();
        clientSock<<"message du serveur";
        clientSock.send();
    }
    else
    {
        std::cerr<<"Client connection lost <id:"<<clientSock.id()<<">"<<std::endl; 
        selector.remove(&clientSock);
        delete &clientSock;
    }
};
*/

int main(int argc, char* argv[])
{

    return serveur(argc,argv);
    /*
    ntw::Socket sock(ntw::Socket::Dommaine::IP,ntw::Socket::Type::TCP);
    ntw::Socket client = sock.Wait();
    char msg[32] = "hello word!";
    std::cout<<"Envoi du message: "<<msg<<std::endl;
    client.Send(msg,32);
    client.Shutdown();
    */

    /*ntw::SocketSerialized sockSer(ntw::Socket::Dommaine::IP,ntw::Socket::Type::TCP);
    sockSer.ServeurMode();

    ntw::SelectManager serverSelector;
    serverSelector.SetRead(true);
    serverSelector.OnSelect = newclient;
    serverSelector.Add(&sockSer);

    clientSelector.SetRead(true);
    clientSelector.OnSelect = reply;

    clientSelector.Start();
    serverSelector.Start();
    //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    //serverSelector.Stop();

    clientSelector.Wait();
    serverSelector.Wait();*/

};


