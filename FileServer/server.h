#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QFileDialog>
#include "./QtNetwork/QtNetwork"
#include "./QtNetwork/QTcpServer"

QT_BEGIN_NAMESPACE
namespace Ui {
class server;
}
class QLabel;
class QTcpServer;
QT_END_NAMESPACE


class server : public QMainWindow
{
    Q_OBJECT

public:
    server(QWidget *parent = nullptr);
    ~server();

private slots:
    void on_QuitButton_clicked();
    void on_sendFileButton_clicked();

private:
    Ui::server *ui;

    QTcpServer *tcpServer = nullptr;
    QTcpSocket *tcpSocket = nullptr;

    QString hostName;
    int portNumber = 7500;

    void newConnection();
    void readSocket();

    void sendFileList();

    // on request send a file to the client via port 7505
    void sendFile(QTcpSocket* socket, QString filename);

    // close connection
    void close();
};

#endif // SERVER_H
