/**
 * Copyright (c) 2016 - Present, RFTP Technologies.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#import <Rooftop/RTConstants.h>
#import <Rooftop/RTQuery.h>

NS_ASSUME_NONNULL_BEGIN

/**
 This category lists all methods of `RTQuery` class that are synchronous, but have asynchronous counterpart,
 Calling one of these synchronous methods could potentially block the current thread for a large amount of time,
 since it might be fetching from network or saving/loading data from disk.
 */
@interface RTQuery<RTGenericObject : RTObject *> (Synchronous)

///--------------------------------------
#pragma mark - Getting Objects by ID
///--------------------------------------

/**
 Returns a `RTObject` with a given class and id.

 @param objectClass The class name for the object that is being requested.
 @param objectId The id of the object that is being requested.

 @return The `RTObject` if found. Returns `nil` if the object isn't found, or if there was an error.
 */
+ (nullable RTGenericObject)getObjectOfClass:(NSString *)objectClass objectId:(NSString *)objectId RT_SWIFT_UNAVAILABLE;

/**
 Returns a `RTObject` with a given class and id and sets an error if necessary.

 @param objectClass The class name for the object that is being requested.
 @param objectId The id of the object that is being requested.
 @param error Pointer to an `NSError` that will be set if necessary.

 @return The `RTObject` if found. Returns `nil` if the object isn't found, or if there was an `error`.
 */
+ (nullable RTGenericObject)getObjectOfClass:(NSString *)objectClass objectId:(NSString *)objectId error:(NSError **)error;

/**
 Returns a `RTObject` with the given id.

 @warning This method mutates the query.
 It will reset limit to `1`, skip to `0` and remove all conditions, leaving only `objectId`.

 @param objectId The id of the object that is being requested.

 @return The `RTObject` if found. Returns nil if the object isn't found, or if there was an error.
 */
- (nullable RTGenericObject)getObjectWithId:(NSString *)objectId RT_SWIFT_UNAVAILABLE;

/**
 Returns a `RTObject` with the given id and sets an error if necessary.

 @warning This method mutates the query.
 It will reset limit to `1`, skip to `0` and remove all conditions, leaving only `objectId`.

 @param objectId The id of the object that is being requested.
 @param error Pointer to an `NSError` that will be set if necessary.

 @return The `RTObject` if found. Returns nil if the object isn't found, or if there was an error.
 */
- (nullable RTGenericObject)getObjectWithId:(NSString *)objectId error:(NSError **)error;

///--------------------------------------
#pragma mark - Getting User Objects
///--------------------------------------

/**
 Returns a `RTUser` with a given id.

 @param objectId The id of the object that is being requested.

 @return The RTUser if found. Returns nil if the object isn't found, or if there was an error.
 */
+ (nullable RTUser *)getUserObjectWithId:(NSString *)objectId RT_SWIFT_UNAVAILABLE;

/**
 Returns a RTUser with a given class and id and sets an error if necessary.
 @param objectId The id of the object that is being requested.
 @param error Pointer to an NSError that will be set if necessary.
 @result The RTUser if found. Returns nil if the object isn't found, or if there was an error.
 */
+ (nullable RTUser *)getUserObjectWithId:(NSString *)objectId error:(NSError **)error;

///--------------------------------------
#pragma mark - Getting all Matches for a Query
///--------------------------------------

/**
 Finds objects *synchronously* based on the constructed query.

 @return Returns an array of `RTObject` objects that were found.
 */
- (nullable NSArray<RTGenericObject> *)findObjects RT_SWIFT_UNAVAILABLE;

/**
 Finds objects *synchronously* based on the constructed query and sets an error if there was one.

 @param error Pointer to an `NSError` that will be set if necessary.

 @return Returns an array of `RTObject` objects that were found.
 */
- (nullable NSArray<RTGenericObject> *)findObjects:(NSError **)error;

///--------------------------------------
#pragma mark - Getting the First Match in a Query
///--------------------------------------

/**
 Gets an object *synchronously* based on the constructed query.

 @warning This method mutates the query. It will reset the limit to `1`.

 @return Returns a `RTObject`, or `nil` if none was found.
 */
- (nullable RTGenericObject)getFirstObject RT_SWIFT_UNAVAILABLE;

/**
 Gets an object *synchronously* based on the constructed query and sets an error if any occurred.

 @warning This method mutates the query. It will reset the limit to `1`.

 @param error Pointer to an `NSError` that will be set if necessary.

 @return Returns a `RTObject`, or `nil` if none was found.
 */
- (nullable RTGenericObject)getFirstObject:(NSError **)error;

///--------------------------------------
#pragma mark - Counting the Matches in a Query
///--------------------------------------

/**
 Counts objects *synchronously* based on the constructed query.

 @return Returns the number of `RTObject` objects that match the query, or `-1` if there is an error.
 */
- (NSInteger)countObjects RT_SWIFT_UNAVAILABLE;

/**
 Counts objects *synchronously* based on the constructed query and sets an error if there was one.

 @param error Pointer to an `NSError` that will be set if necessary.

 @return Returns the number of `RTObject` objects that match the query, or `-1` if there is an error.
 */
- (NSInteger)countObjects:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
