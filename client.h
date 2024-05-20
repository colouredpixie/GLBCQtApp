#ifndef CLIENT_H
#define CLIENT_H

#include "network.h"
#include <QMainWindow>
#include <QDataStream>

QT_BEGIN_NAMESPACE
namespace Ui {
class client;
}
QT_END_NAMESPACE

class client : public QMainWindow
{
    Q_OBJECT

public:
    client(QWidget *parent = nullptr);

    // connect to server
    // request to load one file from the list via a specific port. Ex port (7505)
    // opportunity to choose where a file will be saved
    // the client UI should have the ability to navigate through file system
    // the client should have the screen divided by two. Left side is a filesystem of the client, the right side is a filesystem of the server.
    // the file that was chosen by a user should be uploaded to the folder which is opened on the client.

    ~client();

private:
    Ui::client *ui;
};
#endif // CLIENT_H
