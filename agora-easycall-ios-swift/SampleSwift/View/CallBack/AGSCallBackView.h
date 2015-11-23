//
//  AGSCallBackView.h
//  AgoraSample
//
//  Created by apple on 15/9/18.
//  Copyright (c) 2015年 Agora. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol AGSCallBackViewDelegate;

@interface AGSCallBackView : UIView

@property (weak, nonatomic) IBOutlet UILabel *timeLabel;
@property (weak, nonatomic) IBOutlet UILabel *callLabel;
@property (nonatomic) NSInteger durationTime;
@property (nonatomic, weak) id<AGSCallBackViewDelegate> delegate;
@property (nonatomic, strong) NSTimer *timer;

- (void)showCallBackView;
- (void)hideCallBackView;

@end

@protocol AGSCallBackViewDelegate <NSObject>

- (void)didHideCallBackView:(AGSCallBackView *)view;

@end