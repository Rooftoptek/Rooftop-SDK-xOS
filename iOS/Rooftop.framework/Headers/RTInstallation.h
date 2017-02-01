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
#import <Rooftop/RTSubclassing.h>

RT_TV_UNAVAILABLE_WARNING
RT_WATCH_UNAVAILABLE_WARNING

NS_ASSUME_NONNULL_BEGIN

/**
 A Rooftop Framework Installation Object that is a local representation of an
 installation persisted to the Rooftop cloud. This class is a subclass of a
 `RTObject`, and retains the same functionality of a RTObject, but also extends
 it with installation-specific fields and related immutability and validity
 checks.

 A valid `RTInstallation` can only be instantiated via
 `+currentInstallation` because the required identifier fields
 are readonly. The `timeZone` and `badge` fields are also readonly properties which
 are automatically updated to match the device's time zone and application badge
 when the `RTInstallation` is saved, thus these fields might not reflect the
 latest device state if the installation has not recently been saved.

 `RTInstallation` objects which have a valid `deviceToken` and are saved to
 the Rooftop cloud can be used to target push notifications.
 */

RT_TV_UNAVAILABLE RT_WATCH_UNAVAILABLE @interface RTInstallation : RTObject<RTSubclassing>

///--------------------------------------
#pragma mark - Accessing the Current Installation
///--------------------------------------

/**
 Gets the currently-running installation from disk and returns an instance of it.

 If this installation is not stored on disk this method will create a new `RTInstallation`
 with `deviceType` and `installationId` fields set to those of the current installation.

 @result Returns a `RTInstallation` that represents the currently-running installation if it could be loaded from disk, otherwise - `nil`.
 */
+ (nullable instancetype)currentInstallation;

/**
 *Asynchronously* loads the currently-running installation from disk and returns an instance of it.

 If this installation is not stored on disk this method will create a new `RTInstallation`
 with `deviceType` and `installationId` fields set to those of the current installation.

 @result Returns a task that incapsulates the current installation.
 */
+ (BFTask<__kindof RTInstallation *> *)getCurrentInstallationInBackground;

///--------------------------------------
#pragma mark - Installation Properties
///--------------------------------------

/**
 The device type for the `RTInstallation`.
 */
@property (nonatomic, copy, readonly) NSString *deviceType;

/**
 The installationId for the `RTInstallation`.
 */
@property (nonatomic, copy, readonly) NSString *installationId;

/**
 The device token for the `RTInstallation`.
 */
@property (nullable, nonatomic, copy) NSString *deviceToken;

/**
 The badge for the `RTInstallation`.
 */
@property (nonatomic, assign) NSInteger badge;

/**
 The name of the time zone for the `RTInstallation`.
 */
@property (nullable, nonatomic, copy, readonly) NSString *timeZone;

/**
 The channels for the `RTInstallation`.
 */
@property (nullable, nonatomic, copy) NSArray<NSString *> *channels;

/**
 Sets the device token string property from an `NSData`-encoded token.

 @param deviceTokenData A token that identifies the device.
 */
- (void)setDeviceTokenFromData:(nullable NSData *)deviceTokenData;

///--------------------------------------
#pragma mark - Querying for Installations
///--------------------------------------

/**
 Creates a `RTQuery` for `RTInstallation` objects.

 Only the following types of queries are allowed for installations:

 - `[query getObjectWithId:<value>]`
 - `[query whereKey:@"installationId" equalTo:<value>]`
 - `[query whereKey:@"installationId" matchesKey:<key in query> inQuery:<query>]`

 You can add additional query conditions, but one of the above must appear as a top-level `AND` clause in the query.
 */
+ (nullable RTQuery *)query;

@end

NS_ASSUME_NONNULL_END
