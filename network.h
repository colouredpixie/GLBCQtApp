#ifndef NETWORK_H
#define NETWORK_H

#include "./QtNetwork/QtNetwork"
#include "./QtNetwork/QTcpServer"

QT_BEGIN_NAMESPACE
class QTcpServer;
class QTcpSocket;
QT_END_NAMESPACE

class connection {
public:

    // error checking
    void errorReport(const char* message) {
        puts(message);
        exit(-1);
    }

    bool initServer() {
        tcpServer = new QTcpServer();
        if (!tcpServer->listen())
            return false;

        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
        return true;
    }

    /*
    bool createSocket() {
        int fileSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (fileSocket < 0) {
errorReport("Socket not created");
return false;}

        struct hostent* hostPtr = gethostbyname(hostName);
        if (!hostPtr) { errorReport("Host not found"); }
        if (hostPtr->h_addrtype != AF_INET) {
errorReport("Bad address family");
return false;}

        struct sockaddr_in sockAddr { 0 };
        //std::memset(&sockAddr, 0, sizeof(sockAddr));
        sockAddr.sin_family = AF_INET;
        sockAddr.sin_addr.s_addr = ((struct in_addr*)hostPtr->h_addr_list[0])->s_addr;
        sockAddr.sin_port = htons(portNumber);
return true;
    }
*/

    QTcpServer *tcpServer = nullptr;
    QTcpSocket *tcpSocket = nullptr;
    int fileSocket;
    QString ipAddress;

    const char* hostName = "localhost"; // const std::string ?
    const int maxConnects = 4;
    const int conversationLen = 100; // should be based on message len
    const int buffSize = 4096;
    int portNumber; // = 7500;
    int recievingPortNumber; // = 7505;
};

/*
#include "./include/QtNetwork/QTcpSocket"
#include <unistd.h>
#include <netdb.h>

class network {
public:

    // listen
    void readSocket() {
        QTcpSocket * socket = reinterpret_cast<QTcpSocket*>(tcpSocket); //sender());

        QByteArray dataBuffer;
        QDataStream socketStream(socket);
        socketStream.setVersion(QDataStream::Qt_5_15);

        socketStream.startTransaction();
        socketStream >> dataBuffer;

        if (socketStream.commitTransaction() == false) {
            return;
        }

        QString header = dataBuffer.mid(0, 128);
        QString fileName = header.split(",")[0].split(":")[1];
        QString fileExt = fileName.split(".")[1];
        QString fileSize = header.split(",")[1].split(":")[1];

        dataBuffer = dataBuffer.mid(128);

        QString saveFilePath = QCoreApplication::applicationDirPath() + "/" + fileName;
        QFile file(saveFilePath);
        if(file.open(QIODevice::WriteOnly)) {
            file.write(dataBuffer);
            file.close();
        }
    }
void receiveFile(int fileSocket, std::string neededFile = "file.txt");

struct msg {
    int length;
    std::string message[conversationLen - sizeof(int)];
};

    // close connection
    void releaseSocket() {
        QTcpSocket * socket = reinterpret_cast<QTcpSocket*>(tcpSocket); //sender());
        socket->deleteLater();
    }
};
*/
#endif // NETWORK_H
