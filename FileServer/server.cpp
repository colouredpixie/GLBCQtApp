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

    connect(tcpServer, &QTcpServer::newConnection, this, &server::newConnection);

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

void server::readSocket() {
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
    sendFileList();
}

void server::close() {
    QTcpSocket * socket = reinterpret_cast<QTcpSocket*>(sender());
    socket->deleteLater();
}

void server::on_sendFileButton_clicked()
{
    ui->textBrowser->QTextBrowser::setText("Sending file to client");
}

void server::on_QuitButton_clicked()
{
    QCoreApplication::quit();
}
