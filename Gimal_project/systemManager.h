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
	static myBullet* myBulletListHead; // 내 총알 리스트 헤드
	static enemyShooter* enemyShooterListHead;//적 리스트
	static enemyBullet* enemyBulletListHead; // 적 총알 리스트 헤드 
	static star* starListHead; // 별 리스트 헤드
	static myBulletHitEffect* myBulletHitEffectListHead; //내 총알 타격 이펙트 리스트 헤드
	static enemyDyingEffect* enemyDyingEffectListHead; // 적 사망 이펙트 리스트 헤드

	static float score; //점수기록
	static int gameLevel; //게임레벨

	static float enemySpawnTime; // 적 생성 주기
	static float enemyBulletSpawnTime; // 적 총알 생성 주기
	static float starSpawnTime; //별 생성주기 
	static float healthUpTime; //자동체력회복 주기

	static time_t gameStartTime; //시작시간
	static time_t gameTime; // 진행시간

public:
	static myShooter player; // 내 비행기 객체
	static char* gamePage; //게임페이지
	static float stageX; //윈도우창 가로
	static float stageY; //윈도우창 세로

	static void drawBlock(float width, float height, float depth); // 블럭 그리기
	static void drawStandardPoint(); // 기준점 그리기
	static float convertAtan2toNormal(float angle); //atan2의 각도를 일반적인 각도로 변환
	static void closingEvent();

	static void showScore(); // 점수 출력함수
	static void showGameLevel(); //게임레벨 출력함수
	static void showHealth(); // 체력 출력함수

	static int createMyBullet(myBullet* inputNode); // 리스트에 총알 추가하기
	static void myBulletSystem(); // 내 총알 관리 시스템
	static void myBulletShowSystem(); // 화면에 총알모양 그리기
	static void deleteMyBullet(myBullet* del); //리스트에 총알 제거
	static void myBulletAllDelete(); //내 총알 모두 제거
	
	static void drawMyShooter(float myShooterX, float myShooterY, float myShooterZ); //내 비행기 그리기
	static void myShooterShotSystem(); //내 총알 발사 처리
	
	static void createEnemyShooter(enemyShooter* inputNode); //리스트에 적추가
	static void enemyShowSystem();// 리스트에 있는 적 화면에 나타나게 함.
	static void enemySystem(); //적 행동 관련 처리
	static void enemyDelete(enemyShooter* del); // 리스트에서 적 제거
	static void deleteAllEnemyShooter();
	
	static void createEnemyBullet(enemyBullet* inputNode);//적 총알 생성
	static void showEnemyBullet(); //화면에 적 총알 그리기
	static void enemyBulletSystem(); //적 총알 정보 처리
	static void deleteEnemyBullet(enemyBullet* del); // 적 총알 제거
	static void deleteAllEnemyBullet();//적 총알 모두 제거

	static void createStar(star* input);//별 만들기
	static void starShowSystem(); //별 보여주기
	static void starSystem(); // 별 정보 처리
	static void deleteStar(star* del); // 별 제거

	/*총알 타격 효과*/
	static void createMyBulletHitEffect(myBulletHitEffect* input); // 총알 타격 이펙트 추가
	static void deleteMyBulletHitEffect(myBulletHitEffect* del); // 총알 타격 이펙트 제거
	static void showMyBulletHitEffect(); //총알 타격 이펙트 출력
	static void myBulletHitEffectSystem(); // 총알 타격 이펙트 연산
	static void deleteAllMyBulletHitEffect(); // 모든 총알 타격 이펙트 제거

	/*적 사망 효과*/
	static void createEnemyDyingEffect(enemyDyingEffect* input); // 적 사망 이펙트 추가
	static void deleteEnemyDyingEffect(enemyDyingEffect* del); // 적 사망 이펙트 제거
	static void showEnemyDyingEffect(); // 적 사망 이펙트 출력
	static void enemyDyingEffectSystem(); // 적 사망 이펙트 연산
	static void deleteAllEnemyDyingEffect(); // 모든 적 사망 이벤트 제거

	static void collidSystem(); // 충돌 계산
	static void gameSystem(); // 게임시작, 게임오버 담당 시스템

	static void showStartScreen(); // 시작화면 출력 
	static void inItInGameScreen(); // 게임 진입시 셋팅함수
	static void showOverScreen(); // 게임오버 화면 출력
	static void showGameTime(); //게임시간 출력

	static void myHealthUpSystem();//체력 자동회복 시스템
	static void inIt(); //초기 설정
};


#endif 