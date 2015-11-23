//
//  AGSLaunchViewController.m
//  AgoraSample
//
//  Created by Shilong on 9/24/15.
//  Copyright (c) 2015 Agora. All rights reserved.
//

#import "AGSLaunchViewController.h"
#import "FOWebViewController.h"
@interface AGSLaunchViewController ()
@property (weak, nonatomic) IBOutlet UIButton *useKeyButton;
@property (weak, nonatomic) IBOutlet UIButton *noKeyButton;

@end

@implementation AGSLaunchViewController
- (IBAction)didClickNoKeyButton:(id)sender
{
    FOWebViewController *web = [[FOWebViewController alloc] initWithURL:@"http://www.agora.io" title:@"Agora"];
    [self.navigationController pushViewController:web animated:YES];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    self.navigationController.navigationBarHidden = YES;
    
    [self.useKeyButton setTitle:NSLocalizedString(@"Login with Key", @"") forState:UIControlStateNormal];
    [self.noKeyButton setTitle:NSLocalizedString(@"Need a key? Click Here", @"") forState:UIControlStateNormal];
}
@end
