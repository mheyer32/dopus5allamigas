/*
  XADOpus.module 1.22 - DOpus Magellan plugin to browse through XAD archives
  Copyright (C) 1999,2000 Mladen Milinkovic <mladen.milinkovic@ri.tel.hr>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "XADopus.h"

// Definition of the module
#ifdef __AROS__
ModuleInfo_2 module_info = {
	1,					// Version
	"XADopus.module",	// Module name
	"XADopus.catalog",	// Catalog name
	NULL,				// Flags
	2,					// Number of functions
	{{0, "XADOpen", MSG_XADOPEN_DESC, FUNCF_NEED_SOURCE | FUNCF_NEED_FILES | FUNCF_SINGLE_SOURCE, 0},
	 {1,
	  "XADExtract",
	  MSG_XADEXTRACT_DESC,
	  FUNCF_NEED_SOURCE | FUNCF_NEED_DEST | FUNCF_NEED_FILES | FUNCF_SINGLE_SOURCE,
	  0}}};
#else
ModuleInfo module_info = {
	1,					// Version
	"XADopus.module",	// Module name
	"XADopus.catalog",	// Catalog name
	0,					// Flags
	2,					// Number of functions
	{{0, "XADOpen", MSG_XADOPEN_DESC, FUNCF_NEED_SOURCE | FUNCF_NEED_FILES | FUNCF_SINGLE_SOURCE, 0}}};

ModuleFunction module_func = {1,
							  "XADExtract",
							  MSG_XADEXTRACT_DESC,
							  FUNCF_NEED_SOURCE | FUNCF_NEED_DEST | FUNCF_NEED_FILES | FUNCF_SINGLE_SOURCE,
							  0};
#endif
