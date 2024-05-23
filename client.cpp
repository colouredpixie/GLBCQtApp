#include "client.h"
#include "./ui_client.h"
#include <QtWidgets>
#include <QPushButton>

client::client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::client)
    , tcpServer(new QTcpServer(this))
    , tcpSocket(new QTcpSocket(this))
{
    ui->setupUi(this);

    in.setDevice(tcpSocket);
    in.setVersion(QDataStream::Qt_6_5);

    connect(tcpSocket, &QIODevice::readyRead, this, &client::readSocket);

    tcpSocket->connectToHost(QHostAddress::LocalHost, portNumber);
}

client::~client()
{
    delete ui;
}

void client::readSocket(){
    receiveFileList();
}

QByteArray client::receiveFileList() {
    QTcpSocket * socket = reinterpret_cast<QTcpSocket*>(sender());

    QByteArray dataBuffer;
    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_6_6);

    QByteArray byteSize;
    int size;

    socketStream.startTransaction();
    socketStream >> byteSize;
    byteSize = byteSize.remove(0, 1);
    size = byteSize.toInt();

    dataBuffer = socket->readAll();
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

void sendFileRequest() {

}


QByteArray client::receiveFile() {
    QTcpSocket * socket = reinterpret_cast<QTcpSocket*>(sender());

    QByteArray dataBuffer;
    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_6_6);

    QString header = dataBuffer.mid(0, 128);
    QString fileName = header.split(",")[0].split(":")[1];
    QString fileExt = fileName.split(".")[1];
    QString fileSize = header.split(",")[1].split(":")[1];

    dataBuffer = dataBuffer.mid(128);
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
    QString filePath = QFileDialog::getExistingDirectory(this, "Select folder to save file to", QCoreApplication::applicationDirPath());
    ui->textBrowser->QTextBrowser::setText(filePath);
}

void client::on_GetButton_clicked()
{
    ui->textBrowser->QTextBrowser::setText("Selected file to download:");
    ui->textBrowser->QTextBrowser::append(ui->listWidget->selectedItems().first()->text());

    /*
    QString saveFilePath = QCoreApplication::applicationDirPath() + "/" + fileName;
    QFile file(saveFilePath);
    if(file.open(QIODevice::WriteOnly)) {
        file.write(dataBuffer);
        file.close();
    }
    */
}
