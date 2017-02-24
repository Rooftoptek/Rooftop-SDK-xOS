/**
 * Copyright (c) 2016 - Present, RFTP Technologies.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#import <Foundation/Foundation.h>

#import <Rooftop/RTConstants.h>
#import <AWSCore/AWSServiceEnum.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The `RooftopMutableClientConfiguration` represents a `RooftopClientConfiguration` object that can be mutated.

 It is only usable during the execution of the block passed to `RooftopClientConfiguration.+configurationWithBlock:`,
 during which time you should set your properties on it, similar to the following:

 ```
 configuration.applicationId = @"<#YOUR APPLICATION ID#>"
 configuration.clientKey = @"<#YOUR CLIENT KEY#>"
 configuration.localDatastoreEnabled = true
 ```
 */
@protocol RooftopMutableClientConfiguration <NSObject>

///--------------------------------------
#pragma mark - Connecting to Rooftop
///--------------------------------------

/**
 The Rooftop.com application id to configure the SDK with.
 */
@property (nullable, nonatomic, copy) NSString *applicationId;

/**
 The Rooftop.com client key to configure the SDK with.
 */
@property (nullable, nonatomic, copy) NSString *clientKey;

@property (nonatomic, assign) AWSRegionType cognitoRegion;
@property (nonatomic, copy) NSString *cognitoPoolId;

/**
 The URL of the server that is being used by the SDK.
 Defaults to `https://api.rooftop.com/1`.

 @note Setting this property to a non-valid URL or `nil` will throw an `NSInvalidArgumentException`.
 */
@property (nonatomic, copy) NSString *server;

///--------------------------------------
#pragma mark - Enabling Local Datastore
///--------------------------------------

/**
 Whether or not to enable pinning in the SDK.

 The default value is `NO`.
 */
@property (nonatomic, assign, getter=isLocalDatastoreEnabled) BOOL localDatastoreEnabled RT_TV_UNAVAILABLE;

///--------------------------------------
#pragma mark - Enabling Extensions Data Sharing
///--------------------------------------

/**
 When set, enables data sharing with an application group identifier.

 After enabling - Local Datastore, `RTUser.+currentUser`, `RTInstallation.+currentInstallation` and all eventually commands
 are going to be available to every application/extension in a group that have the same Rooftop applicationId.
 */
@property (nullable, nonatomic, copy) NSString *applicationGroupIdentifier RT_TV_UNAVAILABLE RT_WATCH_UNAVAILABLE;

/**
 When set, controls the bundle identifier of the parent bundle to connect to.

 @warning This property should only be set from inside an extension environment.
 */
@property (nullable, nonatomic, copy) NSString *containingApplicationBundleIdentifier RT_TV_UNAVAILABLE RT_WATCH_UNAVAILABLE;

///--------------------------------------
#pragma mark - Other Properties
///--------------------------------------

/**
 The maximum number of retry attempts to make upon a failed network request.
 */
@property (nonatomic, assign) NSUInteger networkRetryAttempts;

@end

/**
 The `RooftopClientConfiguration` represents the local configuration of the SDK to connect to the server with.

 These configurations can be stored, copied, and compared, but cannot be safely changed once the SDK is initialized.

 Use this object to construct a configuration for the SDK in your application, and pass it to
 `Rooftop.+initializeWithConfiguration:`.
 */
@interface RooftopConfiguration : NSObject <NSCopying>

///--------------------------------------
#pragma mark - Connecting to Rooftop
///--------------------------------------

/**
 The Rooftop.com application id to configure the SDK with.
 */
@property (nullable, nonatomic, copy, readonly) NSString *applicationId;

/**
 The Rooftop.com client key to configure the SDK with.
 */
@property (nullable, nonatomic, copy, readonly) NSString *clientKey;

@property (nonatomic, assign, readonly) AWSRegionType cognitoRegion;
@property (nonatomic, copy, readonly) NSString *cognitoPoolId;

/**
 The URL of the server that is being used by the SDK.
 Defaults to `https://api.rooftop.com/1`
 */
@property (nonatomic, copy, readonly) NSString *server;

///--------------------------------------
#pragma mark - Enabling Local Datastore
///--------------------------------------

/**
 Whether or not to enable pinning in the SDK.

 The default value is `NO`.
 */
@property (nonatomic, assign, readonly, getter=isLocalDatastoreEnabled) BOOL localDatastoreEnabled;

///--------------------------------------
#pragma mark - Enabling Extensions Data Sharing
///--------------------------------------

/**
 When set, enables data sharing with an application group identifier.

 After enabling - Local Datastore, `RTUser.+currentUser`, `RTInstallation.+currentInstallation` and all eventually
 commands are going to be available to every application/extension in a group that have the same Rooftop applicationId.
 */
@property (nullable, nonatomic, copy, readonly) NSString *applicationGroupIdentifier;

/**
 When set, controls the bundle identifier of the parent bundle to connect to.

 @warning This property should only be set from inside an extension environment.
 */
@property (nullable, nonatomic, copy, readonly) NSString *containingApplicationBundleIdentifier;

///--------------------------------------
#pragma mark - Other Properties
///--------------------------------------

/**
 The maximum number of retry attempts to make upon a failed network request.
 */
@property (nonatomic, assign, readonly) NSUInteger networkRetryAttempts;

///--------------------------------------
#pragma mark - Creating a Configuration
///--------------------------------------

/**
 Create a new SDK configuration object. This will create a temporarily modifiable configuration, and pass it to a block
 to be initialized.
 
 Example usage:
 
 ```
 [RooftopClientConfiguration configurationWithBlock:^(id<RooftopMutableClientConfiguration> configuration) {
     configuration.applicationId = ...;
     configuration.clientKey = ...;
     configuration.localDatastoreEnabled = ...;
 }];
 ```

 @param configurationBlock A block used to modify the created configuration.

 @return A newly created configuration.
 */
+ (instancetype)configurationWithBlock:(void (^)(id<RooftopMutableClientConfiguration> configuration))configurationBlock;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
