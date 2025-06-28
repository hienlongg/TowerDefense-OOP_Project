﻿#include "cenemy.h"
#include <iostream>

<<<<<<< HEAD
using namespace std;

cenemy::cenemy()
{
    for (int i = 0; i < cpoint::MAP_ROW * cpoint::MAP_COL; i++)
    {
        _p[i] = cpoint();
    }

    dd[0] = -1; dc[0] = 0; // up
    dd[1] = 0; dc[1] = -1; // left
    dd[2] = 1; dc[2] = 0; // down
    dd[3] = 0; dc[3] = 1; // right

    _start = _end = _curr = cpoint();
    _speed = 3;
    _pathLength = 0;

    this->hitCount = 0;
    this->reachEnd = false;
}
cenemy::cenemy(cpoint tstart, cpoint tend, cpoint tcurr) : cenemy()
{
=======
cenemy::cenemy()
    : _posX(0.f), _posY(0.f), _health(3), _speed(3), _currentTarget(1), _reachedEnd(false), _pathLength(0) {

    // Directions: up, left, down, right for pathfinding
    dd[0] = -1; dd[1] = 0; dd[2] = 1; dd[3] = 0;
    dc[0] = 0; dc[1] = -1; dc[2] = 0; dc[3] = 1;

    // Default positions in grid
    _start = cpoint();
    _end = cpoint();
    _curr = cpoint();

    // Path array initialization
    for (int i = 0; i < cpoint::MAP_ROW * cpoint::MAP_COL; i++)
        _p[i] = cpoint();
}


cenemy::cenemy(cpoint tstart, cpoint tend, cpoint tcurr) : cenemy() {
>>>>>>> github-desktop-chinnnn3107/Update3
    _start = tstart;
    _end = tend;
    _curr = tcurr;
}

// runtime process
void cenemy::findPath(cpoint a[][cpoint::MAP_COL], cpoint s, cpoint e)
{
    int ta[cpoint::MAP_ROW][cpoint::MAP_COL];
    for (int i = 0; i < cpoint::MAP_ROW; i++)
    {
        for (int j = 0; j < cpoint::MAP_COL; j++)
            ta[i][j] = a[i][j].getC();
    }
    calcPath(ta, cpoint::MAP_ROW, s, e);
}
void cenemy::move(float dt)
{
    cout << "Moving enemy... target: " << currentTarget << "/" << _pathLength << ", reached: " << reachEnd << endl;

<<<<<<< HEAD
    if (reachEnd || currentTarget >= _pathLength)
    {
        reachEnd = true;
        return;
    }

    float curX = _curr.getPixelX();
    float curY = _curr.getPixelY();
    float targetX = _p[currentTarget].getPixelX();
    float targetY = _p[currentTarget].getPixelY();

    float dx = targetX - curX;
    float dy = targetY - curY;
    float distance = sqrt(dx * dx + dy * dy); // dx and dy are 2 edges of a right angle => dist is the longest edge

    if (distance < 1.f)
    {
        currentTarget++; // move to the next tile
        if (currentTarget >= _pathLength)
            reachEnd = true;
    }
    else
    {
        dx = dx / distance * _speed * dt * 60.f; // dx / distance to make it no longer than 1; (* _speed * dt * 60.f) is how much to move (dt: time passed in 1 frame, 60.f: 60 fps)
        dy = dy / distance * _speed * dt * 60.f;
        _curr.setPixelX(curX + dx);
        _curr.setPixelY(curY + dy);
    }
}
void cenemy::onHit()
{
    hitCount++;
}
bool cenemy::isDead() const
{
    return this->hitCount >= 3;
}
bool cenemy::isReachedEnd() const
{
    return reachEnd;
}

cpoint cenemy::getCurr() const
{
    return _curr;
}
void cenemy::setCurr(const cpoint& tcurr)
{
    _curr = tcurr;
}

// path access
cpoint* cenemy::getP()
{
    return _p;
}
int cenemy::getPathLength() const
{
    return _pathLength;
}
int cenemy::getCurrentTarget() const
{
    return currentTarget;
}
void cenemy::setCurrentTarget(int curTarget)
{
    this->currentTarget = curTarget;
}

// getter setter
cpoint cenemy::getStart() const
{
    return _start;
}
cpoint cenemy::getEnd() const
{
    return _end;
}
int cenemy::getSpeed() const
{
    return _speed;
}
void cenemy::setStart(const cpoint& tstart)
{
    _start = tstart;
}
void cenemy::setEnd(const cpoint& tend)
{
    _end = tend;
}
void cenemy::setSpeed(int tspeed)
{
    if (tspeed > 0 && tspeed < 10) _speed = tspeed;
}

void cenemy::calcPath(int a[][cpoint::MAP_COL], int n, cpoint s, cpoint e)
{
    queue<cpoint> q;
=======

void cenemy::calcPath(int a[][cpoint::MAP_COL], int n, cpoint s, cpoint e) {
    std::queue<cpoint> q;
>>>>>>> github-desktop-chinnnn3107/Update3
    bool visited[cpoint::MAP_ROW][cpoint::MAP_COL] = {};
    cpoint parent[cpoint::MAP_ROW][cpoint::MAP_COL];

    q.push(s);
    visited[s.getRow()][s.getCol()] = true;
    parent[s.getRow()][s.getCol()] = s;

    bool found = false;
    while (!q.empty())
    {
        cpoint curr = q.front(); q.pop();
        if (curr.getRow() == e.getRow() && curr.getCol() == e.getCol())
        {
            found = true;
            break;
        }
        for (int i = 0; i < 4; i++)
        {
            int dmoi = dd[i] + curr.getRow(), cmoi = dc[i] + curr.getCol();
            if (dmoi >= 0 && dmoi < cpoint::MAP_ROW &&
                cmoi >= 0 && cmoi < cpoint::MAP_COL &&
                !visited[dmoi][cmoi] && a[dmoi][cmoi] == 0)
            {
                visited[dmoi][cmoi] = true;
                parent[dmoi][cmoi] = curr;
                q.push(cpoint(dmoi, cmoi, 0));
            }
        }
    }

    if (found)
    {
        vector<cpoint> pathList;
        cpoint curr = e;
        while (!(curr.getRow() == s.getRow() && curr.getCol() == s.getCol()))
        {
            pathList.push_back(curr);
            curr = parent[curr.getRow()][curr.getCol()];
        }
        pathList.push_back(s);
        reverse(pathList.begin(), pathList.end());
        int i = 0;
        for (auto& p : pathList)
        {
            _p[i++] = p;
        }
        _pathLength = i;
    }
    else
    {
        _pathLength = 0;
    }
<<<<<<< HEAD
}
=======
}

void cenemy::findPath(cpoint a[][cpoint::MAP_COL], cpoint s, cpoint e) {
    int ta[cpoint::MAP_ROW][cpoint::MAP_COL];
    for (int i = 0; i < cpoint::MAP_ROW; i++)
        for (int j = 0; j < cpoint::MAP_COL; j++)
            ta[i][j] = a[i][j].getC();
    calcPath(ta, cpoint::MAP_ROW, s, e);
}

void cenemy::init(const sf::Texture& tex, float x, float y, int hp) {
    _sprite.setTexture(tex);
    _sprite.setOrigin(tex.getSize().x / 2.f, tex.getSize().y / 2.f); // Center the sprite origin
    _sprite.setScale(0.5f, 0.5f);
    _posX = x;
    _posY = y;
    _health = hp;
    _reachedEnd = false;
    _currentTarget = 1;  
    updateSprite();
}

void cenemy::updateSprite() {
    _sprite.setPosition(_posX, _posY);
}

void cenemy::setPosition(float x, float y) { 
    _posX = x; 
    _posY = y; 
    updateSprite(); 
}

void cenemy::move(float dx, float dy) { 
    _posX += dx; 
    _posY += dy; 
    updateSprite(); 
}

void cenemy::takeDamage(int damage) {
    _health -= damage;

    if (_health <= 0) {
        _sprite.setColor(sf::Color(255, 255, 255, 0)); // Make enemy disappear
        _reachedEnd = true; 
    }
    else { 
        // Enemy takes damage: color becomes more red as health decreases
        float intensity = static_cast<float>(_health) / 3.f; // Assuming max health is 3 for scaling, adjust based on level setting
        if (intensity < 0.f) intensity = 0.f;
        if (intensity > 1.f) intensity = 1.f;

        int greenBlue = static_cast<int>(255 * intensity);

        // The lower the health, the less green/blue -> more red
        _sprite.setColor(sf::Color(255, greenBlue, greenBlue));
    }
}





>>>>>>> github-desktop-chinnnn3107/Update3
