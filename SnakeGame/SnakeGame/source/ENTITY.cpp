#include "ENTITY.h"
#include"Additional_function.h"
#include"GameMechanism.h"
void play_ground::change_coord(int x, int y)
{
	this->x = x;
	this->y = y;
}
void play_ground::render()// hien thi khung tro choi
{
	
	change_color(12);
	for (int i = x + 1; i <= x+79; i++)// canh tren va duoi
	{	
		gotoxy(i, y);
		cout << char(205);
		gotoxy(i, y + 25);
		cout << char(205);
	}
	for (int i = y + 1; i <= y + 24; i++)// canh ben trai va phai
	{
		gotoxy(x, i);
		cout << char(186);
		gotoxy(x+80,i);
		cout << char(186);
	}
	gotoxy(x, y); // goc trai tren
	cout << char(201);
	gotoxy(x + 80, y);// goc phai tren
	cout << char(187);
	gotoxy(x, y + 25);// goc trai duoi
	cout << char(200);
	gotoxy(x + 80, y + 25);// goc phai duoi
	cout << char(188);

}
void play_ground::game_over() {
	gotoxy(x + 40, y + 12);
		cout << "GAME OVER";
}


void SnakeHead::changedirection(int i)// thay doi huong di cua dau ran
{	
	direction0 = direction;
	switch (direction) // con ran khong the di nguoc lai
	{
	case 1 :
	{
		if (i != 3)
			direction = i;
		break;
	}
	case 2:
	{
		if (i != 4)
			direction = i;
		break;
	}
	case 3:
	{
		if (i != 1)
			direction = i;
		break;
	}
	case 4:
	{
		if (i != 2)
			direction = i;
		break;
	}
	}
}
void SnakeHead::render()// render dau con ran
{
	gotoxy(this->x, this->y);
	gotoxy(x0, y0);
	cout << " ";
	cout << char(153);
	
}
void SnakeHead::render(play_ground area)//render dau ran trong khung tro choi
{	
	

	gotoxy(area.x + x, area.y + y);
	cout << char(153);

	gotoxy(area.x + x0, area.y + y0);
	cout << " ";

}
void SnakeHead::foward()// di chuyen con ran toi truoc
{	
	direction0 = direction;
	x0 = x;
	y0 = y;

	switch (direction)// tuy huong di cua con ran ma chinh toa do cho phu hop
	{
	
	case 1: {
		
		
			if (x == 79)
				x = 1;
			else x = x + 1;
		
		break;
	}
	case 2: {
	
		
			if (y == 24)
				y = 1;
			else y++;
		
		
		break; }
	case 4: {
		if (y == 1)
			y = 24;
		  else y--;
		break; }
	case 3: {if (x == 1)
		x = 79;
		  else x--;
		break; }
	
	}

	

}



void SnakeBody::foward() // loi than ran di theo dau ran hoac dot ran truoc do
{
	direction0 = direction;
	x0 = x;
	y0 = y;
}
void SnakeBody::render()// render
{	
	gotoxy(x0, y0);
	cout << " ";
	gotoxy(x, y);
	if (direction == 1 || direction == 4)
		cout << char(220);
	else
	
		cout << char(233);
}
void SnakeBody::render(play_ground area)// render trong playground
{
	gotoxy(area.x + x0, area.y + y0);
	cout << " ";

	gotoxy(area.x + x, area.y + y); 
	cout << char(178);
}




void Snake::render()
{
	Head.render();
	for (int i = 0; i < length; i++)
		Body[i].render();
}
void Snake::render(play_ground area)
{	
	change_color(14);
	Head.render(area);
	for (int i = 0; i < length; i++)
	{
		Body.at(i).render(area);
	}
	change_color(15);
}
void Snake::foward() // di chuyen ca con ran di toi truoc
{	
	Head.foward();
	for (int i=0; i < length; i++)
	{
		if (i ==0)
		{	
			
			Body.at(i).foward();
			Body.at(i).setcoord(Head.getx0(), Head.gety0());
			Body.at(i).direction = Head.direction0;
		}
		else
		{	
			Body.at(i).foward();
			Body.at(i).setcoord(Body.at(i - 1).getX0(), Body.at(i - 1).getY0());
			Body.at(i).direction = Body.at(i - 1).direction0;
		}
	}
}
void Snake::changedirection(int i) // thay doi huong di cua ran
{
	this->Head.changedirection(i);
}
void Snake::push()// tang chieu dai cho ran
{
	
	SnakeBody newpart;
	newpart.setcoord(Body.at(int(length - 1)).getX0(), Body.at(int(length - 1)).getY0());
	Body.push_back(newpart);
	length++;
}
bool Snake::checkspawn(int x, int y)
{
	if (this->Head.x == x && this->Head.y == y)
		return 1;

	for (int i = 0; i < this->length; i++)
	{
		if (this->Body.at(i).x == x && this->Body.at(i).y == y)
			return 1;
	}
	return 0;
}
bool Snake::checkCollision(int x, int y)
{
	for (int i = 0; i < length; i++)
	{
		if (Body.at(i).x == x && Body.at(i).y == y)
			return 1;
	}
	return 0;
}

bool Food::beEaten(Snake head) // kiem tra thuc an co bi an chua
{
	return this->x == head.Head.x && this->y == head.Head.y;
}
void Food::render()
{
	gotoxy(x,y);
	cout << "x";
}
void Food::render(play_ground area)
{	
	change_color(9);
	gotoxy(area.x+x, area.y+y);
	cout << char(167);
	change_color(15);
}
void Food::disapear(play_ground area)// thuc an bien mat ( khi het thoi gian hoac khi bi con ran an
{
	gotoxy(area.x + x, area.y + y);
	cout << " ";
}