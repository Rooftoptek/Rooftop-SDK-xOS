# Users

At the core of many apps, there is a notion of user accounts that lets users access their information in a secure manner. We provide a specialized user class called `RTUser` that automatically handles much of the functionality required for user account management.

With this class, you'll be able to add user account functionality in your app.

`RTUser` is a subclass of `RTObject` and has all the same features, such as flexible schema, automatic persistence, and a key value interface. All the methods that are on `RTObject` also exist in `RTUser`. The difference is that RTUser has some special additions specific to user accounts.

## Properties

`RTUser` has several properties that set it apart from `RTObject`:

*   **username**: The username for the user (required).
*   **password**: The password for the user (required on signup).
*   **email**: The email address for the user (optional).

We'll go through each of these in detail as we run through the various use cases for users. Keep in mind that if you set `username` and `email` through these properties, you do not need to set it using the `setObject:forKey:` method &mdash; this is set for you automatically.


## Signing Up

The first thing your app will do is probably ask the user to sign up. The following code illustrates a typical sign up:

### Objective - C
<pre><code class="objectivec">- (void)myMethod {
    RTUser *user = [RTUser user];
    user.username = @"my name";
    user.password = @"my pass";
    user.email = @"email@example.com";

    // other fields can be set just like with RTObject
    user[@"phone"] = @"415-392-0202";

    [user signUpInBackgroundWithBlock:^(BOOL succeeded, NSError *error) {
      if (!error) {   // Hooray! Let them use the app now.
      } else {   NSString *errorString = [error userInfo][@"error"];   // Show the errorString somewhere and let the user try again.
      }
    }];
}
</code></pre>

### Swift
<pre><code class="swift">func myMethod() {
	var user = RTUser()
	user.username = "myUsername"
	user.password = "myPassword"
	user.email = "email@example.com"
	// other fields can be set just like with RTObject
	user["phone"] = "415-392-0202"
	
	user.signUpInBackground { (success, error) in
		if let error = error {
		let errorString = error.userInfo["error"] as? NSString
		// Show the errorString somewhere and let the user try again.
		} else {
		// Hooray! Let them use the app now.
		}
	}
}
</code></pre>

This call will asynchronously create a new user in your Rooftop App. Before it does this, it also checks to make sure that both the username and email are unique. Also, it securely hashes the password in the cloud using bcrypt. We never store passwords in plaintext, nor will we ever transmit passwords back to the client in plaintext.

Note that we used the `signUp` method, not the `save` method. New `RTUser`s should always be created using the `signUp` method. Subsequent updates to a user can be done by calling `save`.

The `signUp` method comes in various flavors, with the ability to pass back errors, and also synchronous versions. As usual, we highly recommend using the asynchronous versions when possible, so as not to block the UI in your app. You can read more about these specific methods in our [API docs](/docs/ios/).

If a signup isn't successful, you should read the error object that is returned. The most likely case is that the username or email has already been taken by another user. You should clearly communicate this to your users, and ask them try a different username.

You are free to use an email address as the username. Simply ask your users to enter their email, but fill it in the username property &mdash; `RTUser` will work as normal. We'll go over how this is handled in the reset password section.

## Logging In

Of course, after you allow users to sign up, you need to let them log in to their account in the future. To do this, you can use the class method `logInWithUsernameInBackground:password:`.

### Objective - C
<pre><code class="objectivec">[RTUser logInWithUsernameInBackground:@"myname" password:@"mypass"
  block:^(RTUser *user, NSError *error) {
    if (user) {
      // Do stuff after successful login.
    } else {
      // The login failed. Check error to see why.
    }
}];
</code></pre>

### Swift
<pre><code class="swift">RTUser.logInWithUsernameInBackground("myname", password:"mypass") { (user, error) in
	if user != nil {
		// Do stuff after successful login.
	} else {
		// The login failed. Check error to see why.
	}
}
</code></pre>

## Verifying Emails

Enabling email verification in an application's settings allows the application to reserve part of its experience for users with confirmed email addresses. Email verification adds the `emailVerified` key to the `RTUser` object. When a `RTUser`'s `email` is set or modified, `emailVerified` is set to `false`. Rooftop then emails the user a link which will set `emailVerified` to `true`.

There are three `emailVerified` states to consider:

1.  `true` - the user confirmed his or her email address by clicking on the link Rooftop emailed them. `RTUsers` can never have a `true` value when the user account is first created.
2.  `false` - at the time the `RTUser` object was last refreshed, the user had not confirmed his or her email address. If `emailVerified` is `false`, consider calling `refresh:` on the `RTUser`.
3.  **missing** - the `RTUser` was created when email verification was off or the `RTUser` does not have an `email`.


## Current User

It would be bothersome if the user had to log in every time they open your app. You can avoid this by using the cached `currentUser` object.

Whenever you use any signup or login methods, the user is cached on disk. You can treat this cache as a session, and automatically assume the user is logged in:

### Objective - C
<pre><code class="objectivec">RTUser *currentUser = [RTUser currentUser];
if (currentUser) {
    // do stuff with the user
} else {
    // show the signup or login screen
}
</code></pre>

### Swift
<pre><code class="swift">var currentUser = RTUser.currentUser()
if currentUser != nil {
  // Do stuff with the user
} else {
  // Show the signup or login screen
}
</code></pre>

You can clear the current user by logging them out:

### Objective - C
<pre><code class="objectivec">[RTUser logOut];
RTUser *currentUser = [RTUser currentUser]; // this will now be nil
</code></pre>

### Swift
<pre><code class="swift">RTUser.logOut()
var currentUser = RTUser.currentUser() // this will now be nil
</code></pre>

## Anonymous Users

Being able to associate data and objects with individual users is highly valuable, but sometimes you want to be able to do this without forcing a user to specify a username and password.

An anonymous user is a user that can be created without a username and password but still has all of the same capabilities as any other `RTUser`. After logging out, an anonymous user is abandoned, and its data is no longer accessible.

You can create an anonymous user using `RTAnonymousUtils`:

### Objective - C
<pre><code class="objectivec">[RTAnonymousUtils logInWithBlock:^(RTUser *user, NSError *error) {
    if (error) {
      NSLog(@"Anonymous login failed.");
    } else {
      NSLog(@"Anonymous user logged in.");
    }
}];
</code></pre>

### Swift
<pre><code class="swift">RTAnonymousUtils.logInWithBlock {
  (user: RTUser?, error: NSError?) -> Void in
  if error != nil || user == nil {
    print("Anonymous login failed.")
  } else {
    print("Anonymous user logged in.")
  }
}
</code></pre>

You can convert an anonymous user into a regular user by setting the username and password, then calling `signUp`, or by logging in or linking with a service like [Facebook](#fbusers) or [Twitter](#twitterusers). The converted user will retain all of its data.  To determine whether the current user is an anonymous user, you can check `RTAnonymousUtils isLinkedWithUser`:

### Objective - C
<pre><code class="objectivec">if ([RTAnonymousUtils isLinkedWithUser:[RTUser currentUser]]) {
    [self enableSignUpButton];
} else {
    [self enableLogOutButton];
}
</code></pre>

### Swift
<pre><code class="swift">if RTAnonymousUtils.isLinkedWithUser(RTUser.currentUser()) {
  self.enableSignUpButton()
} else {
  self.enableLogOutButton()
}
</code></pre>

Anonymous users can also be automatically created for you without requiring a network request, so that you can begin working with your user immediately when your application starts.  When you enable automatic anonymous user creation at application startup, `[RTUser currentUser]` will never be `nil`. The user will automatically be created in the cloud the first time the user or any object with a relation to the user is saved.  Until that point, the user's object ID will be `nil`.  Enabling automatic user creation makes associating data with your users painless.  For example, in your `application:didFinishLaunchingWithOptions:` function, you might write:

### Objective - C
<pre><code class="objectivec">
[RTUser enableAutomaticUser];
[[RTUser currentUser] incrementKey:@"RunCount"];
[[RTUser currentUser] saveInBackground];
</code></pre>

### Swift
<pre><code class="swift">
RTUser.enableAutomaticUser()
RTUser.currentUser().incrementKey("RunCount")
RTUser.currentUser().saveInBackground()
</code></pre>

## Setting the Current User

If you’ve created your own authentication routines, or otherwise logged in a user on the server side, you can now pass the session token to the client and use the `become` method. This method will ensure the session token is valid before setting the current user.

### Objective - C
<pre><code class="objectivec">
[RTUser becomeInBackground:@"session-token-here" block:^(RTUser *user, NSError *error) {
  if (error) {
    // The token could not be validated.
  } else {
    // The current user is now set to user.
  }
}];
</code></pre>

### Swift
<pre><code class="swift">RTUser.becomeInBackground("session-token-here", {
  (user, error) in
  if error != nil {
    // The token could not be validated.
  } else {
    // The current user is now set to user.
  }
})
</code></pre>

## Security For User Objects

The `RTUser` class is secured by default. Data stored in a `RTUser` can only be modified by that user. By default, the data can still be read by any client. Thus, some `RTUser` objects are authenticated and can be modified, whereas others are read-only.

Specifically, you are not able to invoke any of the `save` or `delete` methods unless the `RTUser` was obtained using an authenticated method, like `logIn` or `signUp`. This ensures that only the user can alter their own data.

The following illustrates this security policy:

### Objective - C
<pre><code class="objectivec">RTUser *user = [RTUser logInWithUsername:@"my_username" password:@"my_password"];
user.username = "my_new_username"; // attempt to change username
[user save]; // This succeeds, since the user was authenticated on the device

// Get the user from a non-authenticated method
RTQuery *query = [RTUser query];
RTUser *userAgain = (RTUser *)[query getObjectWithId:user.objectId];

userAgain.username = "another_username";

// This will throw an exception, since the RTUser is not authenticated
[userAgain save];
</code></pre>

### Swift
<pre><code class="swift">var user = RTUser.logInWithUsername("my_username", password:"my_password")
user.username = "my_new_username" // attempt to change username
user.save() // This succeeds, since the user was authenticated on the device

// Get the user from a non-authenticated method
var query = RTUser.query()
var userAgain = query.getObjectWithId(user.objectId) as RTUser

userAgain.username = "another_username"

// This will crash, since the RTUser is not authenticated
userAgain.save()
</code></pre>

The `RTUser` obtained from `currentUser` will always be authenticated.

If you need to check if a `RTUser` is authenticated, you can invoke the `isAuthenticated` method. You do not need to check `isAuthenticated` with `RTUser` objects that are obtained via an authenticated method.

## Security For Other Objects

The same security model that applies to the `RTUser` can be applied to other objects. For any object, you can specify which users are allowed to read the object, and which users are allowed to modify an object. To support this type of security, each object has an access control list, implemented by the `RTACL` class.

The simplest way to use a `RTACL` is to specify that an object may only be read or written by a single user. To create such an object, there must first be a logged in `RTUser`. Then, the `ACLWithUser` method generates a `RTACL` that limits access to that user. An object's ACL is updated when the object is saved, like any other property. Thus, to create a private note that can only be accessed by the current user:

### Objective - C
<pre><code class="objectivec">RTObject *privateNote = [RTObject objectWithClassName:@"Note"];
privateNote[@"content"] = @"This note is private!";
privateNote.ACL = [RTACL ACLWithUser:[RTUser currentUser]];
[privateNote saveInBackground];
</code></pre>

### Swift
<pre><code class="swift">var privateNote = RTObject(className:"Note")
privateNote["content"] = "This note is private!"
privateNote.ACL = RTACL.ACLWithUser(RTUser.currentUser())
privateNote.saveInBackground()
</code></pre>

This note will then only be accessible to the current user, although it will be accessible to any device where that user is signed in. This functionality is useful for applications where you want to enable access to user data across multiple devices, like a personal todo list.

Permissions can also be granted on a per-user basis. You can add permissions individually to a `RTACL` using `setReadAccess:forUser:` and `setWriteAccess:forUser:`. For example, let's say you have a message that will be sent to a group of several users, where each of them have the rights to read and delete that message:

### Objective - C
<pre><code class="objectivec">RTObject *groupMessage = [RTObject objectWithClassName:@"Message"];
RTACL *groupACL = [RTACL ACL];

// userList is an NSArray with the users we are sending this message to.
for (RTUser *user in userList) {
    [groupACL setReadAccess:YES forUser:user];
    [groupACL setWriteAccess:YES forUser:user];
}

groupMessage.ACL = groupACL;
[groupMessage saveInBackground];
</code></pre>

### Swift
<pre><code class="swift">var groupMessage = RTObject(className:"Message")
var groupACL = RTACL.ACL()

// userList is an NSArray with the users we are sending this message to.
for (user : RTUser in userList) {
    groupACL.setReadAccess(true, forUser:user)
    groupACL.setWriteAccess(true, forUser:user)
}

groupMessage.ACL = groupACL
groupMessage.saveInBackground()
</code></pre>

You can also grant permissions to all users at once using `setPublicReadAccess:` and `setPublicWriteAccess:`. This allows patterns like posting comments on a message board. For example, to create a post that can only be edited by its author, but can be read by anyone:

### Objective - C
<pre><code class="objectivec">RTObject *publicPost = [RTObject objectWithClassName:@"Post"];
RTACL *postACL = [RTACL ACLWithUser:[RTUser currentUser]];
[postACL setPublicReadAccess:YES];
publicPost.ACL = postACL;
[publicPost saveInBackground];
</code></pre>

### Swift
<pre><code class="swift">var publicPost = RTObject(className:"Post")
var postACL = RTACL.ACLWithUser(RTUser.currentUser())
postACL.setPublicReadAccess(true)
publicPost.ACL = postACL
publicPost.saveInBackground()
</code></pre>

To help ensure that your users' data is secure by default, you can set a default ACL to be applied to all newly-created `RTObjects`:

### Objective - C
<pre><code class="objectivec">[RTACL setDefaultACL:defaultACL withAccessForCurrentUser:YES];
</code></pre>

### Swift
<pre><code class="swift">RTACL.setDefaultACL(defaultACL, withAccessForCurrentUser:true)
</code></pre>

In the code above, the second parameter to setDefaultACL tells Rooftop to ensure that the default ACL assigned at the time of object creation allows read and write access to the current user at that time.  Without this setting, you would need to reset the defaultACL every time a user logs in or out so that the current user would be granted access appropriately.  With this setting, you can ignore changes to the current user until you explicitly need to grant different kinds of access.

Default ACLs make it easy to create apps that follow common access patterns. An application like Twitter, for example, where user content is generally visible to the world, might set a default ACL such as:

### Objective - C
<pre><code class="objectivec">RTACL *defaultACL = [RTACL ACL];
[defaultACL setPublicReadAccess:YES];
[RTACL setDefaultACL:defaultACL withAccessForCurrentUser:YES];
</code></pre>

### Swift
<pre><code class="swift">var defaultACL = RTACL.ACL()
defaultACL.setPublicReadAccess(true)
RTACL.setDefaultACL(defaultACL, withAccessForCurrentUser:true)
</code></pre>

For an app like Dropbox, where a user's data is only accessible by the user itself unless explicit permission is given, you would provide a default ACL where only the current user is given access:

<pre><code class="objectivec">
[RTACL setDefaultACL:[RTACL ACL] withAccessForCurrentUser:YES];
</code></pre>
<pre><code class="swift">
RTACL.setDefaultACL(RTACL.ACL(), withAccessForCurrentUser:true)
</code></pre>

For an application that logs data to Rooftop but doesn't provide any user access to that data, you would deny access to the current user while providing a restrictive ACL:

<pre><code class="objectivec">
[RTACL setDefaultACL:[RTACL ACL] withAccessForCurrentUser:NO];
</code></pre>
<pre><code class="swift">
RTACL.setDefaultACL(RTACL.ACL(), withAccessForCurrentUser:false)
</code></pre>

Operations that are forbidden, such as deleting an object that you do not have write access to, result in a `kRTErrorObjectNotFound` error code. For security purposes, this prevents clients from distinguishing which object ids exist but are secured, versus which object ids do not exist at all.

## Resetting Passwords

It's a fact that as soon as you introduce passwords into a system, users will forget them. In such cases, our library provides a way to let them securely reset their password.

To kick off the password reset flow, ask the user for their email address, and call:

### Objective - C
<pre><code class="objectivec">[RTUser requestPasswordResetForEmailInBackground:@"email@example.com"];
</code></pre>

### Swift
<pre><code class="swift">
RTUser.requestPasswordResetForEmailInBackground("email@example.com")
</code></pre>

This will attempt to match the given email with the user's email or username field, and will send them a password reset email. By doing this, you can opt to have users use their email as their username, or you can collect it separately and store it in the email field.

The flow for password reset is as follows:

1.  User requests that their password be reset by typing in their email.
2.  Rooftop sends an email to their address, with a special password reset link.
3.  User clicks on the reset link, and is directed to a special Rooftop page that will allow them type in a new password.
4.  User types in a new password. Their password has now been reset to a value they specify.

Note that the messaging in this flow will reference your app by the name that you specified when you created this app on Rooftop.

## Querying

To query for users, you need to use the special user query:

### Objective - C
<pre><code class="objectivec">RTQuery *query = [RTUser query];
[query whereKey:@"gender" equalTo:@"female"]; // find all the women
NSArray *girls = [query findObjects];
</code></pre>

### Swift
<pre><code class="swift">var query = RTUser.query()
query.whereKey("gender", equalTo:"female")
var girls = query.findObjects()
</code></pre>

In addition, you can use `getUserObjectWithId:objectId` to get a `RTUser` by id.

## Associations

Associations involving a `RTUser` work right out of the box. For example, let's say you're making a blogging app. To store a new post for a user and retrieve all their posts:

### Objective - C
<pre><code class="objectivec">RTUser *user = [RTUser currentUser];

// Make a new post
RTObject *post = [RTObject objectWithClassName:@"Post"];
post[@"title"] = @"My New Post";
post[@"body"] = @"This is some great content.";
post[@"user"] = user;
[post save];

// Find all posts by the current user
RTQuery *query = [RTQuery queryWithClassName:@"Post"];
[query whereKey:@"user" equalTo:user];
NSArray *usersPosts = [query findObjects];
</code></pre>

### Swift
<pre><code class="swift">var user = RTUser.currentUser()

// Make a new post
var post = RTObject(className:"Post")
post["title"] = "My New Post"
post["body"] = "This is some great content."
post["user"] = user
post.save()
</code></pre>