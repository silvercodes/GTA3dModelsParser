#pragma once
#ifndef __READER_H__

#define _CRT_SECURE_NO_WARNINGS
#define __READER_H__

#include "Structures.cpp"
#include "Buffer.h"
#include "Globals.h"


class Reader
{
public:
	Flags readFlags(unsigned short flags);
	void readGeometry(Buffer &model);
	void readDFF(const char* path);
};

#endif