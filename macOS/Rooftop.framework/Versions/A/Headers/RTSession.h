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

#import <Rooftop/RTObject.h>
#import <Rooftop/RTSubclassing.h>

NS_ASSUME_NONNULL_BEGIN

@class RTSession;

typedef void(^RTSessionResultBlock)(RTSession *_Nullable session, NSError *_Nullable error);

/**
 `RTSession` is a local representation of a session.
 This class is a subclass of a `RTObject`,
 and retains the same functionality as any other subclass of `RTObject`.
 */
@interface RTSession : RTObject<RTSubclassing>

/**
 The session token string for this session.
 */
@property (nullable, nonatomic, copy, readonly) NSString *sessionToken;

/**
 The session token string for this session.
 */
@property (nullable, nonatomic, copy, readonly) NSString *expiresAt;

/**
 *Asynchronously* fetches a `RTSession` object related to the current user.

 @return A task that is `completed` with an instance of `RTSession` class or is `faulted` if the operation fails.
 */
+ (BFTask<RTSession *> *)getCurrentSessionInBackground;

/**
 *Asynchronously* fetches a `RTSession` object related to the current user.

 @param block The block to execute when the operation completes.
 It should have the following argument signature: `^(RTSession *session, NSError *error)`.
 */
+ (void)getCurrentSessionInBackgroundWithBlock:(nullable RTSessionResultBlock)block;

@end

NS_ASSUME_NONNULL_END
