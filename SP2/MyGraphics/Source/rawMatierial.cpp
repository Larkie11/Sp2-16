#include "rawMaterial.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"

rawMaterial::rawMaterial() :hp(3), isAlive(true)
{
	shape = MeshBuilder::GenerateOBJ("material", "OBJ//rawMaterial.obj");
	shape->textureID = LoadTGA("Image//RawMaterial.tga");
};
rawMaterial::~rawMaterial()
{};
