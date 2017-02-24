/**
 * Copyright (c) 2016 - Present, RFTP Technologies.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#import <Rooftop/RTRapid.h>
#import <Rooftop/RTConstants.h>

NS_ASSUME_NONNULL_BEGIN

/**
 This category lists all methods of `RTRapid` class that are synchronous, but have asynchronous counterpart,
 Calling one of these synchronous methods could potentially block the current thread for a large amount of time,
 since it might be fetching from network or saving/loading data from disk.
 */
@interface RTRapid (Synchronous)

/**
 Calls the given cloud function *synchronously* with the parameters provided.

 @param function The function name to call.
 @param parameters The parameters to send to the function.

 @return The response from the cloud function.
 */
+ (nullable id)invoke:(NSString *)function withParameters:(nullable NSDictionary *)parameters RT_SWIFT_UNAVAILABLE;

/**
 Calls the given cloud function *synchronously* with the parameters provided and
 sets the error if there is one.

 @param function The function name to call.
 @param parameters The parameters to send to the function.
 @param error Pointer to an `NSError` that will be set if necessary.

 @return The response from the cloud function.
 This result could be a `NSDictionary`, an `NSArray`, `NSNumber` or `NSString`.
 */
+ (nullable id)invoke:(NSString *)function withParameters:(nullable NSDictionary *)parameters error:(NSError **)error;

@end

NS_ASSUME_NONNULL_END
