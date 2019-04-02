#pragma once
#ifndef __BUFFER_H__

#define _CRT_SECURE_NO_WARNINGS
#define __BUFFER_H__

#include <iostream>
#include <fstream>

class Buffer
{
public:
	unsigned int position;
	std::fstream object_stream;

	Buffer(std::fstream &stream);

	template <class T>
	void read(T &object) 
	{
		this->object_stream.read((char*)&object, sizeof(T));
		this->position += sizeof(T);
	}

	void skip(unsigned int offset);
};


#endif // !__BUFFER_H__