#include "enemyBullet.h"
#include "systemManager.h"

enemyBullet::enemyBullet() {
    bulletSize = 10;
    bulletX = 0;
    bulletY = 0;
    bulletVecX = 0;
    bulletVecY = 0;
    bulletVecZ = 0;
    damage = 20;
    onff = 1;
}

void enemyBullet::drawEnemyBullet() {
    glPushMatrix();
        glTranslatef(bulletX, bulletY, 0);
        glColor3d(0.517, 0.968, 0.937);
        glutSolidSphere(bulletSize, 30, 30);
    glPopMatrix();
}

bool enemyBullet::getOnff() {
    return onff;
}

void enemyBullet::setOnff(bool input) {
    onff = input;
    return;
}

enemyBullet* enemyBullet::getNode() {
    return node;
}
void enemyBullet::setNode(enemyBullet* input) {
    node = input;
}

enemyBullet* enemyBullet::getPrev() {
    return prev;
}
void enemyBullet::setPrev(enemyBullet* input) {
    prev = input;
}