//
//  AGSMenuViewController.h
//  AgoraSample
//
//  Created by Shilong on 9/16/15.
//  Copyright (c) 2015 Agora. All rights reserved.
//

#import <UIKit/UIKit.h>


typedef NS_ENUM(NSInteger, AGSResolutionType) {
    AGSResolutionTypeCIF,
    AGSResolutionTypeLow,
    AGSResolutionTypeMiddle,
    AGSResolutionTypeHigh
};

@interface AGSResolution : NSObject

@property NSNumber *width;
@property NSNumber *height;

+ (instancetype)resolutionWithType:(AGSResolutionType)type;
+ (NSString *)resolutionFormatWithType:(AGSResolutionType)type;
@end

@interface AGSMenuViewController : UITableViewController

@property (nonatomic, copy) void (^resolutionBlock)(AGSResolution*);
@property (nonatomic, copy) void (^frameBlock)(int);
@property (nonatomic, copy) void (^rateBlock)(int);
@property (nonatomic, copy) void (^volumeBlock)(int); // 0-255

@property (nonatomic, copy) void (^recordingBlock)(BOOL);
@property (nonatomic, copy) void (^floatWindowBlock)(BOOL);

@end
