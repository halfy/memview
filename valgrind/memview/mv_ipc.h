/*
   This file is part of memview, a real-time memory trace visualization
   application.

   Copyright (C) 2013 Andrew Clinton

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307, USA.

   The GNU General Public License is contained in the file COPYING.
*/

#ifndef MV_IPC_H
#define MV_IPC_H

//
// The unidirectional (tool to memview) pipe communication protocol is
// simple.  First a message header is sent, followed by the data.  The size
// of the data is specified in the header.
//

// Message types
typedef enum {
    MV_BLOCK,
    MV_STACKTRACE
} MV_MessageType;

typedef struct {
    int			    mySize;
    int			    myType;
} MV_Header;

#define MV_STACKTRACE_BUFSIZE 4096

typedef struct {
    unsigned long long	myAddr;
    char		myBuf[MV_STACKTRACE_BUFSIZE];
    int			mySize;
} MV_StackInfo;

#define MV_BlockSize	(1024*32)

#define MV_AddrMask 0x001FFFFFFFFFFFFFul

#define MV_SizeMask 0xFF00000000000000ul
#define MV_SizeShift 56

#define MV_TypeMask 0x00E0000000000000ul
#define MV_TypeShift 53

// Order is important here - we use a max() for downsampling, which will
// cause reads to be preferred over writes when MV_ event time matches.  If
// you update MV_se values, you will also need to update MV_ shader.frag
// code.
#define MV_TypeAlloc  0
#define MV_TypeInstr  1
#define MV_TypeWrite  2
#define MV_TypeRead   3
#define MV_TypeFree   4

#define MV_ShiftedAlloc  ((unsigned long long)MV_TypeAlloc << MV_TypeShift)
#define MV_ShiftedInstr  ((unsigned long long)MV_TypeInstr << MV_TypeShift)
#define MV_ShiftedWrite  ((unsigned long long)MV_TypeWrite << MV_TypeShift)
#define MV_ShiftedRead   ((unsigned long long)MV_TypeRead << MV_TypeShift)
#define MV_ShiftedFree   ((unsigned long long)7 << MV_TypeShift)

typedef struct {
    unsigned long long	myAddr[MV_BlockSize];
    unsigned int	myEntries;
} MV_TraceBlock;

// Template for future work
typedef struct {} MV_SharedData;

#endif

