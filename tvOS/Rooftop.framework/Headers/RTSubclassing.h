/**
 * Copyright (c) 2016 - Present, RFTP Technologies.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#import <Foundation/Foundation.h>

@class RTQuery<RTGenericObject : RTObject *>;

NS_ASSUME_NONNULL_BEGIN

/**
 If a subclass of `RTObject` conforms to `RTSubclassing` and calls `RTObject.+registerSubclass`,
 Rooftop framework will be able to use that class as the native class for a Rooftop cloud object.

 Classes conforming to this protocol should subclass `RTObject` and
 include `RTObject+Subclass.h` in their implementation file.
 This ensures the methods in the Subclass category of `RTObject` are exposed in its subclasses only.
 */
@protocol RTSubclassing <NSObject>

@required

/**
 The name of the class as seen in the REST API.
 */
+ (NSString *)rooftopClassName;

@optional

/**
 Constructs an object of the most specific class known to implement `+rooftopClassName`.

 This method takes care to help `RTObject` subclasses be subclassed themselves.
 For example, `RTUser.+object` returns a `RTUser` by default but will return an
 object of a registered subclass instead if one is known.
 A default implementation is provided by `RTObject` which should always be sufficient.

 @return Returns the object that is instantiated.
 */
+ (instancetype)object;

/**
 Creates a reference to an existing RTObject for use in creating associations between RTObjects.

 Calling `RTObject.dataAvailable` on this object will return `NO`
 until `RTObject.-fetchIfNeeded` has been called. No network request will be made.
 A default implementation is provided by `RTObject` which should always be sufficient.

 @param objectId The object id for the referenced object.

 @return A new `RTObject` without data.
 */
+ (instancetype)objectWithoutDataWithObjectId:(nullable NSString *)objectId RT_SWIFT_UNAVAILABLE;

/**
 Create a query which returns objects of this type.

 A default implementation is provided by `RTObject` which should always be sufficient.
 */
+ (nullable RTQuery *)query;

/**
 Returns a query for objects of this type with a given predicate.

 A default implementation is provided by `RTObject` which should always be sufficient.

 @param predicate The predicate to create conditions from.

 @return An instance of `RTQuery`.

 @see [RTQuery queryWithClassName:predicate:]
 */
+ (nullable RTQuery *)queryWithPredicate:(nullable NSPredicate *)predicate;

/**
 Lets Rooftop know this class should be used to instantiate all objects with class type `rooftopClassName`.

 @warning This method must be called before `Rooftop.+initializeWithConfiguration:`.
 */
+ (void)registerSubclass;

@end

NS_ASSUME_NONNULL_END
