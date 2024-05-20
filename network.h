#ifndef NETWORK_H
#define NETWORK_H

#include "./include/QtNetwork/QTcpSocket"


QT_BEGIN_NAMESPACE
class QTcpSocket;
QT_END_NAMESPACE

class network {
public:

    // Communication between client and server should be done by port 7500

    // ports
    // host
    // create connection
    // connect
    // listen
    // close connection

private:
    QTcpSocket *tcpSocket = nullptr;

};

#endif // NETWORK_H
