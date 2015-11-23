//
//  AGSAlertView.m
//  AgoraSample
//
//  Created by apple on 15/9/16.
//  Copyright (c) 2015年 Agora. All rights reserved.
//

#import "AGSAlertView.h"
#import "AGSAppDelegate.h"

@implementation AGSAlertView

- (id)init
{
    self = [super init];
    if (self) {
        self = [[[NSBundle mainBundle] loadNibNamed:@"AGSAlertView" owner:self options:nil] lastObject];
    }
    return self;
}

#pragma mark -

- (void)setLeftButtonText:(NSString *)leftButtonText
{
    _leftButtonText = leftButtonText;
    [self.leftButton setTitle:leftButtonText forState:UIControlStateNormal];
}

- (void)setRightButtonText:(NSString *)rightButtonText
{
    _rightButtonText = rightButtonText;
    [self.rightButton setTitle:rightButtonText forState:UIControlStateNormal];
}

- (void)setTitle:(NSString *)title
{
    _title = title;
    self.titleLabel.text = title;
}

- (void)setSubTitle:(NSString *)subTitle
{
    _subTitle = subTitle;
    self.subTitleLabel.text = subTitle;
}

#pragma mark -

- (void)setTitle:(NSString *)title color:(UIColor *)color
{
    self.titleLabel.text = title;
    self.titleLabel.textColor = color;
}

- (void)setSubTitle:(NSString *)text color:(UIColor *)color
{
    self.subTitleLabel.text = text;
    self.subTitleLabel.textColor = color;
}

- (void)setLeftButtonText:(NSString *)text color:(UIColor *)color
{
    [self.leftButton setTitle:text forState:UIControlStateNormal];
    [self.leftButton setTitleColor:color forState:UIControlStateNormal];
}

- (void)setRightButtonText:(NSString *)text color:(UIColor *)color
{
    [self.rightButton setTitle:text forState:UIControlStateNormal];
    [self.rightButton setTitleColor:color forState:UIControlStateNormal];
}

- (void)showAlertView
{
    [self hideAlertView];
    
    self.translatesAutoresizingMaskIntoConstraints = NO;
    
    AGSAppDelegate *delegate = (AGSAppDelegate *)[[UIApplication sharedApplication] delegate];
    UIWindow *window = delegate.window;
    [window addSubview:self];
    
    NSDictionary *views = @{@"SubView":self, @"SuperView":window};
    NSArray *vLayoutArray = [NSLayoutConstraint constraintsWithVisualFormat:@"V:|-0-[SubView]-0-|" options:0 metrics:nil views:views];
    NSArray *hLayoutArray = [NSLayoutConstraint constraintsWithVisualFormat:@"H:|-0-[SubView]-0-|" options:0 metrics:nil views:views];
    
    [window addConstraints:vLayoutArray];
    [window addConstraints:hLayoutArray];
}

- (void)hideAlertView
{
    [self removeFromSuperview];
}

- (void)addStatusView:(UIView *)view
{
    view.translatesAutoresizingMaskIntoConstraints = NO;
    [self.backgroundView addSubview:view];
    
    NSDictionary *views = @{@"SubView":view, @"SuperView":self.backgroundView};
    NSArray *vLayoutArray = [NSLayoutConstraint constraintsWithVisualFormat:@"V:|-0-[SubView]-0-|" options:0 metrics:nil views:views];
    NSArray *hLayoutArray = [NSLayoutConstraint constraintsWithVisualFormat:@"H:|-0-[SubView]-0-|" options:0 metrics:nil views:views];
    
    [self.backgroundView addConstraints:vLayoutArray];
    [self.backgroundView addConstraints:hLayoutArray];
}

- (void)setButtonEnabled:(BOOL)isEnabled
{
    self.rightButton.enabled = isEnabled;
}

- (IBAction)didClickButton:(UIButton *)sender
{
    if ([self.delegate respondsToSelector:@selector(agsAlertView:clickedButtonAtIndex:)]) {
        [self.delegate agsAlertView:self clickedButtonAtIndex:sender.tag];
    }
}

@end
