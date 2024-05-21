#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include "network.h"


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
    ~client();

    connection* newConnection;

private slots:
    void on_QuitButton_clicked();

    void on_GetListButton_clicked();

    void on_SelectButton_clicked();

    void on_GetButton_clicked();

private:
    Ui::client *ui;
};

/*
#include <QDataStream>
#include <filesystem>
#include <vector>
#include <cstring>
#include <iostream>


namespace fs = std::filesystem;

class client : public QMainWindow
{

public:
    // connect to server

    void newConnection();
    // request to load one file from the list via a specific port. Ex port (7505)

    // recieve file list from client
    void receiveFileList(int fileSocket) {
        std::cout << "Files on remote host: " << std::endl;
        for (int i = 0; i < conversationLen; i++) {
            char buffer[buffSize + 1];
            std::memset(buffer, '\0', sizeof(buffer));
            int count = read(fileSocket, buffer, sizeof(buffer));
            if (count > 0) { puts(buffer); }
        }
    }

    // send chosen file name
    char* sendFileName(int fileSocket, char* fileName) {
        std::cout << "What would you like to download?\n";
        std::cin >> fileName;

        // Send request for the file
        int result = write(fileSocket, fileName, sizeof(fileName));

        return fileName;
    }

    // get file from client
    void receiveFile(int fileSocket, std::string neededFile) {

        char buffer[buffSize];
        int count = read(fileSocket, buffer, buffSize);

        FILE* file = std::fopen(neededFile.c_str(), "w+b");
        if (count >= 0) {
            fprintf(file, "%s", buffer);
        }
        fclose(file);
    }

    bool recievedFile = false;


    // opportunity to choose where a file will be saved
    // the client UI should have the ability to navigate through file system
    // the client should have the screen divided by two. Left side is a filesystem of the client, the right side is a filesystem of the server.
    // the file that was chosen by a user should be uploaded to the folder which is opened on the client.

private:

    int fileSocket;
    const char* hostName = "localhost"; // const std::string ?
    const int maxConnects = 4;
    const int conversationLen = 100;
    const int buffSize = 4096;
    int portNumber; // = 7500;
    int recievingPortNumber; // = 7505;

};
*/
#endif // CLIENT_H
