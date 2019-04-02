#include "Reader.h"

Flags Reader::readFlags(unsigned short flags) {
	Flags result = {
		(flags & (1 << 0)) != 0,
		(flags & (1 << 1)) != 0,
		(flags & (1 << 2)) != 0,
		(flags & (1 << 3)) != 0,
		(flags & (1 << 4)) != 0,
		(flags & (1 << 5)) != 0,
		(flags & (1 << 6)) != 0,
		(flags & (1 << 7)) != 0
	};

	std::cout << std::dec << '\n';
	std::cout << result.triangleStrip << result.includesVertex << result.includesUVs;
	std::cout << result.includesColors << result.includesNormals << result.geometryLit;
	std::cout << result.modulateMaterialColor << result.multipleUVSets << '\n';

	return result;
}

void Reader::readGeometry(Buffer &model) {

	std::ofstream out;
	out.open("mp5.obj", std::ios::app);
	out << "o Grip_Plane\n";


	Header head{};
	std::cout << "SKIP: " << "\n\n";
	model.read(head);
	std::cout << std::dec << head.size << "\n";
	model.read(head);
	std::cout << std::dec << head.size << "\n";


	Geometry geom{};
	model.read(geom);
	std::cout << std::dec << "Geometry triangles: " << geom.triangles << '\n';
	std::cout << std::dec << "Geometry vertices: " << geom.vertices << '\n';
	std::cout << std::dec << "Geometry frames: " << geom.frames << '\n';

	Flags flags = readFlags(geom.flags);

	// colors
	if (flags.includesColors != 0) {
		for (unsigned int i = 0; i < geom.vertices; i++) {
			Color color{};
			model.read(color);
			//std::cout << "R:" << color.r << " G:" << color.g << " B:" << color.b;
		}
	}

	//UV
	std::cout << "geom.NumTexCoorsCustom = " << std::dec << geom.NumTexCoorsCustom << "\n";
	if (flags.includesUVs == 1 || flags.multipleUVSets == 1) {
		//for (unsigned int i = 0; i < geom.NumTexCoorsCustom; i++) {
			for (unsigned int i = 0; i < geom.vertices; i++) {
				UV uv{};
				model.read(uv);
				//std::cout << "UV: " << uv.u << " " << uv.v << "\n";
			}
		//}
	}

	//
	// TODO Textured2 == 1!!
	// TODO Textured2 == 1!!
	//

	// Triangles
	Face* triangles = new Face[geom.triangles];
	for (unsigned int i = 0; i < geom.triangles; i++) {
		Face face{};
		model.read(face);

		//std::cout << "v1: " << face.v1 << " v2: " << face.v2 << " v3: " << face.v3 << "\n";
		triangles[i] = face;
	}

	// Bounding sphere
	boundingSphere bs{};
	model.read(bs);
	//std::cout << "Bounding sphere: x: " << bs.x << " y: " << bs.y << " z: " << bs.z << " radius: " << bs.radius << "\n";


	// Vertices
	Vertex* vertices = new Vertex[geom.vertices];
	for (unsigned int i = 0; i < geom.vertices; i++) {
		Vertex vertex{};
		model.read(vertex);
		//std::cout << "vertices: x: " << vertex.x << " y: " << vertex.y << " z: " << vertex.z << "\n";
		out << "v " << vertex.x << " " << vertex.y << " " << vertex.z << "\n";
		vertices[i] = vertex;
	}

	// Normals
	Normal* normals = new Normal[geom.vertices];
	if (flags.includesNormals != 0) {
		for (unsigned int i = 0; i < geom.vertices; i++) {
			Normal normal{};
			model.read(normal);
			//std::cout << "x: " << normal.x << " y: " << normal.y << " z: " << normal.z << "\n";
			out << "vn " << normal.x << " " << normal.y << " " << normal.z << "\n";
			normals[i] = normal;
		}
	}

	////out << "usemtl None\ns off\n";

	for (unsigned int i = 0; i < geom.triangles; i++) {
		// std::cout << "f " << triangles[i].v1 << "//" << triangles[i].v1;
		// std::cout << " " << triangles[i].v2 << "//" << triangles[i].v2;
		// std::cout << " " << triangles[i].v3 << "//" << triangles[i].v3 << "\n";
		/*out << "f " << triangles[i].v1 << "//" << triangles[i].v1;
		out << " " << triangles[i].v2 << "//" << triangles[i].v2;
		out << " " << triangles[i].v3 << "//" << triangles[i].v3 << "\n";*/
		 out << "f " << triangles[i].v1 + 1;
		 out << " " << triangles[i].v2 + 1;
		 out << " " << triangles[i].v3 + 1 << "\n";
	}



	out.close();
}


void Reader::readDFF(const char* path) {
	std::fstream object_stream;
	object_stream.open(path, std::fstream::in | std::fstream::binary);

	Buffer model = Buffer(object_stream);

	Header head{};
	model.read(head);

	std::cout << "id: " << head.id << "\n";
	std::cout << "size: " << head.size << "\n";
	std::cout << "version: " << std::hex << head.version << "\n";

	unsigned int length = head.size;

	while (model.position < length) {
		model.read(head);
		switch (head.id) {
			case RW_GEOMETRY_LIST:
			{
				model.read(head);

				GeometryList geom_list{};
				model.read(geom_list);
				
				std::cout << "geom_list.count = " << geom_list.count << "\n";

				for (unsigned int i = 0; i < geom_list.count; i++)
				{
					readGeometry(model);
				}
				break;
			}
			default:
			{
				model.skip(head.size);
			}
			break;
		}
	}
	object_stream.close();
}










//// #include "Reader.h"
//
//#include <fstream>
//#include "Main.h"
//#include "Buffer.h"
//
//Flags readFlags(unsigned short flags) {
//	Flags result = {
//		(flags & (1 << 0)) != 0,
//		(flags & (1 << 1)) != 0,
//		(flags & (1 << 2)) != 0,
//		(flags & (1 << 3)) != 0,
//		(flags & (1 << 4)) != 0,
//		(flags & (1 << 5)) != 0,
//		(flags & (1 << 6)) != 0,
//		(flags & (1 << 7)) != 0
//	};
//
//	std::cout << std::dec << '\n';
//	std::cout << result.triangleStrip << result.includesVertex << result.includesUVs;
//	std::cout << result.includesColors << result.includesNormals << result.geometryLit;
//	std::cout << result.modulateMaterialColor << result.multipleUVSets << '\n';
//
//	return result;
//}
//
//void readDFF(const char* path) {
//	std::fstream object_stream;
//	object_stream.open(path, std::fstream::in | std::fstream::binary);
//
//	Buffer model = Buffer(object_stream);
//
//	Header head{};
//	model.read(head);
//
//	std::cout << "id: " << head.id << "\n";
//	std::cout << "size:" << head.size << "\n";
//	std::cout << "version" << std::hex << head.version << "\n";
//	//*id: 16
//	//*size:298547
//	//*version1803ffff
//	unsigned int length = head.size;
//
//	while (model.position < length) {
//		model.read(head);
//		switch (head.id) {
//		case RW_GEOMETRY_LIST:
//		{
//			model.read(head);
//
//			GeometryList geom_list{};
//			model.read(geom_list);
//
//			std::cout << "geom_list.count = " << geom_list.count << "\n";
//
//			for (unsigned int i = 0; i < geom_list.count; i++) {
//				readGeometry(model);
//			}
//			break;
//		}
//		default:
//		{
//			model.skip(head.size);
//		}
//		break;
//		}
//	}
//	object_stream.close();
//}
//
//void readGeometry(Buffer &model) {
//
//	std::ofstream out;
//	out.open("mp5.obj", std::ios::app);
//	out << "o Grip_Plane\n";
//
//
//	Header head{};
//
//	std::cout << "SKIP: " << "\n\n";
//
//	model.read(head);
//	model.read(head);
//
//
//	Geometry geom{};
//	model.read(geom);
//	std::cout << std::dec << "Geometry triangles: " << geom.triangles << '\n';
//	std::cout << std::dec << "Geometry vertices: " << geom.vertices << '\n';
//	std::cout << std::dec << "Geometry frames: " << geom.frames << '\n';
//
//	Flags flags = readFlags(geom.flags);
//
//	// colors
//	if (flags.includesColors == 1) {
//		for (unsigned int i = 0; i < geom.vertices; i++) {
//			Color color{};
//			model.read(color);
//			//std::cout << "R:" << color.r << " G:" << color.g << " B:" << color.b;
//		}
//	}
//
//	//UV
//	std::cout << "geom.NumTexCoorsCustom = " << std::dec << geom.NumTexCoorsCustom << "\n";
//	if (flags.includesUVs == 1 || flags.multipleUVSets == 1) {
//		for (unsigned int i = 0; i < geom.NumTexCoorsCustom; i++) {
//			for (unsigned int j = 0; j < geom.vertices; j++) {
//				UV uv{};
//				model.read(uv);
//				//std::cout << "UV: " << uv.u << " " << uv.v << "\n";
//			}
//		}
//	}
//
//	// Triangles
//	//Face triangles[geom.triangles];
//	//for (unsigned int i = 0; i < geom.triangles; i++) {
//	//	Face face{};
//	//	model.read(face);
//
//	//	//std::cout << "v1: " << face.v1 << " v2: " << face.v2 << " v3: " << face.v3 << "\n";
//	//	triangles[i] = face;
//	//}
//
//	//// Bounding sphere
//	//boundingSphere bs{};
//	//model.read(bs);
//	////std::cout << "Bounding sphere: x: " << bs.x << " y: " << bs.y << " z: " << bs.z << " radius: " << bs.radius << "\n";
//
//	//// hasPosition, hasNormals
//	//model.read(head);
//	//model.read(head);
//
//	//// Vertices
//	//Vertex vertices[geom.vertices];
//	//for (unsigned int i = 0; i < geom.vertices; i++) {
//	//	Vertex vertex{};
//	//	model.read(vertex);
//	//	//std::cout << "vertices: x: " << vertex.x << " y: " << vertex.y << " z: " << vertex.z << "\n";
//	//	out << "v " << vertex.x << " " << vertex.y << " " << vertex.z << "\n";
//	//	vertices[i] = vertex;
//	//}
//
//	//// Normals
//	//Normal normals[geom.vertices];
//	//if (flags.includesNormals == 1) {
//	//	for (unsigned int i = 0; i < geom.vertices; i++) {
//	//		Normal normal{};
//	//		model.read(normal);
//	//		//std::cout << "x: " << normal.x << " y: " << normal.y << " z: " << normal.z << "\n";
//	//		out << "vn " << normal.x << " " << normal.y << " " << normal.z << "\n";
//	//		normals[i] = normal;
//	//	}
//	//}
//
//	////out << "usemtl None\ns off\n";
//
//	//for (unsigned int i = 0; i < geom.triangles; i++) {
//	//	// std::cout << "f " << triangles[i].v1 << "//" << triangles[i].v1;
//	//	// std::cout << " " << triangles[i].v2 << "//" << triangles[i].v2;
//	//	// std::cout << " " << triangles[i].v3 << "//" << triangles[i].v3 << "\n";
//	//	out << "f " << triangles[i].v1 << "//" << triangles[i].v1;
//	//	out << " " << triangles[i].v2 << "//" << triangles[i].v2;
//	//	out << " " << triangles[i].v3 << "//" << triangles[i].v3 << "\n";
//	//	// out << "f " << triangles[i].v1;
//	//	// out << " " << triangles[i].v2;
//	//	// out << " " << triangles[i].v3 << "\n";
//	//}
//
//
//
//	out.close();
//}