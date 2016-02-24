#ifndef ANIMATION_H
#define ANIMATION_H

class Animation
{
	public:
		Animation();
		~Animation();
		void Slash(double dt, float& targetRotation);
		void Shoot(double dt, float& targetTranslation);
		void Mine(double dt, float& targetRotation);
		bool Update(double dt);

		bool sliceUp;
		bool sliceDown;
		bool moveFront;
		bool moveBack;
};

#endif