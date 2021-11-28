#include "tcpserver.h"
#include "udpserver.h"
#include "servertools.h"
#include "playerthread.h"

TcpServer::TcpServer(quint16 port,
                     quint8 maxPlayers,
                     UdpServer & udpServer,
                     Shared & shared,
                     QObject * parent) :
    QTcpServer(parent),
    port(port),
    maxPlayers(maxPlayers),
    udpServer(udpServer),
    sharedData(shared)
{
    if (!listen(QHostAddress::Any, port)) {
        qDebug() << "TCP Server: listen failed";
    } else {
        qDebug() << "TCP Serve r: listen OK";
    }
}

void TcpServer::incomingConnection(qintptr socketDescriptor) {
    qDebug() << "TcpServer::incomingConnection";

    quint8 curPlayers = 0;

    sharedData.playerById.readLock();
    curPlayers = sharedData.playerById.get().size();
    sharedData.playerById.readUnlock();

    if (curPlayers < maxPlayers) {

        quint16 id = 0;

        sharedData.nextPlayerId.writeLock();
        id = sharedData.nextPlayerId.read();
        sharedData.nextPlayerId.get()++;
        sharedData.nextPlayerId.writeUnlock();

        PlayerThread * thread = new PlayerThread(id, socketDescriptor,
                                             udpServer, sharedData, this);

        QObject::connect(thread, &PlayerThread::getIP, this, &TcpServer::sendIP);

//        QObject::connect(thread, SIGNAL(finished()),
//                this, SLOT(deletePlayer));
        QObject::connect(thread, SIGNAL(finished()),
                thread, SLOT(deleteLater()));


        sharedData.playerById.writeLock();
        sharedData.playerById.get().insert(id, thread);
        sharedData.playerById.writeUnlock();

        thread->start();
    }
}

//TcpServer::~TcpServer() {
//    Shared & sharedData = static_cast<ServerTools *>(parent())->getShared();
//    sharedData.playerById.writeLock();
//    PlayersMap::iterator playerIt =
//            sharedData.playerById.get().begin();
//    for(; playerIt != sharedData.playerById.get().end(); ++playerIt) {
//        PlayersMap::iterator nextPlayerIt = playerIt + 1;
//        delete playerIt.value(); //is smth wrong?
//        //sharedData.playerById.get().remove(playerIt.key()); ~PlayerThread????
//        playerIt = nextPlayerIt;
//    }
//}
