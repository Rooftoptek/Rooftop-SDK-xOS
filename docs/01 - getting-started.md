# Installation

Add pod `'Rooftop'` to your podfile and run pod install.

# Connect your app to Rooftop Server

Open up the `AppDelegate.m` file and add follow lines to `application:didFinishLaunchingWithOptions:` to be like so:

<pre><code class="objectivec">
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    
	RooftopConfiguration *configuration = [RooftopConfiguration configurationWithBlock:^(id<RooftopMutableClientConfiguration> _Nonnull configuration) {
        [configuration setApplicationId:@"YOUR_APP_ID"];
        [configuration setCognitoRegion:YOUR_APP_REGION];
        [configuration setCognitoPoolId:@"YOUR_POOL_ID"];
        [configuration setClientKey:@"YOUR_CLIENT_KEY"];
   }];
    
   [Rooftop initializeWithConfiguration:configuration];
   return YES;
}
</code></pre>

# Test the SDK

First make sure to include our SDK libraries from your `ViewController.h` file:

<pre><code class="objectivec">
#import Rooftop/Rooftop.h
</code></pre>

Then copy and paste this code into your app, for example in the `viewDidLoad` method of `ViewController.m`:

<pre><code class="objectivec">
RTObject *testObject = [PFObject objectWithClassName:@"TestObject"];
testObject[@"foo"] = @"bar";
[testObject saveInBackground];
</code></pre>
 	Run your app. A new object of class TestObject will be sent to the Parse Server and saved

