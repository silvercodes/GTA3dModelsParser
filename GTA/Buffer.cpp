#include "Buffer.h"

Buffer::Buffer(std::fstream &stream) {
	this->position = 0;
	this->object_stream.swap(stream);
}

void Buffer::skip(unsigned int offset) {
	this->position += offset;
	char * buffer = new char[offset];
	this->object_stream.read(buffer, offset);

	delete[] buffer;
}