//
// Created by Away on 12/29/18.
// Copyright (c) 2018 AwayQu. All rights reserved.
//

#import "AWELoaderStore.h"
#import "AWELoaderInternal.h"
#import <string.h>

@interface AWEEntryItem () {
    AWEEntryType _type;
}
@end

@implementation AWEEntryItem
@dynamic envValue, functionValue, argsCount;

- (AWEEntryType)type {
    if (_type == 0) {
        if (strcmp(self.encoding, AWEEncodingFUNC) == 0) {
            _type = AWEEntryTypeFUNC;
        } else if (strcmp(self.encoding, AWEEncodingENV) == 0) {
            _type = AWEEntryTypeENV;
        }

    }
    return _type;
}

- (instancetype)initWithCategory:(NSString *)category collection:(NSString *)collection name:(NSString *)name key:(NSString *)key value:(void *)value encoding:(char *)encoding {
    self = [super init];
    if (self) {
        self.category = category;
        self.collection = collection;
        self.name = name;
        self.key = key;
        self.value = value;
        self.encoding = encoding;
    }

    return self;
}


- (NSString *)envValue {
    if (self.type == AWEEntryTypeENV) {
        return *(AWELiteralString *) self.value;
    }
    return nil;
}

- (void *)functionValue {
    if (self.type == AWEEntryTypeFUNC) {
        return self.value;
    }
    return NULL;
}

- (int)argsCount {
    if (self.info && self.type == AWEEntryTypeFUNC) {
        return *(int *)self.info;
    }
    return -1;
}


@end

@interface AWELoaderStore ()


@end

@implementation AWELoaderStore

- (instancetype)init {
    self = [super init];
    if (self) {
        _functionStore = [NSMutableDictionary new];
    }
    return self;
}

- (NSMutableDictionary<NSString *, AWEEntryItem *> *)envStore {
    if (!_envStore) {
        _envStore = [NSMutableDictionary new];
    }
    return _envStore;
}


- (void)addItem:(AWEEntryItem *)item {
    if (item.type == AWEEntryTypeFUNC) {
        NSMutableArray *items = self.functionStore[item.key]
                ?: ({
                    __auto_type is = [NSMutableArray new];
                    self.functionStore[item.key] = is;
                    is;
                });
        [items addObject:item];
    } else if (item.type == AWEEntryTypeENV) {
        self.envStore[item.key] = item;
    } else {
        NSAssert(NO, @"key: %@, item: %@, 不合法entry类型 entry type: %d", item.key, item.name, (int)item.type);
    }
}



@end
