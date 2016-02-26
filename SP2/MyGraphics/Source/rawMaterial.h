#ifndef RAWMATERIAL_H
#define RAWMATERIAL_H
#include "Vector3.h"
#include "CollisionDetector.h"
#include "mesh.h"

class rawMaterial
{
	public:
		int hp;
		Vector3 pos;
		Mesh* shape;
		bool isAlive;

		rawMaterial();
		~rawMaterial();
};
#endif