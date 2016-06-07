//
//  AGSKeyLoginViewController.m
//  AgoraSample
//
//  Created by apple on 15/9/15.
//  Copyright (c) 2015年 Agora. All rights reserved.
//

#import "AGSLoginViewController.h"
#import "AGSSelectMediaViewController.h"

@interface AGSLoginViewController ()

@property (weak, nonatomic) IBOutlet UITextField *keyTextField;
@property (weak, nonatomic) IBOutlet UITextField *usernameTextField;
@property (weak, nonatomic) IBOutlet UIButton *backButton;
@property (weak, nonatomic) IBOutlet UILabel *agoraLabel;
@property (weak, nonatomic) IBOutlet UIButton *loginButton;

@end

@implementation AGSLoginViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    NSString *vendorKey = [[NSUserDefaults standardUserDefaults] stringForKey:AGSKeyVendorKey];
    self.usernameTextField.text = [[NSUserDefaults standardUserDefaults] stringForKey:AGSKeyUsername];
    
    //
    [self.backButton setTitle:NSLocalizedString(@"Return", @"") forState:UIControlStateNormal];
    [self.loginButton setTitle:NSLocalizedString(@"Login", @"") forState:UIControlStateNormal];
    self.agoraLabel.text = NSLocalizedString(@"Agora Easy Call", @"");
    self.keyTextField.placeholder = NSLocalizedString(@"Enter Vendor Key", @"");
    self.usernameTextField.placeholder = NSLocalizedString(@"User", @"");
    
    if (vendorKey) {
        self.keyTextField.text = vendorKey;
    } else {
        NSError *err = nil;
        NSURL *innerKeyUrl = [NSURL URLWithString:@"http://192.168.99.253:8970/agora.inner.test.key.txt"];
        NSString *innerVendorKey = [NSString stringWithContentsOfURL:innerKeyUrl
                                                            encoding:NSASCIIStringEncoding
                                                               error:&err];

        if (!err) {
            self.keyTextField.text = [innerVendorKey
                                      stringByReplacingOccurrencesOfString:@"\n" withString:@""];; // Please use your own key. The inner test key is just invalid in public.
        }
    }
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (BOOL)isValidateInput
{
    [self.view endEditing:YES];
    if (self.keyTextField.text.length == 0) {
        UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:nil
                                                            message:NSLocalizedString(@"Vendor key can not be empty", @"")
                                                           delegate:nil
                                                  cancelButtonTitle:NSLocalizedString(@"Done", @"")
                                                  otherButtonTitles:nil];
        [alertView show];
        return NO;
    }
    if (self.usernameTextField.text.length == 0) {
        UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:nil
                                                            message:NSLocalizedString(@"User name can not be empty", @"")
                                                           delegate:nil
                                                  cancelButtonTitle:NSLocalizedString(@"Done", @"")
                                                  otherButtonTitles:nil];
        [alertView show];
        return NO;
    }
    
    return YES;
}

- (IBAction)didClickEnterChatRoom:(id)sender
{
    if ([self isValidateInput]) {
        [self performSegueWithIdentifier:AGSKeySegueIdentifierSelect sender:self];
        
        NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
        [userDefaults setObject:self.keyTextField.text forKey:AGSKeyVendorKey];
        [userDefaults setObject:self.usernameTextField.text forKey:AGSKeyUsername];
    }
}



@end
