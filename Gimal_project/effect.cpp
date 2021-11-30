#include "effect.h"

effect::effect() {
	effectX = 0;
	effectY = 0;
}

float effect::getEffectX() {
	return effectX;
}

void effect::setEffectX(float input){
	effectX = input;
}

float effect::getEffectY() {
	return effectY;
}

void effect::setEffectY(float input) {
	effectY = input;
}