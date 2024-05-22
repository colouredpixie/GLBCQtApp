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

    bool initServer(QHostAddress host, int port);

private slots:
    void on_QuitButton_clicked();

    void on_SelectButton_clicked();

    void on_GetButton_clicked();

private:
    Ui::client *ui;

    QTcpServer *tcpServer = nullptr;
    QTcpSocket *tcpSocket = nullptr;
    QString ipAddress;

    QString hostName;
    int portNumber = 7500;
    int recievingPortNumber = 7505;

    QDataStream in;
    QStringList files;

    QByteArray readSocket();

    void readFileList();

    // close connection
    void close();

    void displayError(QAbstractSocket::SocketError socketError);
};

#endif // CLIENT_H
