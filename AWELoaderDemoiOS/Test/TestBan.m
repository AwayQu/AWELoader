//
//  TestBan.m
//  AWELoaderDemoiOS
//
//  Created by AwayQu on 2019/1/11.
//  Copyright © 2019 AwayQu. All rights reserved.
//

#import "TestBan.h"
#import <AWELoader/AWELoader.h>

AWE_EXPORT_FUNCTION(@"TEST_BAN", @"BAN_ENTRY", NSArray *args) {
    NSLog(@"args: %@", args);
}

@implementation TestBan
+ (void)testBan {
    [self testBan0];
    [self testBan1];
    [self testBan2];
}
+ (void)testBan0 {
    [[AWELoadManager sharedInstance] updateBanItems:@[[AWEEntryItemBase itemWithModule:AWE_COLLECTION_PREFIX_DEFAULT usage:@"TEST_BAN" key:nil]]];
    AWE_LOADER_EXECUTE(@"BAN_ENTRY", @"ENTRY_BAN_ENTRY");
}

+ (void)testBan1 {
    [[AWELoadManager sharedInstance] updateBanItems:@[[AWEEntryItemBase itemWithModule:AWE_COLLECTION_PREFIX_DEFAULT usage:@"TEST_BAN" key:@"BAN_ENTRY"]]];
    AWE_LOADER_EXECUTE(@"BAN_ENTRY", @"ENTRY_BAN_ENTRY");
}

+ (void)testBan2 {
    [[AWELoadManager sharedInstance] updateBanItems:@[[AWEEntryItemBase itemWithModule:AWE_COLLECTION_PREFIX_DEFAULT usage:nil key:@"BAN_ENTRY"]]];
    AWE_LOADER_EXECUTE(@"BAN_ENTRY", @"ENTRY_BAN_ENTRY");
}

@end
