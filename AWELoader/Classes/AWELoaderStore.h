//
// Created by Away on 12/29/18.
// Copyright (c) 2018 AwayQu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AWEEntryItemBase.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, AWEEntryType) {
    AWEEntryTypeENV = 1,
    AWEEntryTypeFUNC
};


@interface AWEEntryItem : AWEEntryItemBase

@property(nonatomic, assign, readonly) AWEEntryType type;

/// optional
@property(nonatomic, copy, readonly, nullable) NSString *envValue;
@property(nonatomic, readonly, nullable) void *functionValue;
@property (nonatomic, assign, readonly) int argsCount;

- (instancetype)initWithCategory:(NSString *)category collection:(NSString *)collection name:(NSString *)name key:(NSString *)key value:(void *)value encoding:(char *)encoding;

@end

@interface AWELoaderStore : NSObject

@property(nonatomic, strong) NSMutableDictionary<NSString *, NSMutableArray<AWEEntryItem *> *> *functionStore;
@property(nonatomic, strong) NSMutableDictionary<NSString *, AWEEntryItem *> *envStore;

- (void)addItem:(AWEEntryItem *)item;

@end

NS_ASSUME_NONNULL_END
