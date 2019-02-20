//
// Created by Away on 12/29/18.
// Copyright (c) 2018 AwayQu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AWELoaderInternal.h"
#import "AWEEntryItemBase.h"


/**
 * AWE_EXPORT_FUNCTION(usage, key, args)
 *
 * 例:
 *
 * AWE_EXPORT_FUNCTION(@"LogApplication", @"application:didFinishLaunchingWithOptions:", NSArray *args) {
 *   UIApplication *application = args.firstObject;
 *   NSLog(application);
 * }
 *
 */

#define AWE_EXPORT_FUNCTION(USAGE, ...) _AWE_EXPORT_FUNCTION_CONVENIENCE(AWE_CATEGORY_PREFIX_DEFAULT, AWE_COLLECTION_PREFIX_DEFAULT, USAGE, __VA_ARGS__)

/**
 * AWE_LOADER_EXECUTE(key, arg1, arg2, ...)
 *
 * 例:
 * AWE_LOADER_EXECUTE(@"application:didFinishLaunchingWithOptions:", application, launchOptions)
 */
#define AWE_LOADER_EXECUTE(...) _AWE_LOADER_EXECUTE(__VA_ARGS__)

/**
 * 例:
 * AWE_EXPORT_ENV(@"AppID", @"12345678")
 */
#define AWE_EXPORT_ENV(key, value) _AWE_EXPORT_ENV(AWE_CATEGORY_PREFIX_DEFAULT, AWE_COLLECTION_PREFIX_DEFAULT, AWE_NAME_PREFIX_DEFAULT, key, value)

/**
 * 例:
 * NSString *appID = AWE_GET_ENV(@"AppID");
 */
#define AWE_GET_ENV(key) _AWE_GET_ENV(key)



NS_ASSUME_NONNULL_BEGIN

@interface AWELoadManager : NSObject

+ (instancetype)sharedInstance;

- (NSString *)env:(NSString *)key;

- (void)execute:(NSString *)key args:(NSArray *)args;

- (void)updateBanItems:(NSArray<AWEEntryItemBase *> *)banItems;

@end

NS_ASSUME_NONNULL_END
