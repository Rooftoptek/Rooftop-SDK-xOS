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
#import <Rooftop/RTUser.h>

NS_ASSUME_NONNULL_BEGIN

@class RTRelation<ObjectType : RTObject *>;

/**
 The `RTRole` class represents a Role on the Rooftop server.
 `RTRoles` represent groupings of `RTUser` objects for the purposes of granting permissions
 (e.g. specifying a `RTACL` for a `RTObject`).
 Roles are specified by their sets of child users and child roles,
 all of which are granted any permissions that the parent role has.

 Roles must have a name (which cannot be changed after creation of the role), and must specify an ACL.
 */
@interface RTRole : RTObject <RTSubclassing>

///--------------------------------------
#pragma mark - Creating a New Role
///--------------------------------------

/**
 Constructs a new `RTRole` with the given name.
 If no default ACL has been specified, you must provide an ACL for the role.

 @param name The name of the Role to create.
 */
- (instancetype)initWithName:(NSString *)name;

/**
 Constructs a new `RTRole` with the given name.

 @param name The name of the Role to create.
 @param acl The ACL for this role. Roles must have an ACL.
 */
- (instancetype)initWithName:(NSString *)name acl:(nullable RTACL *)acl;

/**
 Constructs a new `RTRole` with the given name.

 If no default ACL has been specified, you must provide an ACL for the role.

 @param name The name of the Role to create.
 */
+ (instancetype)roleWithName:(NSString *)name;

/**
 Constructs a new `RTRole` with the given name.

 @param name The name of the Role to create.
 @param acl The ACL for this role. Roles must have an ACL.
 */
+ (instancetype)roleWithName:(NSString *)name acl:(nullable RTACL *)acl;

///--------------------------------------
#pragma mark - Role-specific Properties
///--------------------------------------

/**
 Gets or sets the name for a role.

 This value must be set before the role has been saved to the server,
 and cannot be set once the role has been saved.

 @warning A role's name can only contain alphanumeric characters, `_`, `-`, and spaces.
 */
@property (nonatomic, copy) NSString *name;

/**
 Gets the `RTRelation` for the `RTUser` objects that are direct children of this role.

 These users are granted any privileges that this role has been granted
 (e.g. read or write access through ACLs). You can add or remove users from
 the role through this relation.
 */
@property (nonatomic, strong, readonly) RTRelation<RTUser *> *users;

/**
 Gets the `RTRelation` for the `RTRole` objects that are direct children of this role.

 These roles' users are granted any privileges that this role has been granted
 (e.g. read or write access through ACLs). You can add or remove child roles
 from this role through this relation.
 */
@property (nonatomic, strong, readonly) RTRelation<RTRole *> *roles;

@end

NS_ASSUME_NONNULL_END
