#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include "./QtNetwork/QtNetwork"
#include "./QtNetwork/QTcpServer"

QT_BEGIN_NAMESPACE
namespace Ui {
class client;
}
class QTcpServer;
class QTcpSocket;
QT_END_NAMESPACE

class client : public QMainWindow
{
    Q_OBJECT

public:
    client(QWidget *parent = nullptr);
    ~client();

    void newConnectionSlot();

    bool initServer(QHostAddress host, int port) {
        tcpServer = new QTcpServer();
        if (!tcpServer->listen(host, port))
            return false;

        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
        return true;
    }

private slots:
    void on_QuitButton_clicked();

    void on_GetListButton_clicked();

    void on_SelectButton_clicked();

    void on_GetButton_clicked();

private:
    Ui::client *ui;

    QTcpServer *tcpServer = nullptr;
    QTcpSocket *tcpSocket = nullptr;
    int fileSocket;
    QString ipAddress;

    QString hostName; // = "localhost";
    const int maxConnects = 4;
    const int conversationLen = 100; // should be based on message len
    const int buffSize = 4096;
    int portNumber = 7500;
    int recievingPortNumber = 7505;

    QDataStream in;

    void readSocket() {
        QTcpSocket * socket = reinterpret_cast<QTcpSocket*>(sender());

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

    void readFileList();

    // close connection
    void close() {
        QTcpSocket * socket = reinterpret_cast<QTcpSocket*>(sender());
        socket->deleteLater();
    }
};

/*
#include <unistd.h>
#include <netdb.h>

#include <filesystem>
#include <vector>
#include <cstring>
#include <iostream>

namespace fs = std::filesystem;

class client : public QMainWindow
{

public:

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

    // request to load one file from the list via a specific port. Ex port (7505)

    // recieve file list from client
    void receiveFileList(int fileSocket, std::string neededFile = "file.txt") {
        std::cout << "Files on remote host: " << std::endl;
        for (int i = 0; i < conversationLen; i++) {
            char buffer[buffSize + 1];
            std::memset(buffer, '\0', sizeof(buffer));
            int count = read(fileSocket, buffer, sizeof(buffer));
            if (count > 0) { puts(buffer); }
        }
    }

    // send chosen file name
    char* sendFileName(int fileSocket, char* fileName) {
        std::cout << "What would you like to download?\n";
        std::cin >> fileName;

        // Send request for the file
        int result = write(fileSocket, fileName, sizeof(fileName));

        return fileName;
    }

    // get file from client
    void receiveFile(int fileSocket, std::string neededFile) {

        char buffer[buffSize];
        int count = read(fileSocket, buffer, buffSize);

        FILE* file = std::fopen(neededFile.c_str(), "w+b");
        if (count >= 0) {
            fprintf(file, "%s", buffer);
        }
        fclose(file);
    }

    bool recievedFile = false;

    // opportunity to choose where a file will be saved
    // the client UI should have the ability to navigate through file system
    // the client should have the screen divided by two. Left side is a filesystem of the client, the right side is a filesystem of the server.
    // the file that was chosen by a user should be uploaded to the folder which is opened on the client.
};

struct msg {
    int length;
    std::string message[conversationLen - sizeof(int)];
};
*/

#endif // CLIENT_H
