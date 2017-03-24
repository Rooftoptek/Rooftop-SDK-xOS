# Push Notifications

Push Notifications are a great way to keep your users engaged and informed about your app. You can reach your entire user base quickly and effectively. This guide will help you through the setup process and the general usage of Rooftop to send push notifications.

If you haven't installed the SDK yet, please [head over to the Push QuickStart](https://github.com/Rooftoptek/Rooftop-SDK-xOS) to get our SDK up and running.

## Installations

Every Rooftop application installed on a device registered for push notifications has an associated RTInstallation object. The RTInstallation object is where you store all the data needed to target push notifications. For example, in a baseball app, you could store the teams a user is interested in to send updates about their performance. Saving the RTInstallation object is also required for tracking push-related app open events.

In iOS or OS X, `Installation` objects are available through the `RTInstallation` class, a subclass of `RTObject`. It uses the [same API](#objects) for storing and retrieving data. To access the current `Installation` object from your app, use the `[RTInstallation currentInstallation]` method. The first time you save a `RTInstallation`, Rooftop will add it to your `Installation` class, and it will be available for targeting push notifications as long as its `deviceToken` field is set.

First, make your app register for remote notifications by adding the following in your `application:didFinishLaunchingWithOptions:` method (if you haven't already):

<pre><code class="objectivec">
UIUserNotificationType userNotificationTypes = (UIUserNotificationTypeAlert | UIUserNotificationTypeBadge | UIUserNotificationTypeSound);
UIUserNotificationSettings *settings = [UIUserNotificationSettings settingsForTypes:userNotificationTypes  categories:nil];
[application registerUserNotificationSettings:settings];
[application registerForRemoteNotifications];
</code></pre>

We will then update our `RTInstallation` with the `deviceToken` once the device is registered for push notifications:

<pre><code class="objectivec">
- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken {
  // Store the deviceToken in the current Installation and save it to Rooftop
  RTInstallation *currentInstallation = [RTInstallation currentInstallation];
  [currentInstallation setDeviceTokenFromData:deviceToken];
  [currentInstallation saveInBackground];
  currentInstallation[@"app"] = @"YOUR_APP_NAME";
  currentInstallation[@"test_type"] = @"1";
}
</code></pre>
<pre><code class="swift">
func application(application: UIApplication, didRegisterForRemoteNotificationsWithDeviceToken deviceToken: NSData) {
  // Store the deviceToken in the current Installation and save it to Rooftop
  let installation = RTInstallation.currentInstallation()
  installation.setDeviceTokenFromData(deviceToken)
  installation.saveInBackground()
}
</code></pre>

While it is possible to modify a `RTInstallation` just like you would a `RTObject`, there are several special fields that help manage and target devices.

*   **`channels`**: An array of the channels to which a device is currently subscribed.
*   **`badge`**: The current value of the icon badge for iOS/OS X apps. Changing this value on the `RTInstallation` will update the badge value on the app icon. Changes should be saved to the server so that they will be used for future badge-increment push notifications.
*   **`installationId`**: Unique Id for the device used by Rooftop _(readonly)_.
*   **`deviceType`**: The type of device, "ios", "osx", "android", "winrt", "winphone", "dotnet", or "embedded". On iOS and OS X devices, this field will be set to "ios" and "osx", respectively _(readonly)_.
*   **`deviceToken`**: The Apple generated token used for iOS/OS X devices. On Android devices, this is the token used by GCM to keep track of registration ID _(readonly)_.
*   **`appName`**: The display name of the client application to which this installation belongs. In iOS/OS X, this value is obtained from `kCFBundleNameKey`. This value is synchronized every time a `RTInstallation` object is saved from the device _(readonly)_.
*   **`appVersion`**: The version string of the client application to which this installation belongs. In iOS/OS X, this value is obtained from `kCFBundleVersionKey`. This value is synchronized every time a `RTInstallation` object is saved from the device _(readonly)_.
*   **`appIdentifier`**: A unique identifier for this installation's client application. In iOS/OS X, this value is obtained from `kCFBundleIdentifierKey`. This value is synchronized every time a `RTInstallation` object is saved from the device _(readonly)_.
*   **`RooftopVersion`**: The version of the Rooftop SDK which this installation uses. This value is synchronized every time a `RTInstallation` object is saved from the device _(readonly)_.
*   **`timeZone`**: The current time zone where the target device is located. This value is synchronized every time a `RTInstallation` object is saved from the device _(readonly)_.
*   **`localeIdentifier`**: The locale identifier of the device in the format [language code]-[COUNTRY CODE]. The language codes are two-letter lowercase ISO language codes (such as "en") as defined by [ISO 639-1](http://en.wikipedia.org/wiki/ISO_639-1). The country codes are two-letter uppercase ISO country codes (such as "US") as defined by [ISO 3166-1]("http://en.wikipedia.org/wiki/ISO_3166-1_alpha-3"). This value is synchronized every time a `RTInstallation` object is saved from the device _(readonly)_.
*   **`pushType`**: This field is reserved for directing Rooftop to the push delivery network to be used for Android devices. This parameter is not supported in iOS/OS X devices _(readonly)_.
*   **`GCMSenderId`**: This field only has meaning for Android `RTInstallation`s that use the GCM push type. This parameter is not supported in iOS/OS X devices.
*   **`channelUris`**: The Microsoft-generated push URIs for Windows devices _(readonly)_.

The Rooftop SDK will avoid making unnecessary requests. If a `RTInstallation` is saved on the device, a request to the Rooftop servers will only be made if one of the `RTInstallation`'s fields has been explicitly updated.

