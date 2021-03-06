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

#ifndef StackTraceMap_H
#define StackTraceMap_H

#include <QMutex>
#include "Math.h"
#include <unordered_set>
#include <map>
#include <string>

class StackTraceMap {
public:
     StackTraceMap();
    ~StackTraceMap();

    void    insert(uint64 addr, const char *stack)
    {
	QMutexLocker lock(&myLock);
	myMap[addr] = stack;
    }

    const char	*findClosestStackTrace(uint64 addr)
    {
	QMutexLocker lock(&myLock);
	// Finds the element above and below the query address, and returns
	// the closer of the two.
	auto hi = myMap.lower_bound(addr);
	if (hi != myMap.end())
	{
	    auto lo = --hi;
	    if (lo != myMap.end())
	    {
		return (hi->first - addr) <= (addr - lo->first) ?
		    hi->second.c_str() : lo->second.c_str();
	    }
	    return hi->second.c_str();
	}

	return 0;
    }

private:
    std::map<uint64, std::string>  myMap;
    QMutex			   myLock;
};

#endif
