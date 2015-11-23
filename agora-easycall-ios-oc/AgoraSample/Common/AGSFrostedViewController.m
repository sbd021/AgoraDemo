//
//  AGSFrostedViewController.m
//  AgoraSample
//
//  Created by Shilong on 9/16/15.
//  Copyright (c) 2015 Agora. All rights reserved.
//

#import "AGSFrostedViewController.h"
#import "AGSAppDelegate.h"

@interface AGSFrostedViewController ()

@end

@implementation AGSFrostedViewController

- (void)awakeFromNib
{
    UIStoryboard *loginStoryboard = [UIStoryboard storyboardWithName:@"Login" bundle:nil];
    UIStoryboard *menuStoryboard = [UIStoryboard storyboardWithName:@"Menu" bundle:nil];
    UINavigationController *navigationController = [loginStoryboard instantiateViewControllerWithIdentifier:@"Navigation"];
    self.contentViewController = navigationController;
    self.menuViewController = [menuStoryboard instantiateViewControllerWithIdentifier:@"Menu"];
    
    self.limitMenuViewSize = YES;
    self.direction = REFrostedViewControllerDirectionRight;
    self.menuViewSize = CGSizeMake(208, self.menuViewSize.height);
    self.panGestureEnabled = NO;
    
    AGSAppDelegate *delegate = (AGSAppDelegate *)[UIApplication sharedApplication].delegate;
    navigationController.delegate = delegate;
    delegate.navigationController = navigationController;
    
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}



/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
