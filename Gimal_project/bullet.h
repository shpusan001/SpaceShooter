#ifndef bullet_H
#define bullet_H

class bullet {
protected:
	float speed; //ÃÑ¾Ë ½ºÇÇµå
	float damage; // ÃÑ¾Ë µ¥¹ÌÁö
	float bulletX; // ÃÑ¾Ë x ÁÂÇ¥
	float bulletY; // ÃÑ¾Ë y ÁÂÇ¥
	/*ÃÑ¾Ë ¹æÇâ º¤ÅÍ*/
	float bulletVecX;
	float bulletVecY;
	float bulletVecZ;

public:
	bullet();
	/*getter and setter*/
	float getBulletX();
	void setBulletX(float input);

	float getBulletY();
	void setBulletY(float input);

	float getSpeed();
	void setSpeed(float input);

	float getdamage();
	void setDamage(float input);

	float getBulletVecX();
	void setBulletVecX(float input);

	float getBulletVecY();
	void setBulletVecY(float input);

	float getBulletVecZ();
	void setBulletVecZ(float input);
};

#endif;