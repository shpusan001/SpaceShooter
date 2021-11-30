#include "systemManager.h"
using namespace std;
//////////////////////////////////////////////////////////////////////////����ƽ Ŭ���������� �ʱ�ȭ
myBullet* systemManager::myBulletListHead;
enemyShooter* systemManager::enemyShooterListHead;
enemyBullet* systemManager::enemyBulletListHead;
star* systemManager::starListHead;
myBulletHitEffect* systemManager::myBulletHitEffectListHead;
enemyDyingEffect* systemManager::enemyDyingEffectListHead;
//////////////////////////////////////////////////////////////////////////

float systemManager::stageX = 500; //������â x
float systemManager::stageY = 700; // ������â y
float systemManager::enemySpawnTime = 50;  // �� ���� �ֱ�
float systemManager::enemyBulletSpawnTime = 70; // �� �Ѿ� �����ֱ�
float systemManager::starSpawnTime = 30; // �� ���� �ֱ�
float systemManager::score = 0; // ����
int systemManager::gameLevel = 1; //���� ���̵�
float systemManager::healthUpTime = 30; // �ڵ�ü��ȸ�� �ֱ�
char* systemManager::gamePage; //���������� (����ȭ��, ����ȭ��, ���ӿ���ȭ��)
time_t systemManager::gameStartTime; //���۽ð�
time_t systemManager::gameTime; // ����ð�


/*���� ȭ��  �Լ�*/
void systemManager::showStartScreen() {
	glLineWidth(2.0);
	score = 0; //�����ʱ�ȭ
	gameLevel = 1; //���ӷ��� �ʱ�ȭ
	player.setHealthPoint(player.getHealthMax());//�� ����� ü�� �ʱ�ȭ
	player.setShooterX(stageX / 2); //�� �����X �ʱ�ȭ
	player.setShooterY(stageY / 2); //�� �����Y �ʱ�ȭ
	deleteAllEnemyShooter(); // ��� �� �ʱ�ȭ
	deleteAllEnemyBullet(); //��� �� �Ѿ� �ʱ�ȭ
	deleteAllMyBulletHitEffect(); // ��� Ÿ�� ȿ�� ����
	deleteAllEnemyDyingEffect(); // ��� �� ��� ȿ�� ����
	///////////////////////////////////////////////////////////////////////////////// ����� �����̱�
	static float shooterMoveX = 0; //����ȭ�鿡�� �����̴� �� ����� x��ǥ��
	static float shooterMoveY = 0; //����ȭ�鿡�� �����̴� �� ����� y��ǥ��
	static float time = 0;
	

	shooterMoveX = 100 * sin(((2*PI) / 180) * time);
	shooterMoveY = 120 * cos(((2 * PI) / 180) * (1.8 * time));

	time+=0.33;
	if (time < 0)time = 0;

	/*����� �Ѿ� �߻�*/
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

	////////////////////////////////////////////////////////////////////////////////ȭ�����
	char* buf = new char[100];
	glPushMatrix();
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);  //RGBA values of text color
		const unsigned char* t = reinterpret_cast<const unsigned char*>(buf);

		/*���ν� �������*/
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

/*���ӿ��� ȭ�� �Լ�*/
void systemManager::showOverScreen() {
	myBulletAllDelete(); //��� �Ѿ� ����
	///////////////////////////////////////////////////////////////

	glLineWidth(2.0);
	char* buf = new char[100];
	int scoreOfInt = score;
	glPushMatrix();
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);  //RGBA values of text color
		const unsigned char* t = reinterpret_cast<const unsigned char*>(buf);
		/*���ӿ��� ����*/
		glPushMatrix();
			sprintf(buf, "GAME_OVER");
			glTranslatef(50, stageY / 1.5, 100);
			glScalef(0.5, 0.5, 0.5);
			glutStrokeString(GLUT_STROKE_ROMAN, t);
		glPopMatrix();
		/*����*/
		glPushMatrix();
			sprintf(buf, "score : %d", scoreOfInt);
			//glTranslatef(stageX / 3, stageY / 2.2, 100);
			glRasterPos3f(stageX / 2 - 25, stageY / 1.5 - 80, 100);
			glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, t);
		glPopMatrix();
		/*�ٽ� �ϽǷ���? ���*/
		glPushMatrix();
		sprintf(buf, "Press 'r' to try again");
		//glTranslatef(stageX / 3, stageY / 2.2, 100);
		glRasterPos3f(stageX / 2 - 25, stageY / 1.5 - 120, 100);
		glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, t);
		glPopMatrix();
	glPopMatrix();
	delete[] buf;
}

/*�⺻ �Լ�*/
void systemManager::drawBlock(float width, float height, float depth) { // ��� ����� �Լ� �ʺ�,����,����
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
void systemManager::drawStandardPoint() { //���ؼ� ����� �Լ�
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


/*�����Լ�, �����Լ�*/
void systemManager::inIt() {
	system("mode con:cols=50 lines=12"); // �ܼ�â ����
	system("title Space@Shooter ����");
	/*���� ����â*/
	cout << "******************* ����_���� *******************" << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "���ӽ���ȭ�鿡�� 'Space'�� ������ ���ӽ���" << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "���� : ����Ű, ���� : a" << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "���ӿ���ȭ�鿡�� 'r'�� ������ ����ȭ������ �̵�." << endl;
	cout << "-------------------------------------------------" << endl;
	cout << "30�ʰ� ���� �� ���� ���� ���̵��� ����մϴ�." << endl;
	cout << "**************************************************" << endl;
	//////////////////////////////////////////////////////////////////////////////////////////////////���� ����
	srand((unsigned)time(NULL)); // �����õ� ����
	player.setShooterSpeed(3); // �����̴� �ӵ�
	player.setShooterHitBox(30, 30); //��Ʈ�ڽ� ����
	player.setShooterWidth(30); // �÷��̾� ����ũ��
	player.setShooterHeight(30); // �÷��̾� ����ũ��
	/*�Ҹ����*/
	PlaySound(TEXT("sound/background"), NULL, SND_LOOP | SND_ASYNC);
	///////////////////////////////////////////////////////////////////////////////////////////////// ���Ḯ��Ʈ ��� ����
	/*Ŭ���� ���Ḯ��Ʈ*/
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
	/*���������� �Ҵ�*/
	gamePage = new char[25];
	strcpy(gamePage, "page_start");

	/*���α׷� ����� ����Ǵ� �Լ�*/
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


void systemManager::drawMyShooter(float myShooterX, float myShooterY, float myShooterZ) { //�÷��̾� ����� �׸��� �Լ�
	float scale = 0.7; // ũ�� ����
	glPushMatrix();
	glTranslatef(myShooterX, myShooterY, 0);
	if (player.getLeftMoveOnff() == 1) {
		glRotatef(-45, 0, 1, 0);
	}
	if (player.getRightMoveOnff() == 1) {
		glRotatef(45, 0, 1, 0);
	}
	glScalef(scale, scale, scale);
	glPushMatrix(); // ����
	glColor3d(0.25, 0.25, 0.25);
	drawBlock(70, 40, 15);
	glPopMatrix();
	glPushMatrix(); //�Ӹ�
	glTranslatef(0, 25, 0);
	glColor3d(0.2, 0.2, 0.2);
	drawBlock(20, 30, 9);
	glPopMatrix();
	/*
	glPushMatrix(); // ���ʳ���
		glTranslatef(-37.5 , 0, 0);
		glColor3d(0.8, 0.1, 0);
		drawBlock(15 , 50 , 8 );
	glPopMatrix();
	glPushMatrix(); // �����ʳ���
		glTranslatef(37.5 , 0, 0);
		glColor3d(0.8, 0.1, 0);
		drawBlock(15 , 50 , 8);
	glPopMatrix();
	*/
	glPushMatrix(); // ���ʻ缱����
	glTranslatef(-30, -15, 0);
	glRotatef(-45, 0, 0, 1);
	glColor3d(0.3, 0.3, 0.3);
	drawBlock(40, 40, 12);
	glPopMatrix();
	glPushMatrix(); // ���ʻ缱����
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

	/*���� ��*/
	//glTranslatef(stageX / 4, stageY - 40, 100);
	//glScalef(0.26, 0.26, 0.26);
	//glutStrokeString(GLUT_STROKE_MONO_ROMAN, t);

	/*��Ʈ�� �ε��� �ؽ�Ʈ*/
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

	/*������ ��*/
	//glTranslatef(stageX / 4, stageY - 40, 100);
	//glScalef(0.26, 0.26, 0.26);
	//glutStrokeString(GLUT_STROKE_MONO_ROMAN, t);

	/*��Ʈ�� �ε��� �ؽ�Ʈ*/
	glRasterPos3i(25, stageY - 25, 100);            //Top left corner of text 
	//Since 2nd argument of glutBitmapString must be const unsigned char*
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, t);

	delete[] buf;
	glPopMatrix();
}
void systemManager::showHealth() {
	float healthOfFloat = player.getHealthPoint();
	float healthRatio = player.getHealthPoint() / player.getHealthMax();
	////////////////////////////////////////////////////////////////////////////////////////////////////////////�ؽ�Ʈ �׸���
	float textX = stageX - 170, textY = stageY - 25;
	/*
	char* buf = new char[100];
	sprintf(buf, "%.0f", healthOfFloat);
	glPushMatrix();
	glColor4f(1.0, 1.0, 1.0, 1.0f);  //RGBA values of text color
	const unsigned char* t = reinterpret_cast<const unsigned char*>(buf);

	/*������ ��*/
	//glTranslatef(stageX / 4, stageY - 40, 100);
	//glScalef(0.26, 0.26, 0.26);
	//glutStrokeString(GLUT_STROKE_MONO_ROMAN, t);

	/*��Ʈ�� �ε��� �ؽ�Ʈ*/
	//glRasterPos3i(textX, textY, 100);            //Top left corner of text 
	//Since 2nd argument of glutBitmapString must be const unsigned char*
	/*
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, t);
	delete[] buf;
	glPopMatrix();
	*/
	////////////////////////////////////////////////////////////////////////////////////////////////////////////ü�¹� �׸���
	glPushMatrix();
	/*ü�¹�*/
	glPushMatrix();
	glTranslatef(textX + 22, textY + 6, 99);
	glScalef(healthRatio, 1, 1);
	glColor3d(1.0, 0.0, 0.0);
	drawBlock(240, 20, 1);
	glPopMatrix();
	/*��� ü�¹�*/
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

	/*���� ��*/
	//glTranslatef(stageX / 4, stageY - 40, 100);
	//glScalef(0.26, 0.26, 0.26);
	//glutStrokeString(GLUT_STROKE_MONO_ROMAN, t);

	/*��Ʈ�� �ε��� �ؽ�Ʈ*/
	glRasterPos3i(25, stageY - 75, 100);            //Top left corner of text 
	//Since 2nd argument of glutBitmapString must be const unsigned char*
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, t);

	delete[] buf;
	glPopMatrix();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////// �� �Ѿ� �����Լ�
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
	/*��ġ�� ���*/
	while (temp!= NULL) {
		temp->setBulletX(temp->getBulletX()+ temp->getBulletVecX() * temp->getSpeed());
		temp->setBulletY(temp->getBulletY() + temp->getBulletVecY() * temp->getSpeed());
		temp = temp->getNode();
	}

	temp = systemManager::myBulletListHead;
	myBullet* stemp = NULL;
	/*Ư�����ǽ� ����*/
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
	/*������ ������ ����*/
	while (temp != NULL) {
		stemp = temp->getNode();

		if (temp->getNode() != NULL) {
			temp->getNode()->setPrev(NULL);
			temp->setNode(NULL);
			delete temp;
		}
		temp = stemp;
	}

	delete temp; // ������ �������

	myBulletListHead = NULL;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////�� ���� �Լ�
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

	/*�� ����*/
	if (spawnTime < 0) {
		enemyShooter enemy;
		//���⼭ ���̵� �� �� ���� ��������//
		enemy.setShooterX((rand() / (float)RAND_MAX) * stageX); // ���� ��ȯ�� ��ǥ
		enemy.setShooterY(stageY + 200);
		enemy.setSpeed(0.45 + gameLevel * 0.25);
		enemy.setThisScore(20 + ((rand()%15) * gameLevel)); // �� ���� ����
		enemy.setColorR(0.2 + (rand() / (float)RAND_MAX) * 0.8);
		enemy.setColorG(0.2 + (rand() / (float)RAND_MAX) * 0.8);
		enemy.setColorB(0.2 + (rand() / (float)RAND_MAX) * 0.8);
		systemManager::createEnemyShooter(&enemy); // �� ��ȯ
		spawnTimeCheck = 1;
	}

	enemyShooter* temp = enemyShooterListHead;
	enemyShooter* stemp = NULL;


	while (temp != NULL) { // ��ȸ
		stemp = temp->getNode();

		if (temp->getHealthPoint() < 0) { //hp�� ������
			temp->setOnff(0); // ���ʹ� ���� off
		}
		/*�� �̵�*/
		temp->setShooterX(temp->getShooterX()
			+ temp->getSpeed() * temp->getEnemyVectorX());
		temp->setShooterY(temp->getShooterY()
			+ temp->getSpeed() * temp->getEnemyVectorY()
			- (rand() / (float)RAND_MAX) * 2 * temp->getSpeed());


		/*���� ����*/
		temp->setEnemyToShooterAngle(atan2f(temp->getShooterX() - systemManager::player.getShooterX(),
			temp->getShooterY() - systemManager::player.getShooterY())); // �÷��̾ ���� ���� ����
			/*�÷��̾� �������� ���� ���� +-*/
		temp->setEnemyToShooterAngle(systemManager::convertAtan2toNormal(temp->getEnemyToShooterAngle()));//�Ϲݰ����� ġȯ
		temp->setEnemyToShooterAngle(temp->getEnemyToShooterAngle() 
			+ ((rand() / (float)RAND_MAX) * (PI / 8)*(1 - 0.04 * gameLevel))
			- ((rand() / (float)RAND_MAX) * (PI / 4))*(1 - 0.04 * gameLevel));

		/*�Ѿ� ��ȯ*/
		if (temp->getBulletSpawnTime() <= 0) {
			temp->setBulletSpawnTime(systemManager::enemyBulletSpawnTime
				+ ((rand() / (float)RAND_MAX) * 120 - (gameLevel * 9)));

			enemyBullet enemyBullet;
			//���⼭ �Ѿ˿� ���� ���� ����//
			enemyBullet.setBulletX(temp->getShooterX());
			enemyBullet.setBulletY(temp->getShooterY());
			enemyBullet.setBulletVecX(cos(temp->getEnemyToShooterAngle()));
			enemyBullet.setBulletVecY(sin(temp->getEnemyToShooterAngle()));
			enemyBullet.setBulletVecZ(0);
			enemyBullet.setDamage(enemyBullet.getdamage() + gameLevel * 4);
			enemyBullet.setSpeed(4 + gameLevel * 0.4);
			//std::cout << enemyBullet.bulletVector.x << "  " << enemyBullet.bulletVector.y << std::endl;
			createEnemyBullet(&enemyBullet); // �� �Ѿ� ����
		}

		temp->setBulletSpawnTime(temp->getBulletSpawnTime() - 1);
		if (temp->getHealthPoint() <= 0) { //ü���� 0 ���϶�� 
			enemyDyingEffect effect;
			effect.setEffectX(temp->getShooterX());
			effect.setEffectY(temp->getShooterY());
			effect.setThisScore(temp->getThisScore());
			effect.setEffectR(temp->getColorR());
			effect.setEffectG(temp->getColorG());
			effect.setEffectB(temp->getColorB());
			createEnemyDyingEffect(&effect); //�״� ȿ��  �߰�
			systemManager::score += temp->getThisScore();  // ��ü�� 0�Ǹ� �����߰�
		}
		if (temp->getHealthPoint() <= 0 || temp->getShooterY() < 0) { // ü���� 0���ϸ� ����, ���� y = 0�� ������ ����
			enemyDelete(temp);
		}
		temp = stemp;
	}
}
void systemManager::deleteAllEnemyShooter() {
	enemyShooter* temp = enemyShooterListHead;
	enemyShooter* stemp = NULL;
	/*������ ������ ����*/
	while (temp != NULL) {
		stemp = temp->getNode();

		if (temp->getNode()!= NULL) {
			temp->getNode()->setPrev(NULL);
			temp->setNode(NULL);
			delete temp;
		}
		temp = stemp;
	}

	delete temp; // ������ �������

	enemyShooterListHead = NULL;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////�� �Ѿ� ���� �Լ�
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
	/*������ ������ ����*/
	while (temp != NULL) {
		stemp = temp->getNode();

		if (temp->getNode() != NULL) {
			temp->getNode()->setPrev(NULL);
			temp->setNode(NULL);
			delete temp;
		}
		temp = stemp;
	}

	delete temp; // ������ �������

	enemyBulletListHead = NULL;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////�� �����Լ�
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
	static bool firstStarSpawnCheck = 1; // ó���� ���� ��ġ �Ҷ�
	static int firstStarCount; // ��� ���� ��ġ �� �� �ΰ�
	static float starSpawnTimer; // �� ���� Ÿ�̸�

	/*�� ����*/
	if (starSpawnTimer <= 0)starSpawnCheck = 1;

	if (starSpawnCheck == 1) { // 1

		if (firstStarSpawnCheck == 1) { //2 ó�� ��ġ�� ��
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
		/*�� �̵�*/
		temp->setStarX(temp->getStarX() + temp->getSpeed() * temp->getStarVecX());
		temp->setStarY(temp->getStarY() + temp->getSpeed() * temp->getStarVecY()
			- (rand() / (float)RAND_MAX) * temp->getSpeed());
		temp->setStarZ(temp->getStarZ() + temp->getSpeed() * temp->getStarVecZ());

		/*�� ����*/
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

/*�� ����� �Ѿ� ��Ʈ ����Ʈ ���� �Լ�*/
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

/*�� ���� ����Ʈ ���� �Լ�*/
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

// �浹 ó�� �Լ�
void systemManager::collidSystem() {

	/*�����༱�� ���̻��Ͽ� ���� �浹�˻�*/
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

	/*�� ���༱�� �� �̻��� �浹�˻�*/
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

// ���� ��� �Լ�
void systemManager::inItInGameScreen() {
	gameStartTime = time(NULL); //���ӽ��� �ð� ���
}
void systemManager::gameSystem() {
	if (!(strcmp(gamePage, "page_game")) && player.getHealthPoint() <= 0) {
		strcpy(gamePage, "page_over"); // �������������� ü�� 0 �̸� ���ӿ���ȭ������ ��ȯ
	}
	gameTime = time(NULL) - gameStartTime; //���ݴ����ð� - ���ӽ��۽ô����ð� = �����÷��̽ð�
	gameLevel = gameTime / 30 + 1; // ���ӷ����� 30�ʰ� �������� 1���

	enemySpawnTime = 50 - (gameLevel * 2);

}
void systemManager::myHealthUpSystem() {
	//�� ����� ü�� �ڵ�ȸ�� �ý���
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