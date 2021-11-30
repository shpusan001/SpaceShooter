#include "enemyDyingEffect.h"
#include "systemManager.h"

enemyDyingEffect::enemyDyingEffect() {
	timeMax = 80;
	time = timeMax;
	thisScore = 0;
	effectR = 1.0f;
	effectG = 1.0f;
	effectB = 1.0f;
	node = NULL;
	prev = NULL;
}

void enemyDyingEffect::showEnemyDyingEffect() {
	glPushMatrix();
		glTranslatef(this->effectX, this->effectY, 0);

		glColor4f(effectR/2, effectG/2, effectB/2, 0.6*(time/timeMax));
		glutSolidSphere(40.0, 30, 30);

		glColor4f(effectR, effectG, effectB, 0.9*(time / timeMax));
		glutSolidSphere(20.0, 30, 30);
	glPopMatrix();
}

void enemyDyingEffect::showEnemyDyingScore() {
	glPushMatrix(); //1
	glTranslatef(this->effectX-10, this->effectY-10, 100);
	char* buf = new char[100];
	sprintf(buf, "+%.0f", thisScore);
		glPushMatrix(); //2
			glLineWidth(1);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);  //RGBA values of text color
			const unsigned char* t = reinterpret_cast<const unsigned char*>(buf);

			glScalef(0.1, 0.1, 0.1);
			glutStrokeString(GLUT_STROKE_MONO_ROMAN, t);

			delete[] buf;
		glPopMatrix();// 2
	glPopMatrix();// 1
}

float enemyDyingEffect::getTimeMax() {
	return timeMax;
}

void enemyDyingEffect::setTimeMax(float input) {
	timeMax = input;
}

float enemyDyingEffect::getTime() {
	return time;
}

void enemyDyingEffect::setTime(float input) {
	time = input;
}

enemyDyingEffect* enemyDyingEffect::getPrev() {
	return prev;
}

void enemyDyingEffect::setPrev(enemyDyingEffect* input) {
	prev = input;
}

enemyDyingEffect* enemyDyingEffect::getNode() {
	return node;
}

void enemyDyingEffect::setNode(enemyDyingEffect* input) {
	node = input;
}

float enemyDyingEffect::getThisScore() {
	return thisScore;
}

void enemyDyingEffect::setThisScore(float input) {
	thisScore = input;
}

float enemyDyingEffect::getEffectR() {
	return effectR;
}
void enemyDyingEffect::setEffectR(float input) {
	effectR = input;
}

float enemyDyingEffect::getEffectG() {
	return effectG;
}
void enemyDyingEffect::setEffectG(float input) {
	effectG = input;
}

float enemyDyingEffect::getEffectB() {
	return effectB;
}
void enemyDyingEffect::setEffectB(float input) {
	effectB = input;
}