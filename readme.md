Language/libraries: C/C++, STL, usage of additional libraries or 3rd party code is prohibited. C++17 or above should be used. For UI QT/QML framework version 6 should be used. The application should be written using OOP. Network-dependent code must be in a separate module.

# Client/Server application to load files from remote HOST.

## Second Level Heading


    Communication between client and server should be done by port 7500
    the server has to send a list of files in his folder
    the client will request to load one file from the list via a specific port. Ex port (7505)
    the server has to send a file to the client via port 7505
    the client has the opportunity to choose where a file will be saved
    the client UI should have the ability to navigate through file system
    the client should have the screen divided by two. Left side is a filesystem of the client, the right side is a filesystem of the server.
    the file that was chosen by a user should be uploaded to the folder which is opened on the client.

- Qt qml Macros + added info
- 11 standard +14 +17 
    * Test for different size type files

1. O lo la ignore 
2. Includes only where needed
Extern

### Const std string & not string
*Socket dgram*
**Serialize deserialize **
`Avoid buffers in strings :)`
Fstream
Filesystem iterator exceptions  
Use available func - vector find or FS find 

---
