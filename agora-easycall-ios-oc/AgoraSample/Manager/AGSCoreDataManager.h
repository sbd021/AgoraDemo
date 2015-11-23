//
//  AGSCoreDataManager.h
//  AgoraSample
//
//  Created by Shilong on 9/22/15.
//  Copyright (c) 2015 Agora. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>
#import "Record.h"

@interface AGSCoreDataManager : NSObject

+ (AGSCoreDataManager *)shareManager;
- (void)saveRecordWithCallId:(NSString *)callId date:(NSDate *)date duration:(NSUInteger)duration url:(NSString *)url;

- (NSArray *)allRecords;

// SLStorage

- (void)saveItem:(id)item;
- (NSArray *)allItems;
@end
