#ifndef myBullet_H
#define myBullet_H

#include "bullet.h"
class myBullet : public bullet {
private:
	/*연결리스트용 노드들*/
	myBullet* node;
	myBullet* prev;
	bool myBulletOnff; // 총알 작동 스위치
public:
	myBullet(); //생성자
	void drawMyBullet(); // 총알그리는 함수

	/*getter setter*/
	myBullet* getNode();
	void setNode(myBullet* input);
	myBullet* getPrev();
	void setPrev(myBullet* input);

	bool getBulletOnff();
	void setBulletOnff(bool input);
};

#endif;