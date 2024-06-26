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

    connect(tcpSocket, &QIODevice::readyRead, this, &client::readFileList);

    tcpSocket->connectToHost(QHostAddress::LocalHost, portNumber);
}

client::~client()
{
    delete ui;
}

void client::readFileList(){
    readSocket();

    for (QString file : files) {
        file.removeFirst();
        file.removeLast();
        ui->listWidget->addItem(file);
    }
}

QByteArray client::readSocket() {
    QTcpSocket * socket = reinterpret_cast<QTcpSocket*>(sender());

    QByteArray dataBuffer;
    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_15);

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

    return dataBuffer;
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
    ui->textBrowser->QTextBrowser::setText("Choose file to download");

    /*
    QString saveFilePath = QCoreApplication::applicationDirPath() + "/" + fileName;
    QFile file(saveFilePath);
    if(file.open(QIODevice::WriteOnly)) {
        file.write(dataBuffer);
        file.close();
    }
    */
}
