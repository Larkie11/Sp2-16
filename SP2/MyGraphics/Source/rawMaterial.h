/************************************************************/
/*!
\file	rawMaterial.h
\author	Heng Soon Yap
\par	email:Romeoyap\@hotmail.com
\brief
A class for the raw material to define them in the game
*/
/************************************************************/

#ifndef RAWMATERIAL_H
#define RAWMATERIAL_H
#include "Vector3.h"
#include "CollisionDetector.h"
#include "mesh.h"

/************************************************************/
/*!
Class Dweller:
\brief	Defines a raw material attribute
*/
/************************************************************/

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