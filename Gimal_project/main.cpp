#include "shooter.h"
#include "systemManager.h"
using namespace std;
myShooter systemManager::player;

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPushMatrix();
		if (!(strcmp(systemManager::gamePage, "page_start"))) { // ����ȭ���϶�
			systemManager::showStartScreen();
			systemManager::myBulletShowSystem();
			systemManager::starShowSystem();
		}
	glPopMatrix();

	glPushMatrix();
	if (!(strcmp(systemManager::gamePage, "page_game"))) { //����ȭ���϶�
		glPushMatrix();
		//systemManager::drawStandardPoint();
		systemManager::drawMyShooter(systemManager::player.getShooterX(), systemManager::player.getShooterY(), 0);
		systemManager::myBulletShowSystem();
		systemManager::enemyShowSystem();
		systemManager::showEnemyBullet();
		systemManager::starShowSystem();
		systemManager::showScore();
		systemManager::showHealth();
		systemManager::showGameLevel();
		systemManager::showMyBulletHitEffect();
		systemManager::showEnemyDyingEffect();
		systemManager::showGameTime();
		glPopMatrix();
	}
	glPopMatrix();

	glPushMatrix();
		if (!(strcmp(systemManager::gamePage, "page_over"))) {//���ӿ���ȭ���϶�
			systemManager::showOverScreen();
			systemManager::enemyShowSystem();
			systemManager::starShowSystem();
		}
	glPopMatrix();
	glFlush();
}

void MyReshape(int newWidth ,int newHeight) { //�ְ����
	glViewport(0, 0, newWidth, newHeight);
	GLfloat widthScale = (GLfloat)newWidth / (GLfloat)systemManager::stageX;
	GLfloat heightScale = (GLfloat)newHeight / (GLfloat)systemManager::stageY;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, systemManager::stageX * widthScale, 0, systemManager::stageY * heightScale, -1000.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void MyKeyboard(unsigned char key, int X, int Y) {
	if (key == 'a'|| key == 'A') systemManager::player.attackOn();

	if (!(strcmp(systemManager::gamePage, "page_start")) && key == 32) { // �����̽��� Ű�� ����
		systemManager::inItInGameScreen();
		strcpy(systemManager::gamePage, "page_game");
	}

	if (!(strcmp(systemManager::gamePage, "page_over")) && (key == 'r') || (key =='R')) { //r,RŰ�� �ʱ�ȭ
		strcpy(systemManager::gamePage, "page_start");
	}
}

void MyKeyboardUp(unsigned char key, int X, int Y) {
	if (key == 'a' || key == 'A') systemManager::player.attackOff();
}

void MySpecial(int key, int X, int Y) {
	if (key == GLUT_KEY_LEFT) systemManager::player.moveLeftDown();
	if (key == GLUT_KEY_RIGHT) systemManager::player.moveRightDown();
	if (key == GLUT_KEY_UP) systemManager::player.moveUpDown();
	if (key == GLUT_KEY_DOWN) systemManager::player.moveDownDown();
}

void MySpecialUp(int key, int X, int Y) {
	if (key == GLUT_KEY_LEFT) systemManager::player.moveLeftUp();
	if (key == GLUT_KEY_RIGHT) systemManager::player.moveRightUp();
	if (key == GLUT_KEY_UP) systemManager::player.moveUpUp();
	if (key == GLUT_KEY_DOWN) systemManager::player.moveDownUp();
}

void MyTimer(int Value) {
	if (!(strcmp(systemManager::gamePage, "page_start"))) {// ����ȭ���϶�
		systemManager::starSystem();	//�� �ý���
		systemManager::myBulletSystem(); // �Ѿ� �۵� �ý���
	}
	if (!(strcmp(systemManager::gamePage, "page_game"))) {//���� ���϶�
		systemManager::collidSystem();
		systemManager::player.myShooterMoveSystem(); // �÷��̾� ����� �۵� �ý���
		systemManager::myShooterShotSystem(); // �Ѿ� �߻� �ý���
		systemManager::myBulletSystem(); // �Ѿ� �۵� �ý���
		systemManager::enemySystem(); // �� �۵� �ý���
		systemManager::enemyBulletSystem(); // �� �Ѿ� �۵� �ý���
		systemManager::starSystem(); // �� �۵� �ý���
		systemManager::collidSystem(); // �浹 ���� �� ó�� �ý���
		systemManager::myBulletHitEffectSystem(); //�� �Ѿ� ��Ʈ ����Ʈ �ý���
		systemManager::enemyDyingEffectSystem(); // �� ���� ȿ�� �ý���
		systemManager::myHealthUpSystem();// ü�� �ڵ� ȸ�� �ý���
	}
	if (!(strcmp(systemManager::gamePage, "page_over"))) {//���ӿ��� ȭ���϶�
		systemManager::starSystem(); // �� �۵� �ý���
		systemManager::enemySystem(); // �� �۵� �ý���
	}
		systemManager::gameSystem(); //���� ������ ����
		glutPostRedisplay();
		glutTimerFunc(1000 / 60, MyTimer, 1);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	systemManager::inIt();// �ʱ⼳��
	
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(MyKeyboard);
	glutKeyboardUpFunc(MyKeyboardUp);
	glutSpecialFunc(MySpecial);
	glutSpecialUpFunc(MySpecialUp);
	glutTimerFunc(1, MyTimer, 1);
	glutMainLoop();

	return 0;
}