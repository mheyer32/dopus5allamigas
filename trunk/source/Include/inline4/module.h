#ifndef INLINE4_MODULE_H
#define INLINE4_MODULE_H

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

#include <interfaces/module.h>

/* Inline macros for Interface "main" */
#define Module_Entry(files, screen, ipc, main_ipc, id, data) IModule->Module_Entry((files), (screen), (ipc), (main_ipc), (id), (data)) 
#define Module_Identify(num) IModule->Module_Identify((num)) 

#endif /* INLINE4_MODULE_H */