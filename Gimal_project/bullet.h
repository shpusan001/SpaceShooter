#ifndef bullet_H
#define bullet_H

class bullet {
protected:
	float speed; //�Ѿ� ���ǵ�
	float damage; // �Ѿ� ������
	float bulletX; // �Ѿ� x ��ǥ
	float bulletY; // �Ѿ� y ��ǥ
	/*�Ѿ� ���� ����*/
	float bulletVecX;
	float bulletVecY;
	float bulletVecZ;

public:
	bullet();
	/*getter and setter*/
	float getBulletX();
	void setBulletX(float input);

	float getBulletY();
	void setBulletY(float input);

	float getSpeed();
	void setSpeed(float input);

	float getdamage();
	void setDamage(float input);

	float getBulletVecX();
	void setBulletVecX(float input);

	float getBulletVecY();
	void setBulletVecY(float input);

	float getBulletVecZ();
	void setBulletVecZ(float input);
};

#endif;