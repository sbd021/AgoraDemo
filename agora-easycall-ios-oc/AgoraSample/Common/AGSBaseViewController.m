//
//  AGSBaseViewController.m
//  AgoraSample
//
//  Created by apple on 15/9/14.
//  Copyright (c) 2015年 Agora. All rights reserved.
//

#import "AGSBaseViewController.h"
#import "AGSChatViewController.h"

@interface AGSBaseViewController ()

@end

@implementation AGSBaseViewController

- (void)viewDidLoad {
    [super viewDidLoad];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)didClickBackButton:(id)sender
{
    [self.navigationController popViewControllerAnimated:YES];
}

- (IBAction)didTapHideKeyBoard:(id)sender
{
    [self.view endEditing:YES];
}

@end
