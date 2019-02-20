#ifdef __OBJC__
#import <UIKit/UIKit.h>
#else
#ifndef FOUNDATION_EXPORT
#if defined(__cplusplus)
#define FOUNDATION_EXPORT extern "C"
#else
#define FOUNDATION_EXPORT extern
#endif
#endif
#endif

#import "AWELoaderStore.h"
#import "AWEEntryItemBase.h"
#import "AWELoader.h"
#import "AWELoaderInternal.h"
#import "AWELoadManager.h"
#import "AWEmetamacros.h"

FOUNDATION_EXPORT double AWELoaderVersionNumber;
FOUNDATION_EXPORT const unsigned char AWELoaderVersionString[];

