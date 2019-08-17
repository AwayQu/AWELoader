//
//  AWELoader.h
//  AWELoader
//
//  Created by AwayQu on 2019/1/11.
//  Copyright © 2019 AwayQu. All rights reserved.
//

#if TARGET_OS_IPHONE
    #import <UIKit/UIKit.h>
#elif TARGET_OS_MAC
    #import <AppKit/AppKit.h>
#else
    #import <UIKit/UIKit.h>
#endif

//! Project version number for AWELoader.
FOUNDATION_EXPORT double AWELoaderVersionNumber;

//! Project version string for AWELoader.
FOUNDATION_EXPORT const unsigned char AWELoaderVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <AWELoader/PublicHeader.h>


#import <AWELoader/AWELoadManager.h>
#import <AWELoader/AWEmetamacros.h>
#import <AWELoader/AWEEntryItemBase.h>
