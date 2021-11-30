#ifndef enemyShooter_H
#define enemyShooter_H
#include "shooter.h"

class enemyShooter : public shooter {

	float bulletSpawnTime; //���� �ֱ�
	float speed = 3; // �����̴� �ӵ�
	float enemyToShooterAngle; //���� �÷��̾� ������ ���� 
	float healthPoint; // ü��
	float thisScore = 20;
	bool onff = 1; // �۵� ����ġ

	/*����*/
	double colorR;
	double colorG;
	double colorB;

	/*���� ������ ���� ����*/
	float enemyVecX;
	float enemyVecY;
	float enemyVecZ;

	enemyShooter* node;
	enemyShooter* prev;
public:
	
	enemyShooter();
	void drawEnemy(); //�� �׸��� �Լ�

	/*getter and setter*/
	float getBulletSpawnTime();
	void setBulletSpawnTime(float input);

	float getSpeed();
	void setSpeed(float input);

	float getEnemyToShooterAngle();
	void setEnemyToShooterAngle(float input);

	float getHealthPoint();
	void setHealthPoint(float input);

	bool getOnff();
	void setOnff(bool input);

	float getThisScore();
	void setThisScore(float input);

	double getColorR();
	void setColorR(double input);

	double getColorG();
	void setColorG(double input);

	double getColorB();
	void setColorB(double input);

	float getEnemyVectorX();
	void setEnemyVectorX(float input);

	float getEnemyVectorY();
	void setEnemyVectorY(float input);

	float getEnemyVectorZ();
	void setEnemyVectorZ(float input);

	enemyShooter* getNode();
	void setNode(enemyShooter* input);

	enemyShooter* getPrev();
	void setPrev(enemyShooter* input);
};

#endif