//
//  AGSHistoryCell.m
//  AgoraSample
//
//  Created by Shilong on 9/22/15.
//  Copyright (c) 2015 Agora. All rights reserved.
//

#import "AGSHistoryCell.h"

@interface AGSHistoryCell ()

@property (weak, nonatomic) IBOutlet UILabel *callReport;

@end

@implementation AGSHistoryCell

- (void)awakeFromNib {
    // Initialization code
    self.callReport.text = NSLocalizedString(@"Conf Report", @"");
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

@end
