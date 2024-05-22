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

private slots:
    void on_QuitButton_clicked();
    void on_SelectButton_clicked();
    void on_GetButton_clicked();

    // get files list from server on connection
    void readFileList();

private:
    Ui::client *ui;

    QTcpServer *tcpServer = nullptr;
    QTcpSocket *tcpSocket = nullptr;
    QString ipAddress;
    int portNumber = 7500;

    QDataStream in;
    QStringList files;

    // get files list from server extended functionality
    QByteArray readSocket();

    // close connection
    void close();
};

#endif // CLIENT_H
