#ifndef myBullet_H
#define myBullet_H

#include "bullet.h"
class myBullet : public bullet {
private:
	/*���Ḯ��Ʈ�� ����*/
	myBullet* node;
	myBullet* prev;
	bool myBulletOnff; // �Ѿ� �۵� ����ġ
public:
	myBullet(); //������
	void drawMyBullet(); // �Ѿ˱׸��� �Լ�

	/*getter setter*/
	myBullet* getNode();
	void setNode(myBullet* input);
	myBullet* getPrev();
	void setPrev(myBullet* input);

	bool getBulletOnff();
	void setBulletOnff(bool input);
};

#endif;