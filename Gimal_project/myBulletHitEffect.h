#ifndef myBulletHitEffect_H
#define myBulletHitEffect_H
#include "effect.h"

class myBulletHitEffect: public effect {
	myBulletHitEffect* prev; //���� ���
	myBulletHitEffect* node; // ���� ���
	float timeMax; //������� �ð�
	float time; // ������� ���� �����̴� �ð�
public:
	myBulletHitEffect();
	void showMyBulletHitEffect(); //�� �Ѿ� Ÿ�� ȿ���� �׸��� �Լ�

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