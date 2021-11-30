#ifndef star_H
#define star_H
class star {
	/*�� ��ġ*/
	float starX;
	float starY;
	float starZ;

	float speed; //�����̴� �ӵ�
	float size; //ũ��
	
	/*������ ���⺤��*/
	float starVecX;
	float starVecY;
	float starVecZ;

	/*���Ḯ��Ʈ�� ���� ���*/
	star* node;
	star* prev;
public:
	star();
	void drawStar();//���׸��� �Լ�
	/*getter and setter*/
	float getStarX();
	void setStarX(float input);

	float getStarY();
	void setStarY(float input);

	float getStarZ();
	void setStarZ(float input);

	float getSpeed();
	void setSpeed(float input);

	float getSize();
	void setSize(float input);

	float getStarVecX();
	void setStarVecX(float input);

	float getStarVecY();
	void setStarVecY(float input);

	float getStarVecZ();
	void setStarVecZ(float input);

	star* getNode();
	void setNode(star* input);

	star* getPrev();
	void setPrev(star* input);
};

#endif;