#ifndef INLINE4_MULTIUSER_H
#define INLINE4_MULTIUSER_H

/*
** This file was auto generated by idltool 53.5.
**
** It provides compatibility to OS3 style library
** calls by substituting functions.
**
** Do not edit manually.
*/

#ifndef EXEC_TYPES_H
	#include <exec/types.h>
#endif
#ifndef EXEC_EXEC_H
	#include <exec/exec.h>
#endif
#ifndef EXEC_INTERFACES_H
	#include <exec/interfaces.h>
#endif

#include <interfaces/multiuser.h>

/* Inline macros for Interface "main" */
#define muLogoutA(taglist) Imu->muLogoutA((taglist))
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (__GNUC__ >= 3)
	#define muLogout(...) Imu->muLogout(__VA_ARGS__)
#elif (__GNUC__ == 2 && __GNUC_MINOR__ >= 95)
	#define muLogout(...) Imu->muLogout(##vargs)
#endif
#define muLoginA(taglist) Imu->muLoginA((taglist))
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (__GNUC__ >= 3)
	#define muLogin(...) Imu->muLogin(__VA_ARGS__)
#elif (__GNUC__ == 2 && __GNUC_MINOR__ >= 95)
	#define muLogin(...) Imu->muLogin(##vargs)
#endif
#define muGetTaskOwner(task) Imu->muGetTaskOwner((task))
#define muPasswd(oldpwd, newpwd) Imu->muPasswd((oldpwd), (newpwd))
#define muAllocUserInfo() Imu->muAllocUserInfo()
#define muFreeUserInfo(info) Imu->muFreeUserInfo((info))
#define muGetUserInfo(info, keytype) Imu->muGetUserInfo((info), (keytype))
#define muSetDefProtectionA(taglist) Imu->muSetDefProtectionA((taglist))
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (__GNUC__ >= 3)
	#define muSetDefProtection(...) Imu->muSetDefProtection(__VA_ARGS__)
#elif (__GNUC__ == 2 && __GNUC_MINOR__ >= 95)
	#define muSetDefProtection(...) Imu->muSetDefProtection(##vargs)
#endif
#define muGetDefProtection(task) Imu->muGetDefProtection((task))
#define muSetProtection(name, mask) Imu->muSetProtection((name), (mask))
#define muLimitDOSSetProtection(flag) Imu->muLimitDOSSetProtection((flag))
#define muCheckPasswd(taglist) Imu->muCheckPasswd((taglist))
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (__GNUC__ >= 3)
	#define muCheckPasswdTags(...) Imu->muCheckPasswdTags(__VA_ARGS__)
#elif (__GNUC__ == 2 && __GNUC_MINOR__ >= 95)
	#define muCheckPasswdTags(...) Imu->muCheckPasswdTags(##vargs)
#endif
#define muGetPasswdDirLock() Imu->muGetPasswdDirLock()
#define muGetConfigDirLock() Imu->muGetConfigDirLock()
#define muGetTaskExtOwner(task) Imu->muGetTaskExtOwner((task))
#define muFreeExtOwner(info) Imu->muFreeExtOwner((info))
#define muGetRelationshipA(user, owner, taglist) Imu->muGetRelationshipA((user), (owner), (taglist))
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (__GNUC__ >= 3)
	#define muGetRelationship(user, ...) Imu->muGetRelationship((user), __VA_ARGS__)
#elif (__GNUC__ == 2 && __GNUC_MINOR__ >= 95)
	#define muGetRelationship(user, vargs...) Imu->muGetRelationship(user, ##vargs)
#endif
#define muUserInfo2ExtOwner(info) Imu->muUserInfo2ExtOwner((info))
#define muAllocGroupInfo() Imu->muAllocGroupInfo()
#define muFreeGroupInfo(info) Imu->muFreeGroupInfo((info))
#define muGetGroupInfo(info, keytype) Imu->muGetGroupInfo((info), (keytype))
#define muAddMonitor(monitor) Imu->muAddMonitor((monitor))
#define muRemMonitor(monitor) Imu->muRemMonitor((monitor))
#define muKill(task) Imu->muKill((task))
#define muFreeze(task) Imu->muFreeze((task))
#define muUnfreeze(task) Imu->muUnfreeze((task))

#endif /* INLINE4_MULTIUSER_H */
