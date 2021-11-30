#include "bullet.h"

bullet::bullet() {
	bulletVecX =0;
	bulletVecY= 0;
	bulletVecZ = 0;
	speed  =0;
	bulletX =0;
	bulletY=0;
	damage = 10;
}

float bullet::getdamage() {
	return damage;
}

void bullet::setDamage(float input) {
	damage = input;
}

float bullet::getSpeed() {
	return speed;
}

void bullet::setSpeed(float input) {
	speed = input;
}

float bullet::getBulletX() {
	return bulletX;
}

float bullet::getBulletY() {
	return bulletY;
}

void bullet::setBulletX(float input) {
	bulletX = input;
}

void bullet::setBulletY(float input) {
	bulletY = input;
}

float bullet::getBulletVecX() {
	return bulletVecX;
}
void bullet::setBulletVecX(float input) {
	bulletVecX = input;
}

float bullet::getBulletVecY() {
	return bulletVecY;
}
void bullet::setBulletVecY(float input) {
	bulletVecY = input;
}

float bullet::getBulletVecZ() {
	return bulletVecZ;
}

void bullet::setBulletVecZ(float input) {
	bulletVecZ = input;
}
