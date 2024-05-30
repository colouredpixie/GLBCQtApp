#include "client.h"
#include "./ui_client.h"
#include <QtWidgets>
#include <QPushButton>

client::client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::client)
    , tcpServer(new QTcpServer(this))
{
    ui->setupUi(this);

    tcpSocket = new QTcpSocket();
    connect(tcpSocket, &QIODevice::readyRead, this, &client::readSocket);
    tcpSocket->connectToHost(QHostAddress::LocalHost, portNumber);

    saveFilePath = QCoreApplication::applicationDirPath();

    connect(tcpSocket, &QAbstractSocket::stateChanged, this, &client::stateUpdate);

}

client::~client()
{
    delete ui;
}

void client::readSocket(){
    if(files.isEmpty())
        receiveFileList();
    else
        receiveFile();
}

QByteArray client::receiveFileList() {
    tcpSocket = reinterpret_cast<QTcpSocket*>(sender());

    QByteArray dataBuffer;
    QDataStream socketStream(tcpSocket);
    socketStream.setVersion(QDataStream::Qt_6_6);

    QByteArray byteSize;
    int size;

    socketStream.startTransaction();
    socketStream >> byteSize;
    byteSize = byteSize.remove(0, 1);
    size = byteSize.toInt();

    dataBuffer = tcpSocket->readAll();
    for (int i = 0; i < size; i++) {
        files.append(dataBuffer.split(':')[i+1]);
    }

    if (socketStream.commitTransaction() == false) {
        return 0;
    }

    for (QString file : files) {
        file.removeFirst();
        file.removeLast();
        ui->listWidget->addItem(file);
    }

    return dataBuffer;
}

void client::sendFileRequest(QString filename) {
    tcpSocket = new QTcpSocket();
    //tcpSocket->connectToHost(QHostAddress::LocalHost, portNumber);

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_6);
    out << filename;
    tcpSocket->connectToHost(QHostAddress::LocalHost, portNumber);
    connect(tcpSocket, &QAbstractSocket::disconnected, tcpSocket, &QObject::deleteLater);

    tcpSocket->write(block);
    tcpSocket->flush();
    tcpSocket->disconnectFromHost();
}


QByteArray client::receiveFile()
{
    QTcpSocket * socket = reinterpret_cast<QTcpSocket*>(sender());

    QByteArray dataBuffer;
    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_6_6);

    socketStream >> dataBuffer;

    QString header = dataBuffer.mid(0, 128);
    QString fileName = header.split(",")[0].split(":")[1];
    QString fileSize = header.split(",")[1].split(":")[1];
    dataBuffer = dataBuffer.mid(128);

    saveFilePath = saveFilePath + "/" + fileName;
    QFile file(saveFilePath);
    if(file.open(QIODevice::WriteOnly)) {
        file.write(dataBuffer);
        file.close();
    } else {
        ui->textBrowser->QTextBrowser::setText("file not open");
    }

    return dataBuffer;
}

void client::stateUpdate(){
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

void client::close() {
    QTcpSocket * socket = reinterpret_cast<QTcpSocket*>(sender());
    socket->deleteLater();
}

void client::on_QuitButton_clicked()
{
    QCoreApplication::quit();
}

void client::on_SelectButton_clicked()
{
    saveFilePath = QFileDialog::getExistingDirectory(this, "Select folder to save file to", QCoreApplication::applicationDirPath());
    ui->textBrowser->QTextBrowser::setText(saveFilePath);
}

void client::on_GetButton_clicked()
{
    QString fileName;
    if (!ui->listWidget->selectedItems().isEmpty())
    {
        fileName = ui->listWidget->selectedItems().first()->text();
        ui->textBrowser->QTextBrowser::setText("Selected file: " + fileName);
        sendFileRequest(fileName);
    }
    else
    {
        ui->textBrowser->QTextBrowser::setText("Select a file to download");
    }
}
