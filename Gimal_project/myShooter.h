#ifndef myShooter_H
#define myShooter_H
#include "shooter.h"

class myShooter: public shooter {
private:
	float moveSpeed = 1.2; //이동속도
	bool downMoveOnff = 0; // 아래 방향키 확인 변수
	bool upMoveOnff = 0; // 위 방향키 확인 변수
	bool leftMoveOnff = 0; // 왼쪽 방향키 확인 변수
	bool rightMoveOnff = 0; // 오른쪽 방향키 확인 변수
	float healthPoint = 100; // 체력
	float healthMax = 100; // 최대체력
	bool attackOnff = 0; // 공격 여부
	float shotSpeed = 1; //공격속도
public:
	myShooter();
	void setShooterHitBox(float width, float height);  // hit되는 크기 조정.
	void setShooterSpeed(float speed); //움직이는 속도 변경
	void myShooterMoveSystem(); // 움직임 동작 시스템
	//////////////////////////////////////-----키 입력 알림 함수
	void moveLeftDown(); 
	void moveRightDown();
	void moveDownDown();
	void moveUpDown();
	void moveLeftUp();
	void moveRightUp();
	void moveDownUp();
	void moveUpUp();
	/////////////////////////////////////
	void attackOn(); // 공격 on, off
	void attackOff();
	////////////////////////////////////getter, setter
	short getLeftMoveOnff(); // 왼쪽 방향키 확인 변수 getter
	short getRightMoveOnff(); // 오른쪽 방향키 확인 변수 setter
	float getHealthPoint();
	void setHealthPoint(float input);
	float getHealthMax();
	bool getAttackOnff();
	float getShotSpeed();
};
#endif // !1