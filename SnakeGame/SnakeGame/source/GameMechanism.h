#pragma once
#include<iostream>
#include<string>
#include"Additional_function.h"
#include"ENTITY.h"
#include"HighScore.h"
#include<conio.h>
#include<ctime>
using namespace std;

static Snake resetSnake(Snake &snake)
{
	Snake newsnake;
	return newsnake;
}


static void renderColor(string a,int i,int x,int y)
{	
	gotoxy(x, y);
	change_color(i);
	cout<< a;
	change_color(15);
}



















class GameMenu {
public:
	string menu1 = "NEW GAME";
	string menu2 = "CONTINUE";
	string menu3 = "LEVEL";
	string menu4 = "HIGH SCORE";
	string menu5 = "CREDIT";
	string menu6 = "QUIT";
	int menu_id = 1;
	bool inGame = 0;

	
	void render()
	{	
		gotoxy(40, 12);
		switch (menu_id)
		{
		case 1:
		{
			renderColor(menu1, 10,40,12);
			renderColor(menu2, 15,40,13);
			renderColor(menu3, 15,40,14);
			renderColor(menu4, 15,40,15);
			renderColor(menu5, 15,40,16);
			renderColor(menu6, 15,40,17);
			break;
		}
		case 2:
		{
			renderColor(menu1, 15, 40, 12);
			renderColor(menu2, 10, 40, 13);
			renderColor(menu3, 15, 40, 14);
			renderColor(menu4, 15, 40, 15);
			renderColor(menu5, 15, 40, 16);
			renderColor(menu6, 15, 40, 17);
			break;
		}
		case 3:
		{
			renderColor(menu1, 15, 40, 12);
			renderColor(menu2, 15, 40, 13);
			renderColor(menu3, 10, 40, 14);
			renderColor(menu4, 15, 40, 15);
			renderColor(menu5, 15, 40, 16);
			renderColor(menu6, 15, 40, 17);
			break;
		}
		case 4:
		{
			renderColor(menu1, 15, 40, 12);
			renderColor(menu2, 15, 40, 13);
			renderColor(menu3, 15, 40, 14);
			renderColor(menu4, 10, 40, 15);
			renderColor(menu5, 15, 40, 16);
			renderColor(menu6, 15, 40, 17);
			break;
		}
		case 5:
		{
			renderColor(menu1, 15, 40, 12);
			renderColor(menu2, 15, 40, 13);
			renderColor(menu3, 15, 40, 14);
			renderColor(menu4, 15, 40, 15);
			renderColor(menu5, 10, 40, 16);
			renderColor(menu6, 15, 40, 17);
			break;
		}
		case 6:
		{
			renderColor(menu1, 15, 40, 12);
			renderColor(menu2, 15, 40, 13);
			renderColor(menu3, 15, 40, 14);
			renderColor(menu4, 15, 40, 15);
			renderColor(menu5, 15, 40, 16);
			renderColor(menu6, 10, 40, 17);
			break;
		}

		}

	}
	
};

class TotalGame {
public:
	bool isGameOver = 0;
	play_ground area;
	GameMenu menu;
	Snake snake;
	Food food;
	HighScoreList score_list;
	int score;
	char name[50];
	int diff = 1;
	ifstream input;
	ofstream output;
	bool newGame()
	{	
		isGameOver = 0;
		snake = resetSnake(snake);
		score = 0;
		menu.inGame = 1;

		return 1;
	}
	bool addScore()
	{
		if (food.beEaten(snake))
		{

			food.disapear(area);
			snake.push();

			srand(time(0));
			int randx;
			int randy;

			do
			{
				srand(time(0));
				randx = 1 + rand() % (79);
				randy = 1 + rand() % (24);
			} while (snake.checkspawn(randx, randy));


			food.respawnfood(randx, randy);
			 

			score += 2*diff;
			return 1;
		}
		return 0;
	}
	bool gameOver()
	{
		if (snake.checkCollision(snake.getHeadX(), snake.getHeadY()))
		{
			area.game_over();
			Sleep(200);
			menu.inGame = 0;

			gotoxy(area.getx() + 10, area.gety() + 12);
			cout << " Enter your name (using space cause error ) : ";
			cin >> name;
			score_list.inputFile(input);
			score_list.newhighscore(name, score);
			score_list.outputfile(output);
			isGameOver = 1;
			return 1;

		}
		else return 0;
	}
	int speed()
	{
		return 200 / (diff + 1);
	}
	void eventListener()
	{
		char enterer;

		enterer = _getch();

		switch (enterer)
		{
		case 's': {if (menu.menu_id != 6) { menu.menu_id++; }; break; }
		case 'w': {if (menu.menu_id != 1) { menu.menu_id--; }; break; }
		case 13: {
			if (menu.menu_id == 2 && isGameOver==0) { menu.inGame = 1; system("cls"); break; }
			if (menu.menu_id == 1) { system("cls"); newGame(); menu.inGame = 1; break; }
			if (menu.menu_id == 3) { 
				system("cls");
				gotoxy(area.getx() +30, area.gety() + 10);
				int tempchar;
				cout << " Enter dificulty : ";
				cin >> tempchar;
				if (tempchar >=0 && tempchar <= 10)
					diff = tempchar;
				isGameOver = 1;
			}
			if (menu.menu_id == 4) {
				system("cls");
				while(!_kbhit())
				{ 
					gotoxy(area.getx() + 5, area.gety() + 1);
					cout << " High score list : " << endl;
					score_list.print();
					if (_kbhit())
						return;
				}
				
			}
			if (menu.menu_id == 5) {
				system("cls");
				while (1)
				{
					gotoxy(area.getx() + 5, area.gety() + 10);
					cout << "		CREDIT			";
					gotoxy(area.getx() + 5, area.gety() + 11);
					cout << "PHUNG THANH TU			19522455";
					gotoxy(area.getx() + 5, area.gety() + 12);
					cout << "LAM NGUYEN BUU DUY 		19521421";
					gotoxy(area.getx() + 5, area.gety() + 13);
					cout << "VO THOI DAI 			19521307";
					if (_kbhit())
					{
						break;
					}
				}
			}
			if (menu.menu_id == 6)
			{
				exit(0);
			}
		}
		}
	}
	void gameEventListener()
	{
		char enterer;
		if (_kbhit()) {
			enterer = _getch();

			switch (enterer)
			{
			case 'a': {snake.changedirection(3); break; }
			case 'd': {snake.changedirection(1); break; }
			case 'w': {snake.changedirection(4); break; }
			case 's': {snake.changedirection(2); break; }
			case 27: {menu.inGame = 0; break; }

			}
		}
	}
	void Renderer()
	{
		area.render();
		snake.render(area);
		food.render(area);
		gotoxy(area.getx(),area.gety()-1);
		cout << " score : " << score;
	}

	void LAUNCH_GAME()
	{
		while (1)
		{	
			setcursor(0, 0);
			while (menu.inGame == 0)
			{	
				system("cls");
				score_list.inputFile(input);
				score_list.outputfile(output);
				menu.render();
				eventListener();
			}
			while (menu.inGame == 1)
			{
				gameEventListener(); // bắt sự kiện phím
				snake.foward(); // di chuyển
				gameOver(); // đụng thân
				addScore(); // ăn
				Renderer(); // render


				Sleep(200 / diff+1);


				

			}
		}
	}
};




