/**
 * Copyright (c) 2016 - Present, RFTP Technologies.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#import <Rooftop/RTConstants.h>
#import <Rooftop/RTObject.h>

NS_ASSUME_NONNULL_BEGIN

/**
 This category lists all methods of `RTObject` class that are synchronous, but have asynchronous counterpart,
 Calling one of these synchronous methods could potentially block the current thread for a large amount of time,
 since it might be fetching from network or saving/loading data from disk.
 */
@interface RTObject (Synchronous)

///--------------------------------------
#pragma mark - Saving Objects
///--------------------------------------

/**
 *Synchronously* saves the `RTObject`.

 @return Returns whether the save succeeded.
 */
- (BOOL)save RT_SWIFT_UNAVAILABLE;

/**
 *Synchronously* saves the `RTObject` and sets an error if it occurs.

 @param error Pointer to an `NSError` that will be set if necessary.

 @return Returns whether the save succeeded.
 */
- (BOOL)save:(NSError **)error;

///--------------------------------------
#pragma mark - Saving Many Objects
///--------------------------------------

/**
 Saves a collection of objects *synchronously all at once.

 @param objects The array of objects to save.

 @return Returns whether the save succeeded.
 */
+ (BOOL)saveAll:(nullable NSArray<RTObject *> *)objects RT_SWIFT_UNAVAILABLE;

/**
 Saves a collection of objects *synchronously* all at once and sets an error if necessary.

 @param objects The array of objects to save.
 @param error Pointer to an `NSError` that will be set if necessary.

 @return Returns whether the save succeeded.
 */
+ (BOOL)saveAll:(nullable NSArray<RTObject *> *)objects error:(NSError **)error;

///--------------------------------------
#pragma mark - Getting an Object
///--------------------------------------

/**
 *Synchronously* fetches the RTObject with the current data from the server.
 */
- (nullable instancetype)fetch RT_SWIFT_UNAVAILABLE;
/**
 *Synchronously* fetches the RTObject with the current data from the server and sets an error if it occurs.

 @param error Pointer to an `NSError` that will be set if necessary.
 */
- (nullable instancetype)fetch:(NSError **)error;

/**
 *Synchronously* fetches the `RTObject` data from the server if `dataAvailable` is `NO`.
 */
- (nullable instancetype)fetchIfNeeded RT_SWIFT_UNAVAILABLE;

/**
 *Synchronously* fetches the `RTObject` data from the server if `dataAvailable` is `NO`.

 @param error Pointer to an `NSError` that will be set if necessary.
 */
- (nullable instancetype)fetchIfNeeded:(NSError **)error;

///--------------------------------------
#pragma mark - Getting Many Objects
///--------------------------------------

/**
 *Synchronously* fetches all of the `RTObject` objects with the current data from the server.

 @param objects The list of objects to fetch.
 */
+ (nullable NSArray<__kindof RTObject *> *)fetchAll:(nullable NSArray<RTObject *> *)objects RT_SWIFT_UNAVAILABLE;

/**
 *Synchronously* fetches all of the `RTObject` objects with the current data from the server
 and sets an error if it occurs.

 @param objects The list of objects to fetch.
 @param error Pointer to an `NSError` that will be set if necessary.
 */
+ (nullable NSArray<__kindof RTObject *> *)fetchAll:(nullable NSArray<RTObject *> *)objects
                                              error:(NSError **)error;

/**
 *Synchronously* fetches all of the `RTObject` objects with the current data from the server.
 @param objects The list of objects to fetch.
 */
+ (nullable NSArray<__kindof RTObject *> *)fetchAllIfNeeded:(nullable NSArray<RTObject *> *)objects RT_SWIFT_UNAVAILABLE;

/**
 *Synchronously* fetches all of the `RTObject` objects with the current data from the server
 and sets an error if it occurs.

 @param objects The list of objects to fetch.
 @param error Pointer to an `NSError` that will be set if necessary.
 */
+ (nullable NSArray<__kindof RTObject *> *)fetchAllIfNeeded:(nullable NSArray<RTObject *> *)objects
                                                      error:(NSError **)error;

///--------------------------------------
#pragma mark - Fetching From Local Datastore
///--------------------------------------

/**
 *Synchronously* loads data from the local datastore into this object,
 if it has not been fetched from the server already.
 */
- (nullable instancetype)fetchFromLocalDatastore RT_SWIFT_UNAVAILABLE;

/**
 *Synchronously* loads data from the local datastore into this object, if it has not been fetched
 from the server already.

 If the object is not stored in the local datastore, this `error` will be set to
 return `kRTErrorCacheMiss`.

 @param error Pointer to an `NSError` that will be set if necessary.
 */
- (nullable instancetype)fetchFromLocalDatastore:(NSError **)error;

///--------------------------------------
#pragma mark - Deleting an Object
///--------------------------------------

/**
 *Synchronously* deletes the `RTObject`.

 @return Returns whether the delete succeeded.
 */
- (BOOL)delete RT_SWIFT_UNAVAILABLE;

/**
 *Synchronously* deletes the `RTObject` and sets an error if it occurs.

 @param error Pointer to an `NSError` that will be set if necessary.

 @return Returns whether the delete succeeded.
 */
- (BOOL)delete:(NSError **)error;

///--------------------------------------
#pragma mark - Deleting Many Objects
///--------------------------------------

/**
 *Synchronously* deletes a collection of objects all at once.

 @param objects The array of objects to delete.

 @return Returns whether the delete succeeded.
 */
+ (BOOL)deleteAll:(nullable NSArray<RTObject *> *)objects RT_SWIFT_UNAVAILABLE;

/**
 *Synchronously* deletes a collection of objects all at once and sets an error if necessary.

 @param objects The array of objects to delete.
 @param error Pointer to an `NSError` that will be set if necessary.

 @return Returns whether the delete succeeded.
 */
+ (BOOL)deleteAll:(nullable NSArray<RTObject *> *)objects error:(NSError **)error;

///--------------------------------------
#pragma mark - Pinning
///--------------------------------------

/**
 *Synchronously* stores the object and every object it points to in the local datastore, recursively,
 using a default pin name: `RTObjectDefaultPin`.

 If those other objects have not been fetched from Rooftop, they will not be stored. However,
 if they have changed data, all the changes will be retained. To get the objects back later, you can
 use a `RTQuery` that uses `RTQuery.-fromLocalDatastore`, or you can create an unfetched pointer with
 `+objectWithoutDataWithClassName:objectId:` and then call `-fetchFromLocalDatastore` on it.

 @return Returns whether the pin succeeded.

 @see `-unpin:`
 @see `RTObjectDefaultPin`
 */
- (BOOL)pin RT_SWIFT_UNAVAILABLE;

/**
 *Synchronously* stores the object and every object it points to in the local datastore, recursively,
 using a default pin name: `RTObjectDefaultPin`.

 If those other objects have not been fetched from Rooftop, they will not be stored. However,
 if they have changed data, all the changes will be retained. To get the objects back later, you can
 use a `RTQuery` that uses `RTQuery.-fromLocalDatastore`, or you can create an unfetched pointer with
 `+objectWithoutDataWithClassName:objectId:` and then call `-fetchFromLocalDatastore` on it.

 @param error Pointer to an `NSError` that will be set if necessary.

 @return Returns whether the pin succeeded.

 @see `-unpin:`
 @see `RTObjectDefaultPin`
 */
- (BOOL)pin:(NSError **)error;

/**
 *Synchronously* stores the object and every object it points to in the local datastore, recursively.

 If those other objects have not been fetched from Rooftop, they will not be stored. However,
 if they have changed data, all the changes will be retained. To get the objects back later, you can
 use a `RTQuery` that uses `RTQuery.-fromLocalDatastore`, or you can create an unfetched pointer with
 `+objectWithoutDataWithClassName:objectId:` and then call `-fetchFromLocalDatastore` on it.

 @param name The name of the pin.

 @return Returns whether the pin succeeded.

 @see `-unpinWithName:`
 */
- (BOOL)pinWithName:(NSString *)name RT_SWIFT_UNAVAILABLE;

/**
 *Synchronously* stores the object and every object it points to in the local datastore, recursively.

 If those other objects have not been fetched from Rooftop, they will not be stored. However,
 if they have changed data, all the changes will be retained. To get the objects back later, you can
 use a `RTQuery` that uses `RTQuery.-fromLocalDatastore`, or you can create an unfetched pointer with
 `+objectWithoutDataWithClassName:objectId:` and then call `-fetchFromLocalDatastore` on it.

 @param name    The name of the pin.
 @param error   Pointer to an `NSError` that will be set if necessary.

 @return Returns whether the pin succeeded.

 @see `-unpinWithName:`
 */
- (BOOL)pinWithName:(NSString *)name error:(NSError **)error;

///--------------------------------------
#pragma mark - Pinning Many Objects
///--------------------------------------

/**
 *Synchronously* stores the objects and every object they point to in the local datastore, recursively,
 using a default pin name: `RTObjectDefaultPin`.

 If those other objects have not been fetched from Rooftop, they will not be stored. However,
 if they have changed data, all the changes will be retained. To get the objects back later, you can
 use a `RTQuery` that uses `RTQuery.-fromLocalDatastore`, or you can create an unfetched pointer with
 `+objectWithoutDataWithClassName:objectId:` and then call `fetchFromLocalDatastore:` on it.

 @param objects The objects to be pinned.

 @return Returns whether the pin succeeded.

 @see unpinAll:
 @see RTObjectDefaultPin
 */
+ (BOOL)pinAll:(nullable NSArray<RTObject *> *)objects RT_SWIFT_UNAVAILABLE;

/**
 *Synchronously* stores the objects and every object they point to in the local datastore, recursively,
 using a default pin name: `RTObjectDefaultPin`.

 If those other objects have not been fetched from Rooftop, they will not be stored. However,
 if they have changed data, all the changes will be retained. To get the objects back later, you can
 use a `RTQuery` that uses `RTQuery.-fromLocalDatastore`, or you can create an unfetched pointer with
 `+objectWithoutDataWithClassName:objectId:` and then call `fetchFromLocalDatastore:` on it.

 @param objects The objects to be pinned.
 @param error   Pointer to an `NSError` that will be set if necessary.

 @return Returns whether the pin succeeded.

 @see unpinAll:error:
 @see RTObjectDefaultPin
 */
+ (BOOL)pinAll:(nullable NSArray<RTObject *> *)objects error:(NSError **)error;

/**
 *Synchronously* stores the objects and every object they point to in the local datastore, recursively.

 If those other objects have not been fetched from Rooftop, they will not be stored. However,
 if they have changed data, all the changes will be retained. To get the objects back later, you can
 use a `RTQuery` that uses `RTQuery.-fromLocalDatastore`, or you can create an unfetched pointer with
 `+objectWithoutDataWithClassName:objectId:` and then call `fetchFromLocalDatastore:` on it.

 @param objects The objects to be pinned.
 @param name    The name of the pin.

 @return Returns whether the pin succeeded.

 @see unpinAll:withName:
 */
+ (BOOL)pinAll:(nullable NSArray<RTObject *> *)objects withName:(NSString *)name RT_SWIFT_UNAVAILABLE;

/**
 *Synchronously* stores the objects and every object they point to in the local datastore, recursively.

 If those other objects have not been fetched from Rooftop, they will not be stored. However,
 if they have changed data, all the changes will be retained. To get the objects back later, you can
 use a `RTQuery` that uses `RTQuery.-fromLocalDatastore`, or you can create an unfetched pointer with
 `+objectWithoutDataWithClassName:objectId:` and then call `fetchFromLocalDatastore:` on it.

 @param objects The objects to be pinned.
 @param name    The name of the pin.
 @param error   Pointer to an `NSError` that will be set if necessary.

 @return Returns whether the pin succeeded.

 @see unpinAll:withName:error:
 */
+ (BOOL)pinAll:(nullable NSArray<RTObject *> *)objects withName:(NSString *)name error:(NSError **)error;

///--------------------------------------
#pragma mark - Unpinning
///--------------------------------------

/**
 *Synchronously* removes the object and every object it points to in the local datastore, recursively,
 using a default pin name: `RTObjectDefaultPin`.

 @return Returns whether the unpin succeeded.

 @see pin:
 @see RTObjectDefaultPin
 */
- (BOOL)unpin RT_SWIFT_UNAVAILABLE;

/**
 *Synchronously* removes the object and every object it points to in the local datastore, recursively,
 using a default pin name: `RTObjectDefaultPin`.

 @param error Pointer to an `NSError` that will be set if necessary.

 @return Returns whether the unpin succeeded.

 @see pin:
 @see RTObjectDefaultPin
 */
- (BOOL)unpin:(NSError **)error;

/**
 *Synchronously* removes the object and every object it points to in the local datastore, recursively.

 @param name The name of the pin.

 @return Returns whether the unpin succeeded.

 @see pinWithName:
 */
- (BOOL)unpinWithName:(NSString *)name RT_SWIFT_UNAVAILABLE;

/**
 *Synchronously* removes the object and every object it points to in the local datastore, recursively.

 @param name    The name of the pin.
 @param error   Pointer to an `NSError` that will be set if necessary.

 @return Returns whether the unpin succeeded.

 @see pinWithName:error:
 */
- (BOOL)unpinWithName:(NSString *)name error:(NSError **)error;

///--------------------------------------
#pragma mark - Unpinning Many Objects
///--------------------------------------

/**
 *Synchronously* removes all objects in the local datastore
 using a default pin name: `RTObjectDefaultPin`.

 @return Returns whether the unpin succeeded.

 @see RTObjectDefaultPin
 */
+ (BOOL)unpinAllObjects RT_SWIFT_UNAVAILABLE;

/**
 *Synchronously* removes all objects in the local datastore
 using a default pin name: `RTObjectDefaultPin`.

 @param error   Pointer to an `NSError` that will be set if necessary.

 @return Returns whether the unpin succeeded.

 @see RTObjectDefaultPin
 */
+ (BOOL)unpinAllObjects:(NSError **)error;

/**
 *Synchronously* removes all objects with the specified pin name.

 @param name    The name of the pin.

 @return Returns whether the unpin succeeded.
 */
+ (BOOL)unpinAllObjectsWithName:(NSString *)name RT_SWIFT_UNAVAILABLE;

/**
 *Synchronously* removes all objects with the specified pin name.

 @param name    The name of the pin.
 @param error   Pointer to an `NSError` that will be set if necessary.

 @return Returns whether the unpin succeeded.
 */
+ (BOOL)unpinAllObjectsWithName:(NSString *)name error:(NSError **)error;

/**
 *Synchronously* removes the objects and every object they point to in the local datastore, recursively,
 using a default pin name: `RTObjectDefaultPin`.

 @param objects The objects.

 @return Returns whether the unpin succeeded.

 @see pinAll:
 @see RTObjectDefaultPin
 */
+ (BOOL)unpinAll:(nullable NSArray<RTObject *> *)objects RT_SWIFT_UNAVAILABLE;

/**
 *Synchronously* removes the objects and every object they point to in the local datastore, recursively,
 using a default pin name: `RTObjectDefaultPin`.

 @param objects The objects.
 @param error   Pointer to an `NSError` that will be set if necessary.

 @return Returns whether the unpin succeeded.

 @see pinAll:error:
 @see RTObjectDefaultPin
 */
+ (BOOL)unpinAll:(nullable NSArray<RTObject *> *)objects error:(NSError **)error;

/**
 *Synchronously* removes the objects and every object they point to in the local datastore, recursively.

 @param objects The objects.
 @param name    The name of the pin.

 @return Returns whether the unpin succeeded.

 @see pinAll:withName:
 */
+ (BOOL)unpinAll:(nullable NSArray<RTObject *> *)objects withName:(NSString *)name RT_SWIFT_UNAVAILABLE;

/**
 *Synchronously* removes the objects and every object they point to in the local datastore, recursively.

 @param objects The objects.
 @param name    The name of the pin.
 @param error   Pointer to an `NSError` that will be set if necessary.

 @return Returns whether the unpin succeeded.

 @see pinAll:withName:error:
 */
+ (BOOL)unpinAll:(nullable NSArray<RTObject *> *)objects withName:(NSString *)name error:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
