/**
 * Copyright (c) 2016 - Present, RFTP Technologies.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#import <Foundation/Foundation.h>

#import <Rooftop/RTObject.h>

@class RTQuery<RTGenericObject : RTObject *>;

NS_ASSUME_NONNULL_BEGIN

/**
 ### Subclassing Notes

 Developers can subclass `RTObject` for a more native object-oriented class structure.
 Strongly-typed subclasses of `RTObject` must conform to the `RTSubclassing` protocol
 and must call `RTSubclassing.+registerSubclass` before `Rooftop.+initializeWithConfiguration:` is called.
 After this it will be returned by `RTQuery` and other `RTObject` factories.

 All methods in `RTSubclassing` except for `RTSubclassing.+rooftopClassName`
 are already implemented in the `RTObject(Subclass)` category.

 Including `RTObject+Subclass.h` in your implementation file provides these implementations automatically.

 Subclasses support simpler initializers, query syntax, and dynamic synthesizers.
 The following shows an example subclass:

     \@interface MYGame : RTObject <RTSubclassing>

     // Accessing this property is the same as objectForKey:@"title"
     @property (nonatomic, copy) NSString *title;

     + (NSString *)rooftopClassName;

     @end


     @implementation MYGame

     @dynamic title;

     + (NSString *)rooftopClassName {
         return @"Game";
     }

     @end


     MYGame *game = [[MYGame alloc] init];
     game.title = @"Bughouse";
     [game saveInBackground];
 */
@interface RTObject (Subclass)

///--------------------------------------
#pragma mark - Methods for Subclasses
///--------------------------------------

/**
 Creates an instance of the registered subclass with this class's `RTSubclassing.+rooftopClassName`.

 This helps a subclass ensure that it can be subclassed itself.
 For example, `[RTUser object]` will return a `MyUser` object if `MyUser` is a registered subclass of `RTUser`.
 For this reason, `[MyClass object]` is preferred to `[[MyClass alloc] init]`.
 This method can only be called on subclasses which conform to `RTSubclassing`.
 */
+ (instancetype)object;

/**
 The following ignore statement is required, as otherwise, every time this is compiled - it produces an `swift_name` unused warning.
 This appears to be a clang itself or ClangImporter issue when imported into Swift.
 */

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wignored-attributes"

/**
 Creates a reference to an existing `RTObject` for use in creating associations between `RTObjects`.

 Calling `dataAvailable` on this object will return `NO` until `-fetchIfNeeded` or `-fetch` has been called.
 This method can only be called on subclasses which conform to `RTSubclassing`.
 A default implementation is provided by `RTObject` which should always be sufficient.
 No network request will be made.

 @param objectId The object id for the referenced object.

 @return An instance of `RTObject` without data.
 */
+ (instancetype)objectWithoutDataWithObjectId:(nullable NSString *)objectId NS_SWIFT_NAME(init(withoutDataWithObjectId:));

#pragma clang diagnostic pop

/**
 Registers an Objective-C class for Rooftop to use for representing a given Rooftop class.

 Once this is called on a `RTObject` subclass, any `RTObject` Rooftop creates with a class name
 that matches `[self rooftopClassName]` will be an instance of subclass.
 This method can only be called on subclasses which conform to `RTSubclassing`.
 A default implementation is provided by `RTObject` which should always be sufficient.
 */
+ (void)registerSubclass;

/**
 Returns a query for objects of type `RTSubclassing.+rooftopClassName`.

 This method can only be called on subclasses which conform to `RTSubclassing`.
 A default implementation is provided by `RTObject` which should always be sufficient.

 @see `RTQuery`
 */
+ (nullable RTQuery *)query;

/**
 Returns a query for objects of type `RTSubclassing.+rooftopClassName` with a given predicate.

 A default implementation is provided by `RTObject` which should always be sufficient.
 @warning This method can only be called on subclasses which conform to `RTSubclassing`.

 @param predicate The predicate to create conditions from.

 @return An instance of `RTQuery`.

 @see `RTQuery.+queryWithClassName:predicate:`
 */
+ (nullable RTQuery *)queryWithPredicate:(nullable NSPredicate *)predicate;

@end

/*!
 This protocol exists ONLY so that, if you absolutely need it, you can perform manual subclass registration
 via `[Subclass registerSubclass]`. Note that any calls to `registerSubclass` must happen after rooftop has been
 initialized already. This should only ever be needed in the scenario where you may be dynamically creation new 
 Objective-C classes for rooftop objects, or you are doing conditional subclass registration (e.g. only register class A 
 if config setting 'foo' is defined, otherwise register B).
 */
@protocol RTSubclassingSkipAutomaticRegistration <RTSubclassing>

@end

NS_ASSUME_NONNULL_END
