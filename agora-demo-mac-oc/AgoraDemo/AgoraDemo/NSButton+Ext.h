//
//  NSButton+Ext.h
//  AgoraMacFullset
//
//  Created by Jesse on 14/01/16.
//  Copyright © 2016 Agora. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface NSButton (Ext)

- (void)setTitle:(NSString *)aString withColor:(NSColor *)color;
- (void)setTitle:(NSString *)aString withColor:(NSColor *)color alignment:(NSTextAlignment)alignment;

@end
