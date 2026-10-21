#import <Cocoa/Cocoa.h>
#include <cstdlib>
#include <string>

@interface Win98BevelView : NSView
@property (nonatomic, strong) NSImage* bannerImage;
@property (nonatomic, strong) NSString* statusText;
@property (nonatomic, assign) double progressValue;
@end

@implementation Win98BevelView
- (BOOL)isFlipped { return YES; }

- (void)drawWin98Rect:(NSRect)r sunken:(BOOL)sunken fill:(NSColor*)fill {
    [fill setFill];
    NSRectFill(r);
    NSColor* outerTL = sunken ? [NSColor colorWithCalibratedWhite:0.5 alpha:1.0] : [NSColor whiteColor];
    NSColor* innerTL = sunken ? [NSColor blackColor] : [NSColor colorWithCalibratedWhite:0.87 alpha:1.0];
    NSColor* outerBR = sunken ? [NSColor whiteColor] : [NSColor blackColor];
    NSColor* innerBR = sunken ? [NSColor colorWithCalibratedWhite:0.87 alpha:1.0] : [NSColor colorWithCalibratedWhite:0.5 alpha:1.0];

    [outerTL setFill];
    NSRectFill(NSMakeRect(r.origin.x, r.origin.y, r.size.width - 1, 1));
    NSRectFill(NSMakeRect(r.origin.x, r.origin.y, 1, r.size.height - 1));
    [innerTL setFill];
    NSRectFill(NSMakeRect(r.origin.x + 1, r.origin.y + 1, r.size.width - 2, 1));
    NSRectFill(NSMakeRect(r.origin.x + 1, r.origin.y + 1, 1, r.size.height - 2));
    [innerBR setFill];
    NSRectFill(NSMakeRect(r.origin.x + 1, r.origin.y + r.size.height - 2, r.size.width - 1, 1));
    NSRectFill(NSMakeRect(r.origin.x + r.size.width - 2, r.origin.y + 1, 1, r.size.height - 1));
    [outerBR setFill];
    NSRectFill(NSMakeRect(r.origin.x, r.origin.y + r.size.height - 1, r.size.width, 1));
    NSRectFill(NSMakeRect(r.origin.x + r.size.width - 1, r.origin.y, 1, r.size.height));
}

- (void)drawRect:(NSRect)dirtyRect {
    NSColor* winGray = [NSColor colorWithCalibratedWhite:0.753 alpha:1.0];
    [self drawWin98Rect:self.bounds sunken:NO fill:winGray];

    // Top Windows 98 Title Banner
    NSRect titleBar = NSMakeRect(6, 6, self.bounds.size.width - 12, 24);
    NSGradient* grad = [[NSGradient alloc] initWithStartingColor:[NSColor colorWithCalibratedRed:0 green:0 blue:0.5 alpha:1.0]
                                                     endingColor:[NSColor colorWithCalibratedRed:0.06 green:0.52 blue:0.82 alpha:1.0]];
    [grad drawInRect:titleBar angle:0.0];

    NSDictionary* titleAttrs = @{
        NSFontAttributeName: [NSFont boldSystemFontOfSize:13.0],
        NSForegroundColorAttributeName: [NSColor whiteColor]
    };
    [@"Pro-Fi 98 Setup Wizard — MORI Sounds (Universal macOS)" drawInRect:NSMakeRect(14, 9, 460, 20) withAttributes:titleAttrs];

    // Left Graphic Frame (Nano Banana Assistant Image)
    NSRect leftFrame = NSMakeRect(14, 40, 175, 220);
    [self drawWin98Rect:leftFrame sunken:YES fill:[NSColor whiteColor]];
    if (_bannerImage) {
        [_bannerImage drawInRect:NSInsetRect(leftFrame, 2, 2)
                        fromRect:NSZeroRect
                       operation:NSCompositingOperationSourceOver
                        fraction:1.0
                  respectFlipped:YES
                           hints:nil];
    }

    // Right Dialog Box
    NSRect rightFrame = NSMakeRect(200, 40, 306, 220);
    [self drawWin98Rect:rightFrame sunken:YES fill:[NSColor colorWithCalibratedWhite:0.93 alpha:1.0]];

    NSDictionary* headAttrs = @{
        NSFontAttributeName: [NSFont boldSystemFontOfSize:13.0],
        NSForegroundColorAttributeName: [NSColor colorWithCalibratedRed:0 green:0 blue:0.5 alpha:1.0]
    };
    [@"Welcome to Pro-Fi.xls Setup" drawInRect:NSMakeRect(214, 50, 280, 20) withAttributes:headAttrs];

    NSDictionary* bodyAttrs = @{
        NSFontAttributeName: [NSFont systemFontOfSize:11.5],
        NSForegroundColorAttributeName: [NSColor blackColor]
    };
    [@"This wizard will install the Universal (Apple Silicon & Intel) Pro-Fi Audio Plugin on this Mac:"
        drawInRect:NSMakeRect(214, 72, 280, 36) withAttributes:bodyAttrs];

    // Progress Bar (Windows 98 Navy Blocks)
    NSRect progBox = NSMakeRect(14, 272, 492, 22);
    [self drawWin98Rect:progBox sunken:YES fill:[NSColor whiteColor]];
    int totalBlocks = 24;
    int litBlocks = (int)std::round(_progressValue * totalBlocks);
    for (int i = 0; i < litBlocks; ++i) {
        [[NSColor colorWithCalibratedRed:0 green:0 blue:0.5 alpha:1.0] setFill];
        NSRectFill(NSMakeRect(18 + i * 20, 276, 16, 14));
    }

    // Status Bar
    NSRect statusBox = NSMakeRect(14, 300, 350, 26);
    [self drawWin98Rect:statusBox sunken:YES fill:winGray];
    if (_statusText) {
        [_statusText drawInRect:NSMakeRect(22, 306, 336, 18) withAttributes:bodyAttrs];
    }
}
@end

@interface SetupAppDelegate : NSObject <NSApplicationDelegate>
@property (nonatomic, strong) NSWindow* window;
@property (nonatomic, strong) Win98BevelView* mainView;
@property (nonatomic, strong) NSButton* chkVST3;
@property (nonatomic, strong) NSButton* chkAU;
@property (nonatomic, strong) NSButton* chkApp;
@property (nonatomic, strong) NSButton* installBtn;
@end

@implementation SetupAppDelegate

- (void)applicationDidFinishLaunching:(NSNotification*)notification {
    NSRect frame = NSMakeRect(0, 0, 520, 340);
    _window = [[NSWindow alloc] initWithContentRect:frame
                                          styleMask:(NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable)
                                            backing:NSBackingStoreBuffered
                                              defer:NO];
    [_window setTitle:@"Install Pro-Fi — MORI Sounds"];
    [_window center];

    _mainView = [[Win98BevelView alloc] initWithFrame:frame];
    _mainView.statusText = @"Ready to install Pro-Fi (VST3 / AU / Standalone).";
    _mainView.progressValue = 0.0;

    NSString* resPath = [[NSBundle mainBundle] resourcePath];
    NSString* imgPath = [resPath stringByAppendingPathComponent:@"profi_assistant_98.png"];
    _mainView.bannerImage = [[NSImage alloc] initWithContentsOfFile:imgPath];

    _chkVST3 = [NSButton checkboxWithTitle:@"VST3 Plugin  (~/Library/Audio/Plug-Ins/VST3)" target:nil action:nil];
    _chkVST3.frame = NSMakeRect(214, 118, 280, 22);
    _chkVST3.state = NSControlStateValueOn;
    [_mainView addSubview:_chkVST3];

    _chkAU = [NSButton checkboxWithTitle:@"Audio Unit  (~/Library/Audio/Plug-Ins/Components)" target:nil action:nil];
    _chkAU.frame = NSMakeRect(214, 146, 280, 22);
    _chkAU.state = NSControlStateValueOn;
    [_mainView addSubview:_chkAU];

    _chkApp = [NSButton checkboxWithTitle:@"Standalone App  (/Applications/Pro-Fi.app)" target:nil action:nil];
    _chkApp.frame = NSMakeRect(214, 174, 280, 22);
    _chkApp.state = NSControlStateValueOn;
    [_mainView addSubview:_chkApp];

    _installBtn = [[NSButton alloc] initWithFrame:NSMakeRect(374, 298, 132, 30)];
    [_installBtn setTitle:@"Install Pro-Fi >>"];
    [_installBtn setBezelStyle:NSBezelStyleRegularSquare];
    [_installBtn setTarget:self];
    [_installBtn setAction:@selector(runInstall:)];
    [_mainView addSubview:_installBtn];

    [_window setContentView:_mainView];
    [_window makeKeyAndOrderFront:nil];
    [NSApp activateIgnoringOtherApps:YES];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)sender {
    return YES;
}

- (void)runInstall:(id)sender {
    [_installBtn setEnabled:NO];
    NSString* payloadDir = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:@"Payload"];
    NSFileManager* fm = [NSFileManager defaultManager];
    NSString* home = NSHomeDirectory();

    _mainView.statusText = @"Installing Pro-Fi bundles...";
    _mainView.progressValue = 0.25;
    [_mainView setNeedsDisplay:YES];
    [[NSRunLoop currentRunLoop] runUntilDate:[NSDate dateWithTimeIntervalSinceNow:0.05]];

    NSMutableArray<NSString*>* installedPaths = [NSMutableArray array];

    if (_chkVST3.state == NSControlStateValueOn) {
        NSString* vst3Dir = [home stringByAppendingPathComponent:@"Library/Audio/Plug-Ins/VST3"];
        [fm createDirectoryAtPath:vst3Dir withIntermediateDirectories:YES attributes:nil error:nil];
        NSString* dst = [vst3Dir stringByAppendingPathComponent:@"Pro-Fi.vst3"];
        [fm removeItemAtPath:dst error:nil];
        if ([fm copyItemAtPath:[payloadDir stringByAppendingPathComponent:@"Pro-Fi.vst3"] toPath:dst error:nil]) {
            [installedPaths addObject:dst];
        }
    }
    _mainView.progressValue = 0.55;
    [_mainView setNeedsDisplay:YES];
    [[NSRunLoop currentRunLoop] runUntilDate:[NSDate dateWithTimeIntervalSinceNow:0.05]];

    if (_chkAU.state == NSControlStateValueOn) {
        NSString* auDir = [home stringByAppendingPathComponent:@"Library/Audio/Plug-Ins/Components"];
        [fm createDirectoryAtPath:auDir withIntermediateDirectories:YES attributes:nil error:nil];
        NSString* dst = [auDir stringByAppendingPathComponent:@"Pro-Fi.component"];
        [fm removeItemAtPath:dst error:nil];
        if ([fm copyItemAtPath:[payloadDir stringByAppendingPathComponent:@"Pro-Fi.component"] toPath:dst error:nil]) {
            [installedPaths addObject:dst];
        }
    }
    _mainView.progressValue = 0.80;
    [_mainView setNeedsDisplay:YES];
    [[NSRunLoop currentRunLoop] runUntilDate:[NSDate dateWithTimeIntervalSinceNow:0.05]];

    if (_chkApp.state == NSControlStateValueOn) {
        NSString* dst = @"/Applications/Pro-Fi.app";
        [fm removeItemAtPath:dst error:nil];
        if (![fm copyItemAtPath:[payloadDir stringByAppendingPathComponent:@"Pro-Fi.app"] toPath:dst error:nil]) {
            NSString* userApps = [home stringByAppendingPathComponent:@"Applications"];
            [fm createDirectoryAtPath:userApps withIntermediateDirectories:YES attributes:nil error:nil];
            dst = [userApps stringByAppendingPathComponent:@"Pro-Fi.app"];
            [fm removeItemAtPath:dst error:nil];
            [fm copyItemAtPath:[payloadDir stringByAppendingPathComponent:@"Pro-Fi.app"] toPath:dst error:nil];
        }
        [installedPaths addObject:dst];
    }

    // Clear quarantine attributes & refresh AudioComponentRegistrar
    for (NSString* p in installedPaths) {
        std::string cmd = "xattr -cr \"" + std::string([p UTF8String]) + "\" && codesign --force --deep --sign - \"" + std::string([p UTF8String]) + "\"";
        std::system(cmd.c_str());
    }
    std::system("killall -9 AudioComponentRegistrar >/dev/null 2>&1 || true");

    _mainView.progressValue = 1.0;
    _mainView.statusText = @"Installation Complete! Pro-Fi is ready.";
    [_mainView setNeedsDisplay:YES];

    NSAlert* alert = [[NSAlert alloc] init];
    alert.messageText = @"Pro-Fi 98 Setup Complete!";
    alert.informativeText = [NSString stringWithFormat:@"Successfully installed:\n• %@\n\nRestart your DAW to load Pro-Fi (under MORI Sounds).",
                             [installedPaths componentsJoinedByString:@"\n• "]];
    [alert addButtonWithTitle:@"OK"];
    [alert beginSheetModalForWindow:_window completionHandler:^(NSModalResponse) {
        [_installBtn setTitle:@"Done"];
        [_installBtn setAction:@selector(terminate:)];
        [_installBtn setTarget:NSApp];
        [_installBtn setEnabled:YES];
    }];
}

@end

int main(int argc, const char* argv[]) {
    @autoreleasepool {
        NSApplication* app = [NSApplication sharedApplication];
        [app setActivationPolicy:NSApplicationActivationPolicyRegular];
        SetupAppDelegate* del = [[SetupAppDelegate alloc] init];
        [app setDelegate:del];
        [app run];
    }
    return 0;
}
