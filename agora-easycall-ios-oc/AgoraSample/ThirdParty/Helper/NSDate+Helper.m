//
//  NSDate+Helper.m
//  BaseCode
//
//  Created by Tara on 4/3/15.
//  Copyright (c) 2015 Fellow+. All rights reserved.
//

#import "NSDate+Helper.h"

static NSString *const LOCAL_DEFAULT = @"en_US_POSIX";
static NSString *const LOCAL_ENG = @"en_US_POSIX";
static NSString *const LOCAL_CHI = @"zh_TW";

@implementation NSDate (Helper)

#pragma mark -
+ (BOOL)hasTimePassed:(NSDate *)time {
    return ([[NSDate dateWithTimeIntervalSince1970:[time timeIntervalSince1970]] timeIntervalSinceNow] < 0);
}

+ (NSTimeZone *)HKTimeZone {
    return [NSTimeZone timeZoneForSecondsFromGMT:(8 * 3600)];
}

#pragma mark -
+ (NSDate *)dateFromString:(NSString *)str format:(NSString *)format {
    return [NSDate dateFromString:str format:format withTimeZone:[NSTimeZone timeZoneForSecondsFromGMT:(8 * 3600)]];
}

+ (NSDate *)dateFromString:(NSString *)str format:(NSString *)format withTimeZone:(NSTimeZone *)tz {
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    [dateFormatter setTimeZone:tz];
    [dateFormatter setLocale:[[NSLocale alloc] initWithLocaleIdentifier:LOCAL_DEFAULT]];
    [dateFormatter setDateFormat:format];
    NSDate *date = [dateFormatter dateFromString:str];
    dateFormatter = nil;
    return date;
}

+ (NSDate *)dateFromStringWithIOS8601Format:(NSString *)str {
    return [self dateFromString:str format:@"yyyy-MM-dd'T'HH:mm:ss.SSSZ"];
}

- (NSString *)dateWithFormat:(NSString *)format {
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    [dateFormatter setTimeZone:[NSDate HKTimeZone]];
    [dateFormatter setLocale:[[NSLocale alloc] initWithLocaleIdentifier:LOCAL_DEFAULT]];
    [dateFormatter setDateFormat:format];
    return [dateFormatter stringFromDate:self];
}

- (NSString *)dateWithFormat:(NSString *)format andLocal:(NSString *)identifier {
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    [dateFormatter setTimeZone:[NSDate HKTimeZone]];
    [dateFormatter setLocale:[[NSLocale alloc] initWithLocaleIdentifier:identifier]];
    [dateFormatter setDateFormat:format];
    return [dateFormatter stringFromDate:self];
}

#pragma mark -
- (NSInteger)getWeekDayNumberWithimeZone:(NSTimeZone *)tz {
    NSCalendar *gregorian = [[NSCalendar alloc] initWithCalendarIdentifier:NSGregorianCalendar];
    NSDateComponents *weekdayComponents =[gregorian components:NSWeekdayCalendarUnit fromDate:self];
    [weekdayComponents setTimeZone:tz];
    NSInteger weekday = [weekdayComponents weekday];
    gregorian = nil;
    weekdayComponents = nil;
    return weekday;
}

- (NSInteger)getMonthNumberWithTimeZone:(NSTimeZone *)tz {
    NSUInteger unitFlags = NSMonthCalendarUnit;
    NSCalendar *calendar = [[NSCalendar alloc] initWithCalendarIdentifier:NSGregorianCalendar];
    [calendar setTimeZone:tz];
    NSDateComponents *components = [calendar components:unitFlags fromDate:self];
    calendar = nil;
    return [components month];
    
}

- (NSString *)getWeekDayWithFullName:(BOOL)withFullName {
    if (withFullName) {
        return [self dateWithFormat:@"EEEE" andLocal:LOCAL_CHI];
    }else{
        NSString *dateStr = [self dateWithFormat:@"EEE" andLocal:LOCAL_CHI];
        return [dateStr substringFromIndex:(dateStr.length - 1)];
    }
}

- (NSString *)getMonthWithFullName:(BOOL)withFullName {
    if (withFullName) {
        return [self dateWithFormat:@"MMMM" andLocal:LOCAL_CHI];
    }else{
        return [self dateWithFormat:@"MMM" andLocal:LOCAL_CHI];
    }
}

- (NSString *)getTimeWith24hour:(BOOL)with24hour {
    if (with24hour) {
        return [self dateWithFormat:@"h:mm a" andLocal:LOCAL_CHI];
    }else{
        return [self dateWithFormat:@"HH:mm"];
    }
}

#pragma mark -
- (NSString *)timeAgo {
    NSDate *now = [NSDate date];
    double deltaSeconds = fabs([self timeIntervalSinceDate:now]);
    double deltaMinutes = deltaSeconds / 60.0f;
    
    NSInteger minutes;
    
    if(deltaSeconds < 5) {
        return @"Just now";
    }else if(deltaSeconds < 60){
        return [NSString stringWithFormat:@"%@ %@", @(deltaSeconds), @"seconds ago"];
    }else if(deltaSeconds < 120){
        return @"A minute ago";
    }else if (deltaMinutes < 60){
        return [NSString stringWithFormat:@"%@ %@", @(deltaMinutes), @"minutes ago"];
    }else if (deltaMinutes < 120){
        return @"An hour ago";
    }else if (deltaMinutes < (24 * 60)){
        minutes = (NSInteger)floor(deltaMinutes/60);
        return [NSString stringWithFormat:@"%@ %@", @(minutes), @"hours ago"];
    }else if (deltaMinutes < (24 * 60 * 2)){
        return @"Yesterday";
    }else if (deltaMinutes < (24 * 60 * 7)){
        minutes = (NSInteger)floor(deltaMinutes/(60 * 24));
        return [NSString stringWithFormat:@"%@ %@", @(minutes), @"days ago"];
    }else if (deltaMinutes < (24 * 60 * 14)){
        return @"Last week";
    }else if (deltaMinutes < (24 * 60 * 31)){
        minutes = (NSInteger)floor(deltaMinutes/(60 * 24 * 7));
        return [NSString stringWithFormat:@"%@ %@", @(minutes), @"weeks ago"];
    }else if (deltaMinutes < (24 * 60 * 61)){
        return @"Last month";
    }else if (deltaMinutes < (24 * 60 * 365.25)){
        minutes = (NSInteger)floor(deltaMinutes/(60 * 24 * 30));
        return [NSString stringWithFormat:@"%@ %@", @(minutes), @"months ago"];
    }else if (deltaMinutes < (24 * 60 * 731)){
        return @"Last year";
    }else{
        minutes = (NSInteger)floor(deltaMinutes/(60 * 24 * 365));
        return [NSString stringWithFormat:@"%@ %@", @(minutes), @"years ago"];
    }
}

+ (BOOL)isToday:(NSDate *)date {
    return [self isDaysBeforeToday:date day:0];
}

+ (BOOL)isDaysBeforeToday:(NSDate *)date day:(NSInteger)day {
    NSString *str_Date = [date dateWithFormat:@"yyyyMMdd"];
    NSTimeInterval seconds = 24 * 60 * 60 * day;
    NSDate *nDate = [[NSDate alloc] initWithTimeIntervalSinceNow:-seconds];
    NSString *str_nDate = [nDate dateWithFormat:@"yyyyMMdd"];
    return [str_Date isEqualToString:str_nDate];
}

#pragma mark -
+ (NSInteger)daysBetween:(NSDate *)date {
	NSTimeInterval time = [date timeIntervalSinceDate:[NSDate date]];
	return fabs(((int)time) / (3600 * 24));
}

+ (NSInteger)age:(NSDate *)date {
	NSDateComponents *birthday = [[NSCalendar currentCalendar] components:NSDayCalendarUnit | NSMonthCalendarUnit | NSYearCalendarUnit fromDate:date];
	NSInteger brithDateYear = [birthday year];
	NSInteger brithDateDay = [birthday day];
	NSInteger brithDateMonth = [birthday month];

	NSDateComponents *today = [[NSCalendar currentCalendar] components:NSDayCalendarUnit | NSMonthCalendarUnit | NSYearCalendarUnit fromDate:[NSDate date]];
	NSInteger currentDateYear = [today year];
	NSInteger currentDateDay = [today day];
	NSInteger currentDateMonth = [today month];

	NSInteger iAge = currentDateYear - brithDateYear - 1;
	if ((currentDateMonth > brithDateMonth) || (currentDateMonth == brithDateMonth && currentDateDay >= brithDateDay)) {
		iAge++;
	}

	return iAge;
}

#pragma mark - 

- (NSInteger)dayOfYear
{
    int leapYearMonths[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int tropicalYearMonths[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    int daysOfMonths = 0;
    if ([self isLeapYear]) {
        for (int i = 0; i < [self month]-1; i++) {
            daysOfMonths = daysOfMonths + leapYearMonths[i];
        }
    } else {
        for (int i = 0; i < [self month]-1; i++) {
            daysOfMonths = daysOfMonths + tropicalYearMonths[i];
        }
    }
    
    return daysOfMonths + [self day];
}

- (NSInteger)weekOfYear
{
    NSString *string = [NSString stringWithFormat:@"%d-01-01", (int)[self year]];
    NSDate *firstDayOfYear = [NSDate dateFromString:string format:@"yyyy-MM-dd" withTimeZone:[NSTimeZone localTimeZone]];
    
    NSInteger weekday = [firstDayOfYear weekday];
    NSInteger dayOfYear = [self dayOfYear];
    NSInteger days = dayOfYear + weekday - 1;
    if (days % 7 == 0) {
        return days/7;
    } else {
        return days/7 + 1;
    }
}

- (NSInteger)year
{
    NSDateComponents *compnt = [[NSCalendar currentCalendar] components:NSYearCalendarUnit fromDate:self];
    return compnt.year;
}

- (NSInteger)month
{
    NSDateComponents *compnt = [[NSCalendar currentCalendar] components:NSMonthCalendarUnit fromDate:self];
    return compnt.month;
}

- (NSInteger)day
{
    NSDateComponents *compnt = [[NSCalendar currentCalendar] components:NSDayCalendarUnit fromDate:self];
    return compnt.day;
}

- (NSInteger)weekday
{
    NSDateComponents *compnt = [[NSCalendar currentCalendar] components:NSWeekdayCalendarUnit fromDate:self];
    return compnt.weekday;
}

- (BOOL)isLeapYear
{
    NSInteger year = [self year];
    if (year % 100 == 0) {
        return year % 400 == 0;
    } else {
        return year % 4 == 0;
    }
}

- (NSString *)stringWithCommonFormat
{
    return [self dateWithFormat:@"yyyy-MM-dd"];
}

+ (NSString *)formatStringWithDuration:(NSUInteger)duration
{
    NSUInteger seconds = duration % 60;
    NSUInteger minutes = (duration - seconds) / 60;
    return [NSString stringWithFormat:@"%02ld:%02ld", minutes, seconds];
}
@end
