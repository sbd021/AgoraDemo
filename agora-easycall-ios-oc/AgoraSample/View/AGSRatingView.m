//
//  AGSRatingView.m
//  AgoraSample
//
//  Created by Shilong on 9/21/15.
//  Copyright (c) 2015 Agora. All rights reserved.
//

#import "AGSRatingView.h"

@interface AGSRatingView ()

@property (weak, nonatomic) IBOutlet UIView *ratingView;
@property (strong, nonatomic) RatingBar *ratingBar;
@end

@implementation AGSRatingView

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        
    }
    return self;
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

- (void)awakeFromNib
{
    self.ratingBar = [[RatingBar alloc] init];
    self.ratingBar.frame = CGRectMake(0, 0, 170, 23);
    
    [self.ratingView addSubview:self.ratingBar];
    
    //
    self.titleTimeLabel.text = NSLocalizedString(@"Total Time", @"");
    self.titleTrafficLabel.text = NSLocalizedString(@"Total Trafic", @"");
}

- (void)setDelegate:(id<RatingBarDelegate>)delegate{
    [self.ratingBar setImageDeselected:@"ic_evaluate_dialog_cell_star" halfSelected:nil fullSelected:@"ic_evaluate_dialog_cell_star_yellow" andDelegate:delegate];
}

@end
