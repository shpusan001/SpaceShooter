#ifndef enemyShooter_H
#define enemyShooter_H
#include "shooter.h"

class enemyShooter : public shooter {

	float bulletSpawnTime; //생성 주기
	float speed = 3; // 움직이는 속도
	float enemyToShooterAngle; //적과 플레이어 사이의 각도 
	float healthPoint; // 체력
	float thisScore = 20;
	bool onff = 1; // 작동 스위치

	/*색상*/
	double colorR;
	double colorG;
	double colorB;

	/*적의 움직임 단위 벡터*/
	float enemyVecX;
	float enemyVecY;
	float enemyVecZ;

	enemyShooter* node;
	enemyShooter* prev;
public:
	
	enemyShooter();
	void drawEnemy(); //적 그리는 함수

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