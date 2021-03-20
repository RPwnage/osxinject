//
//  main.m
//  testapp
//
//  Created by Luca on 20.03.21.
//

#include <Cocoa/Cocoa.h>
#include <mach/dyld_kernel.h>

@interface Window : NSWindow {
    NSTextField* label;
    NSView* targetView;
}

- (instancetype)init;
- (BOOL)windowShouldClose:(id)sender;

@end

@implementation Window

- (instancetype)init {
    targetView = [[[NSView alloc] initWithFrame:NSMakeRect(50, 50, 100, 100)] autorelease];
    [targetView setBackgroundColor:[NSColor colorWithSRGBRed:0.0 green:1.0 blue:0.0 alpha:1.0]];
    [super initWithContentRect:NSMakeRect(0, 0, 300, 300) styleMask:NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable backing:NSBackingStoreBuffered defer:NO];
    [self setTitle:@"ExampleApplication"];
    [[self contentView] addSubview:targetView];
    [self center];
    [self setIsVisible:YES];
    printf("UIView Element in memory @ %p\n", &targetView);
    return self;
}

- (BOOL)windowShouldClose:(id)sender {
    [NSApp terminate:sender];
    return YES;
}

@end

int main(int argc, char* argv[]) {
    [NSApplication sharedApplication];
    [[[[Window alloc] init] autorelease] makeMainWindow];
    [NSApp run];
}
