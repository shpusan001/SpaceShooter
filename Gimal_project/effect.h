#ifndef effect_H
#define effect_H

class effect {
protected:
	/*이펙트가 나타날 좌표위치*/
	float effectX;
	float effectY;
public:
	effect();
	float getEffectX();
	void setEffectX(float input);
	float getEffectY();
	void setEffectY(float input);
};

#endif;