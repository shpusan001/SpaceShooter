#ifndef systemManager_H
#define systemManager_H
#define _CRT_SECURE_NO_WARNINGS

#include <gl/glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/freeglut.h>


#include<stdlib.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#include "myShooter.h"
#include "enemyShooter.h"
#include "myBullet.h"
#include "enemyBullet.h"
#include "star.h"
#include "myBulletHitEffect.h"
#include "enemyDyingEffect.h"

#define PI 3.141592
///////////////////////////////////////////////////////////////////////////////////////////////////
class systemManager {
	static myBullet* myBulletListHead; // �� �Ѿ� ����Ʈ ���
	static enemyShooter* enemyShooterListHead;//�� ����Ʈ
	static enemyBullet* enemyBulletListHead; // �� �Ѿ� ����Ʈ ��� 
	static star* starListHead; // �� ����Ʈ ���
	static myBulletHitEffect* myBulletHitEffectListHead; //�� �Ѿ� Ÿ�� ����Ʈ ����Ʈ ���
	static enemyDyingEffect* enemyDyingEffectListHead; // �� ��� ����Ʈ ����Ʈ ���

	static float score; //�������
	static int gameLevel; //���ӷ���

	static float enemySpawnTime; // �� ���� �ֱ�
	static float enemyBulletSpawnTime; // �� �Ѿ� ���� �ֱ�
	static float starSpawnTime; //�� �����ֱ� 
	static float healthUpTime; //�ڵ�ü��ȸ�� �ֱ�

	static time_t gameStartTime; //���۽ð�
	static time_t gameTime; // ����ð�

public:
	static myShooter player; // �� ����� ��ü
	static char* gamePage; //����������
	static float stageX; //������â ����
	static float stageY; //������â ����

	static void drawBlock(float width, float height, float depth); // �� �׸���
	static void drawStandardPoint(); // ������ �׸���
	static float convertAtan2toNormal(float angle); //atan2�� ������ �Ϲ����� ������ ��ȯ
	static void closingEvent();

	static void showScore(); // ���� ����Լ�
	static void showGameLevel(); //���ӷ��� ����Լ�
	static void showHealth(); // ü�� ����Լ�

	static int createMyBullet(myBullet* inputNode); // ����Ʈ�� �Ѿ� �߰��ϱ�
	static void myBulletSystem(); // �� �Ѿ� ���� �ý���
	static void myBulletShowSystem(); // ȭ�鿡 �Ѿ˸�� �׸���
	static void deleteMyBullet(myBullet* del); //����Ʈ�� �Ѿ� ����
	static void myBulletAllDelete(); //�� �Ѿ� ��� ����
	
	static void drawMyShooter(float myShooterX, float myShooterY, float myShooterZ); //�� ����� �׸���
	static void myShooterShotSystem(); //�� �Ѿ� �߻� ó��
	
	static void createEnemyShooter(enemyShooter* inputNode); //����Ʈ�� ���߰�
	static void enemyShowSystem();// ����Ʈ�� �ִ� �� ȭ�鿡 ��Ÿ���� ��.
	static void enemySystem(); //�� �ൿ ���� ó��
	static void enemyDelete(enemyShooter* del); // ����Ʈ���� �� ����
	static void deleteAllEnemyShooter();
	
	static void createEnemyBullet(enemyBullet* inputNode);//�� �Ѿ� ����
	static void showEnemyBullet(); //ȭ�鿡 �� �Ѿ� �׸���
	static void enemyBulletSystem(); //�� �Ѿ� ���� ó��
	static void deleteEnemyBullet(enemyBullet* del); // �� �Ѿ� ����
	static void deleteAllEnemyBullet();//�� �Ѿ� ��� ����

	static void createStar(star* input);//�� �����
	static void starShowSystem(); //�� �����ֱ�
	static void starSystem(); // �� ���� ó��
	static void deleteStar(star* del); // �� ����

	/*�Ѿ� Ÿ�� ȿ��*/
	static void createMyBulletHitEffect(myBulletHitEffect* input); // �Ѿ� Ÿ�� ����Ʈ �߰�
	static void deleteMyBulletHitEffect(myBulletHitEffect* del); // �Ѿ� Ÿ�� ����Ʈ ����
	static void showMyBulletHitEffect(); //�Ѿ� Ÿ�� ����Ʈ ���
	static void myBulletHitEffectSystem(); // �Ѿ� Ÿ�� ����Ʈ ����
	static void deleteAllMyBulletHitEffect(); // ��� �Ѿ� Ÿ�� ����Ʈ ����

	/*�� ��� ȿ��*/
	static void createEnemyDyingEffect(enemyDyingEffect* input); // �� ��� ����Ʈ �߰�
	static void deleteEnemyDyingEffect(enemyDyingEffect* del); // �� ��� ����Ʈ ����
	static void showEnemyDyingEffect(); // �� ��� ����Ʈ ���
	static void enemyDyingEffectSystem(); // �� ��� ����Ʈ ����
	static void deleteAllEnemyDyingEffect(); // ��� �� ��� �̺�Ʈ ����

	static void collidSystem(); // �浹 ���
	static void gameSystem(); // ���ӽ���, ���ӿ��� ��� �ý���

	static void showStartScreen(); // ����ȭ�� ��� 
	static void inItInGameScreen(); // ���� ���Խ� �����Լ�
	static void showOverScreen(); // ���ӿ��� ȭ�� ���
	static void showGameTime(); //���ӽð� ���

	static void myHealthUpSystem();//ü�� �ڵ�ȸ�� �ý���
	static void inIt(); //�ʱ� ����
};


#endif 