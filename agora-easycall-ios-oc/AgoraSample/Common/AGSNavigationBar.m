//
//  AGSNavigationBar.m
//  AgoraSample
//
//  Created by Shilong on 9/22/15.
//  Copyright (c) 2015 Agora. All rights reserved.
//

#import "AGSNavigationBar.h"

@implementation AGSNavigationBar

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

- (void)awakeFromNib
{
    self.barStyle = UIBarStyleBlackTranslucent;
    [self setTintColor:[UIColor whiteColor]];
    [self setBackgroundImage:[UIImage imageNamed:@"ic_room_navi_bg_128"] forBarMetrics:UIBarMetricsDefault];

}
@end
