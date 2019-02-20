//
// Created by Away on 12/29/18.
// Copyright (c) 2018 AwayQu. All rights reserved.
//

#import "AWELoadManager.h"
#import "AWELoaderStore.h"
#import <mach-o/dyld.h>
#import <mach-o/getsect.h>

#ifdef DEBUG
//#define DEV
#endif

@interface AWELoadManager ()

@property(nonatomic, strong) AWELoaderStore *store;
@property(nonatomic, copy) NSArray<AWEEntryItemBase *> *banItems; // 禁用功能
@end

@implementation AWELoadManager

- (instancetype)init {
    self = [super init];
    if (self) {
        _store = [[AWELoaderStore alloc] init];
    }

    return self;
}

+ (instancetype)sharedInstance {
    static id _sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _sharedInstance = [[self alloc] init];
        [_sharedInstance readConfig];
    });

    return _sharedInstance;
}

- (void)readConfig {
#ifdef DEBUG
CFTimeInterval loadStart = CFAbsoluteTimeGetCurrent();
#endif
#ifdef __LP64__
    typedef uint64_t awe_value;
    typedef struct section_64 awe_section;
    typedef struct mach_header_64 awe_header;
#define awe_getsectbynamefromheader getsectbynamefromheader_64
#else
    typedef uint32_t awe_value;
    typedef struct section awe_section;
    typedef struct mach_header awe_header;
#define awe_getsectbynamefromheader getsectbynamefromheader
#endif


    uint32_t image_count = _dyld_image_count();
    for (uint32_t image_index = 0; image_index < image_count; image_index++) {
        const awe_header *mach_header = (const awe_header *) _dyld_get_image_header(image_index);

        unsigned long size;
        awe_entry *data = (awe_entry *) getsectiondata(mach_header, AWESegmentName, AWESectionName, &size);
        if (data == NULL) {
            continue;
        }
        size_t count = size / sizeof(awe_entry);
        for (size_t i = 0; i < count; i++) {
            awe_entry *entry = &data[i];
            AWEEntryItem *item = [[AWEEntryItem alloc] initWithCategory:*entry->category
                                                             collection:*entry->collection
                                                                   name:*entry->name
                                                                    key:*entry->key
                                                                  value:entry->value encoding:*entry->encoding];

            if (entry->info) {
                item.info = entry->info;
                NSAssert(item.argsCount == 0 || item.argsCount == 1, @"key: %@, item: %@, 不支持的参数数量 %d, 只支持0个 或 1个参数", item.key, item.name, item.argsCount);
            }

            [_store addItem:item];
        }
    }
    
#ifdef DEBUG
    CFTimeInterval loadComplete = CFAbsoluteTimeGetCurrent();
    NSLog(@"AWELoader: loaded cost %@ms",@(1000.0 * ( loadComplete - loadStart )));
#endif
}

- (NSString *)env:(NSString *)key {
    return self.store.envStore[key].envValue;
}

// TODO: 上报异常
#ifdef DEBUG

#define AWE_EXECUTE_TRY_CATCH(code_) code_

#else

#define AWE_EXECUTE_TRY_CATCH(code_) \
@try {\
code_\
}@catch (NSException *exception) {\
} @finally {\
}
#endif

- (void)execute:(NSString *)key args:(NSArray *)args {
#ifdef DEBUG
    CFTimeInterval callStart = CFAbsoluteTimeGetCurrent();
#endif
    __auto_type items = self.store.functionStore[key];
    if (items.count == 0) {
#ifdef DEBUG
        NSLog(@"key: %@ 没有需要执行的任务", key);
#endif
    }
#ifdef DEV
    NSLog(@"key: %@ args: %@", key, args);
#endif
    for (AWEEntryItem *item in items) {
        if ([self isItemBan:item]) {
#ifdef DEBUG
            NSLog(@"key: %@, item: %@ 被禁用", item.key, item.name);
#endif
            continue;
        }
        AWE_EXECUTE_TRY_CATCH({
            [self executeWithItem:item args:args];
        })
    }
#ifdef DEBUG
    CFTimeInterval callComplete = CFAbsoluteTimeGetCurrent();
    NSLog(@"AWELoader: call key: %@ cost %@ms", key, @(1000.0 * ( callComplete - callStart )));
#endif
}
#undef AWE_EXECUTE_TRY_CATCH


- (void)executeWithItem:(AWEEntryItem *)item args:(NSArray *)args {
    
    int registerCount = item.argsCount;

    if (registerCount == -1) {
        NSAssert(NO, @"key: %@, item: %@ 未声明 参数数量", item.key, item.name);
        return;
    }

    switch (registerCount) {
        case 0: {
            __auto_type func = *(void (*(*))(void))item.functionValue;
            func();
            break;
        }
        case 1: {
            __auto_type func = *(void (*(*))(id))item.functionValue;
            func(args);
            break;
        }
        default: {
            NSAssert(NO, @"key: %@, item: %@, 不支持的参数数量 %d, 只支持0个 或 1个参数", item.key, item.name, registerCount);
        }
    }
    
}

- (BOOL)isItemBan:(AWEEntryItemBase *)item {
    __block BOOL isBan = NO;
    [self.banItems enumerateObjectsUsingBlock:^(AWEEntryItemBase * _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
        if (obj.collection && obj.name && obj.key) {
            if (
                [obj.collection isEqual:item.collection]
                && [obj.name isEqual:item.name]
                && [obj.key isEqual:item.key]
                ) {
                isBan = YES;
                *stop = YES;
            }
        } else if (obj.collection && obj.name) {
            if (
                [obj.collection isEqual:item.collection]
                && [obj.name isEqual:item.name]
                ) {
                isBan = YES;
                *stop = YES;
            }
        } else if (obj.name && obj.key) {
            if (
                [obj.name isEqual:item.name]
                && [obj.key isEqual:item.key]
                ) {
                isBan = YES;
                *stop = YES;
            }
        } else if (obj.collection && obj.key) {
            if (
                [obj.collection isEqual:item.collection]
                && [obj.key isEqual:item.key]
                ) {
                isBan = YES;
                *stop = YES;
            }
        } else if (obj.collection) {
            if (
                [obj.collection isEqual:item.collection]
                ) {
                isBan = YES;
                *stop = YES;
            }
        } else if (obj.name) {
            if (
                [obj.name isEqual:item.name]
                ) {
                isBan = YES;
                *stop = YES;
            }
        } else if (obj.key) {
            if (
                [obj.key isEqual:item.key]
                ) {
                isBan = YES;
                *stop = YES;
            }
        }
    }];
    return isBan;
}

- (void)updateBanItems:(NSArray<AWEEntryItemBase *> *)banItems {
    self.banItems = banItems;
}

@end
