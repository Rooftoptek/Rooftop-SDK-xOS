## Getting Started

The prefered way to install the library is to use Cocoapods

- **[CocoaPods](https://cocoapods.org)**

Open your project folder in `Terminal` and run `pod init` command. After that you will have a new `Podfile` file in your project folder.

Add the following line to your Podfile:

```
pod 'Rooftop', :git => 'https://github.com/Rooftoptek/Rooftop-SDK-xOS.git', :tag => '0.5.0'
```
Run `pod install`, and you should now have the latest Rooftop release.


# Connect your app to Rooftop Server

### Objective - C

Open up the `AppDelegate.m` file and add follow line above `@interface AppDelegate ()`
<pre><code class="objectivec">#import \<Rooftop/Rooftop.h></code></pre> and follow lines to `application:didFinishLaunchingWithOptions:` to be like so:

<pre><code class="objectivec">- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    
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

### Swift
Open up the `AppDelegate.swift` file and add follow line above `class AppDelegate`
<pre><code class="swift">import Rooftop</code></pre> and follow lines to `application:didFinishLaunchingWithOptions:` to be like so:

<pre><code class="swift">func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {
	let configuration = RooftopConfiguration(block: {(_ configuration: RooftopMutableClientConfiguration) -> Void in
		configuration.applicationId = "YOUR_APP_ID"
		configuration.cognitoRegion = .YOUR_APP_REGION
		configuration.cognitoPoolId = "YOUR_POOL_ID"
		configuration.clientKey = "YOUR_CLIENT_KEY"
	})
	Rooftop.initialize(with: configuration)
	return true
}
</code></pre>

# Test the SDK

### Objective - C

First make sure to include our SDK libraries from your `ViewController.h` file:

<pre><code class="objectivec">#import <\Rooftop/Rooftop.h></code></pre>

Then copy and paste this code into your app, for example in the `viewDidLoad` method of `ViewController.m`:

<pre><code class="objectivec">RTObject *testObject = [RTObject objectWithClassName:@"TestObject"];
testObject[@"foo"] = @"bar";
[testObject saveInBackground];
</code></pre>

Run your app. A new object of class `TestObject` will be sent to the Rooftop Server and saved
	
### Swift

First make sure to include our SDK libraries from your `ViewController.swift` file:

<pre><code class="swift">import Rooftop</code></pre>

Then copy and paste this code into your app, for example in the `viewDidLoad()` method of `ViewController.swift`:

<pre><code class="swift">let testObject = RTObject(className: "TestObject")
testObject["foo"] = "bar"
testObject.saveInBackground()
</code></pre>
 	Run your app. A new object of class `TestObject` will be sent to the Rooftop Server and saved


