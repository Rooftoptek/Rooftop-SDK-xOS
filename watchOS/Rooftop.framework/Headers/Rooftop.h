/**
 * Copyright (c) 2016 - Present, RFTP Technologies.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

//#define Rooftop Rooftop
//#define RooftopClientConfiguration RooftopClientConfiguration

#import <Rooftop/RooftopConfiguration.h>
#import <Rooftop/RTACL.h>
#import <Rooftop/RTAnonymousUtils.h>
#import <Rooftop/RTRapid.h>
#import <Rooftop/RTRapid+Synchronous.h>
#import <Rooftop/RTConstants.h>
#import <Rooftop/RTFile.h>
#import <Rooftop/RTFile+Synchronous.h>
#import <Rooftop/RTGeoPoint.h>
#import <Rooftop/RTObject.h>
#import <Rooftop/RTObject+Subclass.h>
#import <Rooftop/RTObject+Synchronous.h>
#import <Rooftop/RTQuery.h>
#import <Rooftop/RTQuery+Synchronous.h>
#import <Rooftop/RTRelation.h>
#import <Rooftop/RTRole.h>
#import <Rooftop/RTSession.h>
#import <Rooftop/RTSubclassing.h>
#import <Rooftop/RTUser.h>
#import <Rooftop/RTUser+Synchronous.h>
#import <Rooftop/RTUserAuthenticationDelegate.h>

#if TARGET_OS_IOS

#import <Rooftop/RTInstallation.h>
#import <Rooftop/RTNetworkActivityIndicatorManager.h>

#elif RT_TARGET_OS_OSX

#import <Rooftop/RTInstallation.h>

#elif TARGET_OS_TV


#endif

NS_ASSUME_NONNULL_BEGIN

/**
 The `Rooftop` class contains static functions that handle global configuration for the Rooftop framework.
 */
@interface Rooftop : NSObject

///--------------------------------------
#pragma mark - Connecting to Rooftop
///--------------------------------------

/**
 Sets the configuration to be used for the Rooftop SDK.

 @note Re-setting the configuration after having previously sent requests through the SDK results in undefined behavior.

 @param configuration The new configuration to set for the SDK.
 */
+ (void)initializeWithConfiguration:(RooftopConfiguration *)configuration;

/**
 Gets the current configuration in use by the Rooftop SDK.

 @return The current configuration in use by the SDK. Returns nil if the SDK has not been initialized yet.
 */
+ (nullable RooftopConfiguration *)currentConfiguration;

/**
 The current application id that was used to configure Rooftop framework.
 */
+ (NSString *)getApplicationId;

/**
 The current client key that was used to configure Rooftop framework.
 */
+ (nullable NSString *)getClientKey;

///--------------------------------------
#pragma mark - Enabling Local Datastore
///--------------------------------------

/**
 Enable pinning in your application. This must be called before your application can use
 pinning. The recommended way is to call this method before `+initializeWithConfiguration:`.
 */
+ (void)enableLocalDatastore RT_TV_UNAVAILABLE;

/**
 Flag that indicates whether Local Datastore is enabled.

 @return `YES` if Local Datastore is enabled, otherwise `NO`.
 */
+ (BOOL)isLocalDatastoreEnabled RT_TV_UNAVAILABLE;

///--------------------------------------
#pragma mark - Enabling Extensions Data Sharing
///--------------------------------------

/**
 Enables data sharing with an application group identifier.

 After enabling - Local Datastore, `RTUser.+currentUser`, `RTInstallation.+currentInstallation` and all eventually commands
 are going to be available to every application/extension in a group that have the same Rooftop applicationId.

 @warning This method is required to be called before `+initializeWithConfiguration:`.

 @param groupIdentifier Application Group Identifier to share data with.
 */
+ (void)enableDataSharingWithApplicationGroupIdentifier:(NSString *)groupIdentifier RT_EXTENSION_UNAVAILABLE("Use `enableDataSharingWithApplicationGroupIdentifier:containingApplication:`.") RT_WATCH_UNAVAILABLE RT_TV_UNAVAILABLE;

/**
 Enables data sharing with an application group identifier.

 After enabling - Local Datastore, `RTUser.+currentUser`, `RTInstallation.+currentInstallation` and all eventually commands
 are going to be available to every application/extension in a group that have the same Rooftop applicationId.

 @warning This method is required to be called before `+initializeWithConfiguration:`.
 This method can only be used by application extensions.

 @param groupIdentifier Application Group Identifier to share data with.
 @param bundleIdentifier Bundle identifier of the containing application.
 */
+ (void)enableDataSharingWithApplicationGroupIdentifier:(NSString *)groupIdentifier
                                  containingApplication:(NSString *)bundleIdentifier RT_WATCH_UNAVAILABLE RT_TV_UNAVAILABLE;

/**
 Application Group Identifier for Data Sharing.

 @return `NSString` value if data sharing is enabled, otherwise `nil`.
 */
+ (NSString *)applicationGroupIdentifierForDataSharing RT_WATCH_UNAVAILABLE RT_TV_UNAVAILABLE;

/**
 Containing application bundle identifier for Data Sharing.

 @return `NSString` value if data sharing is enabled, otherwise `nil`.
 */
+ (NSString *)containingApplicationBundleIdentifierForDataSharing RT_WATCH_UNAVAILABLE RT_TV_UNAVAILABLE;

///--------------------------------------
#pragma mark - Logging
///--------------------------------------

/**
 Sets the level of logging to display.

 By default:
 - If running inside an app that was downloaded from iOS App Store - it is set to `RTLogLevelNone`
 - All other cases - it is set to `RTLogLevelWarning`

 @param logLevel Log level to set.
 @see RTLogLevel
 */
+ (void)setLogLevel:(RTLogLevel)logLevel;

/**
 Log level that will be displayed.

 By default:

 - If running inside an app that was downloaded from iOS App Store - it is set to `RTLogLevelNone`
 - All other cases - it is set to `RTLogLevelWarning`

 @return A `RTLogLevel` value.
 @see RTLogLevel
 */
+ (RTLogLevel)logLevel;

@end

NS_ASSUME_NONNULL_END
