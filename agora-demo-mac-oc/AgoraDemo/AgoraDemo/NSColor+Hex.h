//
//  NSColor+Extension.h
//  AgoraMacFullset
//
//  Created by Jesse on 12/01/16.
//  Copyright © 2016 Agora. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface NSColor (Hex)

+ (instancetype)colorWithHex:(NSInteger)hex;
+ (instancetype)colorWithHex:(NSInteger)hex alpha:(CGFloat)alpha;

@end
