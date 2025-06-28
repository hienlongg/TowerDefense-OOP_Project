﻿#include "cbullet.h"
#include <vector>
#include <cmath>      
#include <algorithm> 
#include <SFML/Graphics.hpp>
#include "cenemy.h"
#include "cpoint.h"

using namespace std;

<<<<<<< HEAD
cbullet::cbullet()
{
    _n = 0;
    _speed = 4;
    _curr = cpoint(0, 0, 0);
=======
cbullet::cbullet() : _posX(0.f), _posY(0.f), _speed(4), _active(true), _targetIdx(-1), _damage(1), _n(0) {
>>>>>>> github-desktop-chinnnn3107/Update3
    for (int i = 0; i < cpoint::MAP_ROW * cpoint::MAP_COL; i++)
    {
        _p[i] = cpoint(0, 0, 0);
    }
    for (int i = 0; i < cpoint::MAP_ROW; i++)
    {
        for (int j = 0; j < cpoint::MAP_COL; j++)
        {
            _m[i][j] = cpoint(0, 0, 0);
        }
    }
}

<<<<<<< HEAD
// logic
void cbullet::updateMap(int i, int j, cpoint v)
{
    if (i >= 0 && i < cpoint::MAP_ROW && j >= 0 && j < cpoint::MAP_COL)
        _m[i][j] = v;
}
=======
// Update
void cbullet::updateMap(cpoint map[][cpoint::MAP_COL]) {
    for (int i = 0; i < cpoint::MAP_ROW; i++)
        for (int j = 0; j < cpoint::MAP_COL; j++)
            _m[i][j] = map[i][j];
}

cpoint cbullet::getCurr() const { return _curr; }
void cbullet::setCurr(const cpoint& tcurr) { _curr = tcurr; }
cpoint* cbullet::getP() { return _p; }
int cbullet::getSpeed() const { return _speed; }
int cbullet::getN() const { return _n; }
void cbullet::setN(int tn) { if (tn >= 0 && tn <= cpoint::MAP_ROW * cpoint::MAP_COL) _n = tn; }
void cbullet::setSpeed(int tspeed) { if (tspeed > 0 && tspeed < 20) _speed = tspeed; }

>>>>>>> github-desktop-chinnnn3107/Update3
int cbullet::queryCFromRowCol(int row, int col) const {
    if (row < 0 || row >= cpoint::MAP_ROW || col < 0 || col >= cpoint::MAP_COL)
        return -2;
    return _m[row][col].getC();
}
int cbullet::calcPathBullet(const cpoint& tower)
{
    int row = tower.getRow(), col = tower.getCol(), i = 0;

    do {
        col++; row--;
        if (queryCFromRowCol(row, col) == 0)
        {
            _p[i] = cpoint(row, col, 0);
            i += 2;
        }
        else break;
    } while (i < cpoint::MAP_ROW * cpoint::MAP_COL);

    _n = i;
<<<<<<< HEAD
    for (i = 1; i < _n; i += 2) {
        _p[i] = cpoint(_p[i - 1].getRow(), _p[i - 1].getCol(), 0); // center cell, hoặc tùy path bạn muốn
    }
    _p[0] = cpoint(tower.getRow(), tower.getCol(), 0);
=======

    for (i = 1; i < _n; i += 2) 
        _p[i] = cpoint(_p[i - 1].getRow(), _p[i - 1].getCol(), 0); 
    
>>>>>>> github-desktop-chinnnn3107/Update3
    if (_n > 0)
        _curr = _p[0];
    return _n;
}

<<<<<<< HEAD
void cbullet::trackEnemy(const cenemy& enemy) {
    cpoint enemyPos = enemy.getCurr();
    int bulletRow = _curr.getRow();
    int bulletCol = _curr.getCol();
    int enemyRow = enemyPos.getRow();
    int enemyCol = enemyPos.getCol();
=======
// Update changes: 
// Check collision by calculating pixel distance between bullet and enemy instead of grid - based
bool cbullet::checkCollision(const cenemy& enemy) const {
    float dx = _posX - enemy.getX(); // Cal horizontal distance between bullet and enemy
    float dy = _posY - enemy.getY(); // // Cal vertical distance between bullet and enemy

    // Collision threshold
    return sqrt(dx * dx + dy * dy) < 15.f; 
}

// Move the bullet towards the enemy using pixel-based tracking instead of grid - based
void cbullet::trackEnemy(const cenemy& enemy, float deltaTime) {
    float dx = enemy.getX() - _posX; 
    float dy = enemy.getY() - _posY;
    float len = sqrt(dx * dx + dy * dy); 
>>>>>>> github-desktop-chinnnn3107/Update3

    if (len > 0.01f) {
        dx /= len;
        dy /= len;

        // Move the bullet towards the enemy based on speed and frame time
        move(dx * _speed * deltaTime * 200.f, dy * _speed * deltaTime * 200.f); 

        // Cal angle in degrees and rotate
        // atan2(dy, dx): calculates the angle (in radians) between the positive X-axis and the line from the bullet to the enemy
        // 180.f / 3.14159f: convert radians to degrees
        float angle = atan2(dy, dx) * 180.f / 3.14159f; 
        _sprite.setRotation(angle);
    }
}

// Add
void cbullet::init(const sf::Texture& tex, float x, float y) {
    _sprite.setTexture(tex);
    _sprite.setOrigin(tex.getSize().x / 2.f, tex.getSize().y / 2.f); // Center the sprite origin
    _sprite.setScale(0.3f, 0.3f);
    _posX = x;
    _posY = y;
    _sprite.setPosition(_posX, _posY);
    _curr = cpoint::fromXYToRowCol(x, y);
}

void cbullet::updateSprite() {
    _sprite.setPosition(_posX, _posY);
}

void cbullet::setPosition(float x, float y) { 
    _posX = x; 
    _posY = y; 
    updateSprite();
}

void cbullet::move(float dx, float dy) {
    _posX += dx;
    _posY += dy;
    updateSprite();
}
bool cbullet::checkCollision(const cenemy& enemy) const {
    // Compare bullet's current grid position with enemy's grid position
    cpoint enemyPos = enemy.getCurr();
    return _curr.getRow() == enemyPos.getRow() && _curr.getCol() == enemyPos.getCol();
}

// getters
cpoint cbullet::getCurr() const
{
    return _curr;
}
cpoint* cbullet::getP()
{
    return _p;
}
int cbullet::getSpeed() const
{
    return _speed;
}
int cbullet::getN() const
{
    return _n;
}
int cbullet::getTargetIndex() const
{
    return targetIndex;
}
bool cbullet::isActive() const
{
    return active;
}

<<<<<<< HEAD
// setters
void cbullet::setCurr(const cpoint& tcurr)
{
    _curr = tcurr;
}
void cbullet::setN(int tn)
{
    if (tn >= 0 && tn <= cpoint::MAP_ROW * cpoint::MAP_COL) _n = tn;
}
void cbullet::setSpeed(int tspeed)
{
    if (tspeed > 0 && tspeed < 20) _speed = tspeed;
}
void cbullet::setTargetIdx(int idx)
{
    targetIndex = idx;
}
void cbullet::activate()
{
    active = true;
}
void cbullet::deactivate()
{
    active = false;
}
=======

>>>>>>> github-desktop-chinnnn3107/Update3
