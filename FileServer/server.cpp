#include "server.h"
#include "./ui_server.h"
#include <QMessageBox>
#include <QLabel>

server::server(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::server)
    , tcpServer(new QTcpServer(this))
{
    ui->setupUi(this);

    connect(tcpServer, &QTcpServer::newConnection, this, &server::sendFileList);
    connect(tcpSocket, &QIODevice::readyRead, this, &server::newConnection);
    connect(tcpSocket, &QAbstractSocket::stateChanged, this, &server::stateUpdate);

    if(!tcpServer->listen(QHostAddress::Any, portNumber)) {
        ui->textBrowser->QTextBrowser::setText("Couldn't start server. \nPlease, check if network port is available");
    } else {
        ui->textBrowser->QTextBrowser::setText("Started server. \nWaiting on a connection from the client");
    }


}

server::~server()
{
    delete ui;
}

void server::sendFileList()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_6);

    // can add struct here with fixed size
    QDir directory = QDir::current();
    QStringList files = directory.entryList(QStringList() << "*.*", QDir::Files);
    files.emplace(0, QString::number(files.size()));

    for(QString file : files) {
        out << file << ":";
    }

    tcpSocket = tcpServer->nextPendingConnection();
    connect(tcpSocket, &QAbstractSocket::disconnected, tcpSocket, &QObject::deleteLater);

    tcpSocket->write(block);
    tcpSocket->flush();
    tcpSocket->disconnectFromHost();
}

void server::readFileRequest() {
    QTcpSocket * socket = reinterpret_cast<QTcpSocket*>(sender());
    // filePortNumber?
    QByteArray dataBuffer;
    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_6_6);

    socketStream.startTransaction();
    socketStream >> dataBuffer;

    if (socketStream.commitTransaction() == false) {
        return;
    }

    sendFile(socket, dataBuffer);
}

void server::sendFile(QTcpSocket* socket, QString filename)
{
    /*
    QFile filedata(filename);

    if(socket && socket->isOpen()) {

        if (filedata.open(QIODevice::ReadOnly))
        {
            QFileInfo fileinfo(filedata);
            QString fileNameWithExt(fileinfo.fileName());

            QDataStream socketStream(socket);
            socketStream.setVersion(QDataStream::Qt_5_15); // set my Qt version

            QByteArray header;
            header.prepend("filename:") + fileNameWithExt.toUtf8() + ",filesize:" + QString::number(filedata.size()); //toUtf8 ?
            header.resize(128);

            QByteArray byteFileData;
            byteFileData.prepend(header);

            socketStream << byteFileData;
        }
        else {
            qDebug() << "File not open";
        }
    }
    else {
        ui->textBrowser->QTextBrowser::setText("File socket not open");
    }*/
}

void server::newConnection()
{
    ui->textBrowser->QTextBrowser::setText("Received a datagramme from client");
}

void server::stateUpdate(){
    QString temp;
    switch(tcpSocket->state()) {
        case QAbstractSocket::SocketState::UnconnectedState: {
        temp = 	"The socket is not connected.";
        break;
        }
        case QAbstractSocket::HostLookupState: {
        temp = 	"The socket is performing a host name lookup.";
        break;
        }
        case QAbstractSocket::ConnectingState: {
        temp = 	"The socket has started establishing a connection.";
        break;
        }
        case QAbstractSocket::ConnectedState: {
        temp = 	"A connection is established.";
        break;
        }
        case QAbstractSocket::BoundState: {
        temp = 	"The socket is bound to an address and port.";
        break;
        }
        case QAbstractSocket::ClosingState: {
        temp = 	"The socket is about to close (data may still be waiting to be written).";
        break;
        }
        default: {
        temp = 	"For internal use only.";
        break;
        }
    }
    ui->textBrowser->QTextBrowser::append(temp);
}
void server::close() {
    QTcpSocket * socket = reinterpret_cast<QTcpSocket*>(sender());
    socket->deleteLater();
}

void server::on_sendFileButton_clicked()
{
    ui->textBrowser->QTextBrowser::setText("Sending file to client");
    tcpSocket->connectToHost(QHostAddress::LocalHost, portNumber);

}

void server::on_QuitButton_clicked()
{
    QCoreApplication::quit();
}
