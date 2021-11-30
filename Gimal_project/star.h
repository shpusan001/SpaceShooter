#ifndef star_H
#define star_H
class star {
	/*별 위치*/
	float starX;
	float starY;
	float starZ;

	float speed; //움직이는 속도
	float size; //크기
	
	/*움직임 방향벡터*/
	float starVecX;
	float starVecY;
	float starVecZ;

	/*연결리스트를 위한 노드*/
	star* node;
	star* prev;
public:
	star();
	void drawStar();//별그리는 함수
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