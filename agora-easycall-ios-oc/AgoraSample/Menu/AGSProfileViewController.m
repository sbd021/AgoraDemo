//
//  AGSProfileViewController.m
//  AgoraSample
//
//  Created by Shilong on 9/24/15.
//  Copyright (c) 2015 Agora. All rights reserved.
//

#import "AGSProfileViewController.h"
#import "AGSSelectMediaViewController.h"
#import "AGSAlertView.h"

@interface AGSProfileViewController ()

@property (weak, nonatomic) IBOutlet UITextField *key;
@property (weak, nonatomic) IBOutlet UITextField *username;

@property (weak, nonatomic) IBOutlet UIButton *modifyButton;

@end
@implementation AGSProfileViewController

- (IBAction)didClickModifyButton:(id)sender {
    
    if (self.key.text.length == 0) {
        UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:nil
                                                            message:NSLocalizedString(@"Please Enter Vendor Key", @"")
                                                           delegate:nil
                                                  cancelButtonTitle:NSLocalizedString(@"Done", @"")
                                                  otherButtonTitles:nil];
        [alertView show];
        return;
    }
    if (self.username.text.length == 0) {
        UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:nil
                                                            message:NSLocalizedString(@"Please Enter User Name", @"")
                                                           delegate:nil
                                                  cancelButtonTitle:NSLocalizedString(@"Done", @"")
                                                  otherButtonTitles:nil];
        [alertView show];
        return;
    }
    
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    [userDefaults setObject:self.key.text forKey:AGSKeyVendorKey];
    [userDefaults setObject:self.username.text forKey:AGSKeyUsername];
    
    [self.navigationController popViewControllerAnimated:YES];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    //
    self.title = NSLocalizedString(@"Personal Info", @"");
    self.key.placeholder = NSLocalizedString(@"Enter Vendor Key", @"");
    self.username.placeholder = NSLocalizedString(@"User", @"");
    [self.modifyButton setTitle:NSLocalizedString(@"Update", @"") forState:UIControlStateNormal];
    
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    self.key.text = [userDefaults objectForKey:AGSKeyVendorKey];
    self.username.text = [userDefaults objectForKey:AGSKeyUsername];
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    
    [self.key becomeFirstResponder];
}
@end
