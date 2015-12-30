//
//  AGSChatCell.h
//  AgoraDemo
//
//  Created by Shilong on 9/10/15.
//  Copyright (c) 2015 Agora. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AgoraRtcEngineKit/AgoraRtcEngineKit.h>

typedef NS_ENUM(NSInteger, AGSChatType) {
    AGSChatTypeVideo,
    AGSChatTypeAudio,
    AGSChatTypeDefault = AGSChatTypeVideo
};

@protocol AGSChatCellDelegate;

@interface AGSChatCell : UICollectionViewCell

@property (nonatomic) UIView *videoView;
@property (nonatomic) UILabel *nameLabel;
@property (assign, nonatomic) AGSChatType type;

@property (assign, nonatomic) AgoraRtcQuality networkQulity;

@property (weak, nonatomic) id<AGSChatCellDelegate> delegate;
@end

@protocol AGSChatCellDelegate <NSObject>

//
- (void)cell:(AGSChatCell *)cell didMuteAudio:(BOOL)muted;

@end
