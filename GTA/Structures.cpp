struct Header {
	unsigned int id;
	unsigned int size;
	unsigned int version;
};

struct Clump {
	unsigned int count;
};

struct GeometryList {
	unsigned int count;
};

struct Flags {
	bool triangleStrip;
	bool includesVertex;
	bool includesUVs;
	bool includesColors;
	bool includesNormals;
	bool geometryLit;
	bool modulateMaterialColor;
	bool multipleUVSets;
};

struct Geometry {
	unsigned short flags;
	unsigned char NumTexCoorsCustom;
	unsigned char GeometryNativeFlags;
	unsigned int triangles;
	unsigned int vertices;
	unsigned int frames;
};

struct Color {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

struct UV {
	float u;
	float v;
};

struct Face {
	unsigned short v2;
	unsigned short v1;
	unsigned short material_id;
	unsigned short v3;
};

struct boundingSphere {
	float x;
	float y;
	float z;
	float radius;
	float hasPosition;
	float hasNormals;
};

struct attributesInfo {
	unsigned int hasPosition;
	unsigned int hasNormal;
};

struct Vertex {
	float x;
	float y;
	float z;
};

typedef Vertex Normal;