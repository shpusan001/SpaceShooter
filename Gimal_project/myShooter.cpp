#include "myShooter.h"
#include "systemManager.h"

myShooter::myShooter() {
	shooterWidth = 80;
	shooterHeight = 80;
	shooterX = systemManager::stageX/2;
	shooterY = systemManager::stageY/2;
	healthPoint = 100;
	healthMax = 100;
	shotSpeed = 0.85;
}

void myShooter::setShooterHitBox(float width= 30, float height = 30) {
	shooterWidth = width;
	shooterHeight = height;
}

void myShooter::setShooterSpeed(float speed) {
	moveSpeed = speed;
}

void myShooter::moveLeftDown() {
	leftMoveOnff = 1;
}

void myShooter::moveRightDown() {
	rightMoveOnff = 1;
}

void myShooter::moveDownDown() {
	downMoveOnff = 1;
}

void myShooter::moveUpDown() {
	upMoveOnff = 1;
}

void myShooter::moveLeftUp() {
	leftMoveOnff = 0;
}

void myShooter::moveRightUp() {
	rightMoveOnff = 0;
}

void myShooter::moveDownUp() {
	downMoveOnff = 0;
}

void myShooter::moveUpUp() {
	upMoveOnff = 0;
}

void myShooter::attackOn() {
	attackOnff = 1;
}

void myShooter::attackOff() {
	attackOnff = 0;
}

void myShooter::myShooterMoveSystem() {
	if( 0< shooterX - shooterWidth / 2) shooterX -= moveSpeed * leftMoveOnff;
	if (systemManager::stageX > shooterX + shooterWidth/2) shooterX += moveSpeed * rightMoveOnff;
	if (systemManager::stageY > shooterY + shooterHeight) shooterY += moveSpeed * upMoveOnff;
	if (0< shooterY - shooterHeight) shooterY -= moveSpeed * downMoveOnff;
}

short myShooter::getLeftMoveOnff() {
	return leftMoveOnff;
}

short myShooter::getRightMoveOnff() {
	return rightMoveOnff;
}

float myShooter::getHealthPoint() {
	return healthPoint;
}
void myShooter::setHealthPoint(float input) {
	healthPoint = input;
}

float myShooter::getHealthMax() {
	return healthMax;
}

bool myShooter::getAttackOnff() {
	return attackOnff;
}

float myShooter::getShotSpeed() {
	return shotSpeed;
}