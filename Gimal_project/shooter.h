#ifndef shooter_H
#define shooter_H
class shooter {
protected:
	/*������ġ*/
	float shooterX = 0;
	float shooterY = 0;
	/*����ũ��*/
	float shooterWidth;
	float shooterHeight;
public:
	shooter();
	shooter(float x, float y);

	/*getter and setter*/
	float getShooterX();
	void setShooterX(float input);
	float getShooterY();
	void setShooterY(float input);
	float getShooterWidth();
	void setShooterWidth(float input);
	float getShooterHeight();
	void setShooterHeight(float input);
};
#endif // !1
