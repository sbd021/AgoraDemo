//
//  NSDate+Helper.h
//  BaseCode
//
//  Created by Tara on 4/3/15.
//  Copyright (c) 2015 Fellow+. All rights reserved.
//

#import <Foundation/Foundation.h>

#define TIME_HASPASSED(__date) [NSDate hasTimePassed:__date]

@interface NSDate (Helper)

#pragma mark -
+ (BOOL)hasTimePassed:(NSDate *)time;
+ (NSTimeZone *)HKTimeZone;

#pragma mark -
+ (NSDate *)dateFromString:(NSString *)str format:(NSString *)format;
+ (NSDate *)dateFromString:(NSString *)str format:(NSString *)format withTimeZone:(NSTimeZone *)tz;
+ (NSDate *)dateFromStringWithIOS8601Format:(NSString *)str;
- (NSString *)dateWithFormat:(NSString *)format;
- (NSString *)dateWithFormat:(NSString *)format andLocal:(NSString *)identifier;

#pragma mark -
- (NSInteger)getWeekDayNumberWithimeZone:(NSTimeZone *)tz;
- (NSInteger)getMonthNumberWithTimeZone:(NSTimeZone *)tz;
- (NSString *)getWeekDayWithFullName:(BOOL)withFullName;
- (NSString *)getMonthWithFullName:(BOOL)withFullName;
- (NSString *)getTimeWith24hour:(BOOL)with24hour;

#pragma mark -
- (NSString *)timeAgo;
+ (BOOL)isToday:(NSDate *)date;
+ (BOOL)isDaysBeforeToday:(NSDate *)date day:(NSInteger)day;

#pragma mark -
+ (NSInteger)daysBetween:(NSDate *)date;
+ (NSInteger)age:(NSDate *)date;

#pragma mark-
- (NSInteger)dayOfYear;
- (NSInteger)weekOfYear;
- (NSInteger)year;
- (NSInteger)month;
- (NSInteger)day;

#pragma mark-
- (NSString *)stringWithCommonFormat;

+ (NSString *)formatStringWithDuration:(NSUInteger)duration;
@end
