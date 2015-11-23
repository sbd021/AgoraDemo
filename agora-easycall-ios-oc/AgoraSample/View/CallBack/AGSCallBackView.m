//
//  AGSCallBackView.m
//  AgoraSample
//
//  Created by apple on 15/9/18.
//  Copyright (c) 2015年 Agora. All rights reserved.
//

#import "AGSCallBackView.h"
#import "AGSAppDelegate.h"

@implementation AGSCallBackView

- (id)init
{
    self = [super init];
    if (self) {
        self = [[[NSBundle mainBundle] loadNibNamed:@"AGSCallBackView" owner:self options:nil] lastObject];
        self.callLabel.text = NSLocalizedString(@"In Call", @"");
    }
    return self;
}

- (void)showCallBackView
{
    self.translatesAutoresizingMaskIntoConstraints = NO;
    
    AGSAppDelegate *delegate = (AGSAppDelegate *)[UIApplication sharedApplication].delegate;
    UIWindow *window = delegate.window;
    [window addSubview:self];
    
    NSLayoutConstraint *widthConstraint = [NSLayoutConstraint
                                      constraintWithItem:self
                                      attribute:NSLayoutAttributeWidth
                                      relatedBy:NSLayoutRelationEqual
                                      toItem:nil
                                      attribute:NSLayoutAttributeWidth
                                      multiplier:1
                                      constant:60];
    NSLayoutConstraint *heightConstraint = [NSLayoutConstraint
                                       constraintWithItem:self
                                       attribute:NSLayoutAttributeHeight
                                       relatedBy:NSLayoutRelationEqual
                                       toItem:nil
                                       attribute:NSLayoutAttributeHeight
                                       multiplier:1
                                       constant:60];
    
    NSLayoutConstraint *topConstraint = [NSLayoutConstraint
                                       constraintWithItem:self
                                       attribute:NSLayoutAttributeTop
                                       relatedBy:NSLayoutRelationEqual
                                       toItem:window
                                       attribute:NSLayoutAttributeTop
                                       multiplier:1
                                       constant:122];
    NSLayoutConstraint *rightConstraint = [NSLayoutConstraint
                                       constraintWithItem:self
                                       attribute:NSLayoutAttributeRight
                                       relatedBy:NSLayoutRelationEqual
                                       toItem:window
                                       attribute:NSLayoutAttributeRight
                                       multiplier:1
                                       constant:-18];

    [window addConstraint:topConstraint];
    [window addConstraint:rightConstraint];
    [window addConstraint:widthConstraint];
    [window addConstraint:heightConstraint];
    
    [self setTImeLabelTextWithFormat:self.durationTime];
    self.timer = [NSTimer scheduledTimerWithTimeInterval:1 target:self selector:@selector(updateTimeLabel) userInfo:nil repeats:YES];
}

- (void)updateTimeLabel
{
    self.durationTime++;
    [self setTImeLabelTextWithFormat:self.durationTime];
}

- (void)hideCallBackView
{
    [self.timer invalidate];
    [self removeFromSuperview];
}

- (void)setTImeLabelTextWithFormat:(NSInteger)time
{
    NSUInteger seconds = time % 60;
    NSUInteger minutes = (time - seconds) / 60;
    self.timeLabel.text = [NSString stringWithFormat:@"%02td:%02td", minutes, seconds];
}

- (IBAction)didClickBackChatView:(id)sender
{
    if ([self.delegate respondsToSelector:@selector(didHideCallBackView:)]) {
        [self.delegate didHideCallBackView:self];
    }
}

@end
