#ifndef enemyBullet_H
#define enemyBullet_H

#include "bullet.h"

class enemyBullet : public bullet{
private:
	float bulletSize; // �Ѿ�ũ��
	bool onff; // �۵�����
	enemyBullet* node;
	enemyBullet* prev;
public:
	enemyBullet();
	void drawEnemyBullet(); // �� �Ѿ� �׸��� �Լ�

	/*getter and setter*/
	bool getOnff();
	void setOnff(bool input);

	enemyBullet* getNode();
	void setNode(enemyBullet* input);
	enemyBullet* getPrev();
	void setPrev(enemyBullet* input);
};

#endif;