#ifndef _INLINE_SYSINFO_H
#define _INLINE_SYSINFO_H

#ifndef CLIB_SYSINFO_PROTOS_H
	#define CLIB_SYSINFO_PROTOS_H
#endif

#ifndef EXEC_TYPES_H
	#include <exec/types.h>
#endif
#ifndef LIBRARIES_SYSINFO_H
	#include <libraries/SysInfo.h>
#endif

#ifndef SYSINFO_BASE_NAME
	#define SYSINFO_BASE_NAME SysInfoBase
#endif

#define InitSysInfo()                                                                         \
	({                                                                                        \
		register char *_InitSysInfo__bn __asm("a6") = (char *)(SYSINFO_BASE_NAME);            \
		((struct SysInfo * (*)(char *__asm("a6")))(_InitSysInfo__bn - 30))(_InitSysInfo__bn); \
	})

#define FreeSysInfo(si)                                                                                           \
	({                                                                                                            \
		struct SysInfo *_FreeSysInfo_si = (si);                                                                   \
		({                                                                                                        \
			register char *_FreeSysInfo__bn __asm("a6") = (char *)(SYSINFO_BASE_NAME);                            \
			((void (*)(char *__asm("a6"), struct SysInfo *__asm("a0")))(_FreeSysInfo__bn - 36))(_FreeSysInfo__bn, \
																								_FreeSysInfo_si); \
		});                                                                                                       \
	})

#define GetLoadAverage(si, la)                                                                               \
	({                                                                                                       \
		struct SysInfo *_GetLoadAverage_si = (si);                                                           \
		struct SI_LoadAverage *_GetLoadAverage_la = (la);                                                    \
		({                                                                                                   \
			register char *_GetLoadAverage__bn __asm("a6") = (char *)(SYSINFO_BASE_NAME);                    \
			((void (*)(char *__asm("a6"), struct SysInfo *__asm("a0"), struct SI_LoadAverage *__asm("a1")))( \
				_GetLoadAverage__bn - 42))(_GetLoadAverage__bn, _GetLoadAverage_si, _GetLoadAverage_la);     \
		});                                                                                                  \
	})

#define GetPid(si)                                                                                                  \
	({                                                                                                              \
		struct SysInfo *_GetPid_si = (si);                                                                          \
		({                                                                                                          \
			register char *_GetPid__bn __asm("a6") = (char *)(SYSINFO_BASE_NAME);                                   \
			((LONG(*)(char *__asm("a6"), struct SysInfo *__asm("a0")))(_GetPid__bn - 48))(_GetPid__bn, _GetPid_si); \
		});                                                                                                         \
	})

#define GetPpid(si)                                                                                                    \
	({                                                                                                                 \
		struct SysInfo *_GetPpid_si = (si);                                                                            \
		({                                                                                                             \
			register char *_GetPpid__bn __asm("a6") = (char *)(SYSINFO_BASE_NAME);                                     \
			((LONG(*)(char *__asm("a6"), struct SysInfo *__asm("a0")))(_GetPpid__bn - 54))(_GetPpid__bn, _GetPpid_si); \
		});                                                                                                            \
	})

#define GetPgrp(si)                                                                                                    \
	({                                                                                                                 \
		struct SysInfo *_GetPgrp_si = (si);                                                                            \
		({                                                                                                             \
			register char *_GetPgrp__bn __asm("a6") = (char *)(SYSINFO_BASE_NAME);                                     \
			((LONG(*)(char *__asm("a6"), struct SysInfo *__asm("a0")))(_GetPgrp__bn - 60))(_GetPgrp__bn, _GetPgrp_si); \
		});                                                                                                            \
	})

#define GetNice(si, which, who)                                                                             \
	({                                                                                                      \
		struct SysInfo *_GetNice_si = (si);                                                                 \
		LONG _GetNice_which = (which);                                                                      \
		LONG _GetNice_who = (who);                                                                          \
		({                                                                                                  \
			register char *_GetNice__bn __asm("a6") = (char *)(SYSINFO_BASE_NAME);                          \
			((LONG(*)(char *__asm("a6"), struct SysInfo *__asm("a0"), LONG __asm("d0"), LONG __asm("d1")))( \
				_GetNice__bn - 66))(_GetNice__bn, _GetNice_si, _GetNice_which, _GetNice_who);               \
		});                                                                                                 \
	})

#define SetNice(si, which, who, nice)                                                    \
	({                                                                                   \
		struct SysInfo *_SetNice_si = (si);                                              \
		LONG _SetNice_which = (which);                                                   \
		LONG _SetNice_who = (who);                                                       \
		LONG _SetNice_nice = (nice);                                                     \
		({                                                                               \
			register char *_SetNice__bn __asm("a6") = (char *)(SYSINFO_BASE_NAME);       \
			((LONG(*)(char *__asm("a6"),                                                 \
					  struct SysInfo *__asm("a0"),                                       \
					  LONG __asm("d0"),                                                  \
					  LONG __asm("d1"),                                                  \
					  LONG __asm("d2")))(_SetNice__bn - 72))(                            \
				_SetNice__bn, _SetNice_si, _SetNice_which, _SetNice_who, _SetNice_nice); \
		});                                                                              \
	})

#define AddNotify(si, flags, safety_limit)                                                                       \
	({                                                                                                           \
		struct SysInfo *_AddNotify_si = (si);                                                                    \
		WORD _AddNotify_flags = (flags);                                                                         \
		LONG _AddNotify_safety_limit = (safety_limit);                                                           \
		({                                                                                                       \
			register char *_AddNotify__bn __asm("a6") = (char *)(SYSINFO_BASE_NAME);                             \
			((struct SI_Notify *                                                                                 \
			  (*)(char *__asm("a6"), struct SysInfo *__asm("a0"), WORD __asm("d0"), LONG __asm("d1")))(          \
				_AddNotify__bn - 78))(_AddNotify__bn, _AddNotify_si, _AddNotify_flags, _AddNotify_safety_limit); \
		});                                                                                                      \
	})

#define RemoveNotify(si, notify)                                                                        \
	({                                                                                                  \
		struct SysInfo *_RemoveNotify_si = (si);                                                        \
		struct SI_Notify *_RemoveNotify_notify = (notify);                                              \
		({                                                                                              \
			register char *_RemoveNotify__bn __asm("a6") = (char *)(SYSINFO_BASE_NAME);                 \
			((void (*)(char *__asm("a6"), struct SysInfo *__asm("a0"), struct SI_Notify *__asm("a1")))( \
				_RemoveNotify__bn - 84))(_RemoveNotify__bn, _RemoveNotify_si, _RemoveNotify_notify);    \
		});                                                                                             \
	})

#define GetCpuUsage(si, usage)                                                                            \
	({                                                                                                    \
		struct SysInfo *_GetCpuUsage_si = (si);                                                           \
		struct SI_CpuUsage *_GetCpuUsage_usage = (usage);                                                 \
		({                                                                                                \
			register char *_GetCpuUsage__bn __asm("a6") = (char *)(SYSINFO_BASE_NAME);                    \
			((void (*)(char *__asm("a6"), struct SysInfo *__asm("a0"), struct SI_CpuUsage *__asm("a1")))( \
				_GetCpuUsage__bn - 90))(_GetCpuUsage__bn, _GetCpuUsage_si, _GetCpuUsage_usage);           \
		});                                                                                               \
	})

#define GetTaskCpuUsage(si, usage, task)                                                                   \
	({                                                                                                     \
		struct SysInfo *_GetTaskCpuUsage_si = (si);                                                        \
		struct SI_TaskCpuUsage *_GetTaskCpuUsage_usage = (usage);                                          \
		struct Task *_GetTaskCpuUsage_task = (task);                                                       \
		({                                                                                                 \
			register char *_GetTaskCpuUsage__bn __asm("a6") = (char *)(SYSINFO_BASE_NAME);                 \
			((LONG(*)(char *__asm("a6"),                                                                   \
					  struct SysInfo *__asm("a0"),                                                         \
					  struct SI_TaskCpuUsage *__asm("a1"),                                                 \
					  struct Task *__asm("a2")))(_GetTaskCpuUsage__bn - 96))(                              \
				_GetTaskCpuUsage__bn, _GetTaskCpuUsage_si, _GetTaskCpuUsage_usage, _GetTaskCpuUsage_task); \
		});                                                                                                \
	})

#endif /*  _INLINE_SYSINFO_H  */
