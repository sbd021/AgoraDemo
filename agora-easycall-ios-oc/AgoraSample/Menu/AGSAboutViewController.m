//
//  AGSAboutViewController.m
//  AgoraSample
//
//  Created by Shilong on 9/24/15.
//  Copyright (c) 2015 Agora. All rights reserved.
//

#import "AGSAboutViewController.h"
#import "FOWebViewController.h"

@interface AGSAboutViewController ()

@property (weak, nonatomic) IBOutlet UILabel *faqLabel;
@property (weak, nonatomic) IBOutlet UILabel *updateLabel;
@property (weak, nonatomic) IBOutlet UILabel *AgoraLabel;

@end

@implementation AGSAboutViewController

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    //
    self.title = NSLocalizedString(@"About", @"");
    self.AgoraLabel.text = NSLocalizedString(@"Agora Conf.", @"");
    self.updateLabel.text = NSLocalizedString(@"Update", @"");
    self.faqLabel.text = NSLocalizedString(@"FAQ", @"");
}

- (IBAction)didTapFAQView:(id)sender
{
    FOWebViewController *web = [[FOWebViewController alloc] initWithURL:@"http://www.agora.io/faq" title:NSLocalizedString(@"FAQ", @"")];
    [self.navigationController pushViewController:web animated:YES];
}

@end
