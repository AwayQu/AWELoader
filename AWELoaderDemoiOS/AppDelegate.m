//
//  AppDelegate.m
//  AWELoaderDemoiOS
//
//  Created by AwayQu on 2019/1/11.
//  Copyright © 2019 AwayQu. All rights reserved.
//

#import "AppDelegate.h"
#import <AWELoader/AWELoader.h>
#import "TestCXX.h"
#import "TestBan.h"
@interface AppDelegate ()

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    [self testEnv];
    [self testExecutorMacro];
    [self testExecutorScale];
    [self testnilNilNULL];
    [TestBan testBan];
    return YES;
}

- (void)testEnv {
    NSString *env = AWE_GET_ENV(@"TESTENV");
    NSLog(@"env: %@", env);
}

- (void)testExecutorMacro {
    
    AWE_LOADER_EXECUTE(@"TESTARG0");
    
    AWE_LOADER_EXECUTE(@"TESTARG1", @"11");
    
    AWE_LOADER_EXECUTE(@"TESTARG2", @"11", @"22");
    
    AWE_LOADER_EXECUTE(@"TESTARG3", @"11", @"22", @"33");
    
    AWE_LOADER_EXECUTE(@"TESTARG4", @"11", @"22", @"33", @"44");
    
    AWE_LOADER_EXECUTE(@"TESTARG5", @"11", @"22", @"33", @"44", @"55");
    
    AWE_LOADER_EXECUTE(@"TESTARG6", @"11", @"22", @"33", @"44", @"55", @"66");
    
    AWE_LOADER_EXECUTE(@"TESTARG7", @"11", @"22", @"33", @"44", @"55", @"66", @"77");
    
    AWE_LOADER_EXECUTE(@"TESTARG8", @"11", @"22", @"33", @"44", @"55", @"66", @"77", @"88");
}

- (void)testExecutorScale {
    AWE_LOADER_EXECUTE(@"TESTARG2", 1, 0L);
    AWE_LOADER_EXECUTE(@"TESTARG2", 1, 0LL);
    AWE_LOADER_EXECUTE(@"TESTARG2", 1, 0U);
    AWE_LOADER_EXECUTE(@"TESTARG2", 1, 0UL);
    AWE_LOADER_EXECUTE(@"TESTARG2", 1, 0ULL);
    AWE_LOADER_EXECUTE(@"TESTARG2", YES, NO);
    AWE_LOADER_EXECUTE(@"TESTARG2", true, false);
    
    [TestCXX testScale];
    [TestCXX testYESNO];
    [TestCXX testtruefalse];
}

- (void)testnilNilNULL {
    AWE_LOADER_EXECUTE(@"TESTARG1", nil);
    AWE_LOADER_EXECUTE(@"TESTARG1", Nil);
    AWE_LOADER_EXECUTE(@"TESTARG1", NULL);
    [TestCXX testCXXnil];
    [TestCXX testCXXNil];
    [TestCXX testCXXNULL];
}



- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and invalidate graphics rendering callbacks. Games should use this method to pause the game.
}


- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}


- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the active state; here you can undo many of the changes made on entering the background.
}


- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}


- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}


@end
