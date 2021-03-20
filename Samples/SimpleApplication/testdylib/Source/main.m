#import <Foundation/Foundation.h>
#include <unistd.h>
#include <mach/mach.h>
#include <mach-o/dyld.h>
#include <libgen.h>
#include <Cocoa/Cocoa.h>

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
    NSView *targetViewReference = (NSView*)0x10281a8f8;
    [targetViewReference setBackgroundColor:[NSColor colorWithSRGBRed:0.0 green:1.0 blue:0.0 alpha:1.0]];
    return;
}

