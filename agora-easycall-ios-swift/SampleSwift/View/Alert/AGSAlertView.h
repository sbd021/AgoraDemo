//
//  AGSAlertView.h
//  AgoraSample
//
//  Created by apple on 15/9/16.
//  Copyright (c) 2015年 Agora. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol AGSAlertViewDelegate;

@interface AGSAlertView : UIView

@property (nonatomic, weak) NSString *title;
@property (nonatomic, weak) NSString *subTitle;
@property (nonatomic, weak) NSString *leftButtonText;
@property (nonatomic, weak) NSString *rightButtonText;
@property (nonatomic, weak) id<AGSAlertViewDelegate> delegate;

@property (weak, nonatomic) IBOutlet UILabel *titleLabel;
@property (weak, nonatomic) IBOutlet UILabel *subTitleLabel;
@property (weak, nonatomic) IBOutlet UIButton *leftButton;
@property (weak, nonatomic) IBOutlet UIButton *rightButton;
@property (weak, nonatomic) IBOutlet UIView *backgroundView;

- (id)init;
- (void)setTitle:(NSString *)title color:(UIColor *)color;
- (void)setSubTitle:(NSString *)text color:(UIColor *)color;
- (void)setLeftButtonText:(NSString *)text color:(UIColor *)color;
- (void)setRightButtonText:(NSString *)text color:(UIColor *)color;

- (void)showAlertView;
- (void)hideAlertView;
- (void)addStatusView:(UIView *)view;
- (void)setButtonEnabled:(BOOL)isEnabled;

@end

@protocol AGSAlertViewDelegate <NSObject>

- (void)agsAlertView:(AGSAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex;

@end