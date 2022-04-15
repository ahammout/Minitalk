# Minitalk 42_project

## Project Instructions :
### Mandatory part :

 * The purpose of this project is to code a small data exchange program using UNIX signals, to do this we will creat a comminication program in the form of a client and a server
    + the server must be started first . after its launch, it has to print its PID (process ID).
    + The client takes two parameters :
        + The server PID.
        + The string to send.
    + The client must send the string passed as a parameter to the server once the string has ben received, the server must print it. 
    + the server has to display the string pretty quickly means that if you think it takes too long then it is probably too long.
    + Your server should be able to receive strings from several clients in a row without needing to restart.
    + The communication between your client and your server has to be done only using UNIX signals.
    + You can only use these two signals: SIGUSR1 and SIGUSR2.

### Bonus part
    
+ The server acknowledges every message received by sending back a signal to the client.

+ Unicode characters support!

# Knowledgement
<a hrer="https://github.com/ahammout/Minitalk/blob/main/Readme/UNIX_SIGNALS.md">About Unix_signals </a>
