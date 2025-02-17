#include "injector.h"
#include <cstdio>
#include <cstring>
#include <mach/mach.h>
#include <mach/thread_act.h>
#include <mach/mach_init.h>
#include <pthread.h>
#include <dlfcn.h>
#include <signal.h>
#include <sys/proc_info.h>
#include <libproc.h>    

Injector::Injector() : module(0), bootstrapfn(0){
    printf("\nLoading bootstrap...\n");
    module = dlopen("bootstrap.dylib",
        RTLD_NOW | RTLD_LOCAL);
    printf("\tModule:\t\t0x%X\n", *(unsigned int*)(void *)module);
    if (!module){
        fprintf(stderr, "[ERROR] dlopen error: %s\n", dlerror());
        return;
    }
    bootstrapfn = dlsym(module, "bootstrap");
    printf("\tBootstrapfn:\t0x%X\n", *(unsigned int*)(void *)bootstrapfn);
    if (!bootstrapfn){
        fprintf(stderr, "[ERROR] Could not locate bootstrap fn\n");
        return;
    }
}

Injector::~Injector(){
    if (module){
        dlclose(module);
        module = NULL;
    }
}


void Injector::inject(pid_t pid, const char* lib){
    mach_error_t err;
    if (!module || !bootstrapfn){
        fprintf(stderr, "failed to inject: module:0x%X bootstrapfn:0x%X\n", *(unsigned int*)(void *)module, *(unsigned int*)(void *)bootstrapfn);
        return;
    } if((err = mach_inject((mach_inject_entry)bootstrapfn, lib, strlen(lib) + 1, pid, 0)) != 0){
        printf("[Error] mach_inject returned %d!\n", err);
    }
}

pid_t Injector::getProcessByName(const char *name){
    int procCnt = proc_listpids(PROC_ALL_PIDS, 0, NULL, 0);
    pid_t pids[1024];
    memset(pids, 0, sizeof(pids));
    proc_listpids(PROC_ALL_PIDS, 0, pids, sizeof(pids));
    for (int i = 0; i < procCnt; i++){
        if (!pids[i]) break;
        char curPath[PROC_PIDPATHINFO_MAXSIZE];
        char curName[PROC_PIDPATHINFO_MAXSIZE];
        memset(curPath, 0, sizeof curPath);
        proc_pidpath(pids[i], curPath, sizeof curPath);
        int len = (int)strlen(curPath);
        if (len){
            int pos = len;
            while (pos && curPath[pos] != '/') --pos;
            strcpy(curName, curPath + pos + 1);
            if (!strcmp(curName, name)){
                return pids[i];
            }
        }
    }
    return 0;
}
