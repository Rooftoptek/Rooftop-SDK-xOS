/**
 * Copyright (c) 2016 - Present, RFTP Technologies.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#import <Foundation/Foundation.h>

#import <Bolts/BFTask.h>

#import <Rooftop/RTConstants.h>

NS_ASSUME_NONNULL_BEGIN

/**
 The `RTRapid` class provides methods for interacting with Rooftop Cloud Functions.
 */
@interface RTRapid : NSObject

/**
 Calls the given cloud function *asynchronously* with the parameters provided.

 @param function The function name to call.
 @param parameters The parameters to send to the function.

 @return The task, that encapsulates the work being done.
 */
+ (BFTask<id> *)invokeInBackground:(NSString *)function
                          withParameters:(nullable NSDictionary *)parameters;

/**
 Calls the given cloud function *asynchronously* with the parameters provided.
 
 @param function The function name to call.
 @param parameters The parameters to send to the function.
 
 @return The task, that encapsulates the work being done.
 */
+ (BFTask<id> *)invokeInBackground:(NSString *)function
                    withParameters:(nullable NSDictionary *)parameters
                   waitForResponse:(BOOL)waitForResponse;

/**
 Calls the given cloud function *asynchronously* with the parameters provided
 and executes the given block when it is done.

 @param function The function name to call.
 @param parameters The parameters to send to the function.
 @param block The block to execute when the function call finished.
 It should have the following argument signature: `^(id result, NSError *error)`.
 */
+ (void)invokeInBackground:(NSString *)function
                  withParameters:(nullable NSDictionary *)parameters
                           block:(nullable RTIdResultBlock)block;

/**
 Calls the given cloud function *asynchronously* with the parameters provided
 and executes the given block when it is done.
 
 @param function The function name to call.
 @param parameters The parameters to send to the function.
 @param block The block to execute when the function call finished.
 It should have the following argument signature: `^(id result, NSError *error)`.
 */
+ (void)invokeInBackground:(NSString *)function
            withParameters:(nullable NSDictionary *)parameters
           waitForResponse:(BOOL)waitForResponse
                     block:(nullable RTIdResultBlock)block;

@end

NS_ASSUME_NONNULL_END
