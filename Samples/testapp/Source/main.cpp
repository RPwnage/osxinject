#include <cstdio>
#include <unistd.h>
#include <mach-o/dyld.h>

int main(int argc, char* argv[]){
    printf("Testapp started. Try to hook into this process and get the value's of the listed variables.\n");
    
    // Creating some test-variables at absolute addresses
    int secretNumber;
    secretNumber = 1337;
    bool loopRunning;
    loopRunning = true;
    
    // Showing some hints
    printf("\tSecret Number  @\t%p\t\t(integer)\n", &secretNumber);
    printf("\tloopRunning    @\t%p\t\t(boolean)\n", &loopRunning);
    
    while(loopRunning = true && secretNumber == 1337){}
    printf("\nGood job! You've found the value's of (one of) the given addresses by injecting code into this process, and changed it :)\n");
    return 0;
}
