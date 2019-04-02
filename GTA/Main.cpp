#include "Reader.h"

void main()
{
	//readDFF("./models/mp5lng.dff");
	// std::fstream object_stream;
	// Buffer buffer = Buffer(object_stream);

	Reader reader = Reader();
	reader.readDFF("D://MyProjects//GTA//models//mp5lng.dff");

}