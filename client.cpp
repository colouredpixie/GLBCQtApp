#include "client.h"
#include "./ui_client.h"

client::client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::client)
{
    ui->setupUi(this);

    network* networkServer = new network();
    networkServer->tcpServer = new QTcpServer();

    if(networkServer->tcpServer->listen(QHostAddress::AnyIPv4, networkServer->port)) {
        connect(networkServer->tcpServer, &QTcpServer::newConnection, this, &networkServer->newConnection());
        ui->statusbar->showMessage("TCP CLient started");
    } else {
        //QMessageBox::information(this, "TCP Server error", networkServer->tcpServer->errorString());
    }

    //connect(networkServer->tcpSocket->nextPendingConnection(), &QTcpSocket::readyRead, this, &networkServer->readSocket());
    //connect(networkServer->tcpSocket->nextPendingConnection(), &QTcpSocket::disconnected, this, &networkServer->releaseSocket());

}

client::~client()
{
    delete ui;
}


/*
 * #include "client.h"


int main()
{
    int fileSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (fileSocket < 0) { errorReport("Socket not created"); }

    struct hostent* hostPtr = gethostbyname(hostName);
    if (!hostPtr) { errorReport("Host not found"); }
    if (hostPtr->h_addrtype != AF_INET) { errorReport("Bad address family"); }

    struct sockaddr_in sockAddr { 0 };
    //std::memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_addr.s_addr = ((struct in_addr*)hostPtr->h_addr_list[0])->s_addr;
    sockAddr.sin_port = htons(portNumber);

    if (connect(fileSocket, (struct sockaddr*)&sockAddr, sizeof(sockAddr)) < 0) { errorReport("Couldn't connect to the socket"); }

    std::cout << "Sending file list" << std::endl;
    std::vector<std::string> files = getFiles();
    sendFileList(fileSocket, files);

    std::cout << "Waiting on file request..." << std::endl;
    std::string fileName = receiveFileName(fileSocket);

    std::cout << "Sending file" << std::endl;
    sendFile(fileSocket, files, fileName);

    puts("Client done, shutting down...");
    close(fileSocket);

    return 0;
}*/
