#ifndef _INLINE_MULTIUSER_H
#define _INLINE_MULTIUSER_H

#ifndef CLIB_MULTIUSER_PROTOS_H
	#define CLIB_MULTIUSER_PROTOS_H
#endif

#ifndef LIBRARIES_MULTIUSER_H
	#include <libraries/multiuser.h>
#endif

#ifndef MULTIUSER_BASE_NAME
	#define MULTIUSER_BASE_NAME muBase
#endif

#define muLogoutA(taglist)                                                                                         \
	({                                                                                                             \
		struct TagItem *_muLogoutA_taglist = (taglist);                                                            \
		({                                                                                                         \
			register char *_muLogoutA__bn __asm("a6") = (char *)(MULTIUSER_BASE_NAME);                             \
			((ULONG(*)(char *__asm("a6"), struct TagItem *__asm("a0")))(_muLogoutA__bn - 30))(_muLogoutA__bn,      \
																							  _muLogoutA_taglist); \
		});                                                                                                        \
	})

#ifndef NO_INLINE_STDARG
static __inline__ ULONG ___muLogout(struct Library *muBase, ULONG taglist, ...)
{
	return muLogoutA((struct TagItem *)&taglist);
}

	#define muLogout(tags...) ___muLogout(MULTIUSER_BASE_NAME, tags)
#endif

#define muLoginA(taglist)                                                                                        \
	({                                                                                                           \
		struct TagItem *_muLoginA_taglist = (taglist);                                                           \
		({                                                                                                       \
			register char *_muLoginA__bn __asm("a6") = (char *)(MULTIUSER_BASE_NAME);                            \
			((ULONG(*)(char *__asm("a6"), struct TagItem *__asm("a0")))(_muLoginA__bn - 36))(_muLoginA__bn,      \
																							 _muLoginA_taglist); \
		});                                                                                                      \
	})

#ifndef NO_INLINE_STDARG
static __inline__ ULONG ___muLogin(struct Library *muBase, ULONG taglist, ...)
{
	return muLoginA((struct TagItem *)&taglist);
}

	#define muLogin(tags...) ___muLogin(MULTIUSER_BASE_NAME, tags)
#endif

#define muGetTaskOwner(task)                                                                                           \
	({                                                                                                                 \
		struct Task *_muGetTaskOwner_task = (task);                                                                    \
		({                                                                                                             \
			register char *_muGetTaskOwner__bn __asm("a6") = (char *)(MULTIUSER_BASE_NAME);                            \
			((ULONG(*)(char *__asm("a6"), struct Task *__asm("d0")))(_muGetTaskOwner__bn - 42))(_muGetTaskOwner__bn,   \
																								_muGetTaskOwner_task); \
		});                                                                                                            \
	})

#define muPasswd(oldpwd, newpwd)                                                                        \
	({                                                                                                  \
		STRPTR _muPasswd_oldpwd = (oldpwd);                                                             \
		STRPTR _muPasswd_newpwd = (newpwd);                                                             \
		({                                                                                              \
			register char *_muPasswd__bn __asm("a6") = (char *)(MULTIUSER_BASE_NAME);                   \
			((BOOL(*)(char *__asm("a6"), STRPTR __asm("a0"), STRPTR __asm("a1")))(_muPasswd__bn - 48))( \
				_muPasswd__bn, _muPasswd_oldpwd, _muPasswd_newpwd);                                     \
		});                                                                                             \
	})

#define muAllocUserInfo()                                                                                \
	({                                                                                                   \
		register char *_muAllocUserInfo__bn __asm("a6") = (char *)(MULTIUSER_BASE_NAME);                 \
		((struct muUserInfo * (*)(char *__asm("a6")))(_muAllocUserInfo__bn - 54))(_muAllocUserInfo__bn); \
	})

#define muFreeUserInfo(info)                                                                           \
	({                                                                                                 \
		struct muUserInfo *_muFreeUserInfo_info = (info);                                              \
		({                                                                                             \
			register char *_muFreeUserInfo__bn __asm("a6") = (char *)(MULTIUSER_BASE_NAME);            \
			((void (*)(char *__asm("a6"), struct muUserInfo *__asm("a0")))(_muFreeUserInfo__bn - 60))( \
				_muFreeUserInfo__bn, _muFreeUserInfo_info);                                            \
		});                                                                                            \
	})

#define muGetUserInfo(info, keytype)                                                                          \
	({                                                                                                        \
		struct muUserInfo *_muGetUserInfo_info = (info);                                                      \
		ULONG _muGetUserInfo_keytype = (keytype);                                                             \
		({                                                                                                    \
			register char *_muGetUserInfo__bn __asm("a6") = (char *)(MULTIUSER_BASE_NAME);                    \
			((struct muUserInfo * (*)(char *__asm("a6"), struct muUserInfo *__asm("a0"), ULONG __asm("d0")))( \
				_muGetUserInfo__bn - 66))(_muGetUserInfo__bn, _muGetUserInfo_info, _muGetUserInfo_keytype);   \
		});                                                                                                   \
	})

#define muSetDefProtectionA(taglist)                                                                    \
	({                                                                                                  \
		struct TagItem *_muSetDefProtectionA_taglist = (taglist);                                       \
		({                                                                                              \
			register char *_muSetDefProtectionA__bn __asm("a6") = (char *)(MULTIUSER_BASE_NAME);        \
			((BOOL(*)(char *__asm("a6"), struct TagItem *__asm("a0")))(_muSetDefProtectionA__bn - 78))( \
				_muSetDefProtectionA__bn, _muSetDefProtectionA_taglist);                                \
		});                                                                                             \
	})

#ifndef NO_INLINE_STDARG
static __inline__ BOOL ___muSetDefProtection(struct Library *muBase, ULONG taglist, ...)
{
	return muSetDefProtectionA((struct TagItem *)&taglist);
}

	#define muSetDefProtection(tags...) ___muSetDefProtection(MULTIUSER_BASE_NAME, tags)
#endif

#define muGetDefProtection(task)                                                                     \
	({                                                                                               \
		struct Task *_muGetDefProtection_task = (task);                                              \
		({                                                                                           \
			register char *_muGetDefProtection__bn __asm("a6") = (char *)(MULTIUSER_BASE_NAME);      \
			((ULONG(*)(char *__asm("a6"), struct Task *__asm("d0")))(_muGetDefProtection__bn - 84))( \
				_muGetDefProtection__bn, _muGetDefProtection_task);                                  \
		});                                                                                          \
	})

#define muSetProtection(name, mask)                                                                          \
	({                                                                                                       \
		STRPTR _muSetProtection_name = (name);                                                               \
		LONG _muSetProtection_mask = (mask);                                                                 \
		({                                                                                                   \
			register char *_muSetProtection__bn __asm("a6") = (char *)(MULTIUSER_BASE_NAME);                 \
			((BOOL(*)(char *__asm("a6"), STRPTR __asm("d1"), LONG __asm("d2")))(_muSetProtection__bn - 90))( \
				_muSetProtection__bn, _muSetProtection_name, _muSetProtection_mask);                         \
		});                                                                                                  \
	})

#define muLimitDOSSetProtection(flag)                                                                \
	({                                                                                               \
		BOOL _muLimitDOSSetProtection_flag = (flag);                                                 \
		({                                                                                           \
			register char *_muLimitDOSSetProtection__bn __asm("a6") = (char *)(MULTIUSER_BASE_NAME); \
			((BOOL(*)(char *__asm("a6"), BOOL __asm("d0")))(_muLimitDOSSetProtection__bn - 96))(     \
				_muLimitDOSSetProtection__bn, _muLimitDOSSetProtection_flag);                        \
		});                                                                                          \
	})

#define muCheckPasswd(taglist)                                                                     \
	({                                                                                             \
		struct TagItem *_muCheckPasswd_taglist = (taglist);                                        \
		({                                                                                         \
			register char *_muCheckPasswd__bn __asm("a6") = (char *)(MULTIUSER_BASE_NAME);         \
			((BOOL(*)(char *__asm("a6"), struct TagItem *__asm("a0")))(_muCheckPasswd__bn - 102))( \
				_muCheckPasswd__bn, _muCheckPasswd_taglist);                                       \
		});                                                                                        \
	})

#ifndef NO_INLINE_STDARG
static __inline__ BOOL ___muCheckPasswdTags(struct Library *muBase, ULONG taglist, ...)
{
	return muCheckPasswd((struct TagItem *)&taglist);
}

	#define muCheckPasswdTags(tags...) ___muCheckPasswdTags(MULTIUSER_BASE_NAME, tags)
#endif

#define muGetPasswdDirLock()                                                                    \
	({                                                                                          \
		register char *_muGetPasswdDirLock__bn __asm("a6") = (char *)(MULTIUSER_BASE_NAME);     \
		((BPTR(*)(char *__asm("a6")))(_muGetPasswdDirLock__bn - 114))(_muGetPasswdDirLock__bn); \
	})

#define muGetConfigDirLock()                                                                    \
	({                                                                                          \
		register char *_muGetConfigDirLock__bn __asm("a6") = (char *)(MULTIUSER_BASE_NAME);     \
		((BPTR(*)(char *__asm("a6")))(_muGetConfigDirLock__bn - 120))(_muGetConfigDirLock__bn); \
	})

#define muGetTaskExtOwner(task)                                                                                     \
	({                                                                                                              \
		struct Task *_muGetTaskExtOwner_task = (task);                                                              \
		({                                                                                                          \
			register char *_muGetTaskExtOwner__bn __asm("a6") = (char *)(MULTIUSER_BASE_NAME);                      \
			((struct muExtOwner * (*)(char *__asm("a6"), struct Task *__asm("d0")))(_muGetTaskExtOwner__bn - 126))( \
				_muGetTaskExtOwner__bn, _muGetTaskExtOwner_task);                                                   \
		});                                                                                                         \
	})

#define muFreeExtOwner(info)                                                                            \
	({                                                                                                  \
		struct muExtOwner *_muFreeExtOwner_info = (info);                                               \
		({                                                                                              \
			register char *_muFreeExtOwner__bn __asm("a6") = (char *)(MULTIUSER_BASE_NAME);             \
			((void (*)(char *__asm("a6"), struct muExtOwner *__asm("a0")))(_muFreeExtOwner__bn - 132))( \
				_muFreeExtOwner__bn, _muFreeExtOwner_info);                                             \
		});                                                                                             \
	})

#define muGetRelationshipA(user, owner, taglist)                                                                     \
	({                                                                                                               \
		struct muExtOwner *_muGetRelationshipA_user = (user);                                                        \
		ULONG _muGetRelationshipA_owner = (owner);                                                                   \
		struct TagItem *_muGetRelationshipA_taglist = (taglist);                                                     \
		({                                                                                                           \
			register char *_muGetRelationshipA__bn __asm("a6") = (char *)(MULTIUSER_BASE_NAME);                      \
			((ULONG(*)(                                                                                              \
				char *__asm("a6"), struct muExtOwner *__asm("d0"), ULONG __asm("d1"), struct TagItem *__asm("a0")))( \
				_muGetRelationshipA__bn - 138))(_muGetRelationshipA__bn,                                             \
												_muGetRelationshipA_user,                                            \
												_muGetRelationshipA_owner,                                           \
												_muGetRelationshipA_taglist);                                        \
		});                                                                                                          \
	})

#ifndef NO_INLINE_STDARG
static __inline__ ULONG ___muGetRelationship(struct Library *muBase,
											 struct muExtOwner *user,
											 ULONG owner,
											 ULONG taglist,
											 ...)
{
	return muGetRelationshipA(user, owner, (struct TagItem *)&taglist);
}

	#define muGetRelationship(user, owner...) ___muGetRelationship(MULTIUSER_BASE_NAME, user, owner)
#endif

#define muUserInfo2ExtOwner(info)                                                                      \
	({                                                                                                 \
		struct muUserInfo *_muUserInfo2ExtOwner_info = (info);                                         \
		({                                                                                             \
			register char *_muUserInfo2ExtOwner__bn __asm("a6") = (char *)(MULTIUSER_BASE_NAME);       \
			((struct muExtOwner * (*)(char *__asm("a6"), struct muUserInfo *__asm("a0")))(             \
				_muUserInfo2ExtOwner__bn - 144))(_muUserInfo2ExtOwner__bn, _muUserInfo2ExtOwner_info); \
		});                                                                                            \
	})

#define muAllocGroupInfo()                                                                                   \
	({                                                                                                       \
		register char *_muAllocGroupInfo__bn __asm("a6") = (char *)(MULTIUSER_BASE_NAME);                    \
		((struct muGroupInfo * (*)(char *__asm("a6")))(_muAllocGroupInfo__bn - 150))(_muAllocGroupInfo__bn); \
	})

#define muFreeGroupInfo(info)                                                                             \
	({                                                                                                    \
		struct muGroupInfo *_muFreeGroupInfo_info = (info);                                               \
		({                                                                                                \
			register char *_muFreeGroupInfo__bn __asm("a6") = (char *)(MULTIUSER_BASE_NAME);              \
			((void (*)(char *__asm("a6"), struct muGroupInfo *__asm("a0")))(_muFreeGroupInfo__bn - 156))( \
				_muFreeGroupInfo__bn, _muFreeGroupInfo_info);                                             \
		});                                                                                               \
	})

#define muGetGroupInfo(info, keytype)                                                                            \
	({                                                                                                           \
		struct muGroupInfo *_muGetGroupInfo_info = (info);                                                       \
		ULONG _muGetGroupInfo_keytype = (keytype);                                                               \
		({                                                                                                       \
			register char *_muGetGroupInfo__bn __asm("a6") = (char *)(MULTIUSER_BASE_NAME);                      \
			((struct muGroupInfo * (*)(char *__asm("a6"), struct muGroupInfo *__asm("a0"), ULONG __asm("d0")))(  \
				_muGetGroupInfo__bn - 162))(_muGetGroupInfo__bn, _muGetGroupInfo_info, _muGetGroupInfo_keytype); \
		});                                                                                                      \
	})

#define muAddMonitor(monitor)                                                                       \
	({                                                                                              \
		struct muMonitor *_muAddMonitor_monitor = (monitor);                                        \
		({                                                                                          \
			register char *_muAddMonitor__bn __asm("a6") = (char *)(MULTIUSER_BASE_NAME);           \
			((BOOL(*)(char *__asm("a6"), struct muMonitor *__asm("a0")))(_muAddMonitor__bn - 168))( \
				_muAddMonitor__bn, _muAddMonitor_monitor);                                          \
		});                                                                                         \
	})

#define muRemMonitor(monitor)                                                                        \
	({                                                                                               \
		struct muMonitor *_muRemMonitor_monitor = (monitor);                                         \
		({                                                                                           \
			register char *_muRemMonitor__bn __asm("a6") = (char *)(MULTIUSER_BASE_NAME);            \
			((void (*)(char *__asm("a6"), struct muMonitor *__asm("a0")))(_muRemMonitor__bn - 174))( \
				_muRemMonitor__bn, _muRemMonitor_monitor);                                           \
		});                                                                                          \
	})

#define muKill(task)                                                                                                \
	({                                                                                                              \
		struct Task *_muKill_task = (task);                                                                         \
		({                                                                                                          \
			register char *_muKill__bn __asm("a6") = (char *)(MULTIUSER_BASE_NAME);                                 \
			((BOOL(*)(char *__asm("a6"), struct Task *__asm("d0")))(_muKill__bn - 180))(_muKill__bn, _muKill_task); \
		});                                                                                                         \
	})

#define muFreeze(task)                                                                                     \
	({                                                                                                     \
		struct Task *_muFreeze_task = (task);                                                              \
		({                                                                                                 \
			register char *_muFreeze__bn __asm("a6") = (char *)(MULTIUSER_BASE_NAME);                      \
			((BOOL(*)(char *__asm("a6"), struct Task *__asm("d0")))(_muFreeze__bn - 186))(_muFreeze__bn,   \
																						  _muFreeze_task); \
		});                                                                                                \
	})

#define muUnfreeze(task)                                                                                       \
	({                                                                                                         \
		struct Task *_muUnfreeze_task = (task);                                                                \
		({                                                                                                     \
			register char *_muUnfreeze__bn __asm("a6") = (char *)(MULTIUSER_BASE_NAME);                        \
			((BOOL(*)(char *__asm("a6"), struct Task *__asm("d0")))(_muUnfreeze__bn - 192))(_muUnfreeze__bn,   \
																							_muUnfreeze_task); \
		});                                                                                                    \
	})

#endif /*  _INLINE_MULTIUSER_H  */
