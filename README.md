# GhostKey-Basic Backdoor and Server prototype for Ethical Hacking and Penetration Testing

## Overview

This repository contains a **backdoor program** and its corresponding **server** implementation, designed for ethical hacking purposes. These programs demonstrate how attackers establish connections, execute commands, and persist on a target system audit.

> **Disclaimer:** This project is strictly for educational purposes. Unauthorized use of this code is illegal. The author is not responsible for any misuse.

>**Compatibility:** The backdoor program is designed to work on **Windows 10** machines,while the server can run on a **Linux** system. The backdoor uses Windows-specific libraries,including **ws2_32** and **wininet**


### Development Plan 
1. Establish a connection with the server.
2. Implement a shell function to handle incoming commands.
3. Ensure automatic startup after a system reboot.
4. Enable the backdoor to spawn additional programs.
5. Add directory navigation capabilities.
6. Integrate a keylogger to log user inputs.
7. Run the backdoor silently in the background without showing a console window.
## Features

### Backdoor (`backdoor.c`)
- **Server Connection:** Establishes a persistent connection to the attacker's server.
- **Command Execution:** Receives and executes shell commands from the server.
- **Persistence Mechanism:** Modifies the registry to ensure automatic execution after system reboot.
- **Directory Navigation:** Allows changing directories on the target system.
- **Keylogger Integration:** Starts a keylogger to capture keystrokes.
- **Program Spawning:** Enables the spawning of additional programs.

### Server (`server.c`)
- **Connection Listener:** Listens for incoming connections from the backdoor.
- **Command Execution:** Sends shell commands to the backdoor and displays the responses.
- **Special Commands:**
  - `persist`: Activates the backdoor's persistence mechanism.
  - `keylog_start`: Starts the keylogger on the target machine.
  - `cd <directory>`: Changes the working directory on the target machine.
  - `q`: Terminates the connection with the target.

### Embedding the Backdoor in a File
The compiled **malware.exe** can be hidden within an image file or any other file type using **WinRAR**:

1. Place the backdoor.exe and an image file (e.g., image.jpg) in the same directory.
2. Compress both files together using WinRAR.
3. Right-click on the files and select "Add to archive...".
4. In the archive settings > General tab> choose **Create SFX archive** option.
5. now in **Advanced tab** click on **SFX options...**.
6. In **Setup tab**, Add the files(the malware.exe and the file you selected for embedding) in the **Run after extraction** box.
7. In **Modes tab**>**Silent Mode**>Select Hide all.
8. In **Text and Icon**, Browse the ico file (false logo).
9. In **Update tab**, under Updae mode section, select **Extract and update file** . Under overwrite mode, choose **Overwrite all files**.
10. Save the Changes.


## Installation and Setup

### Prerequisites
- **Development Environment:**  
  - GCC (for compilation)
  - Linux for the server and Windows for the backdoor
- **Networking Knowledge:** Basic understanding of socket programming.
- **Environment Setup:** Ensure you have an attacker machine (Linux) and a target machine (Windows-Windows 10 advisable).

### Compiling the Programs
- **Compile the backdoor:**
#### Backdoor
1. Update the following placeholders in `backdoor.c` and `server.c` with the attacker's IP and setup PORT:
  **for backdoor.c**
    ```c
   ServIP = "<attacker-IP>";
   ServPort = <PORT_No>;
  **for server.c**
  ```c
server_address.sin_addr.s_addr=inet_addr("<attacker-IP machine>");
		server_address.sin_port=htons(<PORT_No>);
```
2. Compile the backdoor on Windows 10 using the following command using:
   **for backdoor.c**
```c
   gcc server.c -o server
```
**for server.c**
```c
i686-w64-mingw32-gcc -o malware.exe backdoor.c -lwsock32 -lwininet
```
4. This command will create a Windows executable backdoor.exe that can run on a **Windows 10** system.

5. Transfer the **malware.exe** to the target **Windows 10** machine and run it.

### Disguising your malware
* You may choose any image or any file ,example excel,pdf,word etc.
* Download an ico file for logo of archieved .exe file. 

 ## About Me
This project is my first attempt at malware development, created purely for learning purposes. I developed this project with the help of online resources and tutorials, including YouTube videos (Special thanks! to Vabs Tutorials) , to gain a deeper understanding of how backdoors and servers function in the context of penetration testing.

As a beginner in malware development, this project reflects my initial exploration into this domain and showcases fundamental concepts like socket programming, persistence mechanisms, and keylogging.

