#include "enemyShooter.h"
#include "systemManager.h"



enemyShooter::enemyShooter() {
	speed = 1;
	/*�� ������ ���� ����*/
	enemyVecX = 0;
	enemyVecY = -1;
	enemyVecZ = 0;

	/*�� ��ġ*/
	shooterX = 250;
	shooterY = 700;

	/*�� ũ��*/
	shooterHeight = 60;
	shooterWidth = 60;

	/*ü��*/
	healthPoint = 100;

	/*��ɿ���*/
	onff = 1;

	/*�����ֱ�*/
	bulletSpawnTime = 50;

	/*�ִ� ����*/
	thisScore = 20;

	/*����*/
	colorR = 0.0;
	colorG = 0.0;
	colorB = 0.0;

	/*������⿡�� ������������ ����*/
	enemyToShooterAngle = 0;
}


void enemyShooter::drawEnemy() {
	glPushMatrix();
		glTranslatef(shooterX, shooterY, 0);
		glColor3d(colorR, colorG, colorB);
		systemManager::drawBlock(50,20,10);
		glPushMatrix();
			glTranslatef(25, 0, 0);
			systemManager::drawBlock(5, 40, 10);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-25, 0, 0);
			systemManager::drawBlock(5, 40, 10);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, -15, 0);
			systemManager::drawBlock(15, 20, 20);
		glPopMatrix();
		glutSolidSphere(20, 30, 30);
	glPopMatrix();
}

float enemyShooter::getBulletSpawnTime() {
	return bulletSpawnTime;
}

void enemyShooter::setBulletSpawnTime(float input) {
	bulletSpawnTime = input;
}

float enemyShooter::getSpeed() {
	return speed;
}

void enemyShooter::setSpeed(float input) {
	speed = input;
}

float enemyShooter::getEnemyToShooterAngle() {
	return enemyToShooterAngle;
}

void enemyShooter::setEnemyToShooterAngle(float input) {
	enemyToShooterAngle = input;
}

float enemyShooter::getHealthPoint() {
	return healthPoint;
}

void enemyShooter::setHealthPoint(float input) {
	healthPoint = input;
}

bool enemyShooter::getOnff() {
	return onff;
}

void enemyShooter::setOnff(bool input) {
	onff = input;
}

float enemyShooter::getThisScore() {
	return thisScore;
}

void enemyShooter::setThisScore(float input) {
	thisScore = input;
}

double enemyShooter::getColorR() {
	return colorR;
}
void enemyShooter::setColorR(double input) {
	colorR = input;
}

double enemyShooter::getColorG() {
	return colorG;
}
void enemyShooter::setColorG(double input) {
	colorG = input;
}

double enemyShooter::getColorB() {
	return colorB;
}
void enemyShooter::setColorB(double input) {
	colorB = input;
}

float enemyShooter::getEnemyVectorX() {
	return enemyVecX;
}

float enemyShooter::getEnemyVectorY() {
	return enemyVecY;
}

float enemyShooter::getEnemyVectorZ() {
	return enemyVecZ;
}

void enemyShooter::setEnemyVectorX(float input) {
	enemyVecX = input;
}

void enemyShooter::setEnemyVectorY(float input) {
	enemyVecY = input;
}

void enemyShooter::setEnemyVectorZ(float input) {
	enemyVecZ = input;
}

enemyShooter* enemyShooter::getNode() {
	return node;
}
void enemyShooter::setNode(enemyShooter* input) {
	node = input;
}

enemyShooter* enemyShooter::getPrev() {
	return prev;
}
void enemyShooter::setPrev(enemyShooter* input) {
	prev = input;
}