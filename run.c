#include <unistd.h>
#include <thread>
#include <chrono>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdlib>
#include<stdio.h>
//Function made in less than 5 minute
// You should improve it (error handling, ...)
// I use variadic template to be able to give a non fixed
// number of parameters
template<typename... str>
int my_system(char *p) {
int i, pid, status;
    // Fork create a new process
     pid = fork();
      switch(pid) {
        case 0: // we are in the new process
            //printf(p);
            system(p); // execl execute the executable passed in parameter
            break;
        case -1: // Fork returned an error
            exit(1);
        default: // We are in the parent process
           wait(&status); // We wait for the child process to end
            break;
    }
}

int main() {
    using namespace std::chrono_literals;
    // start a command
    my_system("mkdir xyz") ;
    // sleep for 2 second
    std::this_thread::sleep_for(5s);
    // ....
    my_system("ls") ;
    std::this_thread::sleep_for(5s);
   // my_system("bash") ;
    //std::this_thread::sleep_for(5s);
    printf("soooooooooooonnn");
}
