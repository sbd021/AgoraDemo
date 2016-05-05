//
//  NSButton+Ext.m
//  AgoraMacFullset
//
//  Created by Jesse on 14/01/16.
//  Copyright © 2016 Agora. All rights reserved.
//

#import "NSButton+Ext.h"

@implementation NSButton (Ext)

- (void)setTitle:(NSString *)aString withColor:(NSColor *)color {
    [self setTitle:aString withColor:color alignment:NSTextAlignmentCenter];
}

- (void)setTitle:(NSString *)aString withColor:(NSColor *)color alignment:(NSTextAlignment)alignment
{
    NSMutableParagraphStyle *style = [[NSMutableParagraphStyle alloc] init];
    [style setAlignment:alignment];
    NSDictionary *attrsDictionary = @{NSForegroundColorAttributeName: color,
                                      NSParagraphStyleAttributeName: style,
                                      NSFontAttributeName: self.font};
    
    NSAttributedString *attrString = [[NSAttributedString alloc]
                                      initWithString:aString attributes:attrsDictionary];
    [self setAttributedTitle:attrString];
}

@end
