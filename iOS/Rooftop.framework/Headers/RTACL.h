/**
 * Copyright (c) 2016 - Present, RFTP Technologies.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class RTRole;
@class RTUser;

/**
 The `RTACL` class is used to control which users can access or modify a particular object.
 Each `RTObject` can have its own `RTACL`. You can grant read and write permissions separately to specific users,
 to groups of users that belong to roles, or you can grant permissions to "the public" so that,
 for example, any user could read a particular object but only a particular set of users could write to that object.
 */

typedef enum {
    PublicRead      = 1 << 0,
    PublicUpdate    = 1 << 1,
    PublicDelete    = 1 << 2,
} Permission;


@interface RTACL : NSObject <NSCopying, NSCoding>

///--------------------------------------
#pragma mark - Creating an ACL
///--------------------------------------

/**
 Creates an ACL with no permissions granted.

 @return Returns a new `RTACL`.
 */
+ (instancetype)ACL;

/**
 Creates an ACL where only the provided user has access.

 @param user The user to assign access.
 */
+ (instancetype)ACLWithUser:(RTUser *)user;

///--------------------------------------
#pragma mark - Controlling Public Access
///--------------------------------------

@property (assign, nonatomic) Permission permissions;

/**
 Controls whether the public is allowed to read this object.
 */
@property (nonatomic, assign, getter=getPublicReadAccess) BOOL publicReadAccess;

/**
 Controls whether the public is allowed to delete this object.
 */
@property (nonatomic, assign, getter=getPublicDeleteAccess) BOOL publicDeleteAccess;

/**
 Controls whether the public is allowed to update this object.
 */
@property (nonatomic, assign, getter=getPublicUpdateAccess) BOOL publicUpdateAccess;

/**
 Controls whether the public is allowed to write this object.
 */
@property (nonatomic, assign, getter=getPublicWriteAccess) BOOL publicWriteAccess;

///--------------------------------------
#pragma mark - Controlling Access Per-User
///--------------------------------------


- (void)setPermission:(Permission)permission;
- (void)setPermission:(Permission)permission forUserId:(NSString *)userId;
- (void)setPermission:(Permission)permission forRoleWithName:(NSString *)name;
- (void)setPermission:(Permission)permission forRole:(RTRole *)role;

/**
 SET UPDATE ACCESS
 */

- (void)setPublicUpdateAccess:(BOOL)allowed;
- (void)setUpdateAccess:(BOOL)allowed forUserId:(NSString *)userId;
- (BOOL)getUpdateAccessForUserId:(NSString *)userId;
- (BOOL)getUpdateAccessForRoleWithName:(NSString *)name;
- (void)setUpdateAccess:(BOOL)allowed forRoleWithName:(NSString *)name;
- (BOOL)getUpdateAccessForRole:(RTRole *)role;
- (void)setUpdateAccess:(BOOL)allowed forRole:(RTRole *)role;
- (BOOL)getUpdateReadAccess;

/**
 Set whether the given user id is allowed to read this object.

 @param allowed Whether the given user can write this object.
 @param userId The `RTObject.objectId` of the user to assign access.
 */
- (void)setReadAccess:(BOOL)allowed forUserId:(NSString *)userId;

/**
 Gets whether the given user id is *explicitly* allowed to read this object.
 Even if this returns `NO`, the user may still be able to access it if `publicReadAccess` returns `YES`
 or if the user belongs to a role that has access.

 @param userId The `RTObject.objectId` of the user for which to retrive access.

 @return `YES` if the user with this `objectId` has *explicit* read access, otherwise `NO`.
 */
- (BOOL)getReadAccessForUserId:(NSString *)userId;

/**
 Set whether the given user id is allowed to write this object.

 @param allowed Whether the given user can read this object.
 @param userId The `RTObject.objectId` of the user to assign access.
 */
- (void)setWriteAccess:(BOOL)allowed forUserId:(NSString *)userId;

/**
 Gets whether the given user id is *explicitly* allowed to write this object.
 Even if this returns NO, the user may still be able to write it if `publicWriteAccess` returns `YES`
 or if the user belongs to a role that has access.

 @param userId The `RTObject.objectId` of the user for which to retrive access.

 @return `YES` if the user with this `RTObject.objectId` has *explicit* write access, otherwise `NO`.
 */
- (BOOL)getWriteAccessForUserId:(NSString *)userId;

/**
 Set whether the given user is allowed to read this object.

 @param allowed Whether the given user can read this object.
 @param user The user to assign access.
 */
- (void)setReadAccess:(BOOL)allowed forUser:(RTUser *)user;

/**
 Gets whether the given user is *explicitly* allowed to read this object.
 Even if this returns `NO`, the user may still be able to access it if `publicReadAccess` returns `YES`
 or if the user belongs to a role that has access.

 @param user The user for which to retrive access.

 @return `YES` if the user has *explicit* read access, otherwise `NO`.
 */
- (BOOL)getReadAccessForUser:(RTUser *)user;

/**
 Set whether the given user is allowed to write this object.

 @param allowed Whether the given user can write this object.
 @param user The user to assign access.
 */
- (void)setWriteAccess:(BOOL)allowed forUser:(RTUser *)user;

/**
 Gets whether the given user is *explicitly* allowed to write this object.
 Even if this returns `NO`, the user may still be able to write it if `publicWriteAccess` returns `YES`
 or if the user belongs to a role that has access.

 @param user The user for which to retrive access.

 @return `YES` if the user has *explicit* write access, otherwise `NO`.
 */
- (BOOL)getWriteAccessForUser:(RTUser *)user;

///--------------------------------------
#pragma mark - Controlling Access Per-Role
///--------------------------------------

/**
 Get whether users belonging to the role with the given name are allowed to read this object.
 Even if this returns `NO`, the role may still be able to read it if a parent role has read access.

 @param name The name of the role.

 @return `YES` if the role has read access, otherwise `NO`.
 */
- (BOOL)getReadAccessForRoleWithName:(NSString *)name;

/**
 Set whether users belonging to the role with the given name are allowed to read this object.

 @param allowed Whether the given role can read this object.
 @param name The name of the role.
 */
- (void)setReadAccess:(BOOL)allowed forRoleWithName:(NSString *)name;

/**
 Get whether users belonging to the role with the given name are allowed to write this object.
 Even if this returns `NO`, the role may still be able to write it if a parent role has write access.

 @param name The name of the role.

 @return `YES` if the role has read access, otherwise `NO`.
 */
- (BOOL)getWriteAccessForRoleWithName:(NSString *)name;

/**
 Set whether users belonging to the role with the given name are allowed to write this object.

 @param allowed Whether the given role can write this object.
 @param name The name of the role.
 */
- (void)setWriteAccess:(BOOL)allowed forRoleWithName:(NSString *)name;

/**
 Get whether users belonging to the given role are allowed to read this object.
 Even if this returns `NO`, the role may still be able to read it if a parent role has read access.

 The role must already be saved on the server and
 it's data must have been fetched in order to use this method.

 @param role The name of the role.

 @return `YES` if the role has read access, otherwise `NO`.
 */
- (BOOL)getReadAccessForRole:(RTRole *)role;

/**
 Set whether users belonging to the given role are allowed to read this object.

 The role must already be saved on the server and
 it's data must have been fetched in order to use this method.

 @param allowed Whether the given role can read this object.
 @param role The role to assign access.
 */
- (void)setReadAccess:(BOOL)allowed forRole:(RTRole *)role;

/**
 Get whether users belonging to the given role are allowed to write this object.
 Even if this returns `NO`, the role may still be able to write it if a parent role has write access.

 The role must already be saved on the server and
 it's data must have been fetched in order to use this method.

 @param role The name of the role.

 @return `YES` if the role has write access, otherwise `NO`.
 */
- (BOOL)getWriteAccessForRole:(RTRole *)role;

/**
 Set whether users belonging to the given role are allowed to write this object.

 The role must already be saved on the server and
 it's data must have been fetched in order to use this method.

 @param allowed Whether the given role can write this object.
 @param role The role to assign access.
 */
- (void)setWriteAccess:(BOOL)allowed forRole:(RTRole *)role;

///--------------------------------------
#pragma mark - Setting Access Defaults
///--------------------------------------

/**
 Sets a default ACL that will be applied to all instances of `RTObject` when they are created.

 @param acl The ACL to use as a template for all instance of `RTObject` created after this method has been called.
 This value will be copied and used as a template for the creation of new ACLs, so changes to the
 instance after this method has been called will not be reflected in new instance of `RTObject`.
 @param currentUserAccess - If `YES`, the `RTACL` that is applied to newly-created instance of `RTObject` will
 provide read and write access to the `RTUser.+currentUser` at the time of creation.
 - If `NO`, the provided `acl` will be used without modification.
 - If `acl` is `nil`, this value is ignored.
 */
+ (void)setDefaultACL:(nullable RTACL *)acl withAccessForCurrentUser:(BOOL)currentUserAccess;

@end

NS_ASSUME_NONNULL_END
