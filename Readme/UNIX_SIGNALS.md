# Unix_Signals

+ Signals are software interrupts sent to a program to indicate that an important event has occurred. The events can vary from user requests to illegal memory access errors. Some signals, such as the interrupt signal, indicate that a user has asked the program to do something that is not in the usual flow of control.
+ There is an easy way to list down all the signals supported by your system. Just issue the kill -l command and it would display all the supported signals.
# Default actions

+ Every signal has a default action associated with it. The default action for a signal is the action that a script or program performs when it receives a signal.
    + Some of the possible default actions are :
        + Terminate the process.
        + Ignore the signal.
        + Dump core. This creates a file called core containing the memory image when it received the signal.
        + Stop the precess.
        + Continue a stopped process.
# Sending Signals

+ There are several methods of delivering signals to a program or script. One of the most common is for a user to type CONTROL-C or the INTERRUPT key while a script is executing. When you press the Ctrl+C key, a SIGINT is sent to the script and as per defined default action script terminates. The other common method for delivering signals is to use the kill command, the syntax of which is as follows −
    + `$ kill -signal pid`
+ For example, in order to send the INT signal to process with PID 5342, type :
    + `$ kill -INT 5342`
+ This has the same affect as pressing Ctrl-C in the shell that runs that process, if no signal name or number is specified, the default is to send a TERM signal to the process, which normally causes its termination, and hence the name of the kill command.
## Kill() :
+ The kill() function sends a signal to a process or process group specified by pid. The signal to be sent is specified by sig and is either 0 or one of the signals from the list in the <sys/signal.h> header file.
#### Example :
```c
// sender.c

 #include<signal.h>

 int main (int argc, char **argv)
 {
    int pid;

    pid = ft_atoi(argv[1]);       // the process ID from standard input
    kill(pid, SIGUSR1);           // SIGUSR1 : macro defined in signal.h header
 }
```
+ Now the signal has been sended to the process, to handle this signal we need to know about how to handle a signal.

# Signal handling 
 
+ A signal is said to be generated for (or send to) aprocess when the event that causes the signal first occurs. Examples of such events include detection of hardware faults, timer expiration, and terminal activity, as well as the invocation of kill. In some circumstances, the same event generates signals for multiple processes.
+ If you install no signal handlers of your own (remember what a signal handler is? yes, that function handling a signal?), the runtime environment sets up a set of default signal handlers for your program. For example, the default signal handler for the TERM signal calls the exit() system call. The default handler for the ABRT signal calls the abort() system call, which causes the process's memory image to be dumped into a file named 'core' in the process's current directory, and then exit. for more informations about UNIX signals visite <a href = "http://www.cs.kent.edu/~ruttan/sysprog/lectures/signals.html">UNIX signals</a>

## Signal() :
+ Allows a process to choose one of the several ways to handle an interrupt signal sig drom the operating sytem or from the raise() function.
+ The sig argument must be one of the macros defined in the signal.h header file. 
+ the func argument must be one of the macros, SIG_DFL or SIG_IGN, defined in the signal.h header file, or a function address.
```
#include <signal.h>
void (*signal(int sig, void(*func) (int)))(int);
```
##### Example :
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammout <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 19:58:11 by ahammout          #+#    #+#             */
/*   Updated: 2022/03/15 17:59:56 by ahammout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<signal.h>
#include<stdio.h>

// function to handle the signal
void    ft_handle(int sig)
{
    if (sig == SIGUSR1)
    {
        printf("The signal %d has been received successfully");
    }
}
int main()
{
    int pid;

    pid = getpid();                      // Function to get the process ID.
    printf("This is the process ID : %d", pid);  // Displaying the process ID.
    signal(SIGUSR1, ft_handle);            // if Signal is SIGUSR1 handle it using ft_handle function.
    while(1)
    {
        pause();                         // pause : wait for signal.
    }
}
```

## Sigaction () :
###### Examines and changes the action associated with a specific signal.
#### Format :
```c
#include<signal.h>

int sigaction(int sig, const struct sigaction *__restrict__ new , struct sigaction *__restrict__ old);
```
+ `int sig` is the number of recognized signal.
+ `const struct sigaction *new`, may be a NULL pointer. if so, sigaction() merely determine the action currently defined to handle `sig`. If `new` is not NULL, it should point to a sigaction structure. the action specified in this structure becomes the new action associated with sig.
+ `struct sigaction *old`, points to a memory location where sigaction() can store a sigaction stucture describing the action currently associated with `sig`. old can also be a NULL pointer, in which case sigaction() does not store this information.

### sigaction structure 
+ The structure sigaction defined as follows:
```c
struct sigaction{
    void        (*sa_handler)(int);
    sigset_t    sa_mask;
    int         sa_flags;
    void        (*sa_sigaction)(int, siginfo *, void *);
}
```
+ The structure sigaction it's contain three objects :
    1. The function `(*sa_handler)(int);`: This is a pointer to a function, which handles the received signal, it has the same effect as the the second parameter on `signal()`, it can handle the signal, by give her the address of our handling function like :
    ```c
    void    ft_handle(int sig)
    {
        if (sig == SIGUSR1)
        {
            printf("The signal %d has been received successfully");
        }
    }
    ```
    2. `sigset_t    sa_mask` : A signal set identifies a set of signals that are to be added to the signal-handling function `sa_handler` or `sa_sigaction` (in XPG4.2) is invoked. For more sets, see <a href = "https://www.ibm.com/docs/en/zos/2.2.0?topic=functions-sigemptyset-initialize-signal-mask-exclude-all-signals#rtsige">sigemptyset().</a> You cannot use this mechanism to block SIGKILL, SIGSTOP, or SIGTRACE. If sa_mask includes these signals, they will simply be ignored; `sigaction()` will not return error. `sa_mask` must be set by using one or more of the signals set manipulation functions: `sigemptyset()`, `sigaddset()`, or `sigdelset()`.
    3. `int sa_flags` : A collection flags bits that affect the behavior of signals.
    4. `sa_sigaction` : a pointer to a the function assigned to handle the signal, or `SIG_DFL`, or `SIG_IGN`. This function will be invoked passing three parameters. The first is of type `int` that contains the signal type for which this function is being invoked. The second is of type `pointer to siginfo_t` where the siginfo_t contain additional information about the source of the signal. The third is of type `pointer to void` but will actually point to a ucontext_t containing the context information at the time of the signal interrupt.

## sigemptyset() :
```c
int sigemtyset(sigset_t *set);
```
> sigemptyset() : initializes the signal set given byte by set to empty, with all signals excluded from the set.

## sigaddset() :
```c
int sigaddset(sigset_t *set, int signo);
```
> sigaddset() : adds the individual signal specified by the value of signo to the set pointed to by set.

## getpid() :
```c
pid_t   getpid(void);
```
> getpid() : returns process ID (PID) for the calling process.

## pause() :
```c
int pause(void);
```
> pause() : causes the calling process (or thread) to sleep untill a signal is delivered that either terminates the process or causes the invocation of a signal-catching function.

## sleep() :
```c
unsigned int sleep(unsigned int seconds);
```
> sleep(): causes the calling thread to sleep either until the number of real-time seconds specified in seconds have elapsed or until a signal arrives which is not ignored.

## usleep() :
```c
int usleep(useconds_t usec);
```
> suspends execution of the calling thread for (at least) usec microseconds, The sleep may nbe lengthened slightly by any system activity or the time spent processing the call or by the granularity of the system timers.

# Links
+ <a href = "https://linuxhint.com/signal_handlers_c_programming_language/"> Signal handlers in C language</a>
+ <a href = "https://www.ibm.com/docs/en/zos/2.2.0?topic=functions-sigaction-examine-change-signal-action">IBM Docs - Sigaction()</a>
