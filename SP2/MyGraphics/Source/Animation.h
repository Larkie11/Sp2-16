#ifndef ANIMATION_H
#define ANIMATION_H
#include "Mesh.h"

class Animation
{
	public:
		Animation();
		~Animation();
		void Slash(double dt, float& targetRotation, bool& start);
		void Shoot(double dt, float& targetTranslation, bool& start);
		void Mine(double dt, float& targetRotation, bool& start);
		void moveSword(double dt, float& targetTranslation, bool usingSword);
		void moveGun(double dt, float& targetTranslation, bool usingGun);
		void explosion(double dt, float& explosionScale, bool& playExplosion);
		bool Update(double dt);

		bool sliceUp;
		bool sliceDown;
		bool moveFront;
		bool moveBack;

		bool switchDown;
		bool switchUp;
};

#endif