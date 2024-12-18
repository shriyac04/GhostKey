# Backdoor and Server for Penetration Testing

## Overview

This repository contains a **backdoor program** and its corresponding **server** implementation, designed for penetration testing and ethical hacking purposes. These programs demonstrate how attackers establish connections, execute commands, and persist on a target system.

> **Disclaimer:** This project is strictly for educational purposes. Unauthorized use of this code is illegal. The authors are not responsible for any misuse.

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

### Development Plan (`malwareplan.txt`)
1. Establish a connection with the server.
2. Implement a shell function to handle incoming commands.
3. Ensure automatic startup after a system reboot.
4. Enable the backdoor to spawn additional programs.
5. Add directory navigation capabilities.
6. Integrate a keylogger to log user inputs.

## Installation and Setup

### Prerequisites
- **Development Environment:**  
  - GCC (for compilation)
  - Linux for the server and Windows for the backdoor
- **Networking Knowledge:** Basic understanding of socket programming.
- **Environment Setup:** Ensure you have an attacker machine (Linux) and a target machine (Windows).

### Compiling the Programs

#### Backdoor
1. Update the following placeholders in `backdoor.c`:
   ```c
   ServIP = "<attacker-IP>";
   ServPort = <PORT-No>;
