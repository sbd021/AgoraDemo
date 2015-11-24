//
//  AGDLoginViewController.m
//  AgoraDemo
//
//  Created by apple on 15/9/9.
//  Copyright (c) 2015年 Agora. All rights reserved.
//

#import "AGDLoginViewController.h"
#import "AGDChatViewController.h"

static NSString * const AGDSegueIdentifierChat = @"Chat";

@interface AGDLoginViewController ()

@property (weak, nonatomic) IBOutlet UITextField *keyTextField;
@property (weak, nonatomic) IBOutlet UITextField *roomNumberTextField;

@end

@implementation AGDLoginViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
#ifdef AgoraDemo_IOS
#ifdef DEBUG
    self.keyTextField.text = @"341f3d3c30e94e13bd04be6601dfdd3d"; // Please use your own key. Test key could be forbidden in the future.
    self.roomNumberTextField.text = @"2048";
#endif
#endif
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    self.navigationController.navigationBarHidden = YES;
    
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    NSString *vendorKey = [userDefaults objectForKey:AGDKeyVendorKey];
    if (vendorKey) {
        self.keyTextField.text = vendorKey;
    }
}

- (void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    self.navigationController.navigationBarHidden = NO;
}

#pragma mark -

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    if (![segue.identifier isEqualToString:AGDSegueIdentifierChat]) {return;}
    
    AGDChatViewController *chatViewController = segue.destinationViewController;
    chatViewController.dictionary = @{AGDKeyChannel: self.roomNumberTextField.text,
                                      AGDKeyVendorKey: self.keyTextField.text};
    
    UIButton *button = (UIButton *)sender;
    if (button.tag == 1) {
        chatViewController.chatType = AGDChatTypeVideo;
    } else {
        chatViewController.chatType = AGDChatTypeAudio;
    }
}

#pragma mark -

- (IBAction)didClickPushChatViewController:(id)sender
{
    
    if ([self isValidInput]) {
        [self performSegueWithIdentifier:AGDSegueIdentifierChat sender:sender];
    }
}

- (BOOL)isValidInput
{
    [self.view endEditing:YES];
    if (_keyTextField.text.length && _roomNumberTextField.text.length) {
        return YES;
    } else {
        UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:nil
                                                            message:NSLocalizedString(@"enter_key_room", nil)
                                                           delegate:nil
                                                  cancelButtonTitle:NSLocalizedString(@"done", nil)
                                                  otherButtonTitles:nil];
        [alertView show];
        return NO;
    }
}

- (IBAction)didTapHideKeyboard:(id)sender
{
    [self.view endEditing:YES];
}

@end
