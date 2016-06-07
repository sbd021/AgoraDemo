//
//  AGLoginViewController.m
//  AgoraMacFullset
//
//  Created by Jesse on 14/01/16.
//  Copyright © 2016 Agora. All rights reserved.
//

#import "AGLoginViewController.h"
#import "NSColor+Hex.h"
#import "NSButton+Ext.h"
#import <AgoraRtcEngineKit/AgoraRtcEngineKit.h>
#import "AGGlobalSessionConfiguration.h"

@interface AGLoginViewController ()

@property (weak) IBOutlet NSView *titleBarBackgroundView;
@property (weak) IBOutlet NSTextField *vendorKeyTextField;
@property (weak) IBOutlet NSTextField *roomNumberTextField;

@property (weak) IBOutlet NSButton *loginButton;

@end


@implementation AGLoginViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    self.titleBarBackgroundView.wantsLayer = YES;
    self.titleBarBackgroundView.layer.backgroundColor = [NSColor colorWithHex:0x1677CB].CGColor;
    
    self.vendorKeyTextField.placeholderString = NSLocalizedString(@"Enter Vendor Key", comment: @"");
    self.roomNumberTextField.placeholderString = NSLocalizedString(@"Room Number", comment: @"");
    [self.loginButton setTitle:NSLocalizedString(@"Login", comment: @"") withColor:[NSColor whiteColor]];

    [AGGlobalSessionConfiguration configuration].videoEnabled = YES;
    self.roomNumberTextField.stringValue = @"1024";
    
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    NSString *vendorKey = [userDefaults objectForKey:AGDKeyVendorKey];
    if (vendorKey) {
        self.vendorKeyTextField.stringValue = vendorKey;
    } else {
        NSError *err = nil;
        NSURL *innerKeyUrl = [NSURL URLWithString:@"http://192.168.99.253:8970/agora.inner.test.key.txt"];
        NSString *innerVendorKey = [NSString stringWithContentsOfURL:innerKeyUrl
                                                            encoding:NSASCIIStringEncoding
                                                               error:&err];

        if (!err) {
            if (innerVendorKey != nil) {
                self.vendorKeyTextField.stringValue = [innerVendorKey
                                      stringByReplacingOccurrencesOfString:@"\n" withString:@""];; // Please use your own key. The inner test key is just invalid in public.
            }
        }
    }
}

- (BOOL)validInput {
    if (self.vendorKeyTextField.stringValue.length == 0) {
        NSAlert *alert = [NSAlert new];
        alert.messageText = NSLocalizedString(@"Vendor key can not be empty", comment: @"");
        [alert addButtonWithTitle:NSLocalizedString(@"Done", comment: @"")];
        [alert beginSheetModalForWindow:self.view.window completionHandler:nil];
        
        return NO;
    }
    
    if (self.roomNumberTextField.stringValue.length == 0) {
        NSAlert *alert = [NSAlert new];
        alert.messageText = NSLocalizedString(@"User name can not be empty", comment: @"");
        [alert addButtonWithTitle:NSLocalizedString(@"Done", comment: @"")];
        [alert beginSheetModalForWindow:self.view.window completionHandler:nil];
        
        return NO;
    }
    
    return YES;
}

- (IBAction)loginAction:(id)sender {
    if ([self validInput]) {
        [AGGlobalSessionConfiguration configuration].vendorKey = self.vendorKeyTextField.stringValue;
        [AGGlobalSessionConfiguration configuration].roomIdentifier = self.roomNumberTextField.stringValue;

        [self.view.window orderOut:nil];
        [self performSegueWithIdentifier:@"ShowMainWindow" sender:nil];
    }
}

@end
