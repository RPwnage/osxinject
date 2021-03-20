#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <mach/mach.h>
#include <mach-o/dyld.h>
#include <libgen.h>

void install(void) __attribute__ ((constructor));

intptr_t calculate_aslr_for_proc(char *process_basename){
    for (uint32_t i = 0; i < _dyld_image_count(); i++) {
        const char *name = _dyld_get_image_name(i);
        if(strcmp(basename((char*)name), "testapp") == 0){
            return _dyld_get_image_vmaddr_slide(0);
        }
    } return 0;
}

void install(){
    int *secretNumberReference = (int*)(0x7ffeefbff1dc);
    bool *loopRunningReference = (bool*)(0x7ffeefbff1db);
    printf("\n");
    printf("[testdylib] Secret Number value: %d\n", *secretNumberReference);
    printf("[testdylib] loopRunning value:   %s\n", *loopRunningReference ? "true" : "false");
    *secretNumberReference = 1414;
    return;
}

