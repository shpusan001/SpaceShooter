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
		if (!(strcmp(systemManager::gamePage, "page_start"))) { // 시작화면일때
			systemManager::showStartScreen();
			systemManager::myBulletShowSystem();
			systemManager::starShowSystem();
		}
	glPopMatrix();

	glPushMatrix();
	if (!(strcmp(systemManager::gamePage, "page_game"))) { //게임화면일때
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
		if (!(strcmp(systemManager::gamePage, "page_over"))) {//게임오버화면일때
			systemManager::showOverScreen();
			systemManager::enemyShowSystem();
			systemManager::starShowSystem();
		}
	glPopMatrix();
	glFlush();
}

void MyReshape(int newWidth ,int newHeight) { //왜곡방지
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

	if (!(strcmp(systemManager::gamePage, "page_start")) && key == 32) { // 스페이스바 키로 시작
		systemManager::inItInGameScreen();
		strcpy(systemManager::gamePage, "page_game");
	}

	if (!(strcmp(systemManager::gamePage, "page_over")) && (key == 'r') || (key =='R')) { //r,R키로 초기화
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
	if (!(strcmp(systemManager::gamePage, "page_start"))) {// 시작화면일때
		systemManager::starSystem();	//별 시스템
		systemManager::myBulletSystem(); // 총알 작동 시스템
	}
	if (!(strcmp(systemManager::gamePage, "page_game"))) {//게임 중일때
		systemManager::collidSystem();
		systemManager::player.myShooterMoveSystem(); // 플레이어 비행기 작동 시스템
		systemManager::myShooterShotSystem(); // 총알 발사 시스템
		systemManager::myBulletSystem(); // 총알 작동 시스템
		systemManager::enemySystem(); // 적 작동 시스템
		systemManager::enemyBulletSystem(); // 적 총알 작동 시스템
		systemManager::starSystem(); // 별 작동 시스템
		systemManager::collidSystem(); // 충돌 감지 및 처리 시스템
		systemManager::myBulletHitEffectSystem(); //내 총알 히트 이펙트 시스템
		systemManager::enemyDyingEffectSystem(); // 적 죽음 효과 시스템
		systemManager::myHealthUpSystem();// 체력 자동 회복 시스템
	}
	if (!(strcmp(systemManager::gamePage, "page_over"))) {//게임오버 화면일때
		systemManager::starSystem(); // 별 작동 시스템
		systemManager::enemySystem(); // 적 작동 시스템
	}
		systemManager::gameSystem(); //게임 페이지 관리
		glutPostRedisplay();
		glutTimerFunc(1000 / 60, MyTimer, 1);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	systemManager::inIt();// 초기설정
	
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