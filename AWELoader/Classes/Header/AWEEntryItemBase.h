//
//  AWEEntryItemBase.h
//  AWELoader
//
//  Created by AwayQu on 2019/1/11.
//  Copyright © 2019 AwayQu. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface AWEEntryItemBase : NSObject

@property(nonatomic, copy) NSString *category;
@property(nonatomic, copy) NSString *collection;
@property(nonatomic, copy) NSString *name;
@property(nonatomic, copy) NSString *key;
@property(nonatomic) void *value;
@property (nonatomic) char *encoding;
@property (nonatomic) void *info;

@property(nonatomic, copy, readonly) NSString *identify;

- (instancetype)initWithCategory:(NSString *)category collection:(NSString *)collection name:(NSString *)name key:(NSString *)key;

+ (instancetype)itemWithModule:(nullable NSString *)module usage:(nullable NSString *)usage key:(nullable NSString *)key;

@end
NS_ASSUME_NONNULL_END
