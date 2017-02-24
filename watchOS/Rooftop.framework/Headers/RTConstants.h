/**
 * Copyright (c) 2016 - Present, RFTP Technologies.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#import <Foundation/Foundation.h>

///--------------------------------------
#pragma mark - SDK Version
///--------------------------------------

#define RT_VERSION @"0.5.0"

///--------------------------------------
#pragma mark - Platform
///--------------------------------------

extern NSString *const _Nonnull kRTDeviceType;

///--------------------------------------
#pragma mark - Cache Policies
///--------------------------------------

/**
 `RTCachePolicy` specifies different caching policies that could be used with `RTQuery`.

 This lets you show data when the user's device is offline,
 or when the app has just started and network requests have not yet had time to complete.
 Rooftop takes care of automatically flushing the cache when it takes up too much space.

 @warning Cache policy could only be set when Local Datastore is not enabled.

 @see RTQuery
 */
typedef NS_ENUM(uint8_t, RTCachePolicy) {
    /**
     The query does not load from the cache or save results to the cache.
     This is the default cache policy.
     */
    kRTCachePolicyIgnoreCache = 0,
    /**
     The query only loads from the cache, ignoring the network.
     If there are no cached results, this causes a `NSError` with `kRTErrorCacheMiss` code.
     */
    kRTCachePolicyCacheOnly,
    /**
     The query does not load from the cache, but it will save results to the cache.
     */
    kRTCachePolicyNetworkOnly,
    /**
     The query first tries to load from the cache, but if that fails, it loads results from the network.
     If there are no cached results, this causes a `NSError` with `kRTErrorCacheMiss` code.
     */
    kRTCachePolicyCacheElseNetwork,
    /**
     The query first tries to load from the network, but if that fails, it loads results from the cache.
     If there are no cached results, this causes a `NSError` with `kRTErrorCacheMiss` code.
     */
    kRTCachePolicyNetworkElseCache,
    /**
     The query first loads from the cache, then loads from the network.
     The callback will be called twice - first with the cached results, then with the network results.
     Since it returns two results at different times, this cache policy cannot be used with synchronous or task methods.
     */
    kRTCachePolicyCacheThenNetwork
};

///--------------------------------------
#pragma mark - Logging Levels
///--------------------------------------

/**
 `RTLogLevel` enum specifies different levels of logging that could be used to limit or display more messages in logs.

 @see `Rooftop.+setLogLevel:`
 @see `Rooftop.+logLevel`
 */
typedef NS_ENUM(uint8_t, RTLogLevel) {
    /**
     Log level that disables all logging.
     */
    RTLogLevelNone = 0,
    /**
     Log level that if set is going to output error messages to the log.
     */
    RTLogLevelError = 1,
    /**
     Log level that if set is going to output the following messages to log:
     - Errors
     - Warnings
     */
    RTLogLevelWarning = 2,
    /**
     Log level that if set is going to output the following messages to log:
     - Errors
     - Warnings
     - Informational messages
     */
    RTLogLevelInfo = 3,
    /**
     Log level that if set is going to output the following messages to log:
     - Errors
     - Warnings
     - Informational messages
     - Debug messages
     */
    RTLogLevelDebug = 4
};

///--------------------------------------
#pragma mark - Errors
///--------------------------------------

/**
 Error domain used for all `NSError`s in the SDK.
 */
extern NSString *const _Nonnull RTRooftopErrorDomain;

/**
 `RTErrorCode` enum contains all custom error codes that are used as `code` for `NSError` for callbacks on all classes.

 These codes are used when `domain` of `NSError` that you receive is set to `RTRooftopErrorDomain`.
 */
typedef NS_ENUM(NSInteger, RTErrorCode) {
    /**
     Internal server error. No information available.
     */
    kRTErrorInternalServer = 1,
    /**
     The connection to the Rooftop servers failed.
     */
    kRTErrorConnectionFailed = 100,
    /**
     Object doesn't exist, or has an incorrect password.
     */
    kRTErrorObjectNotFound = 101,
    /**
     You tried to find values matching a datatype that doesn't
     support exact database matching, like an array or a dictionary.
     */
    kRTErrorInvalidQuery = 102,
    /**
     Missing or invalid classname. Classnames are case-sensitive.
     They must start with a letter, and `a-zA-Z0-9_` are the only valid characters.
     */
    kRTErrorInvalidClassName = 103,
    /**
     Missing object id.
     */
    kRTErrorMissingObjectId = 104,
    /**
     Invalid key name. Keys are case-sensitive.
     They must start with a letter, and `a-zA-Z0-9_` are the only valid characters.
     */
    kRTErrorInvalidKeyName = 105,
    /**
     Malformed pointer. Pointers must be arrays of a classname and an object id.
     */
    kRTErrorInvalidPointer = 106,
    /**
     Malformed json object. A json dictionary is expected.
     */
    kRTErrorInvalidJSON = 107,
    /**
     Tried to access a feature only available internally.
     */
    kRTErrorCommandUnavailable = 108,
    /**
     Field set to incorrect type.
     */
    kRTErrorIncorrectType = 111,
    /**
     Invalid channel name. A channel name is either an empty string (the broadcast channel)
     or contains only `a-zA-Z0-9_` characters and starts with a letter.
     */
    kRTErrorInvalidChannelName = 112,
    /**
     Invalid device token.
     */
    kRTErrorInvalidDeviceToken = 114,
    /**
     Push is misconfigured. See details to find out how.
     */
    kRTErrorPushMisconfigured = 115,
    /**
     The object is too large.
     */
    kRTErrorObjectTooLarge = 116,
    /**
     That operation isn't allowed for clients.
     */
    kRTErrorOperationForbidden = 119,
    /**
     The results were not found in the cache.
     */
    kRTErrorCacheMiss = 120,
    /**
     Keys in `NSDictionary` values may not include `$` or `.`.
     */
    kRTErrorInvalidNestedKey = 121,
    /**
     Invalid file name.
     A file name can contain only `a-zA-Z0-9_.` characters and should be between 1 and 36 characters.
     */
    kRTErrorInvalidFileName = 122,
    /**
     Invalid ACL. An ACL with an invalid format was saved. This should not happen if you use `RTACL`.
     */
    kRTErrorInvalidACL = 123,
    /**
     The request timed out on the server. Typically this indicates the request is too expensive.
     */
    kRTErrorTimeout = 124,
    /**
     The email address was invalid.
     */
    kRTErrorInvalidEmailAddress = 125,
    /**
     A unique field was given a value that is already taken.
     */
    kRTErrorDuplicateValue = 137,
    /**
     Role's name is invalid.
     */
    kRTErrorInvalidRoleName = 139,
    /**
     Exceeded an application quota. Upgrade to resolve.
     */
    kRTErrorExceededQuota = 140,
    /**
     Cloud Code script had an error.
     */
    kRTScriptError = 141,
    /**
     Cloud Code validation failed.
     */
    kRTValidationError = 142,
    /**
     Product purchase receipt is missing.
     */
    kRTErrorReceiptMissing = 143,
    /**
     Product purchase receipt is invalid.
     */
    kRTErrorInvalidPurchaseReceipt = 144,
    /**
     Payment is disabled on this device.
     */
    kRTErrorPaymentDisabled = 145,
    /**
     The product identifier is invalid.
     */
    kRTErrorInvalidProductIdentifier = 146,
    /**
     The product is not found in the App Store.
     */
    kRTErrorProductNotFoundInAppStore = 147,
    /**
     The Apple server response is not valid.
     */
    kRTErrorInvalidServerResponse = 148,
    /**
     Product fails to download due to file system error.
     */
    kRTErrorProductDownloadFileSystemFailure = 149,
    /**
     Fail to convert data to image.
     */
    kRTErrorInvalidImageData = 150,
    /**
     Unsaved file.
     */
    kRTErrorUnsavedFile = 151,
    /**
     Fail to delete file.
     */
    kRTErrorFileDeleteFailure = 153,
    /**
     Application has exceeded its request limit.
     */
    kRTErrorRequestLimitExceeded = 155,
    /**
     Invalid event name.
     */
    kRTErrorInvalidEventName = 160,
    /**
     Username is missing or empty.
     */
    kRTErrorUsernameMissing = 200,
    /**
     Password is missing or empty.
     */
    kRTErrorUserPasswordMissing = 201,
    /**
     Username has already been taken.
     */
    kRTErrorUsernameTaken = 202,
    /**
     Email has already been taken.
     */
    kRTErrorUserEmailTaken = 203,
    /**
     The email is missing, and must be specified.
     */
    kRTErrorUserEmailMissing = 204,
    /**
     A user with the specified email was not found.
     */
    kRTErrorUserWithEmailNotFound = 205,
    /**
     The user cannot be altered by a client without the session.
     */
    kRTErrorUserCannotBeAlteredWithoutSession = 206,
    /**
     Users can only be created through sign up.
     */
    kRTErrorUserCanOnlyBeCreatedThroughSignUp = 207,
    /**
     An existing Facebook account already linked to another user.
     */
    kRTErrorFacebookAccountAlreadyLinked = 208,
    /**
     An existing account already linked to another user.
     */
    kRTErrorAccountAlreadyLinked = 208,
    /**
     Error code indicating that the current session token is invalid.
     */
    kRTErrorInvalidSessionToken = 209,
    kRTErrorUserIdMismatch = 209,
    /**
     Facebook id missing from request.
     */
    kRTErrorFacebookIdMissing = 250,
    /**
     Linked id missing from request.
     */
    kRTErrorLinkedIdMissing = 250,
    /**
     Invalid Facebook session.
     */
    kRTErrorFacebookInvalidSession = 251,
    /**
     Invalid linked session.
     */
    kRTErrorInvalidLinkedSession = 251,
};

///--------------------------------------
#pragma mark - Blocks
///--------------------------------------

@class RTObject;
@class RTUser;

typedef void (^RTBooleanResultBlock)(BOOL succeeded, NSError *_Nullable error);
typedef void (^RTIntegerResultBlock)(int number, NSError *_Nullable error);
typedef void (^RTArrayResultBlock)(NSArray *_Nullable objects, NSError *_Nullable error);
typedef void (^RTObjectResultBlock)(RTObject *_Nullable object,  NSError *_Nullable error);
typedef void (^RTSetResultBlock)(NSSet *_Nullable channels, NSError *_Nullable error);
typedef void (^RTUserResultBlock)(RTUser *_Nullable user, NSError *_Nullable error);
typedef void (^RTDataResultBlock)(NSData *_Nullable data, NSError *_Nullable error);
typedef void (^RTDataStreamResultBlock)(NSInputStream *_Nullable stream, NSError *_Nullable error);
typedef void (^RTFilePathResultBlock)(NSString *_Nullable filePath, NSError *_Nullable error);
typedef void (^RTStringResultBlock)(NSString *_Nullable string, NSError *_Nullable error);
typedef void (^RTIdResultBlock)(_Nullable id object, NSError *_Nullable error);
typedef void (^RTProgressBlock)(int percentDone);

///--------------------------------------
#pragma mark - Network Notifications
///--------------------------------------

/**
 The name of the notification that is going to be sent before any URL request is sent.
 */
extern NSString *const _Nonnull RTNetworkWillSendURLRequestNotification;

/**
 The name of the notification that is going to be sent after any URL response is received.
 */
extern NSString *const _Nonnull RTNetworkDidReceiveURLResponseNotification;

/**
 The key of request(NSURLRequest) in the userInfo dictionary of a notification.
 @note This key is populated in userInfo, only if `RTLogLevel` on `Rooftop` is set to `RTLogLevelDebug`.
 */
extern NSString *const _Nonnull RTNetworkNotificationURLRequestUserInfoKey;

/**
 The key of response(NSHTTPURLResponse) in the userInfo dictionary of a notification.
 @note This key is populated in userInfo, only if `RTLogLevel` on `Rooftop` is set to `RTLogLevelDebug`.
 */
extern NSString *const _Nonnull RTNetworkNotificationURLResponseUserInfoKey;

/**
 The key of repsonse body (usually `NSString` with JSON) in the userInfo dictionary of a notification.
 @note This key is populated in userInfo, only if `RTLogLevel` on `Rooftop` is set to `RTLogLevelDebug`.
 */
extern NSString *const _Nonnull RTNetworkNotificationURLResponseBodyUserInfoKey;


///--------------------------------------
#pragma mark - Deprecated Macros
///--------------------------------------

#ifndef RT_DEPRECATED
#  ifdef __deprecated_msg
#    define RT_DEPRECATED(_MSG) __deprecated_msg(_MSG)
#  else
#    ifdef __deprecated
#      define RT_DEPRECATED(_MSG) __attribute__((deprecated))
#    else
#      define RT_DEPRECATED(_MSG)
#    endif
#  endif
#endif

///--------------------------------------
#pragma mark - Extensions Macros
///--------------------------------------

#ifndef RT_EXTENSION_UNAVAILABLE
#  if RT_IOS_ONLY
#    ifdef NS_EXTENSION_UNAVAILABLE_IOS
#      define RT_EXTENSION_UNAVAILABLE(_msg) NS_EXTENSION_UNAVAILABLE_IOS(_msg)
#    else
#      define RT_EXTENSION_UNAVAILABLE(_msg)
#    endif
#  else
#    ifdef NS_EXTENSION_UNAVAILABLE_MAC
#      define RT_EXTENSION_UNAVAILABLE(_msg) NS_EXTENSION_UNAVAILABLE_MAC(_msg)
#    else
#      define RT_EXTENSION_UNAVAILABLE(_msg)
#    endif
#  endif
#endif

///--------------------------------------
#pragma mark - Swift Macros
///--------------------------------------

#ifndef RT_SWIFT_UNAVAILABLE
#  ifdef NS_SWIFT_UNAVAILABLE
#    define RT_SWIFT_UNAVAILABLE NS_SWIFT_UNAVAILABLE("")
#  else
#    define RT_SWIFT_UNAVAILABLE
#  endif
#endif

///--------------------------------------
#pragma mark - Platform Availability Defines
///--------------------------------------

#ifndef TARGET_OS_IOS
#  define TARGET_OS_IOS TARGET_OS_IPHONE
#endif
#ifndef TARGET_OS_WATCH
#  define TARGET_OS_WATCH 0
#endif
#ifndef TARGET_OS_TV
#  define TARGET_OS_TV 0
#endif

#ifndef RT_TARGET_OS_OSX
#  define RT_TARGET_OS_OSX (TARGET_OS_MAC && !TARGET_OS_IOS && !TARGET_OS_WATCH && !TARGET_OS_TV)
#endif

///--------------------------------------
#pragma mark - Avaiability Macros
///--------------------------------------

#ifndef RT_IOS_UNAVAILABLE
#  ifdef __IOS_UNAVILABLE
#    define RT_IOS_UNAVAILABLE __IOS_UNAVAILABLE
#  else
#    define RT_IOS_UNAVAILABLE
#  endif
#endif

#ifndef RT_IOS_UNAVAILABLE_WARNING
#  if TARGET_OS_IOS
#    define RT_IOS_UNAVAILABLE_WARNING _Pragma("GCC warning \"This file is unavailable on iOS.\"")
#  else
#    define RT_IOS_UNAVAILABLE_WARNING
#  endif
#endif

#ifndef RT_OSX_UNAVAILABLE
#  if RT_TARGET_OS_OSX
#    define RT_OSX_UNAVAILABLE __OSX_UNAVAILABLE
#  else
#    define RT_OSX_UNAVAILABLE
#  endif
#endif

#ifndef RT_OSX_UNAVAILABLE_WARNING
#  if RT_TARGET_OS_OSX
#    define RT_OSX_UNAVAILABLE_WARNING _Pragma("GCC warning \"This file is unavailable on OS X.\"")
#  else
#    define RT_OSX_UNAVAILABLE_WARNING
#  endif
#endif

#ifndef RT_WATCH_UNAVAILABLE
#  ifdef __WATCHOS_UNAVAILABLE
#    define RT_WATCH_UNAVAILABLE __WATCHOS_UNAVAILABLE
#  else
#    define RT_WATCH_UNAVAILABLE
#  endif
#endif

#ifndef RT_WATCH_UNAVAILABLE_WARNING
#  if TARGET_OS_WATCH
#    define RT_WATCH_UNAVAILABLE_WARNING _Pragma("GCC warning \"This file is unavailable on watchOS.\"")
#  else
#    define RT_WATCH_UNAVAILABLE_WARNING
#  endif
#endif

#ifndef RT_TV_UNAVAILABLE
#  ifdef __TVOS_PROHIBITED
#    define RT_TV_UNAVAILABLE __TVOS_PROHIBITED
#  else
#    define RT_TV_UNAVAILABLE
#  endif
#endif

#ifndef RT_TV_UNAVAILABLE_WARNING
#  if TARGET_OS_TV
#    define RT_TV_UNAVAILABLE_WARNING _Pragma("GCC warning \"This file is unavailable on tvOS.\"")
#  else
#    define RT_TV_UNAVAILABLE_WARNING
#  endif
#endif
