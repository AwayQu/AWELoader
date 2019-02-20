# AWELoader

## usage:

```objective-c

  // executor
  AWE_EXPORT_FUNCTION(@"LogApplication", @"application:didFinishLaunchingWithOptions:", NSArray *args) {
    UIApplication *application = args.firstObject;
    NSLog(application);
  }

  AWE_LOADER_EXECUTE(@"application:didFinishLaunchingWithOptions:", application, launchOptions)

  // env
  AWE_EXPORT_ENV(@"AppID", @"12345678")

  NSString *appID = AWE_GET_ENV(@"AppID");

```