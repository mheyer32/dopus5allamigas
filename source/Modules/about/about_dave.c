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

#include <dopus/common.h>

FAR const UWORD dave_data[] = {
	0xbff6, 0x5425, 0x3595, 0x2c90, 0x5c00, 0xbffb, 0x8241, 0x9678, 0x433b, 0xe400, 0x3ff6, 0x9291, 0x6e11, 0x08d5,
	0x5c00, 0xfffb, 0x86ad, 0x1d74, 0x5753, 0xfc00, 0xffe4, 0x362a, 0x15dd, 0x44a0, 0x4c00, 0xffe7, 0x1297, 0x7251,
	0x187b, 0xf400, 0x5fec, 0x30be, 0xf698, 0xd4f6, 0x7c00, 0xbfe7, 0x5f81, 0xe11f, 0x9f11, 0x4c00, 0x9ff4, 0x4a84,
	0x5a1c, 0xbc12, 0xfc00, 0xbffb, 0x14e6, 0x9754, 0xe630, 0x6400, 0x9fff, 0x14b0, 0x105a, 0x4cd5, 0xcc00, 0xfea2,
	0x4235, 0x8124, 0x714f, 0xe400, 0x7474, 0x5a1d, 0x4354, 0x03f9, 0xfc00, 0x8ae4, 0xb5ed, 0x494a, 0x5934, 0xbc00,
	0x5a2f, 0xf4c9, 0xab57, 0x6c2f, 0x0400, 0x4916, 0x0b32, 0xb152, 0x355d, 0x6400, 0x4ab6, 0xcd97, 0x2a56, 0x7545,
	0xfc00, 0x6aaa, 0xab61, 0x79da, 0x6a95, 0x5400, 0x1111, 0xeb68, 0xdf56, 0x1444, 0x4400, 0x5555, 0x9af8, 0xa1eb,
	0xfc44, 0x4000, 0x0000, 0x82a3, 0x0e1a, 0x1000, 0x2000, 0x5554, 0x9180, 0x572b, 0x1555, 0x1400, 0x1088, 0x90e3,
	0x88eb, 0xa111, 0x3c00, 0x4519, 0x05c3, 0x95eb, 0x044c, 0x3400, 0x0000, 0x0470, 0xe882, 0x251a, 0xcc00, 0x5555,
	0x510f, 0x9705, 0x789c, 0x2000, 0x1001, 0x11cc, 0xb1b5, 0x0945, 0x5800, 0x4555, 0x45a2, 0x1ca1, 0x4cfa, 0x6800,
	0x4000, 0x50eb, 0xe164, 0x5031, 0x6800, 0x1555, 0x0528, 0x05fe, 0x893a, 0xbc00, 0x1110, 0x4075, 0x1d02, 0x140e,
	0x3400, 0x4444, 0x21c4, 0xb488, 0xf22e, 0xc800, 0x5004, 0x4364, 0x0ce7, 0x201e, 0x2000, 0x1515, 0x1791, 0xaff7,
	0xe08e, 0xd800, 0x1111, 0x060d, 0x58eb, 0x8e52, 0x2800, 0x4544, 0x79cb, 0x3ce4, 0x1d06, 0xb800, 0xf825, 0x2afe,
	0xbfdf, 0x3f1a, 0xb000, 0x7861, 0x35bd, 0xbcf0, 0xfed6, 0x8800, 0xcbc8, 0x4779, 0xb73a, 0x315e, 0xfc00, 0xd40c,
	0x1b94, 0x2b97, 0x34a6, 0xc400, 0xc40b, 0xdc20, 0xa605, 0xb717, 0x5400, 0x556a, 0x8717, 0x9fe7, 0xfcac, 0xa000,
	0xddad, 0xfdd7, 0xfbf7, 0x9481, 0xcc00, 0xc562, 0x8bcc, 0x7a68, 0x7ac7, 0x6400, 0xc637, 0x71b5, 0xbaa9, 0x74e4,
	0xdc00, 0x0165, 0x036d, 0xad56, 0xa08c, 0x2000, 0xc5a9, 0x775d, 0xc614, 0x7507, 0xcc00, 0x5f46, 0x6af7, 0x012a,
	0x4224, 0xe400, 0x4307, 0x8694, 0x097b, 0xb084, 0xc400, 0x97ef, 0x202b, 0x2923, 0xd1ed, 0x2000, 0x51a1, 0x8ca4,
	0xe508, 0x3d00, 0xe400, 0xc25e, 0xc15b, 0x2a94, 0x47ff, 0x1800, 0xc1df, 0x2a01, 0x8a06, 0x45ec, 0x3800, 0x56fe,
	0xe756, 0xe347, 0xc07c, 0x1800, 0xcb12, 0x2b90, 0x0111, 0xc5b5, 0x1800, 0x94cc, 0xd3c0, 0x4441, 0xc23d, 0x7400,
	0x83be, 0x2381, 0x5556, 0x9530, 0x1400, 0x974f, 0xed0a, 0x009e, 0x66fd, 0x5800, 0x838f, 0x6710, 0x4443, 0x2e76,
	0x1400, 0x950f, 0x7e42, 0xaa17, 0x41ed, 0xe000, 0x869c, 0xc5f8, 0x013c, 0x437c, 0x4000, 0x1783, 0xc481, 0xa13e,
	0x3880, 0x2000, 0xdb4c, 0xe958, 0x065f, 0xa032, 0xbc00, 0x1d83, 0x6138, 0x82de, 0xe0aa, 0x9800, 0x8781, 0xfad7,
	0x5721, 0x0e53, 0x6400, 0x9486, 0x724b, 0xa425, 0x8f60, 0x1400, 0x450e, 0x7e36, 0xdafd, 0x0386, 0x7800, 0xbfed,
	0x13c0, 0x6578, 0x081f, 0xfc00, 0x3fee, 0x1b6a, 0x4dba, 0xe19f, 0xf400, 0x3fed, 0xc464, 0xa37c, 0x0c1f, 0xfc00,
	0x7fe2, 0xeaaa, 0xed32, 0xf1b7, 0x7400, 0xfff3, 0x40bc, 0x0078, 0x484e, 0x6c00, 0x7ffa, 0xba27, 0x4832, 0x5eff,
	0x7400, 0x7ff3, 0x850d, 0x62dd, 0xfe5c, 0x5c00, 0x7ffa, 0x7ae6, 0xa910, 0x5ff7, 0xd400, 0xfff3, 0x7f4f, 0x1aa9,
	0xa61d, 0x5c00, 0x7ff2, 0xcf87, 0xb74a, 0x9e96, 0xe400, 0xfff8, 0x4943, 0xb3f8, 0x161d, 0xec00, 0x3ff2, 0xb0ee,
	0xa974, 0xd9d9, 0xe400, 0xb0ef, 0x1a74, 0x53ff, 0x65d5, 0xec00, 0x2043, 0xf532, 0x815e, 0x9ea4, 0xe800, 0x05d2,
	0x7e9c, 0x4bfc, 0x6e26, 0x3c00, 0xbee8, 0x9f07, 0xf157, 0x9559, 0x7400, 0xeabe, 0xb78e, 0x2afd, 0xc014, 0x8000,
	0xbfff, 0xff43, 0x01df, 0x5fd5, 0x5400, 0x4444, 0x55ee, 0xc3fd, 0x8000, 0x0000, 0xaaaa, 0xefd4, 0x39fe, 0xe2aa,
	0xa800, 0x5555, 0x5566, 0x02f5, 0x3555, 0x5400, 0xaaab, 0xeecc, 0xa17e, 0xdaab, 0x6c00, 0x4555, 0x456a, 0x70d4,
	0x5444, 0x7800, 0xaaee, 0xeac0, 0xd07e, 0xeaa8, 0x1000, 0x5555, 0x5169, 0x6c35, 0x5002, 0xc800, 0xaaaa, 0xaacc,
	0xd19a, 0xba2c, 0x4000, 0x4554, 0x4466, 0x42bc, 0x541f, 0x9c00, 0xaaaa, 0xaaf1, 0x167a, 0xbc6c, 0x2c00, 0x1555,
	0x056a, 0x6c1f, 0x021f, 0x8400, 0xaaaa, 0xaa00, 0x91cd, 0x63d7, 0x9000, 0x4445, 0x053f, 0x6b18, 0x0095, 0xb800,
	0xaaab, 0x8f5d, 0x6840, 0xe89f, 0xd000, 0x0551, 0x1610, 0xb562, 0x9015, 0xa800, 0xaaaa, 0xafd7, 0xb9c8, 0xae3f,
	0xd000, 0x4444, 0x5bc9, 0x3f16, 0x7a09, 0xb000, 0xaaaa, 0xb73e, 0xfc78, 0xf31f, 0x9800, 0x3280, 0x7d9f, 0xf412,
	0x3971, 0x1800, 0x7d2a, 0xd2bf, 0x1b18, 0x23df, 0xb800, 0xd7c5, 0xd29f, 0xbeb0, 0x67d5, 0x4c00, 0x696b, 0x5aaf,
	0x02ed, 0xabdf, 0x9c00, 0xd3cd, 0xfc6d, 0x2dcd, 0xa1d6, 0xb400, 0x6806, 0x142f, 0x9d19, 0x63d4, 0xbc00, 0xc2e0,
	0x3e75, 0x3a43, 0xa132, 0xb400, 0x6800, 0xdf31, 0x9081, 0x617f, 0x3c00, 0xd3ee, 0xb7ac, 0xbaab, 0xe1d6, 0xb400,
	0x7804, 0x1f45, 0x0257, 0xe2b4, 0x3c00, 0xdaea, 0xb5fe, 0x013f, 0xd896, 0xb400, 0x6a06, 0x1ff4, 0x92bf, 0xf09c,
	0x3c00, 0xd0ac, 0xb17d, 0x3055, 0x1856, 0xb400, 0xecee, 0x3bfc, 0x7d7f, 0xf3d5, 0x3c00, 0xc00a, 0xc15e, 0xdfd4,
	0x99d2, 0x9400, 0xecfe, 0x7eaf, 0x7fea, 0x71c7, 0x2400, 0x5454, 0x1157, 0x7551, 0xd97e, 0x8c00, 0xecde, 0x74ab,
	0xbeaa, 0xf244, 0x2400, 0xd298, 0x18c5, 0x5446, 0x58a7, 0x8c00, 0x6efe, 0x622a, 0xaaad, 0x2045, 0x5000, 0xd014,
	0xd8c0, 0x0007, 0x60e2, 0xf800, 0x6eff, 0x9f20, 0xaa2d, 0xb0c5, 0x1800, 0xd015, 0x3c60, 0x0019, 0x5ae5, 0xf800,
	0x6ebf, 0x8ff8, 0x00a2, 0x33a6, 0xb800, 0xd516, 0x1f64, 0x005b, 0x590d, 0x3000, 0x6e7f, 0xb5d6, 0x0af3, 0xabbf,
	0xb800, 0xc056, 0xdbf3, 0x5df9, 0x79e1, 0x5000, 0x6e7f, 0x7179, 0xf7d3, 0x93c0, 0x1c00, 0x54d6, 0xdafb, 0xffa7,
	0xc9c2, 0x1000, 0xee7e, 0x305d, 0xf409, 0xe348, 0xa800, 0xdbaa, 0x9a3c, 0xfaa7, 0xc482, 0x2400, 0xbfe0, 0x8071,
	0xae78, 0x77dd, 0xf000, 0x3fe0, 0x80b1, 0x8e78, 0x3edd, 0xf800, 0x3fe0, 0x41f1, 0x2478, 0x77dd, 0xf000, 0x7fec,
	0x01f1, 0x7d70, 0x2ed4, 0xf800, 0xffec, 0x01d1, 0xffb8, 0x37cd, 0xe000, 0x7fec, 0x4198, 0xbff0, 0xa7dc, 0xf800,
	0x7fec, 0x1030, 0x1d78, 0x07dd, 0xf000, 0x7fec, 0x91f8, 0x1ef0, 0xa6d4, 0xf800, 0xffec, 0xf1f0, 0x0578, 0x77dd,
	0xf000, 0x7fec, 0x23f8, 0x08b8, 0x77d5, 0xe800, 0xffe4, 0x07fc, 0x4c04, 0x57dd, 0xe000, 0x7fec, 0x0ff8, 0x7e8a,
	0x269d, 0xe800, 0xc0f0, 0x05f8, 0x3c00, 0x107d, 0xe000, 0x7fb8, 0x2af8, 0x3ea1, 0xd7c5, 0xec00, 0xfffd, 0x8170,
	0x1401, 0x11d5, 0x4000, 0xffff, 0xa0f8, 0x0ea8, 0x6aa6, 0x0800, 0xeabe, 0xc071, 0xd500, 0x8007, 0x8000, 0x0000,
	0x00bf, 0x7e20, 0xe02a, 0xa800, 0x0000, 0x0016, 0xfc00, 0x4000, 0x0000, 0x0000, 0x002c, 0x3e00, 0x2800, 0x0000,
	0x0000, 0x001e, 0x0d00, 0x4800, 0x0000, 0x0000, 0x003c, 0x0680, 0x2000, 0x7800, 0x0000, 0x001a, 0x0300, 0x0001,
	0xbc00, 0x0000, 0x0030, 0x2980, 0x0007, 0x1400, 0x0000, 0x0018, 0x10c0, 0x0005, 0x4c00, 0x0000, 0x003c, 0x29e0,
	0x0003, 0xc400, 0x0000, 0x001e, 0x0340, 0x0000, 0x2400, 0x0000, 0x000f, 0x17fc, 0x0383, 0xbc00, 0x0000, 0x0015,
	0xeffc, 0x0020, 0x3c00, 0x0000, 0x00ff, 0xa63e, 0x80e8, 0x2c00, 0x0000, 0x00c0, 0xbc7b, 0xc048, 0x0400, 0x0000,
	0x00a2, 0xb7c1, 0x8008, 0x6400, 0x0000, 0x01ff, 0xf7e3, 0xc008, 0x1c00, 0x0000, 0x03d7, 0x71c1, 0xd808, 0x6400,
	0x0000, 0x0608, 0xf003, 0xddfc, 0x0400, 0x0000, 0x0cff, 0xfb81, 0xf718, 0x2400, 0xc770, 0x147f, 0x79e3, 0x8e9c,
	0x2400, 0x0500, 0x3c7e, 0xe0e1, 0xb6b8, 0x2400, 0x8780, 0x2e7c, 0x3e43, 0xb6f8, 0x4800, 0x0500, 0xae78, 0x7e06,
	0xb6f8, 0x5800, 0x8780, 0x0a13, 0xd20e, 0x36f9, 0x7800, 0x0509, 0xf302, 0xe31e, 0xf6fb, 0x7800, 0x87af, 0xc1f1,
	0xc5fc, 0x36dd, 0x7800, 0x0503, 0xe0f1, 0xeffe, 0xf6d8, 0xf800, 0x87ad, 0xc05f, 0x4554, 0x7659, 0x7800, 0x0507,
	0x60ba, 0xffa8, 0x761b, 0xf800, 0x87a9, 0xc001, 0xffc0, 0x6e19, 0x7800, 0x0705, 0x600b, 0xefc0, 0xe61b, 0xf800,
	0x87ad, 0xc003, 0xc780, 0xae59, 0x7800, 0x83ed, 0x4003, 0x8280, 0xe75a, 0xf800, 0x87a9, 0xf001, 0x0001, 0xaf1d,
	0x7800, 0x83fd, 0x7800, 0x8001, 0x6758, 0xf800, 0x83fd, 0x3c00, 0x0001, 0xef71, 0x7000, 0x83fd, 0x7700, 0x0001,
	0xe6db, 0xf800, 0x05b9, 0x3a00, 0x0001, 0xee38, 0x7000, 0x83fd, 0x7280, 0x0002, 0xc6da, 0xa800, 0x07bd, 0xfb00,
	0x0000, 0x1e7d, 0x0000, 0x83fc, 0xfec0, 0x0002, 0x0e5a, 0xa000, 0x07bc, 0xdfc0, 0x0006, 0x0478, 0x0000, 0x83bc,
	0xffe0, 0x000f, 0x8f78, 0x0000, 0x03bd, 0xfff0, 0x0007, 0x8770, 0x0000, 0x83fc, 0xf5d8, 0x000f, 0xc7f8, 0x0000,
	0x07fd, 0xfbfc, 0x0007, 0xc7dc, 0x0000, 0x83fc, 0x717e, 0x082f, 0xefff, 0xe000, 0x837d, 0xfafc, 0x005f, 0xf7fd,
	0xfc00, 0x83fe, 0x705e, 0x0bfd, 0xff7f, 0xfc00, 0x87aa, 0xfa3f, 0x055f, 0xff7d, 0xdc00, 0x7ff0, 0x61e0, 0xdff0,
	0x0fe3, 0xe000, 0xfff0, 0x61e0, 0xfff0, 0x0fe3, 0xe000, 0xfff0, 0x01e0, 0xdff0, 0x0fe3, 0xe000, 0xbff0, 0x01e0,
	0x82f8, 0x0feb, 0xe000, 0x3ff0, 0x01e0, 0x0070, 0x0ff3, 0xf000, 0xbff0, 0x21e0, 0x0038, 0x0fe3, 0xe000, 0xbff0,
	0x61c0, 0x0030, 0x0fe3, 0xe000, 0xbff0, 0x6000, 0x0038, 0x0feb, 0xe000, 0x3ff0, 0x0000, 0x0010, 0x0fe3, 0xe000,
	0xbff0, 0x0000, 0x0000, 0x2feb, 0xf000, 0x3ff0, 0x0000, 0x0000, 0x2fe3, 0xf000, 0xbff0, 0x0000, 0x0000, 0x0fe3,
	0xf000, 0x3f00, 0x0000, 0x0000, 0x0f83, 0xf000, 0xffff, 0xc000, 0x0000, 0x2ffb, 0xf000, 0xffff, 0xc000, 0x0000,
	0xfff8, 0xfc00, 0xffff, 0xc000, 0x0000, 0xfff8, 0xfc00, 0x1541, 0x0000, 0x0000, 0x7ff8, 0x7c00, 0x0000, 0x0000,
	0x8000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0003, 0xc000, 0x1000, 0x0000, 0x0000,
	0x0001, 0xf000, 0x3000, 0x0000, 0x0000, 0x0003, 0xf800, 0x0000, 0x8000, 0x0000, 0x0005, 0xfc00, 0x0000, 0xc000,
	0x0000, 0x000f, 0xfe00, 0x0000, 0xe800, 0x0000, 0x0007, 0xff00, 0x0000, 0x3000, 0x0000, 0x0003, 0xfe00, 0x0000,
	0x3800, 0x0000, 0x0001, 0xfc00, 0x0000, 0x7800, 0x0000, 0x0000, 0xe800, 0x0000, 0x7800, 0x0000, 0x0000, 0x1000,
	0x01c0, 0x7800, 0x0000, 0x0000, 0x7800, 0x0000, 0x7800, 0x0000, 0x0000, 0x7004, 0x0000, 0x7800, 0x0000, 0x0000,
	0x783e, 0x0000, 0x3800, 0x0000, 0x0000, 0x781c, 0x0000, 0x7000, 0x0000, 0x0028, 0xfe3e, 0x0000, 0x3800, 0x0000,
	0x01f7, 0xfffc, 0x0000, 0x7800, 0x0000, 0x03ff, 0xfffe, 0x08e0, 0x7800, 0x0000, 0x03ff, 0xfffc, 0x71e0, 0x7800,
	0x82f0, 0x03ff, 0xfffe, 0x79e0, 0x7800, 0x0070, 0x11ff, 0xc1fc, 0x79e0, 0x3000, 0x82f0, 0x11ff, 0x81f8, 0x79e0,
	0x2000, 0x0070, 0x11ff, 0x01f0, 0x79e0, 0x0000, 0x82f0, 0x08ff, 0x00e0, 0x39e0, 0x0000, 0x0050, 0x000e, 0x0000,
	0x79e0, 0x0000, 0x82fc, 0x000e, 0x0000, 0x39a0, 0x0000, 0x0050, 0x0000, 0x0000, 0x39a0, 0x0000, 0x82f8, 0x8000,
	0x0000, 0x39e0, 0x0000, 0x0054, 0x0000, 0x0000, 0x31e0, 0x0000, 0x80f8, 0x8000, 0x0000, 0x39e0, 0x0000, 0x0050,
	0x0000, 0x0000, 0x71a0, 0x0000, 0x0010, 0x8000, 0x0000, 0x38a0, 0x0000, 0x0054, 0x0000, 0x0000, 0x70e0, 0x0000,
	0x0000, 0x8000, 0x0000, 0xb8a0, 0x0000, 0x0000, 0xc000, 0x0000, 0x3080, 0x0000, 0x0000, 0x8800, 0x0000, 0x39a0,
	0x0000, 0x0044, 0xc500, 0x0000, 0x31c0, 0x0000, 0x0000, 0x8d00, 0x0000, 0x39a0, 0x0000, 0x0040, 0x0400, 0x0000,
	0x0180, 0x0000, 0x0000, 0x0000, 0x0000, 0x01a0, 0x0000, 0x0040, 0x0000, 0x0000, 0x0180, 0x0000, 0x0040, 0x0000,
	0x0000, 0x0080, 0x0000, 0x0040, 0x0000, 0x0000, 0x0080, 0x0000, 0x0000, 0x0a20, 0x0000, 0x0000, 0x0000, 0x0000,
	0x0400, 0x0000, 0x0000, 0x0000, 0x0000, 0x8e80, 0x0000, 0x0000, 0x0000, 0x0000, 0x0500, 0x0000, 0x0000, 0x0000,
	0x0001, 0x8fa0, 0x0002, 0x0080, 0x0000, 0x0055, 0x05c0, 0x0000, 0x0000, 0x0000};

ULONG
dave_palette[] = {0x00100000, 0x00000000, 0x00000000, 0x00000000, 0x11111111, 0x11111111, 0x11111111,
				  0x22222222, 0x22222222, 0x22222222, 0x33333333, 0x33333333, 0x33333333, 0x44444444,
				  0x44444444, 0x44444444, 0x55555555, 0x55555555, 0x55555555, 0x66666666, 0x66666666,
				  0x66666666, 0x77777777, 0x77777777, 0x77777777, 0x88888888, 0x88888888, 0x88888888,
				  0x99999999, 0x99999999, 0x99999999, 0xaaaaaaaa, 0xaaaaaaaa, 0xaaaaaaaa, 0xbbbbbbbb,
				  0xbbbbbbbb, 0xbbbbbbbb, 0xcccccccc, 0xcccccccc, 0xcccccccc, 0xdddddddd, 0xdddddddd,
				  0xdddddddd, 0xeeeeeeee, 0xeeeeeeee, 0xeeeeeeee, 0xffffffff, 0xffffffff, 0xffffffff};
