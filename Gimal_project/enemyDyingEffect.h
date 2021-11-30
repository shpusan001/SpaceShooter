#ifndef enemyDyingEffect_H
#define enemyDyingEffect_H
#include "effect.h"

class enemyDyingEffect : public effect {
	/*연결리스트용 노드들*/
	enemyDyingEffect* prev;
	enemyDyingEffect* node;
	float timeMax; //총 이벤트 시간
	float time; //시간기록용 변수
	float thisScore; // 나타낼 점수
	/*이펙트 색깔*/
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