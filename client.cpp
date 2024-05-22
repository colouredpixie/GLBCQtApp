#include "client.h"
#include "./ui_client.h"
#include <QtWidgets>

client::client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::client)
    , tcpServer(new QTcpServer(this))
    , tcpSocket(new QTcpSocket(this))
{
    ui->setupUi(this);

    in.setDevice(tcpSocket);
    in.setVersion(QDataStream::Qt_6_5);

    connect(tcpSocket, &QIODevice::readyRead, this, &client::newConnectionSlot);
    //connect(tcpSocket, &QAbstractSocket::errorOccurred, this, &client::displayError);

    hostName = QHostInfo::localHostName();

    tcpSocket->connectToHost("127.0.0.1", portNumber);


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
    ui->textBrowser->QTextBrowser::setText("new Connection Slot open!");
}

void client::readFileList(){
    in.startTransaction();

    QString incomingText;
    in >> incomingText;

    if (!in.commitTransaction())
        return;

    ui->InTextBrowser->QTextBrowser::setText(incomingText);
}

void client::displayError(QAbstractSocket::SocketError socketError) {
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The host was not found. Please check the "
                                    "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
        break;
    default:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The following error occurred: %1.")
                                     .arg(tcpSocket->errorString()));
    }
}
