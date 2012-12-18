/*

Directory Opus 5
Original APL release version 5.82
Copyright 1993-2012 Jonathan Potter & GP Software

This program is free software; you can redistribute it and/or
modify it under the terms of the AROS Public License version 1.1.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
AROS Public License for more details.

The release of Directory Opus 5 under the GPL in NO WAY affects
the existing commercial status of Directory Opus for Windows.

For more information on Directory Opus for Windows please see:

                 http://www.gpsoft.com.au

*/

/* "dopus.library"                                             */
/*                                                             */
/* Support routines for Directory Opus and associated programs */
/* (c) Copyright 1995 Jonathan Potter                          */
/*                                                             */
#pragma libcall DOpusBase RemovedFunc0 1e 0
#pragma libcall DOpusBase Random 24 001
/**/
#pragma libcall DOpusBase Atoh 2a 0802
#pragma libcall DOpusBase BtoCStr 30 09803
#pragma libcall DOpusBase DivideU 36 981004
#pragma libcall DOpusBase Itoa 3c 18003
#pragma libcall DOpusBase ItoaU 42 18003
#pragma libcall DOpusBase Ito26 48 8002
/**/
#pragma libcall DOpusBase BytesToString 4e 218004
#pragma libcall DOpusBase DivideToString 54 3210805
/**/
#pragma libcall DOpusBase SetBusyPointer 5a 801
#pragma libcall DOpusBase BuildKeyString 60 8321005
#pragma libcall DOpusBase ActivateStrGad 66 9802
/**/
#pragma libcall DOpusBase AllocTimer 6c 8002
#pragma libcall DOpusBase FreeTimer 72 801
#pragma libcall DOpusBase StartTimer 78 10803
#pragma libcall DOpusBase CheckTimer 7e 801
#pragma libcall DOpusBase StopTimer 84 801
/**/
#pragma libcall DOpusBase GetDosPathList 8a 801
#pragma libcall DOpusBase FreeDosPathList 90 801
/**/
#pragma libcall DOpusBase DoSimpleRequest 96 9802
#pragma libcall DOpusBase SimpleRequest 9c 10DCBA9808
#pragma libcall DOpusBase SelectionList a2 43210BA9809
/*                                                             */
#pragma libcall DOpusBase WriteIcon a8 9802
#pragma libcall DOpusBase WriteFileIcon ae 9802
/**/
#pragma libcall DOpusBase GetDragInfo b4 2109805
#pragma libcall DOpusBase FreeDragInfo ba 801
#pragma libcall DOpusBase GetDragImage c0 10803
#pragma libcall DOpusBase ShowDragImage c6 10803
#pragma libcall DOpusBase HideDragImage cc 801
#pragma libcall DOpusBase StampDragImage d2 10803
#pragma libcall DOpusBase GetDragMask d8 801
#pragma libcall DOpusBase CheckDragDeadlock de 801
#pragma libcall DOpusBase AddDragImage e4 801
#pragma libcall DOpusBase RemDragImage ea 801
/**/
#pragma libcall DOpusBase OpenConfigWindow f0 801
#pragma libcall DOpusBase CloseConfigWindow f6 801
/**/
#pragma libcall DOpusBase GetWindowMsg fc 801
#pragma libcall DOpusBase ReplyWindowMsg 102 801
#pragma libcall DOpusBase StripIntuiMessages 108 801
#pragma libcall DOpusBase CloseWindowSafely 10e 801
/**/
#pragma libcall DOpusBase CalcObjectDims 114 210CBA9808
#pragma libcall DOpusBase CalcWindowDims 11a 0BA9805
/**/
#pragma libcall DOpusBase AddObjectList 120 9802
#pragma libcall DOpusBase FreeObject 126 9802
#pragma libcall DOpusBase FreeObjectList 12c 801
#pragma libcall DOpusBase RefreshObjectList 132 9802
/**/
#pragma libcall DOpusBase GetObject 138 0802
/**/
#pragma libcall DOpusBase StoreGadgetValue 13e 9802
#pragma libcall DOpusBase SetGadgetValue 144 10803
#pragma libcall DOpusBase GetGadgetValue 14a 9802
#pragma libcall DOpusBase SetObjectKind 150 10803
#pragma libcall DOpusBase SetGadgetChoices 156 90803
/**/
#pragma libcall DOpusBase CheckObjectArea 15c 10803
#pragma libcall DOpusBase GetObjectRect 162 90803
#pragma libcall DOpusBase DisplayObject 168 A109805
#pragma libcall DOpusBase DisableObject 16e 10803
#pragma libcall DOpusBase BoundsCheckGadget 174 210804
/**/
#pragma libcall DOpusBase AddWindowMenus 17a 9802
#pragma libcall DOpusBase FreeWindowMenus 180 801
/**/
#pragma libcall DOpusBase SetWindowBusy 186 801
#pragma libcall DOpusBase ClearWindowBusy 18c 801
/**/
#pragma libcall DOpusBase GetString 192 0802
/**/
#pragma libcall DOpusBase FindKeyEquivalent 198 09803
#pragma libcall DOpusBase ShowProgressBar 19e 109804
/**/
#pragma libcall DOpusBase SetWindowID 1a4 A09804
#pragma libcall DOpusBase GetWindowID 1aa 801
#pragma libcall DOpusBase GetWindowAppPort 1b0 801
/**/
#pragma libcall DOpusBase Att_NewList 1b6 001
#pragma libcall DOpusBase Att_NewNode 1bc 109804
#pragma libcall DOpusBase Att_RemNode 1c2 801
#pragma libcall DOpusBase Att_PosNode 1c8 A9803
#pragma libcall DOpusBase Att_RemList 1ce 0802
#pragma libcall DOpusBase Att_FindNode 1d4 0802
#pragma libcall DOpusBase Att_NodeNumber 1da 9802
#pragma libcall DOpusBase Att_FindNodeData 1e0 0802
#pragma libcall DOpusBase Att_NodeDataNumber 1e6 0802
#pragma libcall DOpusBase Att_NodeName 1ec 0802
#pragma libcall DOpusBase Att_NodeCount 1f2 801
#pragma libcall DOpusBase Att_ChangeNodeName 1f8 9802
#pragma libcall DOpusBase Att_FindNodeNumber 1fe 9802
#pragma libcall DOpusBase AddSorted 204 9802
/**/
#pragma libcall DOpusBase BuildMenuStrip 20a 9802
#pragma libcall DOpusBase FindMenuItem 210 0802
#pragma libcall DOpusBase DoPopUpMenu 216 0A9804
#pragma libcall DOpusBase GetPopUpItem 21c 0802
/*                                                             */
#pragma libcall DOpusBase IPC_Startup 222 A9803
#pragma libcall DOpusBase IPC_Command 228 BA910806
#pragma libcall DOpusBase IPC_Reply 22e 801
#pragma libcall DOpusBase IPC_Free 234 801
#pragma libcall DOpusBase IPC_FindProc 23a 109804
#pragma libcall DOpusBase IPC_Quit 240 10803
#pragma libcall DOpusBase IPC_Hello 246 9802
#pragma libcall DOpusBase IPC_Goodbye 24c 09803
#pragma libcall DOpusBase IPC_GetGoodbye 252 801
#pragma libcall DOpusBase IPC_ListQuit 258 109804
#pragma libcall DOpusBase IPC_Flush 25e 801
#pragma libcall DOpusBase IPC_ListCommand 264 3210805
#pragma libcall DOpusBase IPC_ProcStartup 26a 9802
#pragma libcall DOpusBase IPC_Launch 270 B210A9807
/**/
#pragma libcall DOpusBase OpenImage 276 9802
#pragma libcall DOpusBase CloseImage 27c 801
#pragma libcall DOpusBase CopyImage 282 801
#pragma libcall DOpusBase FlushImages 288 0
#pragma libcall DOpusBase RenderImage 28e A109805
#pragma libcall DOpusBase GetImageAttrs 294 9802
/**/
#pragma libcall DOpusBase NewMemHandle 29a 21003
#pragma libcall DOpusBase FreeMemHandle 2a0 801
#pragma libcall DOpusBase ClearMemHandle 2a6 801
#pragma libcall DOpusBase AllocMemH 2ac 0802
#pragma libcall DOpusBase FreeMemH 2b2 801
/**/
#pragma libcall DOpusBase DrawBox 2b8 0A9804
#pragma libcall DOpusBase DrawFieldBox 2be A9803
/**/
#pragma libcall DOpusBase NewLister 2c4 801
#pragma libcall DOpusBase NewButtonBank 2ca 1002
#pragma libcall DOpusBase NewButton 2d0 801
#pragma libcall DOpusBase NewFunction 2d6 0802
#pragma libcall DOpusBase NewInstruction 2dc 90803
#pragma libcall DOpusBase ReadSettings 2e2 9802
#pragma libcall DOpusBase ReadListerDef 2e8 0802
#pragma libcall DOpusBase OpenButtonBank 2ee 801
#pragma libcall DOpusBase DefaultSettings 2f4 801
#pragma libcall DOpusBase DefaultEnvironment 2fa 801
#pragma libcall DOpusBase DefaultButtonBank 300 0
#pragma libcall DOpusBase SaveSettings 306 9802
#pragma libcall DOpusBase SaveListerDef 30c 9802
#pragma libcall DOpusBase SaveButtonBank 312 9802
#pragma libcall DOpusBase CloseButtonBank 318 801
#pragma libcall DOpusBase FreeListerDef 31e 801
#pragma libcall DOpusBase FreeButtonList 324 801
#pragma libcall DOpusBase FreeButtonImages 32a 801
#pragma libcall DOpusBase FreeButton 330 801
#pragma libcall DOpusBase FreeFunction 336 801
#pragma libcall DOpusBase FreeInstruction 33c 801
#pragma libcall DOpusBase FreeInstructionList 342 801
#pragma libcall DOpusBase CopyButtonBank 348 801
#pragma libcall DOpusBase CopyButton 34e 09803
#pragma libcall DOpusBase CopyFunction 354 A9803
#pragma libcall DOpusBase NewFiletype 35a 801
#pragma libcall DOpusBase ReadFiletypes 360 9802
#pragma libcall DOpusBase SaveFiletypeList 366 9802
#pragma libcall DOpusBase FreeFiletypeList 36c 801
#pragma libcall DOpusBase FreeFiletype 372 801
#pragma libcall DOpusBase CopyFiletype 378 9802
#pragma libcall DOpusBase FindFunctionType 37e 0802
#pragma libcall DOpusBase SaveButton 384 9802
#pragma libcall DOpusBase ReadButton 38a 9802
#pragma libcall DOpusBase ReadFunction 390 BA9804
/**/
#pragma libcall DOpusBase OpenIFFFile 396 10803
#pragma libcall DOpusBase CloseIFFFile 39c 801
/**/
#pragma libcall DOpusBase OpenStatusWindow 3a2 01A9805
#pragma libcall DOpusBase SetStatusText 3a8 9802
#pragma libcall DOpusBase UpdateStatusGraph 3ae 109804
/**/
#pragma libcall DOpusBase ReadILBM 3b4 0802
#pragma libcall DOpusBase FreeILBM 3ba 801
#pragma libcall DOpusBase DecodeILBM 3c0 439210807
#pragma libcall DOpusBase DecodeRLE 3c6 801
/**/
#pragma libcall DOpusBase LoadPalette32 3cc 9802
#pragma libcall DOpusBase GetPalette32 3d2 109804
/**/
#pragma libcall DOpusBase OpenBuf 3d8 10803
#pragma libcall DOpusBase CloseBuf 3de 801
#pragma libcall DOpusBase ReadBuf 3e4 09803
#pragma libcall DOpusBase WriteBuf 3ea 09803
#pragma libcall DOpusBase FlushBuf 3f0 801
#pragma libcall DOpusBase SeekBuf 3f6 10803
#pragma libcall DOpusBase ExamineBuf 3fc 9802
/**/
#pragma libcall DOpusBase OpenDisk 402 9802
#pragma libcall DOpusBase CloseDisk 408 801
/**/
#pragma libcall DOpusBase AddScrollBars 40e 0A9804
#pragma libcall DOpusBase FindBOOPSIGadget 414 0802
#pragma libcall DOpusBase BOOPSIFree 41a 801
/**/
#pragma libcall DOpusBase SerialValid 420 801
/**/
#pragma libcall DOpusBase WB_Install_Patch 426 0
#pragma libcall DOpusBase WB_Remove_Patch 42c 0
#pragma libcall DOpusBase WB_AddAppWindow 432 A981005
#pragma libcall DOpusBase WB_RemoveAppWindow 438 801
#pragma libcall DOpusBase WB_FindAppWindow 43e 801
#pragma libcall DOpusBase WB_AppWindowData 444 A9803
#pragma libcall DOpusBase WB_AppWindowLocal 44a 801
#pragma libcall DOpusBase LockAppList 450 0
#pragma libcall DOpusBase NextAppEntry 456 0802
#pragma libcall DOpusBase UnlockAppList 45c 0
/**/
#pragma libcall DOpusBase AddNotifyRequest 462 81003
#pragma libcall DOpusBase RemoveNotifyRequest 468 801
#pragma libcall DOpusBase SendNotifyMsg 46e 98321006
/**/
#pragma libcall DOpusBase StrCombine 474 0A9804
#pragma libcall DOpusBase StrConcat 47a 09803
/**/
#pragma libcall DOpusBase WB_Launch 480 09803
/**/
#pragma libcall DOpusBase CopyLocalEnv 486 801
/**/
#pragma libcall DOpusBase CLI_Launch 48c 32109806
/**/
#pragma libcall DOpusBase SerialCheck 492 9802
#pragma libcall DOpusBase ChecksumFile 498 0802
/**/
#pragma libcall DOpusBase ReplyFreeMsg 49e 801
/**/
#pragma libcall DOpusBase TimerActive 4a4 801
/**/
#pragma libcall DOpusBase NewButtonFunction 4aa 0802
/**/
#pragma libcall DOpusBase IFFOpen 4b0 10803
#pragma libcall DOpusBase IFFClose 4b6 801
#pragma libcall DOpusBase IFFPushChunk 4bc 0802
#pragma libcall DOpusBase IFFWriteChunkBytes 4c2 09803
#pragma libcall DOpusBase IFFPopChunk 4c8 801
#pragma libcall DOpusBase IFFWriteChunk 4ce 109804
/**/
#pragma libcall DOpusBase FindNameI 4d4 9802
/**/
#pragma libcall DOpusBase AnimDecodeRIFFXor 4da 109804
#pragma libcall DOpusBase AnimDecodeRIFFSet 4e0 109804
/**/
#pragma libcall DOpusBase ConvertRawKey 4e6 81003
/**/
#pragma libcall DOpusBase OpenClipBoard 4ec 001
#pragma libcall DOpusBase CloseClipBoard 4f2 801
#pragma libcall DOpusBase WriteClipString 4f8 09803
#pragma libcall DOpusBase ReadClipString 4fe 09803
/**/
#pragma libcall DOpusBase LockAttList 504 0802
#pragma libcall DOpusBase UnlockAttList 50a 801
/**/
#pragma libcall DOpusBase RemovedFunc1 510 0
#pragma libcall DOpusBase RemovedFunc2 516 0
#pragma libcall DOpusBase RemovedFunc3 51c 0
#pragma libcall DOpusBase RemovedFunc4 522 0
#pragma libcall DOpusBase RemovedFunc5 528 0
#pragma libcall DOpusBase RemovedFunc6 52e 0
#pragma libcall DOpusBase RemovedFunc7 534 0
/**/
#pragma libcall DOpusBase GetSemaphore 53a 90803
#pragma libcall DOpusBase FreeSemaphore 540 801
#pragma libcall DOpusBase ShowSemaphore 546 801
/**/
#pragma libcall DOpusBase SaveFunction 54c 9802
/**/
#pragma libcall DOpusBase IFFNextChunk 552 0802
#pragma libcall DOpusBase IFFChunkSize 558 801
#pragma libcall DOpusBase IFFReadChunkBytes 55e 09803
#pragma libcall DOpusBase IFFFileHandle 564 801
#pragma libcall DOpusBase IFFChunkRemain 56a 801
#pragma libcall DOpusBase IFFChunkID 570 801
#pragma libcall DOpusBase IFFGetFORM 576 801
/**/
#pragma libcall DOpusBase ScreenInfo 57c 801
/**/
#pragma libcall DOpusBase GetEditHook 582 81003
#pragma libcall DOpusBase FreeEditHook 588 801
/**/
#pragma libcall DOpusBase InitWindowDims 58e 9802
#pragma libcall DOpusBase StoreWindowDims 594 9802
#pragma libcall DOpusBase CheckWindowDims 59a 9802
/**/
#pragma libcall DOpusBase InitListLock 5a0 9802
/**/
#pragma libcall DOpusBase IPC_QuitName 5a6 09803
/**/
#pragma libcall DOpusBase QualValid 5ac 001
/**/
#pragma libcall DOpusBase FHFromBuf 5b2 801
/**/
#pragma libcall DOpusBase WB_AppIconFlags 5b8 801
/**/
#pragma libcall DOpusBase GetWBArgPath 5be 09803
/**/
#pragma libcall DOpusBase RemovedFunc8 5c4 0
/**/
#pragma libcall DOpusBase DeviceFromLock 5ca 9802
#pragma libcall DOpusBase DeviceFromHandler 5d0 9802
#pragma libcall DOpusBase DevNameFromLock 5d6 32103
/**/
#pragma libcall DOpusBase GetIconFlags 5dc 801
#pragma libcall DOpusBase SetIconFlags 5e2 0802
#pragma libcall DOpusBase GetIconPosition 5e8 A9803
#pragma libcall DOpusBase SetIconPosition 5ee 10803
/**/
#pragma libcall DOpusBase BuildTransDragMask 5f4 2109805
/**/
#pragma libcall DOpusBase GetImagePalette 5fa 801
#pragma libcall DOpusBase FreeImageRemap 600 801
/**/
#pragma libcall DOpusBase SwapListNodes 606 A9803
/**/
#pragma libcall DOpusBase RemovedFunc9 60c 0
/**/
#pragma libcall DOpusBase Seed 612 001
/**/
#pragma libcall DOpusBase RemovedFunc10 618 0
#pragma libcall DOpusBase RemovedFunc11 61e 0
#pragma libcall DOpusBase RemovedFunc12 624 0
/**/
#pragma libcall DOpusBase CopyDiskObject 62a 0802
#pragma libcall DOpusBase FreeDiskObjectCopy 630 801
/**/
#pragma libcall DOpusBase IFFFailure 636 801
/**/
#pragma libcall DOpusBase GetCachedDefDiskObject 63c 001
#pragma libcall DOpusBase FreeCachedDiskObject 642 801
#pragma libcall DOpusBase GetCachedDiskObject 648 801
#pragma libcall DOpusBase GetCachedDiskObjectNew 64e 801
#pragma libcall DOpusBase IconCheckSum 654 0802
/**/
#pragma libcall DOpusBase OpenProgressWindow 65a 801
#pragma libcall DOpusBase CloseProgressWindow 660 801
#pragma libcall DOpusBase HideProgressWindow 666 801
#pragma libcall DOpusBase ShowProgressWindow 66c A9803
#pragma libcall DOpusBase SetProgressWindow 672 9802
#pragma libcall DOpusBase GetProgressWindow 678 9802
/**/
#pragma libcall DOpusBase SetNotifyRequest 67e 10803
/**/
#pragma libcall DOpusBase ChangeAppIcon 684 0BA9805
/**/
#pragma libcall DOpusBase CheckProgressAbort 68a 801
/**/
#pragma libcall DOpusBase GetSecureString 690 801
/**/
#pragma libcall DOpusBase NewButtonWithFunc 696 09803
/**/
#pragma libcall DOpusBase FreeButtonFunction 69c 801
#pragma libcall DOpusBase CopyButtonFunction 6a2 A9803
/**/
#pragma libcall DOpusBase FindPubScreen 6a8 0802
/**/
#pragma libcall DOpusBase SetAppIconMenuState 6ae 10803
/**/
#pragma libcall DOpusBase SearchFile 6b4 1A09805
#pragma libcall DOpusBase ParseDateStrings 6ba BA9804
#pragma libcall DOpusBase DateFromStrings 6c0 A9803
/**/
#pragma libcall DOpusBase GetMatchHandle 6c6 801
#pragma libcall DOpusBase FreeMatchHandle 6cc 801
#pragma libcall DOpusBase MatchFiletype 6d2 9802
/**/
#pragma libcall DOpusBase LayoutResize 6d8 801
/**/
#pragma libcall DOpusBase GetFileVersion 6de A910805
/**/
#pragma libcall DOpusBase AsyncRequest 6e4 1BA90806
#pragma libcall DOpusBase CheckRefreshMsg 6ea 0802
/**/
#pragma libcall DOpusBase RemapImage 6f0 A9803
#pragma libcall DOpusBase FreeRemapImage 6f6 9802
/**/
#pragma libcall DOpusBase FreeAppMessage 6fc 801
#pragma libcall DOpusBase ReplyAppMessage 702 801
/**/
#pragma libcall DOpusBase SetLibraryFlags 708 1002
/**/
#pragma libcall DOpusBase StartRefreshConfigWindow 70e 0802
#pragma libcall DOpusBase EndRefreshConfigWindow 714 801
/**/
#pragma libcall DOpusBase CompareListFormat 71a 9802
/**/
#pragma libcall DOpusBase UpdateGadgetValue 720 09803
#pragma libcall DOpusBase UpdateGadgetList 726 801
/**/
#pragma libcall DOpusBase NewBitMap 72c 8321005
#pragma libcall DOpusBase DisposeBitMap 732 801
/**/
#pragma libcall DOpusBase ParseArgs 738 9802
#pragma libcall DOpusBase DisposeArgs 73e 801
/**/
#pragma libcall DOpusBase SetConfigWindowLimits 744 A9803
/**/
#pragma libcall DOpusBase SetEnv 74a 09803
#pragma libcall DOpusBase IsListLockEmpty 750 801
/**/
#pragma libcall DOpusBase AllocAppMessage 756 09803
#pragma libcall DOpusBase CheckAppMessage 75c 801
#pragma libcall DOpusBase CopyAppMessage 762 9802
#pragma libcall DOpusBase SetWBArg 768 A910805
/**/
#pragma libcall DOpusBase OriginalCreateDir 76e 101
#pragma libcall DOpusBase OriginalDeleteFile 774 101
#pragma libcall DOpusBase OriginalSetFileDate 77a 2102
#pragma libcall DOpusBase OriginalSetComment 780 2102
#pragma libcall DOpusBase OriginalSetProtection 786 2102
#pragma libcall DOpusBase OriginalRename 78c 2102
#pragma libcall DOpusBase OriginalOpen 792 2102
#pragma libcall DOpusBase OriginalClose 798 101
#pragma libcall DOpusBase OriginalWrite 79e 32103
/**/
#pragma libcall DOpusBase CreateTitleGadget 7a4 32109806
#pragma libcall DOpusBase FindGadgetType 7aa 0802
#pragma libcall DOpusBase FixTitleGadgets 7b0 801
/**/
#pragma libcall DOpusBase OriginalRelabel 7b6 2102
/**/
#pragma libcall DOpusBase FakeILBM 7bc 32109806
/**/
#pragma libcall DOpusBase IPC_SafeCommand 7c2 CBA910807
/**/
#pragma libcall DOpusBase ClearFiletypeCache 7c8 0
/**/
#pragma libcall DOpusBase GetTimerBase 7ce 0
/**/
/**/
/**/
/**/
/* end "dopus.library" pragmas */
