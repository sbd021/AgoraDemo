//
//  AGSRatingView.h
//  AgoraSample
//
//  Created by Shilong on 9/21/15.
//  Copyright (c) 2015 Agora. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RatingBar.h"

@interface AGSRatingView : UIView

@property (weak, nonatomic) id<RatingBarDelegate> delegate;
@property (weak, nonatomic) IBOutlet UILabel *talkTimeLabel;
@property (weak, nonatomic) IBOutlet UILabel *dataTrafficLabel;

@property (weak, nonatomic) IBOutlet UILabel *titleTimeLabel;
@property (weak, nonatomic) IBOutlet UILabel *titleTrafficLabel;

@end
