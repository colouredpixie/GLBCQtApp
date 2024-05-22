#include "client.h"
#include "./ui_client.h"

client::client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::client)
{
    ui->setupUi(this);

    portNumber = 7500;

    if (initServer(QHostAddress::AnyIPv4, portNumber))
    {
        ui->textBrowser->QTextBrowser::setText("Connection created");
        ui->statusbar->showMessage("TCP CLient started");
        connect(tcpServer, &QTcpServer::newConnection, this, &client::newConnectionSlot);
    }
    else
       ui->textBrowser->QTextBrowser::setText("Connection not created");

    connect(tcpServer->nextPendingConnection(), &QTcpSocket::readyRead, this, &client::readSocket);
    connect(tcpServer->nextPendingConnection(), &QTcpSocket::disconnected, this, &client::close);
/*
    int fileSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (fileSocket < 0) { networkServer->errorReport("Socket not created"); }

    // bind the server's local address in memory
    struct sockaddr_in sockAddr { 0 };
    //std::memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    sockAddr.sin_port = htons(portNumber);

    if (bind(fileSocket, (struct sockaddr*)&sockAddr, sizeof(sockAddr)) < 0) { networkServer->errorReport("Couldn't bind server's address"); }

    if (listen(fileSocket, maxConnects) < 0) { networkServer->errorReport("Listening error"); }
    fprintf(stderr, "Listening on port %i for clients...\n", portNumber);

    while (!recievedFile) {
        struct sockaddr_in clientAddr;
        socklen_t len = sizeof(clientAddr);

        int clientFileSocket = accept(fileSocket, (struct sockaddr*)&clientAddr, &len);
        if (clientFileSocket < 0) {
            perror("Connections error");
            continue;
        }

        std::cout << "Receiving file list..." << std::endl;
        receiveFileList(clientFileSocket);

        std::cout << "Sending file request" << std::endl;
        char fileName[conversationLen];
        sendFileName(clientFileSocket, fileName);

        std::cout << "Waiting on remote file..." << std::endl;
        receiveFile(clientFileSocket, fileName);

        recievedFile = true;

        puts("Server done, shutting down...");
        ::close(clientFileSocket);
    }
*/
}

client::~client()
{
    delete ui;
}

void client::on_QuitButton_clicked()
{
    QCoreApplication::quit();
}


void client::on_GetListButton_clicked()
{
    ui->textBrowser->QTextBrowser::setText("Recieving file");
}


void client::on_SelectButton_clicked()
{
    ui->textBrowser->QTextBrowser::setText("Select input folder");
}


void client::on_GetButton_clicked()
{
    ui->textBrowser->QTextBrowser::setText("Choose file to download");
}

void client::newConnectionSlot() {
    ui->textBrowser->QTextBrowser::setText("new Connection Slot");
}
