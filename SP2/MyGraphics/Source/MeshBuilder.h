#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Mesh.h"
#include "Vertex.h"

/******************************************************************************/
/*!
		Class MeshBuilder:
\brief	Provides methods to generate mesh of different shapes
*/
/******************************************************************************/
class MeshBuilder
{
public:
	//Lab meshes
	static Mesh* GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ);
    static Mesh* GenerateQuad(const std::string &meshName, Color color, float lengthX, float lengthY);
	static Mesh* GenerateRepeatQuad(const std::string &meshName, Color color, float lengthX, float lengthY, int textCoord);
    static Mesh* GenerateCube(const std::string &meshName, Color color, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateCircle(const std::string &meshName, Color color, float lengthX, float lengthZ);
	static Mesh* GenerateCircles(const std::string &meshName, Color color, unsigned numSlices);
	static Mesh* GenerateHemisphere(const std::string &meshName, Color color, float lengthX, float lengthY, float lengthZ, float radius);
	static Mesh* GenerateSphere(const std::string &meshName, Color color, float radius, float lengthX, float lengthY);
	static Mesh* GenerateSpheres(const std::string &meshName, Color color, unsigned numStacks, unsigned numSlices, float lengthX = 1, float lengthY = 1, float lengthZ = 1);
	static Mesh* GenerateConeHem(const std::string &meshName, Color color, unsigned numStacks = 18, unsigned numSlices = 36);
	static Mesh* GenerateCylinder(const std::string &meshName, Color color, unsigned numSlices);
	static Mesh* GenerateCone(const std::string &meshName, Color color, unsigned numSlices);
	static Mesh* GenerateRing(const std::string &meshName, Color color, float innerRadius, float outerRadius);
	static Mesh* GenerateRings(const std::string &meshName, Color color, float innerRadius, unsigned numSlices);
	static Mesh* GenerateTorus(const std::string &meshName, Color color, float outerRadius, float innerRadius, unsigned numSlices, unsigned numStacks);
	static Mesh* GenerateOBJ(const std::string &meshName, const std::string &file_path);
	static Mesh* GenerateText(const std::string &meshName, unsigned numRow, unsigned numCol);

	//Assignment 2 meshes
	static Mesh* GenerateCone2(const std::string &meshName, Color color, unsigned numStacks, unsigned numSlices, float lengthX = 1, float lengthY = 1, float lengthZ = 1);
	static Mesh* GenerateCylinder2(const std::string &meshName, Color color, float height, float numStack, float radius, float lengthX = 1, float lengthY = 1, float lengthZ = 1);
	static Mesh* GenerateCones2(const std::string &meshName, Color color, unsigned numSlices, float lengthX = 1, float lengthY = 1, float lengthZ = 1);
	static Mesh* GenerateCubes2(const std::string &meshName, Color color, float lengthX = 1, float lengthY = 1, float lengthZ = 1);
	static Mesh* GenerateHemispheres2(const std::string &meshName, Color color, unsigned numStacks, unsigned numSlices, float lengthX = 1, float lengthY = 1, float lengthZ = 1);
};

#endif