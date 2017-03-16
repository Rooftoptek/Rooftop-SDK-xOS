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
#import <Rooftop/RTACL.h>

NS_ASSUME_NONNULL_BEGIN

/**
 `RTFile` representes a file of binary data stored in S3.
 This can be a image, video, or anything else that an application needs to reference in a non-relational way.
 */
@interface RTFile : NSObject

///--------------------------------------
#pragma mark - File Properties
///--------------------------------------

/**
 The name of the file.

 The filename. The name cannot be changed once data has been assigned to the file
 or if the file has already been uploaded (it should be set first for new files)
 */
@property (nonatomic, copy) NSString *name;

/**
 The mime type of the file.
 
 After the file is saved, the mime type cannot be changed.
 */
@property (nonatomic, copy) NSString *mimeType;

/**
 The url of the file. Available only after the file is saved.
 */
@property (nullable, nonatomic, copy, readonly) NSString *url;

/**
 True if the file needs saving (data or ACL changed)
 */
@property (nonatomic, assign, readonly, getter=isDirty) BOOL dirty;

/**
 True if the data is available locally, false if it needs to be downloaded.
 */
@property (nonatomic, assign, readonly, getter=isDataAvailable) BOOL dataAvailable;

/**
 Privacy of the file.
 
 When set to true, the file will be saved in the private S3 folder.
 It has no effect on saved files
 */
- (void)setPrivate:(BOOL)private;

/**
 ACL of the file.
 
 Controls who can delete or overwrite the file.
 It has no effect on saved files
 */
- (void)setACL:(RTACL *)ACL;

///--------------------------------------
#pragma mark - File content
///--------------------------------------

/**
 Set the data to be saved from a data object.
 */
- (void)setContentFromData:(NSData *)data;

/**
 Set the data to be saved from a file at given path.
 */
- (void)setContentFromPath:(NSString *)contentPath;

///--------------------------------------
#pragma mark - Storing Data with Rooftop
///--------------------------------------


/**
 Saves the file *asynchronously*.

 @return The task, that encapsulates the work being done.
 */
- (BFTask<NSNumber *> *)saveInBackground;

/**
 Saves the file *asynchronously*

 @param progressBlock The block should have the following argument signature: `^(int percentDone)`

 @return The task, that encapsulates the work being done.
 */
- (BFTask<NSNumber *> *)saveInBackgroundWithProgressBlock:(nullable RTProgressBlock)progressBlock;

/**
 Saves the file *asynchronously* and executes the given block.

 @param block The block should have the following argument signature: `^(BOOL succeeded, NSError *error)`.
 */
- (void)saveInBackgroundWithBlock:(nullable RTBooleanResultBlock)block;

/**
 Saves the file *asynchronously* and executes the given block.

 This method will execute the progressBlock periodically with the percent progress.
 `progressBlock` will get called with `100` before `resultBlock` is called.

 @param block The block should have the following argument signature: `^(BOOL succeeded, NSError *error)`
 @param progressBlock The block should have the following argument signature: `^(int percentDone)`
 */
- (void)saveInBackgroundWithBlock:(nullable RTBooleanResultBlock)block
                    progressBlock:(nullable RTProgressBlock)progressBlock;

///--------------------------------------
#pragma mark - Getting File Data
///--------------------------------------

/**
 This method is like `-getData` but it fetches asynchronously to avoid blocking the current thread.

 @see getData

 @return The task, that encapsulates the work being done.
 */
- (BFTask<NSData *> *)getDataInBackground;

/**
 This method is like `-getData` but it fetches asynchronously to avoid blocking the current thread.

 This can help applications with many large files avoid memory warnings.

 @see getData

 @param progressBlock The block should have the following argument signature: ^(int percentDone)

 @return The task, that encapsulates the work being done.
 */
- (BFTask<NSData *> *)getDataInBackgroundWithProgressBlock:(nullable RTProgressBlock)progressBlock;

/**
 This method is like `-getDataInBackground` but avoids ever holding the entire `RTFile` contents in memory at once.

 This can help applications with many large files avoid memory warnings.

 @return The task, that encapsulates the work being done.
 */
- (BFTask<NSInputStream *> *)getDataStreamInBackground;

/**
 This method is like `-getDataStreamInBackground`, but yields a live-updating stream.

 Instead of `-getDataStream`, which yields a stream that can be read from only after the request has
 completed, this method gives you a stream directly written to by the HTTP session. As this stream is not pre-buffered,
 it is strongly advised to use the `NSStreamDelegate` methods, in combination with a run loop, to consume the data in
 the stream, to do proper async file downloading.

 @note You MUST open this stream before reading from it.
 @note Do NOT call `waitUntilFinished` on this task from the main thread. It may result in a deadlock.

 @return A task that produces a *live* stream that is being written to with the data from the server.
 */
- (BFTask<NSInputStream *> *)getDataDownloadStreamInBackground;

/**
 This method is like `-getDataInBackground` but avoids
 ever holding the entire `RTFile` contents in memory at once.

 This can help applications with many large files avoid memory warnings.
 @param progressBlock The block should have the following argument signature: ^(int percentDone)

 @return The task, that encapsulates the work being done.
 */
- (BFTask<NSInputStream *> *)getDataStreamInBackgroundWithProgressBlock:(nullable RTProgressBlock)progressBlock;

/**
 This method is like `-getDataStreamInBackgroundWithProgressBlock:`, but yields a live-updating stream.

 Instead of `-getDataStream`, which yields a stream that can be read from only after the request has
 completed, this method gives you a stream directly written to by the HTTP session. As this stream is not pre-buffered,
 it is strongly advised to use the `NSStreamDelegate` methods, in combination with a run loop, to consume the data in
 the stream, to do proper async file downloading.

 @note You MUST open this stream before reading from it.
 @note Do NOT call `waitUntilFinished` on this task from the main thread. It may result in a deadlock.

 @param progressBlock The block should have the following argument signature: `^(int percentDone)`

 @return A task that produces a *live* stream that is being written to with the data from the server.
 */
- (BFTask<NSInputStream *> *)getDataDownloadStreamInBackgroundWithProgressBlock:(nullable RTProgressBlock)progressBlock;

/**
 *Asynchronously* gets the data from cache if available or fetches its contents from the network.

 @param block The block should have the following argument signature: `^(NSData *result, NSError *error)`
 */
- (void)getDataInBackgroundWithBlock:(nullable RTDataResultBlock)block;

/**
 This method is like `-getDataInBackgroundWithBlock:` but avoids ever holding the entire `RTFile` contents in memory at once.

 This can help applications with many large files avoid memory warnings.

 @param block The block should have the following argument signature: `(NSInputStream *result, NSError *error)`
 */
- (void)getDataStreamInBackgroundWithBlock:(nullable RTDataStreamResultBlock)block;

/**
 *Asynchronously* gets the data from cache if available or fetches its contents from the network.

 This method will execute the progressBlock periodically with the percent progress.
 `progressBlock` will get called with `100` before `resultBlock` is called.

 @param resultBlock The block should have the following argument signature: ^(NSData *result, NSError *error)
 @param progressBlock The block should have the following argument signature: ^(int percentDone)
 */
- (void)getDataInBackgroundWithBlock:(nullable RTDataResultBlock)resultBlock
                       progressBlock:(nullable RTProgressBlock)progressBlock;

/**
 This method is like `-getDataInBackgroundWithBlock:progressBlock:` but avoids
 ever holding the entire `RTFile` contents in memory at once.

 This can help applications with many large files avoid memory warnings.

 @param resultBlock The block should have the following argument signature: `^(NSInputStream *result, NSError *error)`.
 @param progressBlock The block should have the following argument signature: `^(int percentDone)`.
 */
- (void)getDataStreamInBackgroundWithBlock:(nullable RTDataStreamResultBlock)resultBlock
                             progressBlock:(nullable RTProgressBlock)progressBlock;

/**
 *Asynchronously* gets the file path for file from cache if available or fetches its contents from the network.

 @note The file path may change between versions of SDK.
 @note If you overwrite the contents of the file at returned path it will persist those change
 until the file cache is cleared.

 @return The task, with the result set to `NSString` representation of a file path.
 */
- (BFTask<NSString *> *)getFilePathInBackground;

/**
 *Asynchronously* gets the file path for file from cache if available or fetches its contents from the network.

 @note The file path may change between versions of SDK.
 @note If you overwrite the contents of the file at returned path it will persist those change
 until the file cache is cleared.

 @param progressBlock The block should have the following argument signature: `^(int percentDone)`.

 @return The task, with the result set to `NSString` representation of a file path.
 */
- (BFTask<NSString *> *)getFilePathInBackgroundWithProgressBlock:(nullable RTProgressBlock)progressBlock;

/**
 *Asynchronously* gets the file path for file from cache if available or fetches its contents from the network.

 @note The file path may change between versions of SDK.
 @note If you overwrite the contents of the file at returned path it will persist those change
 until the file cache is cleared.

 @param block The block should have the following argument signature: `^(NSString *filePath, NSError *error)`.
 */
- (void)getFilePathInBackgroundWithBlock:(nullable RTFilePathResultBlock)block;

/**
 *Asynchronously* gets the file path for file from cache if available or fetches its contents from the network.

 @note The file path may change between versions of SDK.
 @note If you overwrite the contents of the file at returned path it will persist those change
 until the file cache is cleared.

 @param block The block should have the following argument signature: `^(NSString *filePath, NSError *error)`.
 @param progressBlock The block should have the following argument signature: `^(int percentDone)`.
 */
- (void)getFilePathInBackgroundWithBlock:(nullable RTFilePathResultBlock)block
                           progressBlock:(nullable RTProgressBlock)progressBlock;

///--------------------------------------
#pragma mark - Deleting a File
///--------------------------------------

/**
 Deletes the file *asynchronously*.
 
 @return The task, that encapsulates the work being done.
 */
- (BFTask *)deleteInBackground;

/**
 Deletes the file *asynchronously* and executes the given block.
 
 @param block The block should have the following argument signature: `^(BOOL succeeded, NSError *error)`.
 */
- (void)deleteInBackgroundWithBlock:(nullable RTBooleanResultBlock)block;

///--------------------------------------
#pragma mark - Interrupting a Transfer
///--------------------------------------

/**
 Cancels the current request (upload or download of file).
 */
- (void)cancel;

///--------------------------------------
#pragma mark - Cache
///--------------------------------------

/**
 Clears all cached data for this file.

 @return The task, with the result set to `nil` if the operation succeeds.
 */
- (BFTask *)clearCachedDataInBackground;

/**
 Clears all cached data for all downloaded files.

 @return The task, with the result set to `nil` if the operation succeeds.
 */
+ (BFTask *)clearAllCachedDataInBackground;

@end

NS_ASSUME_NONNULL_END
