//
//  AGSChatViewController.h
//  AgoraDemo
//
//  Created by apple on 15/9/9.
//  Copyright (c) 2015年 Agora. All rights reserved.
//

#import "AGSBaseViewController.h"
#import "AGSChatCell.h"
#import "AGSSelectMediaViewController.h"
#import "AGSMenuViewController.h"
#import "AGSAlertView.h"
#import "AGSRatingView.h"

@interface AGSChatViewController : AGSBaseViewController <AGSAlertViewDelegate, RatingBarDelegate, UITableViewDataSource, AGSChatCellDelegate, UIAlertViewDelegate>

@property(nonatomic,retain) NSDictionary *dictionary;
@property (assign, nonatomic) AGSChatType chatType;
@property (nonatomic) NSUInteger duration;

@end

@interface AGSChatActivityCell : UITableViewCell

@property (weak, nonatomic) IBOutlet UILabel *titleLabel;

@end