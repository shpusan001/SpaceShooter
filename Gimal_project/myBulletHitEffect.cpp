#include "myBulletHitEffect.h"
#include "systemManager.h"

myBulletHitEffect::myBulletHitEffect() {
	effectX = 0;
	effectY = 0;
	timeMax = 1.2;
	time = timeMax;
	node = NULL;
	prev = NULL;
}

void myBulletHitEffect::showMyBulletHitEffect() {
	glPushMatrix();
		glColor4d(1.0, 0.0, 0.0, time/timeMax);
		glTranslatef(effectX, effectY, 30);
		glutSolidSphere(10, 30, 30);
	glPopMatrix();
}

float myBulletHitEffect::getTimeMax() {
	return timeMax;
}

void myBulletHitEffect::setTimeMax(float input) {
	timeMax = input;
}

float myBulletHitEffect::getTime() {
	return time;
}

void myBulletHitEffect::setTime(float input) {
	time = input;
}

myBulletHitEffect* myBulletHitEffect::getPrev() {
	return prev;
}

void myBulletHitEffect::setPrev(myBulletHitEffect* input) {
	prev = input;
}

myBulletHitEffect* myBulletHitEffect::getNode() {
	return node;
}

void myBulletHitEffect::setNode(myBulletHitEffect* input) {
	node = input;
}


