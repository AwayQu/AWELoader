//
//  AWEEntryItemBase.m
//  AWELoader
//
//  Created by AwayQu on 2019/1/11.
//  Copyright © 2019 AwayQu. All rights reserved.
//

#import "AWEEntryItemBase.h"
#import "AWELoaderInternal.h"

@implementation AWEEntryItemBase {
    NSString *_identify;
}

- (instancetype)initWithCategory:(NSString *)category collection:(NSString *)collection name:(NSString *)name key:(NSString *)key {
    self = [super init];
    if (self) {
        self.category = category;
        self.collection = collection;
        self.name = name;
        self.key = key;
    }
    
    return self;
}

+ (instancetype)itemWithModule:(NSString *)module usage:(NSString *)usage key:(NSString *)key {
    return [[self alloc] initWithCategory:AWE_CATEGORY_PREFIX_DEFAULT collection:module name:usage key:key];
}

- (NSString *)identify {
    if (!_identify) {
        return [[NSString alloc] initWithFormat:@"%@_%@_%@_%@", self.category, self.collection, self.name, self.key];
    }
    return _identify;
}

@end
