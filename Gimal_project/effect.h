#ifndef effect_H
#define effect_H

class effect {
protected:
	/*����Ʈ�� ��Ÿ�� ��ǥ��ġ*/
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