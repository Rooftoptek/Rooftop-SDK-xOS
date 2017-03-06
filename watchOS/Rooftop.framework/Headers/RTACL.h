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
    RTACLAccessTypeRead      = 1 << 0,
    RTACLAccessTypeUpdate    = 1 << 1,
    RTACLAccessTypeDelete    = 1 << 2,
} RTACLAccessType;


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

- (void)setPublicAccess:(RTACLAccessType)permissions;

///--------------------------------------
#pragma mark - Controlling Access Per-User
///--------------------------------------

/**
 Gets the *explicit* permissions this object for the given user.
 
 @param user The user for which to retrive access.
 
 @return *explicit* permissions for the user.
 */
- (RTACLAccessType)getAccessForUser:(RTUser *)user;

/**
 Set the permissions on this object for a given user.
 
 @param permissions given permissions on this object.
 @param user The user to assign access to.
 */
- (void)setAccess:(RTACLAccessType)permissions forUser:(RTUser *)user;

/**
 Gets whether the given user is *explicitly* allowed to read this object.
 Even if this returns NO, the user may still be able to read it if `publicReadAccess` returns `YES`
 or if the user belongs to a role that has access.
 
 @param user The user for which to retrive access.
 
 @return `YES` if the user has *explicit* read access, otherwise `NO`.
 */
- (BOOL)getReadAccessForUser:(RTUser *)user;

/**
 Set whether the given user is allowed to read this object.
 
 @param allowed Whether the given user can read this object.
 @param user The user to assign access to.
 */
- (void)setReadAccess:(BOOL)allowed forUser:(RTUser *)user;

/**
 Gets whether the given user is *explicitly* allowed to update this object.
 Even if this returns NO, the user may still be able to update it if `publicUpdateAccess` returns `YES`
 or if the user belongs to a role that has access.
 
 @param user The user for which to retrive access.
 
 @return `YES` if the user has *explicit* update access, otherwise `NO`.
 */
- (BOOL)getUpdateAccessForUser:(RTUser *)user;

/**
 Set whether the given user is allowed to update this object.
 
 @param allowed Whether the given user can update this object.
 @param user The user to assign access to.
 */
- (void)setUpdateAccess:(BOOL)allowed forUser:(RTUser *)user;

/**
 Gets whether the given user is *explicitly* allowed to delete this object.
 Even if this returns NO, the user may still be able to delete it if `publicDeleteAccess` returns `YES`
 or if the user belongs to a role that has access.
 
 @param user The user for which to retrive access.
 
 @return `YES` if the user has *explicit* delete access, otherwise `NO`.
 */
- (BOOL)getDeleteAccessForUser:(RTUser *)user;

/**
 Set whether the given user is allowed to delete this object.
 
 @param allowed Whether the given user can delete this object.
 @param user The user to assign access to.
 */
- (void)setDeleteAccess:(BOOL)allowed forUser:(RTUser *)user;

///-------------------------------------------------
#pragma mark - Controlling Access Per-User by userId
///-------------------------------------------------

/**
 Gets the *explicit* permissions this object for the user with the given user id.
 
 @param userId The user if the user for which to retrive access.
 
 @return *explicit* permissions for the user.
 */
- (RTACLAccessType)getAccessForUserId:(NSString *)userId;

/**
 Set the permissions on this object for a given user id.
 
 @param permissions given permissions on this object.
 @param userId The `RTObject.objectId` of the user to assign access.
 */
- (void)setAccess:(RTACLAccessType)permissions forUserId:(NSString *)userId;

/**
 Gets whether the given user id is *explicitly* allowed to read this object.
 Even if this returns NO, the user may still be able to read it if `publicReadAccess` returns `YES`
 or if the user belongs to a role that has access.
 
 @param userId The `RTObject.objectId` of the user for which to retrive access.
 
 @return `YES` if the user with this `RTObject.objectId` has *explicit* read access, otherwise `NO`.
 */
- (BOOL)getReadAccessForUserId:(NSString *)userId;

/**
 Set whether the given user id is allowed to read this object.
 
 @param allowed Whether the given user can read this object.
 @param userId The `RTObject.objectId` of the user to assign access.
 */
- (void)setReadAccess:(BOOL)allowed forUserId:(NSString *)userId;

/**
 Gets whether the given user id is *explicitly* allowed to update this object.
 Even if this returns NO, the user may still be able to update it if `publicUpdateAccess` returns `YES`
 or if the user belongs to a role that has access.
 
 @param userId The `RTObject.objectId` of the user for which to retrive access.
 
 @return `YES` if the user with this `RTObject.objectId` has *explicit* update access, otherwise `NO`.
 */
- (BOOL)getUpdateAccessForUserId:(NSString *)userId;

/**
 Set whether the given user id is allowed to update this object.
 
 @param allowed Whether the given user can update this object.
 @param userId The `RTObject.objectId` of the user to assign access.
 */
- (void)setUpdateAccess:(BOOL)allowed forUserId:(NSString *)userId;

/**
 Gets whether the given user id is *explicitly* allowed to delete this object.
 Even if this returns NO, the user may still be able to delete it if `publicDeleteAccess` returns `YES`
 or if the user belongs to a role that has access.
 
 @param userId The `RTObject.objectId` of the user for which to retrive access.
 
 @return `YES` if the user with this `RTObject.objectId` has *explicit* delete access, otherwise `NO`.
 */
- (BOOL)getDeleteAccessForUserId:(NSString *)userId;

/**
 Set whether the given user id is allowed to delete this object.
 
 @param allowed Whether the given user can delete this object.
 @param userId The `RTObject.objectId` of the user to assign access.
 */
- (void)setDeleteAccess:(BOOL)allowed forUserId:(NSString *)userId;

///--------------------------------------
#pragma mark - Controlling Access Per-Role
///--------------------------------------

/**
 Get permissions for users belonging to the given role for that object.
 
 The role must already be saved on the server and
 it's data must have been fetched in order to use this method.
 
 @param role The role.
 
 @return permissions for the given role.
 */
- (RTACLAccessType)getAccessForRole:(RTRole *)role;

/**
 Set the permissions on this object for a given role.
 
 @param permissions given permissions on this object.
 @param role The role to assign access to.
 */
- (void)setAccess:(RTACLAccessType)permissions forRole:(RTRole *)role;

/**
 Get whether users belonging to the given role are allowed to read this object.
 Even if this returns `NO`, the user may still be able to read if it belongs to a role with read access.
 
 The role must already be saved on the server and
 it's data must have been fetched in order to use this method.
 
 @param role The name of the role.
 
 @return `YES` if the role has read access, otherwise `NO`.
 */
- (BOOL)getReadAccessForRole:(RTRole *)role;

/**
 Set whether the given role is allowed to read this object.
 
 @param allowed Whether the given user can read this object.
 @param role The role to assign access to.
 */
- (void)setReadAccess:(BOOL)allowed forRole:(RTRole *)role;

/**
 Get whether users belonging to the given role are allowed to update this object.
 Even if this returns `NO`, the user may still be able to update if it belongs to a role with update access.
 
 The role must already be saved on the server and
 it's data must have been fetched in order to use this method.
 
 @param role A Role
 
 @return `YES` if the role has update access, otherwise `NO`.
 */
- (BOOL)getUpdateAccessForRole:(RTRole *)role;

/**
 Set whether the given role is allowed to update this object.
 
 @param allowed Whether the given user can update this object.
 @param role The role to assign access to.
 */
- (void)setUpdateAccess:(BOOL)allowed forRole:(RTRole *)role;

/**
 Get whether users belonging to the given role are allowed to delete this object.
 Even if this returns `NO`, the user may still be able to delete if it belongs to a role with delete access.
 
 The role must already be saved on the server and
 it's data must have been fetched in order to use this method.
 
 @param role A role.
 
 @return `YES` if the role has delete access, otherwise `NO`.
 */
- (BOOL)getDeleteAccessForRole:(RTRole *)role;

/**
 Set whether the given role is allowed to delete this object.
 
 @param allowed Whether the given user can delete this object.
 @param role The role to assign access to.
 */
- (void)setDeleteAccess:(BOOL)allowed forRole:(RTRole *)role;

///----------------------------------------------------
#pragma mark - Controlling Access Per-Role by role name
///----------------------------------------------------

/**
 Get permissions for users belonging to the role with the given name for that object.
 
 The role must already be saved on the server and
 it's data must have been fetched in order to use this method.
 
 @param name The name of the role.
 
 @return permissions for the role with the given name.
 */
- (RTACLAccessType)getAccessForRoleWithName:(NSString *)name;

/**
 Set the permissions on this object for a given role name.
 
 @param permissions given permissions on this object.
 @param name The RTRole name of the role to assign access.
 */
- (void)setAccess:(RTACLAccessType)permissions forRoleWithName:(NSString *)name;

/**
 Get whether users belonging to the role with the given role name are allowed to read this object.
 Even if this returns `NO`, the user may still be able to read if it belongs to a role with read access.
 
 The role must already be saved on the server and
 it's data must have been fetched in order to use this method.
 
 @param name The name of the role.
 
 @return `YES` if the role has read access, otherwise `NO`.
 */
- (BOOL)getReadAccessForRoleWithName:(NSString *)name;

/**
 Set whether the role with the given name is allowed to read this object.
 
 @param allowed Whether the given user can read this object.
 @param name The RTRole name of the role to assign access.
 */
- (void)setReadAccess:(BOOL)allowed forRoleWithName:(NSString *)name;

/**
 Get whether users belonging to the role with the given role name are allowed to update this object.
 Even if this returns `NO`, the user may still be able to update if it belongs to a role with update access.
 
 The role must already be saved on the server and
 it's data must have been fetched in order to use this method.
 
 @param name The name of the role.
 
 @return `YES` if the role has update access, otherwise `NO`.
 */
- (BOOL)getUpdateAccessForRoleWithName:(NSString *)name;

/**
 Set whether the role with the given name is allowed to update this object.
 
 @param allowed Whether the given user can update this object.
 @param name The RTRole name of the role to assign access.
 */
- (void)setUpdateAccess:(BOOL)allowed forRoleWithName:(NSString *)name;

/**
 Get whether users belonging to the role with the given role name are allowed to delete this object.
 Even if this returns `NO`, the user may still be able to delete if it belongs to a role with delete access.
 
 The role must already be saved on the server and
 it's data must have been fetched in order to use this method.
 
 @param name The name of the role.
 
 @return `YES` if the role has delete access, otherwise `NO`.
 */
- (BOOL)getDeleteAccessForRoleWithName:(NSString *)name;

/**
 Set whether the role with the given name is allowed to delete this object.
 
 @param allowed Whether the given user can delete this object.
 @param name The RTRole name of the role to assign access.
 */
- (void)setDeleteAccess:(BOOL)allowed forRoleWithName:(NSString *)name;

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
