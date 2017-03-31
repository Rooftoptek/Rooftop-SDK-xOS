# Local Datastore

The Rooftop iOS/OS X SDK provides a local datastore which can be used to store and retrieve `RTObject`s, even when the network is unavailable. To enable this functionality, add `libsqlite3.dylib` and call 
### Objective - C
`[Rooftop enableLocalDatastore]`

### Swift
`Rooftop.enableLocalDatastore()`

before your call to `setApplicationId:clientKey:`.

### Objective C
<pre><code class="objectivec">@implementation AppDelegate

- (void)application:(UIApplication *)application didFinishLaunchWithOptions:(NSDictionary *)options {
	[Rooftop enableLocalDatastore];
	[Rooftop setApplicationId:@"rooftopAppId" clientKey:@"rooftopClientKey"];
}

@end
</code></pre>

### Swift
<pre><code class="swift">@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate {

	func application(application: UIApplication, didFinishLaunchingWithOptions launchOptions: [NSObject: AnyObject]?) -> Bool {
		Rooftop.enableLocalDatastore()
		Rooftop.setApplicationId("rooftopAppId", clientKey: "rooftopClientKey")
	}
}
</code></pre>

There are a couple of side effects of enabling the local datastore that you should be aware of. When enabled, there will only be one instance of any given `RTObject`. For example, imagine you have an instance of the `"GameScore"` class with an `objectId` of `"xWMyZ4YEGZ"`, and then you issue a `RTQuery` for all instances of `"GameScore"` with that `objectId`. The result will be the same instance of the object you already have in memory.

Another side effect is that the current user and current installation will be stored in the local datastore, so you can persist unsaved changes to these objects between runs of your app using the methods below.

Calling the `saveEventually` method on a `RTObject` will cause the object to be pinned in the local datastore until the save completes. So now, if you change the current `RTUser` and call `[[RTUser currentUser] saveEventually]`, your app will always see the changes that you have made.

## Pinning

You can store a `RTObject` in the local datastore by pinning it. Pinning a `RTObject` is recursive, just like saving, so any objects that are pointed to by the one you are pinning will also be pinned. When an object is pinned, every time you update it by fetching or saving new data, the copy in the local datastore will be updated automatically. You don't need to worry about it at all.

### Objective - C
<pre><code class="objectivec">RTObject *gameScore = [RTObject objectWithClassName:@"GameScore"];
gameScore[@"score"] = @1337;
gameScore[@"playerName"] = @"Sean Plott";
gameScore[@"cheatMode"] = @NO;
[gameScore pinInBackground];
</code></pre>

### Swift
<pre><code class="swift">let gameScore = RTObject(className:"GameScore")
gameScore["score"] = 1337
gameScore["playerName"] = "Sean Plott"
gameScore["cheatMode"] = false
gameScore.pinInBackground()
</code></pre>

If you have multiple objects, you can pin them all at once with the `pinAllInBackground` convenience method.

### Objective - C
<pre><code class="objectivec">[RTObject pinAllInBackground:listOfObjects];
</code></pre>

### Swift
<pre><code class="swift">RTObject.pinAllInBackground(listOfObjects)
</code></pre>

## Retrieving Objects

Storing objects is great, but it's only useful if you can then get the objects back out later. Retrieving an object from the local datastore works just like retrieving one over the network. The only difference is calling the `fromLocalDatastore` method to tell the `RTQuery` where to look for its results.

### Objective - C
<pre><code class="objectivec">RTQuery *query = [RTQuery queryWithClassName:@"GameScore"];
[query fromLocalDatastore];
[[query getObjectInBackgroundWithId:@"xWMyZ4YE"] continueWithBlock:^id(BFTask *task) {
	if (task.error) {
		// Something went wrong.
		return task;
  	}
  // task.result will be your game score
  return task;
}];
</code></pre>

### Swift
<pre><code class="swift">let query = RTQuery(className: "GameScore")
query.fromLocalDatastore()
query.getObjectInBackgroundWithId("xWMyZ4YE") { (task) in
    if let error = task.error {
        // Something went wrong.
        return task;
    }
    // task.result will be your game score
    return task;
}
</code></pre>

## Querying

Often, you'll want to find a whole list of objects that match certain criteria, instead of getting a single object by id. To do that, you can use a RTQuery. Any `RTQuery` can be used with the local datastore just as with the network. The results will include any object you have pinned that matches the query. Any unsaved changes you have made to the object will be considered when evaluating the query. So you can find a local object that matches, even if it was never returned from the server for this particular query.

### Objective - C
<pre><code class="objectivec">RTQuery *query = [RTQuery queryWithClassName:@"GameScore"];
[query fromLocalDatastore];
[query whereKey:@"playerName" equalTo:@"Joe Bob"];
[[query findObjectsInBackground] continueWithBlock:^id(BFTask *task) {
  if (task.error) {
    NSLog(@"Error: %@", task.error);
    return task;
  }

  NSLog(@"Retrieved %d", task.result.count);
  return task;
}];
</code></pre>

### Swift
<pre><code class="swift">let query = RTQuery(className: "GameScore")
query.fromLocalDatastore()
query.whereKey("playerName", equalTo: "Joe Bob")
query.findObjectsInBackground() { (task) in
    if let error = task.error {
        print("Error: \(error)")
        return task
    }

    print("Retrieved \(task.result.count)")
    return task
}
</code></pre>

## Security

The same security model that applies to objects in Rooftop applies to objects in the Local Datastore. Read-write permissions are defined by `RTACL`s and a user cannot access or modify anything they don't have permission to.

The only difference is that you won't be able to access any data protected by Role based ACLs due to the fact that the Roles are stored on the server. To access this data protected by Role based ACLs, you will need to ignore ACLs when executing a Local Datastore query:

### Objective - C
<pre><code class="objectivec">RTQuery *query = [[[RTQuery queryWithClassName:@"Note"] fromLocalDatastore] ignoreACLs];
</code></pre>

### Swift
<pre><code class="swift">let query = RTQuery(className: "Note").fromLocalDatastore.ignoreACLs
</code></pre>


## Unpinning

When you are done with an object and no longer need it to be in the local datastore, you can simply unpin it. This will free up disk space on the device and keep your queries on the local datastore running quickly.

### Objective - C
<pre><code class="objectivec">[gameScore unpinInBackground];
</code></pre>

### Swift
<pre><code class="swift">gameScore.unpinInBackground()
</code></pre>

There's also a method to unpin several objects at once.

### Objective - C
<pre><code class="objectivec">[RTObject unpinAllInBackground:listOfObjects];
</code></pre>

### Swift
<pre><code class="swift">RTObject.unpinAllInBackground(listOfObjects)
</code></pre>

## Pinning with Labels

Manually pinning and unpinning each object individual is a bit like using `malloc` and `free`. It is a very powerful tool, but it can be difficult to manage what objects get stored in complex scenarios. For example, imagine you are making a game with separate high score lists for global high scores and your friends' high scores. If one of your friends happens to have a globally high score, you need to make sure you don't unpin them completely when you remove them from one of the cached queries. To make these scenarios easier, you can also pin with a label. Labels indicate a group of objects that should be stored together.

### Objective - C
<pre><code class="objectivec">// Add several objects with a label.
[RTObject pinAllInBackground:someGameScores withName:@"MyScores"];

// Add another object with the same label.
[anotherGameScore pinInBackgroundWithName:@"MyScores"];
</code></pre>

### Swift
<pre><code class="swift">// Add several objects with a label.
RTObject.pinAllInBackground(objects:someGameScores withName:"MyScores")

// Add another object with the same label.
anotherGameScore.pinInBackgroundWithName("MyScores")
</code></pre>

To unpin all of the objects with the same label at the same time, you can pass a label to the unpin methods. This saves you from having to manually track which objects are in each group you care about.

### Objective - C
<pre><code class="objectivec">[RTObject unpinAllObjectsInBackgroundWithName:@"MyScores"];
</code></pre>

### Swift
<pre><code class="swift">RTObject.unpinAllObjectsInBackgroundWithName("MyScores")
</code></pre>

Any object will stay in the datastore as long as it is pinned with any label. In other words, if you pin an object with two different labels, and then unpin it with one label, the object will stay in the datastore until you also unpin it with the other label.

## Caching Query Results

Pinning with labels makes it easy to cache the results of queries. You can use one label to pin the results of each different query. To get new results from the network, just do a query and update the pinned objects.

### Objective - C
<pre><code class="objectivec">RTQuery *query = [RTQuery queryWithClassName:@"GameScore"];
[query orderByDescending:@"score"];

// Query for new results from the network
[[query findObjectsInBackground] continueWithSuccessBlock:^id(BFTask *task) {
  return [[RTObject unpinAllObjectsInBackgroundWithName:@"HighScores"] continueWithSuccessBlock:^id(BFTask *ignored) {
    // Cache the new results.
    NSArray *scores = task.result;
    return [RTObject pinAllInBackground:scores withName:@"HighScores"];
  }];
}];
</code></pre>

### Swift
<pre><code class="swift">let query = RTQuery(className:"GameScore")
query.order(byDescending: "score")
        
// Query for new results from the network
query.findObjectsInBackground().continue(successBlock: { (task: BFTask!) -> AnyObject! in        
	return RTObject.unpinAllObjectsInBackground(withName:"HighScores").continue(successBlock: { (ignored: BFTask!) -> AnyObject! in
		// Cache new results
		let scores = task.result as NSArray!
		return RTObject.pinAllInBackground(((scores as [AnyObject])!), withName: "HighScores")
  	})
})</code></pre>

When you want to get the cached results for the query, you can then
      run the same query against the local datastore.

### Objective - C
<pre><code class="objectivec">RTQuery *query = [RTQuery queryWithClassName:@"GameScore"];
[query fromLocalDatastore];
[query orderByDescending:@"score"];
[[query findObjectsInBackground] continueWithBlock:^id(BFTask *task) {
  if (task.error) {
    // Something went wrong.
    return task;
  }
  // Yay! Cached scores!
  return task;
}];
</code></pre>

### Swift
<pre><code class="swift">let query = RTQuery(className:"GameScore")
query.fromLocalDatastore()
query.order(byDescending: "score")   
query.findObjectsInBackground().continue({ (task: BFTask!) -> AnyObject! in
	if task.error != nil {
		// There was an error.
		return task
	}
	// Yay! Cached scores!
	return task
})
</code></pre>

## Syncing Local Changes

Once you've saved some changes locally, there are a few different ways you can save those changes back to Rooftop over the network. The easiest way to do this is with `saveEventually`. When you call `saveEventually` on a `RTObject`, it will be pinned until it can be saved. The SDK will make sure to save the object the next time the network is available.

### Objective - C
<pre><code class="objectivec">[gameScore saveEventually];
</code></pre>

### Swift
<pre><code class="swift">gameScore.saveEventually()
</code></pre>

If you'd like to have more control over the way objects are synced, you can keep them in the local datastore until you are ready to save them yourself using `saveInBackground`. To manage the set of objects that need to be saved, you can again use a label. The `fromPinWithName:` method on `RTQuery` makes it easy to fetch just the objects you care about.

### Objective - C
<pre><code class="objectivec">RTQuery *query = [RTQuery queryWithClassName:@"GameScore"];
[query fromPinWithName:@"MyChanges"];
[[query findObjectsInBackground] continueWithBlock:^id(BFTask *task) {
  NSArray *scores = task.result;
  for (RTObject *score in scores) {
    [[score saveInBackground] continueWithSuccessBlock:^id(BFTask *task) {
      return [score unpinInBackground];
    }];
  }
  return task;
}];
</code></pre>

### Swift
<pre><code class="swift">let query = RTQuery(className:"GameScore")
query.fromPin(withName: "MyChanges")
query.findObjectsInBackground().continue( {(task: BFTask!) -> AnyObject! in
	let scores = task.result! as NSArray
	for score in scores {
		(score as AnyObject).saveInBackground().continue(successBlock: {(task: BFTask!) -> AnyObject! in
			return (score as AnyObject).unpinInBackground()
       })
    } 
    return task
})
</code></pre>
