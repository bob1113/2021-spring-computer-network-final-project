<div id="top"></div>

# TCP number guessing game

![](https://badgen.net/badge/last-modify/2022-06-27/)

## Table of contents

<div>
    <!-- <summary>Table of Contents</summary> -->
    <ul>
        <li>
            <a href="#about-the-project">About The Project</a>
            <ul>
                <li><a href="#built-with">Built With</a></li>
            </ul>
        </li>
        <li>
            <a href="#how-to-run-the-project">Getting Started</a>
            <ul>
                <li><a href="#prerequisites">Prerequisites</a></li>
                <li><a href="#installation-and-simulation">Installation</a></li>
                <li><a href="#remarks">Remarks</a></li>
            </ul>
        </li>
        <li><a href="#acknowledgments">Acknowledgments</a></li>
        <li><a href="#license">License</a></li>
        <li><a href="#contact">Contact</a></li>
    </ul>
</div>



## About the project

Tis is a number guessing game based on TCP socket. The server side allows clients to guess a number between 0 to 999, and replies a guessing result, onthe other hand, the client side can access the server, guess a number, and read the result replied by the server. Since this project is implemented by Windows Sockets API, it can only run on Windows system, but one shall be able to modify it into a Linux/Unix system version easily.


### Built with

+ Windows Sockets API

<p align="right">(<a href="#top">back to top</a>)</p>



## How to run the project

### Prerequisites

+ [gcc compiler](https://gcc.gnu.org/)
+ [Loopback adapter](https://docs.microsoft.com/en-us/troubleshoot/windows-server/networking/install-microsoft-loopback-adapter)
+ [Wireshark(optional)](https://www.wireshark.org/)

<!-- TODO: Loopback adapter -->
Loopback adapter is a network interface that can be used to route network traffic from one application to another on the same computer, but does NOT send that traffic to any other device on the network, which is useful to observe the behaviors on both server side and client side with only one Windows-system computer.  

<!-- TODO: Wireshark usage -->
Wireshark is a free and open-source packet analyzer, one may use it to observe the communication between server and slient in this project.


### Installation and simulation

To get a local copy up and running follow these simple steps.

1. Clone the repo
    <!-- TODO: detail instruction -->
    ```sh
    git clone https://github.com/bob1113/tcp-number-guessing-game.git
    ```

2. Compile the `ser.cpp` and `cli.cpp` files
    <!-- TODO: compilation -->
    ```sh
    g++ -o cli cli.cpp -lws2_32
    ```
    ```sh
    g++ -o ser ser.cpp -lws2_32
    ```

3. Initialize server and client \
    Open two powershell windows, one for server side, and the other for client side. \
    \
    **Server**
    ```sh
    .\ser 5555
    ```
    **Client**
    ```sh
    .\cli 127.0.0.1 5555
    ```
    
    <!-- TODO: Server behavior with screenshot -->
    <!-- TODO: Client behavior with screenshot -->
    | Game start                  | Guess number              | Correct guess             |
    | --------------------------- | ------------------------- | ------------------------- |
    | ![](/image/game-start.png) | ![](/image/guessing.png) | ![](/image/correct.png)  |
     
### Remarks


The number used in `.\ser 5555` is the port number that server and client communicate with, and the address `127.0.0.1` means that the client communicate with the server through loopback adapter, i.e., sending and receiving packets on the same computer.

<p align="right">(<a href="#top">back to top</a>)</p>



## Acknowledgments

+ [Windows Socket 2 document](https://docs.microsoft.com/en-us/windows/win32/winsock/windows-sockets-start-page-2)
+ [Winsock tutorial – Socket programming in C on windows](https://www.binarytides.com/winsock-socket-programming-tutorial/)

<p align="right">(<a href="#top">back to top</a>)</p>



## License

Distributed under the MIT License. See `LICENSE` for more information.

<p align="right">(<a href="#top">back to top</a>)</p>



## Contact

Bob Lai - [bobolai1113@gmail.com](bobolai1113@gmail.com) \
Project Link - [https://github.com/bob1113/tcp-number-guessing-game](https://github.com/bob1113/tcp-number-guessing-game)

<p align="right">(<a href="#top">back to top</a>)</p>