#include "servertools.h"
#include "botthread.h"

ServerTools::ServerTools) {

}

ServerTools::~ServerTools() {
    
}

BroadcastSender & ServerTools::getBroadcastSender() {
    return * broadcastSender;
}

UdpServer & ServerTools::getUdpServer() {
    return * udpServer;
}

Shared & ServerTools::getShared() {
    return data;
}

qint32 ServerTools::getCurentTime() {
    return curTime.elapsed();
}

void ServerTools::IPtoConsole(QString ipStr) {
    qDebug() << "ST: " << ipStr;
    emit newPlayer(ipStr);
}

void ServerTools::setNewUdpPacket() {
    
}
