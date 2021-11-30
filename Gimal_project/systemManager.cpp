#include "systemManager.h"
using namespace std;
//////////////////////////////////////////////////////////////////////////스태틱 클래스변수들 초기화
myBullet* systemManager::myBulletListHead;
enemyShooter* systemManager::enemyShooterListHead;
enemyBullet* systemManager::enemyBulletListHead;
star* systemManager::starListHead;
myBulletHitEffect* systemManager::myBulletHitEffectListHead;
enemyDyingEffect* systemManager::enemyDyingEffectListHead;
//////////////////////////////////////////////////////////////////////////

float systemManager::stageX = 500; //윈도우창 x
float systemManager::stageY = 700; // 윈도우창 y
float systemManager::enemySpawnTime = 50;  // 적 생성 주기
float systemManager::enemyBulletSpawnTime = 70; // 적 총알 생성주기
float systemManager::starSpawnTime = 30; // 별 생성 주기
float systemManager::score = 0; // 점수
int systemManager::gameLevel = 1; //게임 난이도
float systemManager::healthUpTime = 30; // 자동체력회복 주기
char* systemManager::gamePage; //게임페이지 (시작화면, 게임화면, 게임오버화면)
time_t systemManager::gameStartTime; //시작시간
time_t systemManager::gameTime; // 진행시간


/*시작 화면  함수*/
void systemManager::showStartScreen() {
	glLineWidth(2.0);
	score = 0; //점수초기화
	gameLevel = 1; //게임레벨 초기화
	player.setHealthPoint(player.getHealthMax());//내 비행기 체력 초기화
	player.setShooterX(stageX / 2); //내 비행기X 초기화
	player.setShooterY(stageY / 2); //내 비행기Y 초기화
	deleteAllEnemyShooter(); // 모든 적 초기화
	deleteAllEnemyBullet(); //모든 적 총알 초기화
	deleteAllMyBulletHitEffect(); // 모든 타격 효과 제거
	deleteAllEnemyDyingEffect(); // 모든 적 사망 효과 제거
	///////////////////////////////////////////////////////////////////////////////// 비행기 움직이기
	static float shooterMoveX = 0; //시작화면에서 움직이는 내 비행기 x좌표값
	static float shooterMoveY = 0; //시작화면에서 움직이는 내 비행기 y좌표값
	static float time = 0;
	

	shooterMoveX = 100 * sin(((2*PI) / 180) * time);
	shooterMoveY = 120 * cos(((2 * PI) / 180) * (1.8 * time));

	time+=0.33;
	if (time < 0)time = 0;

	/*비행기 총알 발사*/
	static float shotTime = 0;
	static float shotTimeMax = 25;
	if (shotTime > shotTimeMax) {
		myBullet currentBullet;
		currentBullet.setBulletX(shooterMoveX+200);
		currentBullet.setBulletY(shooterMoveY+350);
		currentBullet.setSpeed(7);
		createMyBullet(&currentBullet);
		shotTime = 0;
		shotTimeMax = ((float)rand() / (float)RAND_MAX) * 40 + 10;
	}

	shotTime++;

	////////////////////////////////////////////////////////////////////////////////화면출력
	char* buf = new char[100];
	glPushMatrix();
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);  //RGBA values of text color
		const unsigned char* t = reinterpret_cast<const unsigned char*>(buf);

		/*라인식 글자출력*/
		glPushMatrix();
			sprintf(buf, "Space@Shooter");
			glTranslatef(30 , stageY / 1.5, 100);
			glScalef(0.5, 0.5, 0.5);
			glutStrokeString(GLUT_STROKE_ROMAN, t);
		glPopMatrix();

		glPushMatrix();
			sprintf(buf, "Press \'space\' to start");
			glTranslatef(100, stageY / 1.5 - 60, 100);
			glScalef(0.2, 0.2, 0.2);
			glutStrokeString(GLUT_STROKE_ROMAN, t);
		glPopMatrix();

		glPushMatrix();
			glLineWidth(1.0);
			sprintf(buf, "Copyright 2019 . Sanghoon_Lee . All rights resereved.");
			glTranslatef(15, stageY / 6 - 60, 100);
			glScalef(0.13, 0.13, 0.13);
			glutStrokeString(GLUT_STROKE_ROMAN, t);
			glLineWidth(2.0);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(200, 300, 0);
			drawMyShooter(shooterMoveX, shooterMoveY, 0);
		glPopMatrix();
		///////////////////////////////////////////////////////////////////////////////
		delete[] buf;
	glPopMatrix();
}

/*게임오버 화면 함수*/
void systemManager::showOverScreen() {
	myBulletAllDelete(); //모든 총알 제거
	///////////////////////////////////////////////////////////////

	glLineWidth(2.0);
	char* buf = new char[100];
	int scoreOfInt = score;
	glPushMatrix();
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);  //RGBA values of text color
		const unsigned char* t = reinterpret_cast<const unsigned char*>(buf);
		/*게임오버 글자*/
		glPushMatrix();
			sprintf(buf, "GAME_OVER");
			glTranslatef(50, stageY / 1.5, 100);
			glScalef(0.5, 0.5, 0.5);
			glutStrokeString(GLUT_STROKE_ROMAN, t);
		glPopMatrix();
		/*점수*/
		glPushMatrix();
			sprintf(buf, "score : %d", scoreOfInt);
			//glTranslatef(stageX / 3, stageY / 2.2, 100);
			glRasterPos3f(stageX / 2 - 25, stageY / 1.5 - 80, 100);
			glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, t);
		glPopMatrix();
		/*다시 하실래요? 출력*/
		glPushMatrix();
		sprintf(buf, "Press 'r' to try again");
		//glTranslatef(stageX / 3, stageY / 2.2, 100);
		glRasterPos3f(stageX / 2 - 25, stageY / 1.5 - 120, 100);
		glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, t);
		glPopMatrix();
	glPopMatrix();
	delete[] buf;
}

/*기본 함수*/
void systemManager::drawBlock(float width, float height, float depth) { // 블록 만드는 함수 너비,높이,깊이
	glPushMatrix();
		glTranslatef(-width / 2, -height / 2, -depth / 2);
		glBegin(GL_POLYGON);
			glNormal3d(0, 0, -1);
			glVertex3d(0, 0, 0);
			glVertex3d(width, 0, 0);
			glVertex3d(width, height, 0);
			glVertex3d(0, height, 0);
		glEnd();
		glBegin(GL_POLYGON);
			glNormal3d(0, -1, 0);
			glVertex3d(0, 0, 0);
			glVertex3d(width, 0, 0);
			glVertex3d(width, 0, depth);
			glVertex3d(0, 0, depth);
		glEnd();
		glBegin(GL_POLYGON);
			glNormal3d(1, 0, 0);
			glVertex3d(width, 0, 0);
			glVertex3d(width, height, 0);
			glVertex3d(width, height, depth);
			glVertex3d(width, 0, depth);
		glEnd();
		glBegin(GL_POLYGON);
			glNormal3d(-1, 0, 0);
			glVertex3d(0, 0, 0);
			glVertex3d(0, height, 0);
			glVertex3d(0, height, depth);
			glVertex3d(0, 0, depth);
		glEnd();
		glBegin(GL_POLYGON);
			glNormal3d(0, 1, 0);
			glVertex3d(0, height, 0);
			glVertex3d(width, height, 0);
			glVertex3d(width, height, depth);
			glVertex3d(0, height, depth);
		glEnd();
		glBegin(GL_POLYGON);
			glNormal3d(0, 0, 1);
			glVertex3d(0, 0, depth);
			glVertex3d(width, 0, depth);
			glVertex3d(width, height, depth);
			glVertex3d(0, height, depth);
		glEnd();
	glPopMatrix();
} 
void systemManager::drawStandardPoint() { //기준선 만드는 함수
		glPushMatrix();
			glLineWidth(5.0);
			glColor3f(0.0f, 0.0f, 1.0f);
			glBegin(GL_LINES);
			glVertex3f(0, 0, 0);
			glVertex3f(systemManager::stageX, 0, 0);
			glEnd();
			glColor3f(1.0f, 0.0f, 0.0f);
			glBegin(GL_LINES);
			glVertex3f(0, 0, 0);
			glVertex3f(0, systemManager::stageY, 0);
			glEnd();
			glColor3f(0.0f, 1.0f, 0.0f);
			glBegin(GL_LINES);
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, systemManager::stageX);
			glEnd();
		glPopMatrix();
}
float systemManager::convertAtan2toNormal(float angle) {
	if (angle >= 0 && angle < (PI / 2)) {
		angle = (PI / 2) - angle + PI;
	}
	if (angle >= (PI / 2) && angle <= PI) {
		angle = (2 * PI) - ((PI / 2) + angle);
	}
	if (angle >= -(PI / 2) && angle < 0) {
		angle = (PI / 2) - (angle) + PI;
	}
	if (angle >= -PI && angle < -(PI / 2)) {
		angle = PI - (-(PI / 2) + angle);
	}
	return angle;
}


/*도입함수, 종료함수*/
void systemManager::inIt() {
	system("mode con:cols=50 lines=12"); // 콘솔창 설정
	system("title Space@Shooter 설명");
	/*게임 설명창*/
	cout << "******************* 게임_설명 *******************" << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "게임시작화면에서 'Space'를 누르면 게임시작" << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "조작 : 방향키, 공격 : a" << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "게임오버화면에서 'r'을 누르면 시작화면으로 이동." << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "30초가 지날 때 마다 게임 난이도가 상승합니다." << endl;
	cout << "**************************************************" << endl;
	//////////////////////////////////////////////////////////////////////////////////////////////////게임 셋팅
	srand((unsigned)time(NULL)); // 랜덤시드 설정
	player.setShooterSpeed(3); // 움직이는 속도
	player.setShooterHitBox(30, 30); //히트박스 설정
	player.setShooterWidth(30); // 플레이어 가로크기
	player.setShooterHeight(30); // 플레이어 세로크기
	/*소리재생*/
	PlaySound(TEXT("sound/background"), NULL, SND_LOOP | SND_ASYNC);
	///////////////////////////////////////////////////////////////////////////////////////////////// 연결리스트 헤드 정의
	/*클래스 연결리스트*/
	myBulletListHead = new myBullet;
	myBulletListHead = NULL;

	enemyShooterListHead = new enemyShooter;
	enemyShooterListHead = NULL;

	enemyBulletListHead = new enemyBullet;
	enemyBulletListHead = NULL;

	starListHead = new star;
	starListHead = NULL;

	myBulletHitEffectListHead = new myBulletHitEffect;
	myBulletHitEffectListHead = NULL;

	enemyDyingEffectListHead = new enemyDyingEffect;
	enemyDyingEffectListHead = NULL;

	/////////////////////////////////////////////////////////////////////////////////////////////////
	/*게임페이지 할당*/
	gamePage = new char[25];
	strcpy(gamePage, "page_start");

	/*프로그램 종료시 실행되는 함수*/
	atexit(closingEvent);

	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(systemManager::stageX, systemManager::stageY);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Space@Shooter");
	glClearColor(0.0, 0.0, 0.0, 1.0);


	GLfloat light_specular[] = { 1.0,1.0,1.0,1.0 };
	GLfloat light_diffuse[] = { 0.9,0.9,0.9,1.0 };
	GLfloat light_ambient[] = { 0.3,0.3,0.3,1.0 };
	GLfloat light_position[] = { 250,350,1000.0,0.0 };
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glEnable(GL_COLOR_MATERIAL);

}
void systemManager::closingEvent() {
	delete myBulletListHead;
	delete enemyShooterListHead;
	delete enemyBulletListHead;
	delete starListHead;
	delete myBulletHitEffectListHead;
	delete enemyDyingEffectListHead;
	delete[] gamePage;
}


void systemManager::drawMyShooter(float myShooterX, float myShooterY, float myShooterZ) { //플레이어 비행기 그리는 함수
	float scale = 0.7; // 크기 배율
	glPushMatrix();
	glTranslatef(myShooterX, myShooterY, 0);
	if (player.getLeftMoveOnff() == 1) {
		glRotatef(-45, 0, 1, 0);
	}
	if (player.getRightMoveOnff() == 1) {
		glRotatef(45, 0, 1, 0);
	}
	glScalef(scale, scale, scale);
	glPushMatrix(); // 몸통
	glColor3d(0.25, 0.25, 0.25);
	drawBlock(70, 40, 15);
	glPopMatrix();
	glPushMatrix(); //머리
	glTranslatef(0, 25, 0);
	glColor3d(0.2, 0.2, 0.2);
	drawBlock(20, 30, 9);
	glPopMatrix();
	/*
	glPushMatrix(); // 왼쪽날개
		glTranslatef(-37.5 , 0, 0);
		glColor3d(0.8, 0.1, 0);
		drawBlock(15 , 50 , 8 );
	glPopMatrix();
	glPushMatrix(); // 오른쪽날개
		glTranslatef(37.5 , 0, 0);
		glColor3d(0.8, 0.1, 0);
		drawBlock(15 , 50 , 8);
	glPopMatrix();
	*/
	glPushMatrix(); // 왼쪽사선날개
	glTranslatef(-30, -15, 0);
	glRotatef(-45, 0, 0, 1);
	glColor3d(0.3, 0.3, 0.3);
	drawBlock(40, 40, 12);
	glPopMatrix();
	glPushMatrix(); // 왼쪽사선날개
	glTranslatef(30, -15, 0);
	glRotatef(45, 0, 0, 1);
	glColor3d(0.3, 0.3, 0.3);
	drawBlock(40, 40, 12);
	glPopMatrix();
	glPopMatrix();
}
void systemManager::myShooterShotSystem() {
	static float playerShotSpeed = player.getShotSpeed() * (1000 / 60);
	static float playerShotSpeedManagerNum = 0;
	if (player.getAttackOnff() == 1 && playerShotSpeedManagerNum >= playerShotSpeed) {
		myBullet currentBullet;
		currentBullet.setBulletX(player.getShooterX());
		currentBullet.setBulletY(player.getShooterY() + 35);
		if (player.getLeftMoveOnff() == 1)currentBullet.setBulletVecX(-0.3);
		else if (player.getRightMoveOnff() == 1)currentBullet.setBulletVecX(0.3);
		createMyBullet(&currentBullet);
		playerShotSpeedManagerNum = 0;
	}
	if (playerShotSpeedManagerNum < playerShotSpeed) {
		playerShotSpeedManagerNum += 1;
	}
}

void systemManager::showScore() {
	int scoreOfInt = score;
	char* buf = new char[100];
	sprintf(buf, "score : %d", scoreOfInt);
	glPushMatrix();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);  //RGBA values of text color
	const unsigned char* t = reinterpret_cast<const unsigned char*>(buf);

	/*라인 식*/
	//glTranslatef(stageX / 4, stageY - 40, 100);
	//glScalef(0.26, 0.26, 0.26);
	//glutStrokeString(GLUT_STROKE_MONO_ROMAN, t);

	/*비트맵 로딩식 텍스트*/
	glRasterPos3i(25, stageY - 50, 100);            //Top left corner of text 
	//Since 2nd argument of glutBitmapString must be const unsigned char*
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, t);

	delete[] buf;
	glPopMatrix();
}
void systemManager::showGameLevel() {
	int gameLevelOfInt = gameLevel;
	char* buf = new char[100];
	sprintf(buf, "Game_Level : %d", gameLevelOfInt);
	glPushMatrix();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);  //RGBA values of text color
	const unsigned char* t = reinterpret_cast<const unsigned char*>(buf);

	/*폴리곤 식*/
	//glTranslatef(stageX / 4, stageY - 40, 100);
	//glScalef(0.26, 0.26, 0.26);
	//glutStrokeString(GLUT_STROKE_MONO_ROMAN, t);

	/*비트맵 로딩식 텍스트*/
	glRasterPos3i(25, stageY - 25, 100);            //Top left corner of text 
	//Since 2nd argument of glutBitmapString must be const unsigned char*
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, t);

	delete[] buf;
	glPopMatrix();
}
void systemManager::showHealth() {
	float healthOfFloat = player.getHealthPoint();
	float healthRatio = player.getHealthPoint() / player.getHealthMax();
	////////////////////////////////////////////////////////////////////////////////////////////////////////////텍스트 그리기
	float textX = stageX - 170, textY = stageY - 25;
	/*
	char* buf = new char[100];
	sprintf(buf, "%.0f", healthOfFloat);
	glPushMatrix();
	glColor4f(1.0, 1.0, 1.0, 1.0f);  //RGBA values of text color
	const unsigned char* t = reinterpret_cast<const unsigned char*>(buf);

	/*폴리곤 식*/
	//glTranslatef(stageX / 4, stageY - 40, 100);
	//glScalef(0.26, 0.26, 0.26);
	//glutStrokeString(GLUT_STROKE_MONO_ROMAN, t);

	/*비트맵 로딩식 텍스트*/
	//glRasterPos3i(textX, textY, 100);            //Top left corner of text 
	//Since 2nd argument of glutBitmapString must be const unsigned char*
	/*
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, t);
	delete[] buf;
	glPopMatrix();
	*/
	////////////////////////////////////////////////////////////////////////////////////////////////////////////체력바 그리기
	glPushMatrix();
	/*체력바*/
	glPushMatrix();
	glTranslatef(textX + 22, textY + 6, 99);
	glScalef(healthRatio, 1, 1);
	glColor3d(1.0, 0.0, 0.0);
	drawBlock(240, 20, 1);
	glPopMatrix();
	/*배경 체력바*/
	glPushMatrix();
	glTranslatef(textX + 22, textY + 6, 98);
	glColor3d(1.0, 1.0, 1.0);
	drawBlock(240, 20, 1);
	glPopMatrix();
	glPopMatrix();

}
void systemManager::showGameTime() {
	int gameTimeOfInt = gameTime;
	char* buf = new char[100];
	sprintf(buf, "Time : %d", gameTimeOfInt);
	glPushMatrix();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);  //RGBA values of text color
	const unsigned char* t = reinterpret_cast<const unsigned char*>(buf);

	/*라인 식*/
	//glTranslatef(stageX / 4, stageY - 40, 100);
	//glScalef(0.26, 0.26, 0.26);
	//glutStrokeString(GLUT_STROKE_MONO_ROMAN, t);

	/*비트맵 로딩식 텍스트*/
	glRasterPos3i(25, stageY - 75, 100);            //Top left corner of text 
	//Since 2nd argument of glutBitmapString must be const unsigned char*
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, t);

	delete[] buf;
	glPopMatrix();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 내 총알 관련함수
int systemManager::createMyBullet( myBullet* inputNode) {
	myBullet* newNode = new myBullet;
	newNode->setBulletX(inputNode->getBulletX());
	newNode->setBulletY(inputNode->getBulletY());
	newNode->setBulletVecX(inputNode->getBulletVecX());
	newNode->setBulletVecY(inputNode->getBulletVecY());
	newNode->setBulletVecZ(inputNode->getBulletVecZ());
	newNode->setSpeed(inputNode->getSpeed());
	newNode->setDamage(inputNode->getdamage());
	newNode->setNode(NULL);
	newNode->setPrev(NULL);

	if (myBulletListHead == NULL) {
		myBulletListHead = newNode;
		return 0; 
	}

	myBullet* temp;
	temp = myBulletListHead;

	while (temp->getNode() != NULL) { temp = temp->getNode(); }
	temp->setNode(newNode);
	newNode->setPrev(temp);
}
void systemManager::myBulletSystem() {
	myBullet* temp = myBulletListHead;
	/*위치값 계산*/
	while (temp!= NULL) {
		temp->setBulletX(temp->getBulletX()+ temp->getBulletVecX() * temp->getSpeed());
		temp->setBulletY(temp->getBulletY() + temp->getBulletVecY() * temp->getSpeed());
		temp = temp->getNode();
	}

	temp = systemManager::myBulletListHead;
	myBullet* stemp = NULL;
	/*특정조건시 제거*/
	while (temp != NULL) {
		stemp = temp->getNode();
		if (temp->getBulletOnff() == 0) {
			myBulletHitEffect effect;
			effect.setTimeMax(20);
			effect.setTime(effect.getTimeMax());
			effect.setEffectX(temp->getBulletX());
			effect.setEffectY(temp->getBulletY());
			createMyBulletHitEffect(&effect);
			deleteMyBullet(temp);
		}
		else if (temp->getBulletY() > 700) {
			deleteMyBullet(temp);
		}
		temp = stemp;
	}
}
void systemManager::myBulletShowSystem() {
	myBullet* temp = myBulletListHead;
		while (temp != NULL) {
			if (temp->getBulletOnff() == 1) {
			temp->drawMyBullet();
		}
		temp = temp->getNode();
	}
}
void systemManager::deleteMyBullet(myBullet* del) {
	if (del->getPrev() == NULL && del->getNode() == NULL) {
		myBulletListHead = NULL;
		delete del;
		return;
	}
	if (del->getPrev() == NULL && del->getNode() != NULL) {
		myBulletListHead = del->getNode();
		myBulletListHead->setPrev(NULL);
		delete del;
		return;
	}

	if (del->getPrev() != NULL && del->getNode() == NULL) {
		del->getPrev()->setNode(NULL);
		delete del;
		return;
	}
	del->getPrev()->setNode(del->getNode());
	del->getNode()->setPrev(del->getPrev());
	delete del;
	return;
}
void systemManager::myBulletAllDelete() {
	myBullet* temp = myBulletListHead;
	myBullet* stemp = NULL;
	/*마지막 전까지 제거*/
	while (temp != NULL) {
		stemp = temp->getNode();

		if (temp->getNode() != NULL) {
			temp->getNode()->setPrev(NULL);
			temp->setNode(NULL);
			delete temp;
		}
		temp = stemp;
	}

	delete temp; // 마지막 노드제거

	myBulletListHead = NULL;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////적 관련 함수
void systemManager::createEnemyShooter( enemyShooter* inputNode) {
	enemyShooter* newNode = new enemyShooter;
	newNode->setShooterX(inputNode->getShooterX());
	newNode->setShooterY(inputNode->getShooterY());
	newNode->setOnff(inputNode->getOnff());
	newNode->setEnemyToShooterAngle(inputNode->getEnemyToShooterAngle());
	newNode->setShooterWidth(inputNode->getShooterWidth());
	newNode->setShooterHeight(inputNode->getShooterHeight());
	newNode->setThisScore(inputNode->getThisScore());
	newNode->setColorR(inputNode->getColorR());
	newNode->setColorG(inputNode->getColorG());
	newNode->setColorB(inputNode->getColorB());
	newNode->setEnemyVectorX(inputNode->getEnemyVectorX());
	newNode->setEnemyVectorY(inputNode->getEnemyVectorY());
	newNode->setEnemyVectorZ(inputNode->getEnemyVectorZ());
	newNode->setNode(NULL);
	newNode->setPrev(NULL);

	if (enemyShooterListHead== NULL) {
		enemyShooterListHead = newNode;
		return;
	}

	enemyShooter* temp = enemyShooterListHead;
	
	while (temp->getNode() != NULL)temp = temp->getNode();
	temp->setNode(newNode);
	newNode->setPrev(temp);
}
void systemManager::enemyDelete(enemyShooter* del) {
	if (del->getPrev() == NULL && del->getNode() == NULL) {
		enemyShooterListHead = NULL;
		delete del;
		return;
	}
	if (del->getPrev() == NULL && del->getNode() != NULL) {
		enemyShooterListHead = del->getNode();
		enemyShooterListHead->setPrev(NULL);
		delete del;
		return;
	}

	if (del->getPrev() != NULL && del->getNode() == NULL) {
		del->getPrev()->setNode(NULL);
		delete del;
		return;
	}
	del->getPrev()->setNode(del->getNode());
	del->getNode()->setPrev(del->getPrev());
	delete del;
	return;
}
void systemManager::enemyShowSystem() {
	enemyShooter* temp = enemyShooterListHead;
	while (temp != NULL) {
		if (temp->getOnff() == 1) {
			temp->drawEnemy();
			temp = temp->getNode();
		}
	}
}
void systemManager::enemySystem() {
	static float spawnTime;
	static bool spawnTimeCheck = 0;

	if (spawnTimeCheck == 1) {
		spawnTime = systemManager::enemySpawnTime;
		spawnTime += rand() % 50;
		spawnTimeCheck = 0;
	}
	spawnTime--;

	/*적 생성*/
	if (spawnTime < 0) {
		enemyShooter enemy;
		//여기서 난이도 및 적 정보 조절가능//
		enemy.setShooterX((rand() / (float)RAND_MAX) * stageX); // 적이 소환될 좌표
		enemy.setShooterY(stageY + 200);
		enemy.setSpeed(0.45 + gameLevel * 0.25);
		enemy.setThisScore(20 + ((rand()%15) * gameLevel)); // 적 점수 설정
		enemy.setColorR(0.2 + (rand() / (float)RAND_MAX) * 0.8);
		enemy.setColorG(0.2 + (rand() / (float)RAND_MAX) * 0.8);
		enemy.setColorB(0.2 + (rand() / (float)RAND_MAX) * 0.8);
		systemManager::createEnemyShooter(&enemy); // 적 소환
		spawnTimeCheck = 1;
	}

	enemyShooter* temp = enemyShooterListHead;
	enemyShooter* stemp = NULL;


	while (temp != NULL) { // 순회
		stemp = temp->getNode();

		if (temp->getHealthPoint() < 0) { //hp가 없으면
			temp->setOnff(0); // 에너미 전원 off
		}
		/*적 이동*/
		temp->setShooterX(temp->getShooterX()
			+ temp->getSpeed() * temp->getEnemyVectorX());
		temp->setShooterY(temp->getShooterY()
			+ temp->getSpeed() * temp->getEnemyVectorY()
			- (rand() / (float)RAND_MAX) * 2 * temp->getSpeed());


		/*각도 설정*/
		temp->setEnemyToShooterAngle(atan2f(temp->getShooterX() - systemManager::player.getShooterX(),
			temp->getShooterY() - systemManager::player.getShooterY())); // 플레이어에 대한 각도 설정
			/*플레이어 기준으로 각도 랜덤 +-*/
		temp->setEnemyToShooterAngle(systemManager::convertAtan2toNormal(temp->getEnemyToShooterAngle()));//일반각으로 치환
		temp->setEnemyToShooterAngle(temp->getEnemyToShooterAngle() 
			+ ((rand() / (float)RAND_MAX) * (PI / 8)*(1 - 0.04 * gameLevel))
			- ((rand() / (float)RAND_MAX) * (PI / 4))*(1 - 0.04 * gameLevel));

		/*총알 소환*/
		if (temp->getBulletSpawnTime() <= 0) {
			temp->setBulletSpawnTime(systemManager::enemyBulletSpawnTime
				+ ((rand() / (float)RAND_MAX) * 120 - (gameLevel * 9)));

			enemyBullet enemyBullet;
			//여기서 총알에 대한 정보 수정//
			enemyBullet.setBulletX(temp->getShooterX());
			enemyBullet.setBulletY(temp->getShooterY());
			enemyBullet.setBulletVecX(cos(temp->getEnemyToShooterAngle()));
			enemyBullet.setBulletVecY(sin(temp->getEnemyToShooterAngle()));
			enemyBullet.setBulletVecZ(0);
			enemyBullet.setDamage(enemyBullet.getdamage() + gameLevel * 4);
			enemyBullet.setSpeed(4 + gameLevel * 0.4);
			//std::cout << enemyBullet.bulletVector.x << "  " << enemyBullet.bulletVector.y << std::endl;
			createEnemyBullet(&enemyBullet); // 적 총알 생성
		}

		temp->setBulletSpawnTime(temp->getBulletSpawnTime() - 1);
		if (temp->getHealthPoint() <= 0) { //체력이 0 이하라면 
			enemyDyingEffect effect;
			effect.setEffectX(temp->getShooterX());
			effect.setEffectY(temp->getShooterY());
			effect.setThisScore(temp->getThisScore());
			effect.setEffectR(temp->getColorR());
			effect.setEffectG(temp->getColorG());
			effect.setEffectB(temp->getColorB());
			createEnemyDyingEffect(&effect); //죽는 효과  추가
			systemManager::score += temp->getThisScore();  // 적체력 0되면 점수추가
		}
		if (temp->getHealthPoint() <= 0 || temp->getShooterY() < 0) { // 체력이 0이하면 삭제, 적이 y = 0을 넘으면 삭제
			enemyDelete(temp);
		}
		temp = stemp;
	}
}
void systemManager::deleteAllEnemyShooter() {
	enemyShooter* temp = enemyShooterListHead;
	enemyShooter* stemp = NULL;
	/*마지막 전까지 제거*/
	while (temp != NULL) {
		stemp = temp->getNode();

		if (temp->getNode()!= NULL) {
			temp->getNode()->setPrev(NULL);
			temp->setNode(NULL);
			delete temp;
		}
		temp = stemp;
	}

	delete temp; // 마지막 노드제거

	enemyShooterListHead = NULL;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////적 총알 관련 함수
void  systemManager::createEnemyBullet(enemyBullet* inputNode) {
	enemyBullet* newNode = new enemyBullet;
	newNode->setBulletX(inputNode->getBulletX());
	newNode->setBulletY(inputNode->getBulletY());
	newNode->setBulletVecX(inputNode->getBulletVecX());
	newNode->setBulletVecY(inputNode->getBulletVecY());
	newNode->setBulletVecZ(inputNode->getBulletVecZ());
	newNode->setDamage(inputNode->getdamage());
	newNode->setSpeed(inputNode->getSpeed());
	newNode->setNode(NULL);
	newNode->setPrev(NULL);


	if (enemyBulletListHead == NULL) {
		enemyBulletListHead = newNode;
		return;
	}

	enemyBullet* temp = enemyBulletListHead;

	while (temp->getNode() != NULL) temp = temp->getNode();
	temp->setNode(newNode);
	newNode->setPrev(temp);
}
void  systemManager::showEnemyBullet() {
	enemyBullet* temp = enemyBulletListHead;
	while (temp != NULL) {
		if (temp->getOnff() == 1) {
			temp->drawEnemyBullet();
			temp = temp->getNode();
		}
	}
}
void systemManager::deleteEnemyBullet(enemyBullet* del) {
	if (del->getPrev() == NULL && del->getNode() == NULL) {
		enemyBulletListHead = NULL;
		delete del;
		return;
	}
	if (del->getPrev() == NULL && del->getNode() != NULL) {
		enemyBulletListHead = del->getNode();
		enemyBulletListHead->setPrev(NULL);
		delete del;
		return;
	}

	if (del->getPrev() != NULL && del->getNode() == NULL) {
		del->getPrev()->setNode(NULL);
		delete del;
		return;
	}
	del->getPrev()->setNode(del->getNode());
	del->getNode()->setPrev(del->getPrev());
	delete del;
	return;
}
void systemManager::enemyBulletSystem() {
	enemyBullet* temp = enemyBulletListHead;
	enemyBullet* stemp = NULL;
	
	while (temp != NULL) {
		stemp = temp->getNode();
		temp->setBulletX(temp->getBulletX() 
			+ temp->getSpeed() * temp->getBulletVecX());
		temp->setBulletY(temp->getBulletY() 
			+ temp->getSpeed() * temp->getBulletVecY());
		
		//std::cout <<temp->enemyBullet.bulletVector.x << "  " << temp->enemyBullet.bulletVector.y << std::endl;
		if (temp->getOnff() == 0 || temp->getBulletY() < 0 || temp->getBulletY() >
			systemManager::stageY)
		{
			deleteEnemyBullet(temp);
		}
		temp = stemp;
	}
}
void systemManager::deleteAllEnemyBullet() {
	enemyBullet* temp = enemyBulletListHead;
	enemyBullet* stemp = NULL;
	/*마지막 전까지 제거*/
	while (temp != NULL) {
		stemp = temp->getNode();

		if (temp->getNode() != NULL) {
			temp->getNode()->setPrev(NULL);
			temp->setNode(NULL);
			delete temp;
		}
		temp = stemp;
	}

	delete temp; // 마지막 노드제거

	enemyBulletListHead = NULL;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////별 관련함수
void systemManager::createStar(star* input) {
	star* newNode = new star;
	newNode->setStarX(input->getStarX());
	newNode->setStarY(input->getStarY());
	newNode->setStarZ(input->getStarZ());
	newNode->setStarVecX(input->getStarVecX());
	newNode->setStarVecY(input->getStarVecY());
	newNode->setStarVecZ(input->getStarVecZ());
	newNode->setSpeed(input->getSpeed());
	newNode->setSize(input->getSize());
	newNode->setPrev(NULL);
	newNode->setNode(NULL);

	if (starListHead == NULL) {
		starListHead = newNode;
		return;
	}

	star* temp = starListHead;

	while (temp->getNode() != NULL)temp = temp->getNode();
	temp->setNode(newNode);
	newNode->setPrev(temp);
}
void systemManager::starShowSystem() {
	star* temp = starListHead;
	while (temp != NULL) {
		temp->drawStar();
		temp = temp->getNode();
	}
}
void systemManager::starSystem() {
	star* temp = starListHead;
	star* stemp = NULL;
	static bool starSpawnCheck=1;
	static bool firstStarSpawnCheck = 1; // 처음에 별을 배치 할때
	static int firstStarCount; // 몇개의 별을 배치 할 것 인가
	static float starSpawnTimer; // 별 스폰 타이머

	/*별 생성*/
	if (starSpawnTimer <= 0)starSpawnCheck = 1;

	if (starSpawnCheck == 1) { // 1

		if (firstStarSpawnCheck == 1) { //2 처음 배치할 때
			firstStarCount = 30;
			for (int i = 0; i < firstStarCount; i++) {// 3
				starSpawnTimer = systemManager::starSpawnTime;
				float randSize = ((rand() / (float)RAND_MAX) * 2) + 1.5;
				star newStar;
				newStar.setStarX((rand() / (float)RAND_MAX) * systemManager::stageX);
				newStar.setStarY((rand() / (float)RAND_MAX) * systemManager::stageY);
				newStar.setStarZ(-40);
				newStar.setSize(randSize);
				newStar.setSpeed((randSize * randSize) / 11);
				createStar(&newStar);
			}//3
				firstStarCount = 0;
				firstStarSpawnCheck = 0;
		}//2

		starSpawnTimer = systemManager::starSpawnTime;
		float randSize = ((rand() / (float)RAND_MAX) * 2) + 1.5;
		star newStar;
		newStar.setStarX((rand() / (float)RAND_MAX) * systemManager::stageX);
		newStar.setStarY(stageY);
		newStar.setStarZ(-40);
		newStar.setSize(randSize);
		newStar.setSpeed((randSize * randSize) / 11);
		createStar(&newStar);
		starSpawnCheck = 0;
	}//1

	while (temp != NULL) {
		stemp = temp->getNode();
		/*별 이동*/
		temp->setStarX(temp->getStarX() + temp->getSpeed() * temp->getStarVecX());
		temp->setStarY(temp->getStarY() + temp->getSpeed() * temp->getStarVecY()
			- (rand() / (float)RAND_MAX) * temp->getSpeed());
		temp->setStarZ(temp->getStarZ() + temp->getSpeed() * temp->getStarVecZ());

		/*별 삭제*/
		if (temp->getStarY() <= 0)deleteStar(temp); 
		temp = stemp;
	}
	starSpawnTimer--;
}
void systemManager::deleteStar(star* del) {
	if (del->getPrev() == NULL && del->getNode() == NULL) {
		starListHead = NULL;
		delete del;
		return;
	}
	if (del->getPrev() == NULL && del->getNode() != NULL) {
		starListHead = del->getNode();
		starListHead->setPrev(NULL);
		delete del;
		return;
	}

	if (del->getPrev() != NULL && del->getNode() == NULL) {
		del->getPrev()->setNode(NULL);
		delete del;
		return;
	}
	del->getPrev()->setNode(del->getNode());
	del->getNode()->setPrev(del->getPrev());
	delete del;
	return;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*내 비행기 총알 히트 이펙트 관련 함수*/
void systemManager::createMyBulletHitEffect(myBulletHitEffect* input) {
	myBulletHitEffect* newNode = new myBulletHitEffect;
	newNode->setEffectX(input->getEffectX());
	newNode->setEffectY(input->getEffectY());
	newNode->setTime(input->getTime());
	newNode->setTimeMax(input->getTimeMax());
	newNode->setPrev(NULL);
	newNode->setNode(NULL);

	if (myBulletHitEffectListHead == NULL) {
		myBulletHitEffectListHead = newNode;
		return;
	}
	
	myBulletHitEffect* temp = myBulletHitEffectListHead;

	while ((temp->getNode()) != NULL) {
		temp = temp->getNode();
	}

	temp->setNode(newNode);
	newNode->setPrev(temp);

}
void systemManager::deleteMyBulletHitEffect(myBulletHitEffect* del) {
	if (del->getPrev() == NULL && del->getNode() == NULL) {
		myBulletHitEffectListHead = NULL;
		delete del;
		return;
	}
	if (del->getPrev() == NULL && del->getNode() != NULL) {
		myBulletHitEffectListHead = del->getNode();
		myBulletHitEffectListHead->setPrev(NULL);
		delete del;
		return;
	}

	if (del->getPrev() != NULL && del->getNode() == NULL) {
		del->getPrev()->setNode(NULL);
		delete del;
		return;
	}
	del->getPrev()->setNode(del->getNode());
	del->getNode()->setPrev(del->getPrev());
	delete del;
	return;
}
void systemManager::showMyBulletHitEffect() {
	myBulletHitEffect* temp = myBulletHitEffectListHead;
	while (temp != NULL) {
		temp->showMyBulletHitEffect();
		temp = temp->getNode();
	}
}
void systemManager::myBulletHitEffectSystem() {
	myBulletHitEffect* temp = myBulletHitEffectListHead;
	myBulletHitEffect* stemp = NULL;
	if (temp != NULL) {
		stemp = temp->getNode();

		if (temp->getTime() <= 0) {
			deleteMyBulletHitEffect(temp);
		}

		temp->setTime(temp->getTime() - 10*(1 - (temp->getTime()/temp->getTimeMax() -0.1)));
		temp = stemp;
	}
}
void systemManager::deleteAllMyBulletHitEffect() {
	myBulletHitEffect* temp = myBulletHitEffectListHead;
	myBulletHitEffect* stemp = NULL;

	if (temp == NULL) return;

	while (temp->getNode() != NULL) {
		stemp = temp->getNode();
		delete temp;
		temp = stemp;
	}
	delete temp->getNode();
	myBulletHitEffectListHead = NULL;
}

/*적 죽음 이펙트 관련 함수*/
void systemManager::createEnemyDyingEffect(enemyDyingEffect* input) {
	enemyDyingEffect* newNode = new enemyDyingEffect;
	newNode->setEffectX(input->getEffectX());
	newNode->setEffectY(input->getEffectY());
	newNode->setTime(input->getTime());
	newNode->setTimeMax(input->getTimeMax());
	newNode->setThisScore(input->getThisScore());
	newNode->setEffectR(input->getEffectR());
	newNode->setEffectG(input->getEffectG());
	newNode->setEffectB(input->getEffectB());
	newNode->setPrev(NULL);
	newNode->setNode(NULL);

	if (enemyDyingEffectListHead== NULL) {
		enemyDyingEffectListHead = newNode;
		return;
	}

	enemyDyingEffect* temp = enemyDyingEffectListHead;

	while ((temp->getNode()) != NULL) {
		std::cout << temp->getNode() << std::endl;
		temp = temp->getNode();
	}

	temp->setNode(newNode);
	newNode->setPrev(temp);
}
void systemManager::deleteEnemyDyingEffect(enemyDyingEffect* del) {
	if (del->getPrev() == NULL && del->getNode() == NULL) {
		enemyDyingEffectListHead = NULL;
		delete del;
		return;
	}
	if (del->getPrev() == NULL && del->getNode() != NULL) {
		enemyDyingEffectListHead = del->getNode();
		enemyDyingEffectListHead->setPrev(NULL);
		delete del;
		return;
	}

	if (del->getPrev() != NULL && del->getNode() == NULL) {
		del->getPrev()->setNode(NULL);
		delete del;
		return;
	}
	del->getPrev()->setNode(del->getNode());
	del->getNode()->setPrev(del->getPrev());
	delete del;
	return;
}
void systemManager::showEnemyDyingEffect() {
	enemyDyingEffect* temp = enemyDyingEffectListHead;
	while (temp != NULL) {
		temp->showEnemyDyingEffect();
		temp->showEnemyDyingScore();
		temp = temp->getNode();
	}
}
void systemManager::enemyDyingEffectSystem(){
	enemyDyingEffect* temp = enemyDyingEffectListHead;
	enemyDyingEffect* stemp = NULL;

	if (temp != NULL) {
		stemp = temp->getNode();

		if (temp->getTime() <= 0) {
			deleteEnemyDyingEffect(temp);
		}

		temp->setTime(temp->getTime() - 7 * ((temp->getTime() / temp->getTimeMax() + 0.1)));
		temp = stemp;
	}
}
void systemManager::deleteAllEnemyDyingEffect() {
	enemyDyingEffect* temp = enemyDyingEffectListHead;
	enemyDyingEffect* stemp = NULL;

	if (temp == NULL) return;

	while (temp->getNode() != NULL) {
		stemp = temp->getNode();
		delete temp;
		temp = stemp;
	}
	delete temp->getNode();
	enemyDyingEffectListHead = NULL;
}

// 충돌 처리 함수
void systemManager::collidSystem() {

	/*적비행선과 내미사일에 대한 충돌검사*/
	myBullet* tempBullet;
	enemyShooter* tempEnemy;
	
	tempBullet = myBulletListHead;
	tempEnemy = enemyShooterListHead;

	while (tempBullet != NULL) {
		tempEnemy = enemyShooterListHead;
		while (tempEnemy != NULL) {
			if (tempBullet->getBulletX() > tempEnemy->getShooterX() - tempEnemy->getShooterWidth() / 2
				&& tempBullet->getBulletX() < tempEnemy->getShooterX() + tempEnemy->getShooterWidth() / 2
				&& tempBullet->getBulletY() > tempEnemy->getShooterY() - tempEnemy->getShooterHeight() / 2
				&& tempBullet->getBulletY() < tempEnemy->getShooterY() + tempEnemy->getShooterHeight() / 2
				&& tempBullet->getBulletOnff() ==1)
			{
				tempBullet->setBulletOnff(0);
				tempEnemy->setHealthPoint(tempEnemy->getHealthPoint()
					- tempBullet->getdamage());
			}
			tempEnemy = tempEnemy->getNode();
		}
		tempBullet = tempBullet->getNode();
	}

	/*내 비행선과 적 미사일 충돌검사*/
	enemyBullet* tempEnemyBullet = enemyBulletListHead;
	enemyBullet*  stempEnemyBullet = NULL;
	while (tempEnemyBullet != NULL) {
		stempEnemyBullet = tempEnemyBullet->getNode();
	//	printf("gimo");
		if (tempEnemyBullet->getBulletX() > player.getShooterX() - player.getShooterWidth() / 2 &&
			tempEnemyBullet->getBulletX() < player.getShooterX()+ player.getShooterWidth() / 2 &&
			tempEnemyBullet->getBulletY() > player.getShooterY() - player.getShooterHeight() / 2 &&
			tempEnemyBullet->getBulletY() <player.getShooterY()+ player.getShooterHeight() / 2 )
		{
			player.setHealthPoint(player.getHealthPoint() - tempEnemyBullet->getdamage());
			deleteEnemyBullet(tempEnemyBullet);
		}
		tempEnemyBullet = stempEnemyBullet;
	}

}

// 게임 담당 함수
void systemManager::inItInGameScreen() {
	gameStartTime = time(NULL); //게임시작 시간 기록
}
void systemManager::gameSystem() {
	if (!(strcmp(gamePage, "page_game")) && player.getHealthPoint() <= 0) {
		strcpy(gamePage, "page_over"); // 게임페이지에서 체력 0 이면 게임오버화면으로 전환
	}
	gameTime = time(NULL) - gameStartTime; //지금누적시간 - 게임시작시누적시간 = 게임플레이시간
	gameLevel = gameTime / 30 + 1; // 게임레벨은 30초가 지날수록 1상승

	enemySpawnTime = 50 - (gameLevel * 2);

}
void systemManager::myHealthUpSystem() {
	//내 비행기 체력 자동회복 시스템
	static float timeMax = healthUpTime;
	static float time = timeMax;

	if (time <= 0) {
		player.setHealthPoint(player.getHealthPoint() + 2);
		time = timeMax;
	}

	if (player.getHealthPoint() > player.getHealthMax()) {
		player.setHealthPoint(player.getHealthMax());
	}
	time--;
}