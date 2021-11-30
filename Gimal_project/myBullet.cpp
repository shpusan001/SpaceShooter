#include "myBullet.h"
#include "systemManager.h"

myBullet::myBullet() {
	bulletVecX = 0;
	bulletVecY = 1;
	bulletVecZ = 0;
	speed = 5;
	bulletX = 250;
	bulletY = 250;
	damage = 20;
	myBulletOnff = 1;
}

void myBullet::drawMyBullet() {
	glPushMatrix();
		glTranslatef(bulletX, bulletY, 0);
		glColor3d(1, 0.1, 0);
		systemManager::drawBlock(6, 23, 10);
	glPopMatrix();
}

myBullet* myBullet::getNode() {
	return node;
}
void myBullet::setNode(myBullet* input) {
	node = input;
}

myBullet* myBullet::getPrev() {
	return prev;
}
void myBullet::setPrev(myBullet* input) {
	prev = input;
}

bool myBullet::getBulletOnff() {
	return myBulletOnff;
}

void myBullet::setBulletOnff(bool input) {
	myBulletOnff = input;
}