#pragma once
#include<vector>
#include<iostream>
#include<Windows.h>
#include"Additional_function.h"
using namespace std;

class ENTITY
{
protected:
	int x;
	int y;
	

public:
	ENTITY() {  }
	~ENTITY(){}
	virtual void render() = 0;
	int getx() { return x; }
	int gety() { return y; }
};
class play_ground : public ENTITY
{
public:
	play_ground() { x = 20; y = 5; }
	~play_ground(){}
	void render();
	void change_coord(int x, int y);
	void game_over();
	friend class SnakeHead;
	friend class SnakeBody;
	friend class Food;
};
class SnakeHead : public ENTITY
{
	int x0;
	int y0;
public:
	SnakeHead() { x = 25; y = 10; x0 = 25; y0 = 10; }
	~SnakeHead(){}
	int direction = 1;
	int direction0;
	int getx0() { return x0; }
	int gety0() { return y0; }
	void foward();
	void render();
	void render(play_ground area);
	void changedirection(int i);
	void rendercoord()
	{
		gotoxy(0, 0);
		cout << "\nx : " << x;
		cout << "\ny : " << y;
		cout << "\nx0 : " << x0;
		cout << "\ny0 : " << y0;
	}
	friend class play_ground;
	friend class Snake;
	friend class Food;
};
class SnakeBody : public ENTITY
{
	int x0;
	int y0;

public:
	int direction = 1;
	int direction0;


	SnakeBody() { x0 = x; y0 = y; }
	~SnakeBody(){}
	int getX0() { return x0; }
	int getY0() { return y0; }
	void setcoord(int x, int y) { this->x = x; this->y = y; }
	void foward();
	void render();
	void render(play_ground area);
	friend class play_ground;
	friend class SnakeHead;
	friend class Snake;
	
};
class Snake
{
	int length;
	SnakeHead Head;
	vector < SnakeBody> Body;
public:
	Snake() {
		length = 2;
		Head.x = 40;
		Head.y = 12;
		for (int i = 0; i < length; i++)
		{
			if (i == 0)
			{
				SnakeBody newpart;
				newpart.setcoord(39-i,12);
				newpart.x0 = newpart.x;
				newpart.y0 = newpart.y;
				Body.push_back(newpart);
			}
			else
			{
				SnakeBody newpart;
				newpart.setcoord(39-i,12);
				Body.push_back(newpart);
			}
		}
	};
	~Snake() { Body.clear(); }
	int getHeadX() { return Head.x; }
	int getHeadY() { return Head.y; }
	void render();
	void render(play_ground area);
	void foward();
	void changedirection(int i);
	void push();
	SnakeHead getHead() { return this->Head; }
	friend class play_ground;
	friend class Food;
	bool checkspawn(int x, int y);
	bool checkCollision(int x, int y);
	
};
class Food : public ENTITY
{
public :
	Food() { x = 6; y = 6; }
	~Food(){}
	bool interaction(int x, int y)
	{
		return x == this->x && y == this->y;
	}
	void respawnfood(int x, int y) {
		this->x = x;
		this->y = y;
	}
	void render();
	void render(play_ground area);

	friend class SnakeHead;
	bool beEaten(Snake head);
	void disapear(play_ground area);
	
	
};