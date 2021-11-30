#ifndef enemyBullet_H
#define enemyBullet_H

#include "bullet.h"

class enemyBullet : public bullet{
private:
	float bulletSize; // 총알크기
	bool onff; // 작동여부
	enemyBullet* node;
	enemyBullet* prev;
public:
	enemyBullet();
	void drawEnemyBullet(); // 적 총알 그리는 함수

	/*getter and setter*/
	bool getOnff();
	void setOnff(bool input);

	enemyBullet* getNode();
	void setNode(enemyBullet* input);
	enemyBullet* getPrev();
	void setPrev(enemyBullet* input);
};

#endif;