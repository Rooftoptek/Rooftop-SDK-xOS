# RAPID

## Custom Code

Rapid allows you to run custom JavaScript logic on Rooftop instead of on the client.
You can use this to offload processing to the Rooftop thus increasing your app’s perceived performance. You can create hooks that run whenever an object is saved or deleted. This is useful if you want to validate or sanitise your data. You can also use Rapid to modify related objects or kick off other processes such as sending off a push notification.

```objc

[RTRapid invokeInBackground:@"sendNotification"
                   withParameters:@{}
                            block:^(id object, NSError *error) {
  if (!error) {
     NSLog(@"Notification is here!");
  }
}];

```


