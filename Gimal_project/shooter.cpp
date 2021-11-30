#include "shooter.h"
#include "systemManager.h"

shooter::shooter() {
	shooterX = systemManager::stageX / 2;
	shooterY = systemManager::stageY / 2;
}

shooter::shooter(float x, float y) {
	shooterX = x;
	shooterY = y;
}

float shooter::getShooterX() {
	return shooterX;
}

void shooter::setShooterX(float input) {
	shooterX = input;
}

float shooter::getShooterY() {
	return shooterY;
}

void shooter::setShooterY(float input) {
	shooterY = input;
}

float shooter::getShooterWidth() {
	return shooterWidth;
}

void shooter::setShooterWidth(float input) {
	shooterWidth = input;
}

float shooter::getShooterHeight() {
	return shooterHeight;
}

void shooter::setShooterHeight(float input) {
	shooterHeight = input;
}




