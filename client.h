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

    void newConnection();
    // request to load one file from the list via a specific port. Ex port (7505)
    // opportunity to choose where a file will be saved
    // the client UI should have the ability to navigate through file system
    // the client should have the screen divided by two. Left side is a filesystem of the client, the right side is a filesystem of the server.
    // the file that was chosen by a user should be uploaded to the folder which is opened on the client.


    ~client();

private:

    Ui::client *ui;
};

/*
 * #pragma once
#include <filesystem>
#include <vector>
#include <cstring>
#include <iostream>
#include "network.h"


namespace fs = std::filesystem;

// get files in its folder in list
std::vector<std::string> getFiles() {
    std::vector<std::string> filesList;

    fs::path currentFolder = fs::current_path();
    for (const auto& element : fs::directory_iterator(currentFolder)) {
        if (element.is_regular_file()) {
            filesList.push_back(element.path().filename().string());
        }
    }
    return filesList;
}

// send file list to the server
void sendFileList(int fileSocket, std::vector<std::string> files) {
    for (int i = 0; i < files.size(); i++) {
        write(fileSocket, files[i].c_str(), files[i].length());
    }
}

// receive file name to send
std::string receiveFileName(int fileSocket) {
    std::string fileName;
    for (int i = 0; i < conversationLen; i++) {
        char buffer[buffSize + 1];
        std::memset(buffer, '\0', sizeof(buffer));
        int count = read(fileSocket, buffer, sizeof(buffer));
        if (count > 0) {
            fileName = buffer;
            std::cout << fileName << std::endl;
        }
    }
    return fileName;
}

// send file to the server
void sendFile(int fileSocket, std::vector<std::string> files, std::string fileName) {
    bool isInFolder = false;
    for (const auto& element : files) {
        if (element == fileName) {
            std::cout << "Sending the file: " << fileName << std::endl;
            isInFolder = true;

            FILE* file = fopen(fileName.c_str(), "r+b");
            int bytes_read;
            char buffer[buffSize + 1];
            while (!feof(file)) {
                if ((bytes_read = fread(&buffer, 1, buffSize, file)) > 0) {
                    send(fileSocket, buffer, bytes_read, 0);
                    std::cout << "Sending..." << std::endl;
                }
                else
                    break;
            }
            fclose(file);
        }
    }
    if (!isInFolder) { std::cout << "No such file in folder. Please, try again" << std::endl; }
}


// error checking
void errorReport(const char* message) {
    perror(message);
    exit(-1);
}

bool recievedFile = false;

class client {
    connection sock;

};
*/


#endif // CLIENT_H
