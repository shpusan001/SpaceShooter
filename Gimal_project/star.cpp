#include "systemManager.h"
#include "star.h"

star::star() {
	starX = 0;
	starY = 0;
	starZ = 0;
	starVecX = 0;
	starVecY = -1;
	starVecY = 0;
	speed = 5;
	size = 2.5;
}

void star::drawStar() {
	glPushMatrix();
		glTranslatef(starX, starY, starZ);
		glColor4d(1, 1, 0, size / 3.5);
		glutSolidCube(size);
	glPopMatrix();
}

float star::getStarX() {
	return starX;
}

void star::setStarX(float input) {
	starX = input;
}

float star::getStarY() {
	return starY;
}

void star::setStarY(float input) {
	starY = input;
}

float star::getStarZ() {
	return starZ;
}

void star::setStarZ(float input) {
	starZ = input;
}

float star::getSpeed() {
	return speed;
}

void star::setSpeed(float input) {
	speed = input;
}

float star::getSize() {
	return size;
}

void star::setSize(float input) {
	size = input;
}

float star::getStarVecX() {
	return starVecX;
}
void star::setStarVecX(float input) {
	starVecX = input;
}

float star::getStarVecY() {
	return starVecY;
}
void star::setStarVecY(float input) {
	starVecY = input;
}

float star::getStarVecZ() {
	return starVecZ;
}
void star::setStarVecZ(float input) {
	starVecZ = input;
}

star* star::getNode() {
	return node;
}
void star::setNode(star* input) {
	node = input;
}

star* star::getPrev() {
	return prev;
}
void star::setPrev(star* input) {
	prev = input;
}