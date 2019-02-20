//
//  AWELoaderInternal.h
//  AWELoader
//
//  Created by Away on 12/29/18.
//  Copyright © 2018 AwayQu. All rights reserved.
//

#ifndef AWELoaderInternal_h
#define AWELoaderInternal_h

#import "AWEmetamacros.h"


#ifdef __cplusplus
extern "C" {
#endif
    
#define AWE_CATEGORY_PREFIX_DEFAULT @"AWE_CATEGORY" // category
#define AWE_COLLECTION_PREFIX_DEFAULT @"AWE_COLLECTION" // collection
#define AWE_NAME_PREFIX_DEFAULT @"AWE_NAME" // name
    
#define __AWEConcat2_(X, Y) X ## Y
#define __AWEConcat3_(X, Y, Z) X ## Y # Z

#define __AWEConcat(X, ...)\
    metamacro_if_eq(1, metamacro_argcount(__VA_ARGS__))\
    (__AWEConcat2_(X, __VA_ARGS__))\
    (__AWEConcat3_(X, __VA_ARGS__))



#define AWESegmentName "__DATA"
#define AWESectionName "AWELoader"
#define AWEEncodingFUNC "__FUNC__"
#define AWEEncodingENV "__ENV__"


#define AWE_FUNC_CATEGORY_PREFIX           __awe_func_category_
#define AWE_FUNC_COLLECTION_PREFIX         __awe_func_collection_
#define AWE_FUNC_NAME_PREFIX               __awe_func_name_
#define AWE_FUNC_KEY_PREFIX                __awe_func_key_
#define AWE_FUNC_PTR_PREFIX                __awe_func_ptr_
#define AWE_FUNC_DECLARE_NAME_PREFIX       __awe_func_declare_name_
#define AWE_FUNC_ENCODING_PREFIX           __awe_func_encoding_
#define AWE_FUNC_ENTRY_PREFIX              __awe_func_entry_
#define AWE_FUNC_INFO_ENTRY_PREFIX         __awe_func_info_entry_

#define AWE_ENV_CATEGORY_PREFIX            __awe_env_category_
#define AWE_ENV_COLLECTION_PREFIX          __awe_env_collection_
#define AWE_ENV_NAME_PREFIX                __awe_env_name_
#define AWE_ENV_KEY_PREFIX                 __awe_env_key_
#define AWE_ENV_VALUE_PREFIX               __awe_env_value_
#define AWE_ENV_ENCODING_PREFIX            __awe_env_encoding_
#define AWE_ENV_ENTRY_PREFIX               __awe_env_entry_

#define _AWE_VOID_FUNC(...) _AWE_VOID_FUNC_COUNT_DISPATCH(__VA_ARGS__)

#define _AWE_VOID_FUNC_COUNT_DISPATCH(counter, CMD, ...) \
 metamacro_if_eq(1, metamacro_argcount(__VA_ARGS__))\
   (CMD(0, counter, __VA_ARGS__))\
   (metamacro_if_eq(2, metamacro_argcount(__VA_ARGS__))\
     (CMD(1, counter, __VA_ARGS__))\
     (CMD(1, counter, __VA_ARGS__))\
   )



#define _AWE_FUNC_COUNT_DECLARE(args_count, counter_, ...) \
  __attribute__((used)) static int __AWEConcat(AWE_FUNC_INFO_ENTRY_PREFIX, counter_) = args_count;\
  metamacro_if_eq(0, args_count) \
   (_AWE_FUNC_COUNT_0(counter_, __VA_ARGS__)) \
   (_AWE_FUNC_COUNT(args_count, counter_, __VA_ARGS__))

#define _AWE_FUNC_COUNT_IMP(args_count, counter_, ...) \
  metamacro_if_eq(0, args_count) \
   (_AWE_FUNC_COUNT_0(counter_, __VA_ARGS__)) \
   (_AWE_FUNC_COUNT(args_count, counter_, __VA_ARGS__))

#define _AWE_FUNC_COUNT_0(counter_, ...) \
_AWE_DECLARE_VOID_FUNC(__AWEConcat(AWE_FUNC_DECLARE_NAME_PREFIX, counter_), void)

#define _AWE_FUNC_COUNT(args_count, counter, key, ...)\
_AWE_VOID_FUNC_COUNT_INTERNAL(counter, args_count, __VA_ARGS__)

#define _AWE_VOID_FUNC_COUNT_INTERNAL(counter, arg_count, ...) \
_AWE_DECLARE_VOID_FUNC(__AWEConcat(AWE_FUNC_DECLARE_NAME_PREFIX, counter), __VA_ARGS__)

#define _AWE_DECLARE_VOID_FUNC(name, ...) static void name(__VA_ARGS__)



// TODO: 优先级

typedef __unsafe_unretained NSString *AWELiteralString;

typedef struct {
    AWELiteralString *category;
    AWELiteralString *collection;
    AWELiteralString *name;
    AWELiteralString *key;
    void *value;
    char **encoding;
    void *info;
} awe_entry;

__attribute__((used)) static id _awe_wrap_arg(void *value, char *encoding) {
/**
 * C++编译 和 OC环境下 nil 和 Nil 都正常
 * C++编译环境下传入NULL, 处理会异常, 宏会展开为 __null, encode 为 encode(long) "q"
 */
    __auto_type nilType = nil;
//  https://nshipster.com/type-encodings/
    if (strcmp(encoding, @encode(BOOL)) == 0) {
        return @(*(BOOL *) value);
    } else if (strcmp(encoding, @encode(float)) == 0) {
        return @(*(float *) value);
    } else if (strcmp(encoding, @encode(double)) == 0) {
        return @(*(double *) value);
    } else if (strcmp(encoding, @encode(short)) == 0) {
        return @(*(short *) value);
    } else if (strcmp(encoding, @encode(unsigned short)) == 0) {
        return @(*(unsigned short *) value);
    } else if (strcmp(encoding, @encode(int)) == 0) {
        return @(*(int *)value);
    } else if (strcmp(encoding, @encode(unsigned int)) == 0) {
        return @(*(unsigned int *)value);
    } else if (strcmp(encoding, @encode(long)) == 0) {
        return @(*(long *)value);
    } else if (strcmp(encoding, @encode(unsigned long)) == 0) {
        return @(*(unsigned long *)value);
    } else if (strcmp(encoding, @encode(long long)) == 0) {
        return @(*(long long *)value);
    } else if (strcmp(encoding, @encode(unsigned long long)) == 0) {
        return @(*(unsigned long long *)value);
    } else if (strcmp(encoding, @encode(NSInteger)) == 0) {
        return @(*(NSInteger *)value);
    } else if (strcmp(encoding, @encode(NSUInteger)) == 0) {
        return @(*(NSUInteger *)value);
    } else if (strcmp(encoding, @encode(id)) == 0) {
#if __has_feature(objc_arc)
        return *(id __weak *)value;
#else
        return *(id __unsafe_unretained  *)value;
#endif
    } else if (strcmp(encoding, @encode(__typeof__(nilType))) == 0) {
        return nil;
    } else {
        NSCAssert(NO, @"Unknown encoding %s . Value was %p.", encoding, value);
        return nil;
    }
}

#define _AWE_EXPORT_ENV(category_, collection_, name_, key_, value_) \
_AWE_EXPORT_ENV_INTERNAL(category_, collection_, name_, __COUNTER__, key_, value_)
#define _AWE_EXPORT_ENV_INTERNAL(category_, collection_, name_, suffix_, key_, value_) \
/* store the loader entry data in the binary at compile time. */ \
__attribute__((used)) static AWELiteralString __AWEConcat(AWE_ENV_CATEGORY_PREFIX, suffix_) = category_; \
__attribute__((used)) static AWELiteralString __AWEConcat(AWE_ENV_COLLECTION_PREFIX, suffix_) = collection_; \
__attribute__((used)) static AWELiteralString __AWEConcat(AWE_ENV_NAME_PREFIX, suffix_) = name_; \
__attribute__((used)) static AWELiteralString __AWEConcat(AWE_ENV_KEY_PREFIX, suffix_) = key_; \
__attribute__((used)) static void * __AWEConcat(AWE_ENV_VALUE_PREFIX, suffix_) = value_; \
__attribute__((used)) static char *__AWEConcat(AWE_ENV_ENCODING_PREFIX, suffix_) = (char *)AWEEncodingENV; \
__attribute__((used)) __attribute__((section (AWESegmentName "," AWESectionName))) static awe_entry __AWEConcat(AWE_ENV_ENTRY_PREFIX, suffix_) = { \
&__AWEConcat(AWE_ENV_CATEGORY_PREFIX, suffix_), \
&__AWEConcat(AWE_ENV_COLLECTION_PREFIX, suffix_), \
&__AWEConcat(AWE_ENV_NAME_PREFIX, suffix_), \
&__AWEConcat(AWE_ENV_KEY_PREFIX, suffix_), \
&__AWEConcat(AWE_ENV_VALUE_PREFIX, suffix_), \
&__AWEConcat(AWE_ENV_ENCODING_PREFIX, suffix_), \
NULL,\
}; \

#define _AWE_EXPORT_FUNCTION_ATTRIBUTE_INTERNAL(category_, collection_, name_, suffix_, function_, key_, ...) \
/* store the loader entry data in the binary at compile time. */ \
__attribute__((used)) static AWELiteralString __AWEConcat(AWE_FUNC_CATEGORY_PREFIX, suffix_) = category_; \
__attribute__((used)) static AWELiteralString __AWEConcat(AWE_FUNC_COLLECTION_PREFIX, suffix_) = collection_; \
__attribute__((used)) static AWELiteralString __AWEConcat(AWE_FUNC_NAME_PREFIX, suffix_) = name_; \
__attribute__((used)) static AWELiteralString __AWEConcat(AWE_FUNC_KEY_PREFIX, suffix_) = key_; \
__attribute__((used)) static void * __AWEConcat(AWE_FUNC_PTR_PREFIX, suffix_) = function_; \
__attribute__((used)) static char *__AWEConcat(AWE_FUNC_ENCODING_PREFIX, suffix_) = (char *)AWEEncodingFUNC;


#define _AWE_EXPORT_FUNCTION_ENTRY_INTERNAL_2(suffix_) \
__attribute__((used)) __attribute__((section (AWESegmentName "," AWESectionName))) static awe_entry __AWEConcat(AWE_FUNC_ENTRY_PREFIX, suffix_) = { \
&__AWEConcat(AWE_FUNC_CATEGORY_PREFIX, suffix_), \
&__AWEConcat(AWE_FUNC_COLLECTION_PREFIX, suffix_), \
&__AWEConcat(AWE_FUNC_NAME_PREFIX, suffix_), \
&__AWEConcat(AWE_FUNC_KEY_PREFIX, suffix_), \
&__AWEConcat(AWE_FUNC_PTR_PREFIX, suffix_), \
&__AWEConcat(AWE_FUNC_ENCODING_PREFIX, suffix_), \
&__AWEConcat(AWE_FUNC_INFO_ENTRY_PREFIX, suffix_),\
}; \


#define _AWE_EXPORT_FUNCTION_INTERNAL(category_, collection_, name_, counter_, function_, key_, ...) \
_AWE_EXPORT_FUNCTION_ATTRIBUTE_INTERNAL(category_, collection_, name_, counter_, function_, key_)\
_AWE_EXPORT_FUNCTION_ENTRY_INTERNAL_2(counter_)

#define _AWE_EXPORT_FUNCTION_CONVENIENCE(category_, collection_, name_, ...) \
    _AWE_EXPORT_FUNCTION_CONVENIENCE_INTERNAL(category_, collection_, name_, __COUNTER__, __VA_ARGS__)

#define _AWE_EXPORT_FUNCTION_CONVENIENCE_INTERNAL(category_, collection_, name_, counter_, ...) \
_AWE_VOID_FUNC(counter_, _AWE_FUNC_COUNT_DECLARE, __VA_ARGS__); \
_AWE_EXPORT_FUNCTION_INTERNAL(category_, collection_, name_, counter_, __AWEConcat(AWE_FUNC_DECLARE_NAME_PREFIX, counter_), __VA_ARGS__) \
_AWE_VOID_FUNC(counter_, _AWE_FUNC_COUNT_IMP, __VA_ARGS__)

#define _AWE_WRAP_VALUE(index, arg, ...)\
metamacro_if_eq(0, index)\
(__auto_type awe_call_key = arg;)\
({\
 __auto_type __AWEConcat(awe_arg, index) = arg;\
 __auto_type __AWEConcat(awe_arg_type, index) = (char *)@encode(__typeof__(__AWEConcat(awe_arg, index)));\
 id __AWEConcat(awe_wraped_arg, index) = _awe_wrap_arg(&__AWEConcat(awe_arg, index), __AWEConcat(awe_arg_type, index));\
 [awe_args_array addObject:__AWEConcat(awe_wraped_arg, index) ?: [NSNull null]];\
})

// key, args
#define _AWE_LOADER_EXECUTE(...) {\
 __auto_type awe_args_array = [NSMutableArray new];\
 metamacro_foreach(_AWE_WRAP_VALUE, ,__VA_ARGS__)\
 [[AWELoadManager sharedInstance] execute:awe_call_key args:awe_args_array];\
}
    
#define _AWE_GET_ENV(key) [[AWELoadManager sharedInstance] env:key]
    
#ifdef __cplusplus
}
#endif

#endif /* AWELoaderInternal_h */



