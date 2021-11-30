#ifndef myBulletHitEffect_H
#define myBulletHitEffect_H
#include "effect.h"

class myBulletHitEffect: public effect {
	myBulletHitEffect* prev; //이전 노드
	myBulletHitEffect* node; // 다음 노드
	float timeMax; //사라지는 시간
	float time; // 사라지기 위해 움직이는 시간
public:
	myBulletHitEffect();
	void showMyBulletHitEffect(); //내 총알 타격 효과를 그리는 함수

	/*getter setter*/
	myBulletHitEffect* getPrev();
	void setPrev(myBulletHitEffect* input);

	myBulletHitEffect* getNode();
	void setNode(myBulletHitEffect* input);

	float getTimeMax();
	void setTimeMax(float input);

	float getTime();
	void setTime(float input);
};

#endif;