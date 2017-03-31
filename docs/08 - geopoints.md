# GeoPoints

Rooftop allows you to associate real-world latitude and longitude coordinates with an object.  Adding a `RTGeoPoint` to a `RTObject` allows queries to take into account the proximity of an object to a reference point. This allows you to easily do things like find out what user is closest to another user or which places are closest to a user.

## RTGeoPoint

To associate a point with an object you first need to create a `RTGeoPoint`. For example, to create a point with latitude of 40.0 degrees and -30.0 degrees longitude:

### Objective - C
<pre><code class="objectivec">RTGeoPoint *point = [RTGeoPoint geoPointWithLatitude:40.0 longitude:-30.0];
</code></pre>

### Swift
<pre><code class="swift">let point = RTGeoPoint(latitude:40.0, longitude:-30.0)
</code></pre>

This point is then stored in the object as a regular field.

### Objective - C
<pre><code class="objectivec">placeObject[@"location"] = point;
</code></pre>

### Swift
<pre><code class="swift">placeObject["location"] = point
</code></pre>

Note: Currently only one key in a class may be a `RTGeoPoint`.

### Getting the User's Current Location

`RTGeoPoint` also provides a helper method for fetching the user's current location. This is accomplished via `geoPointForCurrentLocationInBackground`:

### Objective - C
<pre><code class="objectivec">[RTGeoPoint geoPointForCurrentLocationInBackground:^(RTGeoPoint *geoPoint, NSError *error) {
    if (!error) {
        // do something with the new geoPoint
    }
}];
</code></pre>

### Swift
<pre><code class="swift">RTGeoPoint.geoPointForCurrentLocationInBackground {
  (geoPoint: RTGeoPoint?, error: NSError?) -> Void in
  if error == nil {
    // do something with the new geoPoint
  }
}
</code></pre>

When this code is run, the following happens:

1.  An internal `CLLocationManager` starts listening for location updates (via `startsUpdatingLocation`).
2.  Once a location is received, the location manager stops listening for location updates (via `stopsUpdatingLocation`) and a `RTGeoPoint` is created from the new location. If the location manager errors out, it still stops listening for updates, and returns an `NSError` instead.
3.  Your `block` is called with the `RTGeoPoint`.

For those who choose to use `CLLocationManager` directly, we also provide a `+geoPointWithLocation:` constructor to transform `CLLocation`s directly into `RTGeoPoint`s - great for apps that require constant polling.

## Geo Queries

Now that you have a bunch of objects with spatial coordinates, it would be nice to find out which objects are closest to a point. This can be done by adding another restriction to `RTQuery` using `whereKey:nearGeoPoint:`. Getting a list of ten places that are closest to a user may look something like:

### Objective - C
<pre><code class="objectivec">// User's location
RTGeoPoint *userGeoPoint = userObject[@"location"];
// Create a query for places
RTQuery *query = [RTQuery queryWithClassName:@"PlaceObject"];
// Interested in locations near user.
[query whereKey:@"location" nearGeoPoint:userGeoPoint];
// Limit what could be a lot of points.
query.limit = 10;
// Final list of objects
placesObjects = [query findObjects];
</code></pre>

### Swift
<pre><code class="swift">// User's location
let userGeoPoint = userObject["location"] as RTGeoPoint
// Create a query for places
var query = RTQuery(className:"PlaceObject")
// Interested in locations near user.
query.whereKey("location", nearGeoPoint:userGeoPoint)
// Limit what could be a lot of points.
query.limit = 10
// Final list of objects
placesObjects = query.findObjects()
</code></pre>

 At this point `placesObjects` will be an array of objects ordered by distance (nearest to farthest) from `userGeoPoint`. Note that if an additional `orderByAscending:`/`orderByDescending:` constraint is applied, it will take precedence over the distance ordering.

 To limit the results using distance check out `whereKey:nearGeoPoint:withinMiles`, `whereKey:nearGeoPoint:withinKilometers`, and `whereKey:nearGeoPoint:withinRadians`.

It's also possible to query for the set of objects that are contained within a particular area. To find the objects in a rectangular bounding box, add the `whereKey:withinGeoBoxFromSouthwest:toNortheast:` restriction to your `RTQuery`.

### Objective - C
<pre><code class="objectivec">RTGeoPoint *swOfSF = [RTGeoPoint geoPointWithLatitude:37.708813 longitude:-122.526398];
RTGeoPoint *neOfSF = [RTGeoPoint geoPointWithLatitude:37.822802 longitude:-122.373962];
RTQuery *query = [RTQuery queryWithClassName:@"PizzaPlaceObject"];
[query whereKey:@"location" withinGeoBoxFromSouthwest:swOfSF toNortheast:neOfSF];
NSArray *pizzaPlacesInSF = [query findObjects];
</code></pre>

### Swift
<pre><code class="swift">let swOfSF = RTGeoPoint(latitude:37.708813, longitude:-122.526398)
let neOfSF = RTGeoPoint(latitude:37.822802, longitude:-122.373962)
var query = RTQuery(className:"PizzaPlaceObject")
query.whereKey("location", withinGeoBoxFromSouthwest:swOfSF, toNortheast:neOfSF)
var pizzaPlacesInSF = query.findObjects()
</code></pre>

## Caveats

At the moment there are a couple of things to watch out for:

1.  Using the `nearGeoPoint` constraint will also limit results to within 100 miles.
2.  Points should not equal or exceed the extreme ends of the ranges. Latitude should not be -90.0 or 90.0. Longitude should not be -180.0 or 180.0. Attempting to set latitude or longitude out of bounds will cause an error.