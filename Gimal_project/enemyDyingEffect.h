#ifndef enemyDyingEffect_H
#define enemyDyingEffect_H
#include "effect.h"

class enemyDyingEffect : public effect {
	/*���Ḯ��Ʈ�� ����*/
	enemyDyingEffect* prev;
	enemyDyingEffect* node;
	float timeMax; //�� �̺�Ʈ �ð�
	float time; //�ð���Ͽ� ����
	float thisScore; // ��Ÿ�� ����
	/*����Ʈ ����*/
	float effectR; 
	float effectG;
	float effectB;
public:
	enemyDyingEffect();
	void showEnemyDyingEffect();
	void showEnemyDyingScore();

	/*getter setter*/

	enemyDyingEffect* getPrev();
	void setPrev(enemyDyingEffect* input);
	enemyDyingEffect* getNode();
	void setNode(enemyDyingEffect* input);

	float getTimeMax();
	void setTimeMax(float input);
	float getTime();
	void setTime(float input);
	float getThisScore();
	void setThisScore(float input);

	float getEffectR();
	void setEffectR(float input);

	float getEffectG();
	void setEffectG(float input);

	float getEffectB();
	void setEffectB(float input);
};

#endif;