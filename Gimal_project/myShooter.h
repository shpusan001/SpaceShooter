#ifndef myShooter_H
#define myShooter_H
#include "shooter.h"

class myShooter: public shooter {
private:
	float moveSpeed = 1.2; //�̵��ӵ�
	bool downMoveOnff = 0; // �Ʒ� ����Ű Ȯ�� ����
	bool upMoveOnff = 0; // �� ����Ű Ȯ�� ����
	bool leftMoveOnff = 0; // ���� ����Ű Ȯ�� ����
	bool rightMoveOnff = 0; // ������ ����Ű Ȯ�� ����
	float healthPoint = 100; // ü��
	float healthMax = 100; // �ִ�ü��
	bool attackOnff = 0; // ���� ����
	float shotSpeed = 1; //���ݼӵ�
public:
	myShooter();
	void setShooterHitBox(float width, float height);  // hit�Ǵ� ũ�� ����.
	void setShooterSpeed(float speed); //�����̴� �ӵ� ����
	void myShooterMoveSystem(); // ������ ���� �ý���
	//////////////////////////////////////-----Ű �Է� �˸� �Լ�
	void moveLeftDown(); 
	void moveRightDown();
	void moveDownDown();
	void moveUpDown();
	void moveLeftUp();
	void moveRightUp();
	void moveDownUp();
	void moveUpUp();
	/////////////////////////////////////
	void attackOn(); // ���� on, off
	void attackOff();
	////////////////////////////////////getter, setter
	short getLeftMoveOnff(); // ���� ����Ű Ȯ�� ���� getter
	short getRightMoveOnff(); // ������ ����Ű Ȯ�� ���� setter
	float getHealthPoint();
	void setHealthPoint(float input);
	float getHealthMax();
	bool getAttackOnff();
	float getShotSpeed();
};
#endif // !1