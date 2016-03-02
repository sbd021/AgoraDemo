//
//  NSColor+Extension.m
//  AgoraMacFullset
//
//  Created by Jesse on 12/01/16.
//  Copyright © 2016 Agora. All rights reserved.
//

#import "NSColor+Hex.h"

@implementation NSColor (Hex)

+ (instancetype)colorWithHex:(NSInteger)hex {
    return [NSColor colorWithHex:hex alpha:1.0f];
}


+ (instancetype)colorWithHex:(NSInteger)hex alpha:(CGFloat)alpha {
    NSColor *color =
    [NSColor colorWithRed:((CGFloat) ((hex & 0xFF0000) >> 16))/255
                    green:((CGFloat) ((hex & 0xFF00) >> 8))/255
                     blue:((CGFloat) (hex & 0xFF))/255
                    alpha:alpha];
    
    return color;
}

@end
