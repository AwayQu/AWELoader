#import "TestCXX.h"
#import <AWELoader/AWELoader.h>
@implementation TestCXX : NSObject

+ (void)testCXXnil {
    NSLog(@"Test CXX nil");
    AWE_LOADER_EXECUTE(@"TESTARG1", nil);
}

+ (void)testCXXNil {
    NSLog(@"Test CXX Nil");
    AWE_LOADER_EXECUTE(@"TESTARG1", Nil);
}

+ (void)testCXXNULL {
    NSLog(@"Test CXX NULL");
    AWE_LOADER_EXECUTE(@"TESTARG1", NULL);
}

+ (void)testScale {
    NSLog(@"Test CXX Scale");
    AWE_LOADER_EXECUTE(@"TESTARG2", 1, 0L);
    AWE_LOADER_EXECUTE(@"TESTARG2", 1, 0LL);
    AWE_LOADER_EXECUTE(@"TESTARG2", 1, 0U);
    AWE_LOADER_EXECUTE(@"TESTARG2", 1, 0UL);
    AWE_LOADER_EXECUTE(@"TESTARG2", 1, 0ULL);
}

+ (void)testYESNO {
    NSLog(@"Test CXX YES NO");
    AWE_LOADER_EXECUTE(@"TESTARG2", YES, NO);
}

+ (void)testtruefalse {
    NSLog(@"Test CXX true false");
    AWE_LOADER_EXECUTE(@"TESTARG2", true, false);
}

@end
