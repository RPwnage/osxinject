#include "injector.h"
#include <cstdio>
#include <cassert>
#include <cstring>
#include <dlfcn.h>
#include <stdlib.h>
#include <unistd.h>
#include <filesystem>
#include <iostream>
#include <sys/types.h>
#include <string.h>
#include <filesystem>
#include <iostream>

namespace fs = std::__fs::filesystem;


int main(int argc, char* argv[]){
    if(argc < 3){
        fprintf(stderr, "==> Usage:\n\t./osxinj [proc_name] [lib]\n");
        return -1;
    }if(getuid() > 0){
        fprintf(stderr, "[ERROR] Please run me as root\n");
        return -1;
    }if(!std::__fs::filesystem::exists(argv[2])) {
        fprintf(stderr, "[ERROR] Library not found!\t(%s)\n", argv[2]);
        return -1;
    }

    char path[4096];
    realpath(argv[2], path);
    fprintf(stderr, "Injecting %s into %s...", fs::path(path).filename().c_str(), argv[1]);
    Injector inj;
    
    pid_t pid = inj.getProcessByName(argv[1]);
    if (!pid){
        fprintf(stderr, "[ERROR] Process %s not found!\n", argv[1]);
        return 0;
    }
    
    fprintf(stderr, "\nInjecting library...\n");
    fprintf(stderr, "\tTarget PID:\t%u\n", pid);
    inj.inject(pid, path);
    return 0;
}
