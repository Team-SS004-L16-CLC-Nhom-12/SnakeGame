#include <iostream>
#include "mylib.h"
#define MAX 100
using namespace std;
//-------------- khoi tao bien toan cuc ---------
int toado_x[MAX];
int toado_y[MAX];
int sl = 4;// ban đầu có 4 đốt
int toado_xcu[MAX];
int toado_ycu[MAX];
int xqua;
int yqua;
void game();
void ve_tuong();
void ve_ran();
void khoi_tao_ran();
void them(int x, int y);
void xoa();
void khoi_tao_toa_do_cu();
void cap_nhat_du_lieu_cu();
void xoa_du_lieu_cu();
void tao_qua();
bool gameover();
//======================
int main()
{
	srand(time(NULL));
	ShowCur(0);
	game();
	_getch();
	return 0;
}
void game()
{
	//--------- khoi tao --------
	ve_tuong();
	khoi_tao_ran(); //có vị trí ban đầu của rắn
	tao_qua();
	int x = 50, y = 13;// vị trí hiện tại của đầu rắn
	int check = 2;// 0:	đi xuống
					// 1: đi lên
					//	2:	đi qua phải
					// 3: đi qua trái
	//------- xu ly game ----------
	while (true)
	{
		//---------- B1: xoa du lieu cu ----------
		/*system("cls");
		ve_tuong();*/
		xoa_du_lieu_cu();
		cap_nhat_du_lieu_cu();
		//--------- B2: ve ran -----------
		ve_ran();
		//------------- bắt game over ------------
		if (gameover() == true)
		{
			break;
		}
		//--------- B3: điều khiển để chính hướng rắn di chuyển ----------
		if (_kbhit() == true) //  72
		{
			char c = _getch();// lấy dữ liệu bộ nhớ đệm và trả cho c
			if (c == -32)
			{
				c = _getch();
				if (c == 72 && check != 0)
				{
					check = 1;
				}
				else if (c == 80 && check!=1)
				{
					check = 0;
				}
				else if (c == 75 && check != 2)
				{
					check = 3;
				}
				else if (c == 77 && check != 3)
				{
					check = 2;
				}
			}
		}
		//---------------B4: dựa vào hướng để xử lý di chuyển -------------
		if (check == 0)
		{
			y++;
		}
		else if (check == 1)
		{
			y--;
		}
		else if (check == 2)
		{
			x++;
		}
		else if (check == 3)
		{
			x--;
		}
		them(x, y);
		if (toado_x[0] == xqua && toado_y[0] == yqua)//kh rắn ăn quả
		{
			//B1: không xóa đuôi
			//B2: tao quả mới
			tao_qua();
		}
		else
		{
			xoa();
		}
		Sleep(100);
	}
}
void ve_tuong()
{
	SetColor(11);
	for (int x = 5;x <= 100;x++)
	{
		gotoXY(x, 1);
		cout << "+";
		gotoXY(x, 27);
		cout << "+";
	}
	for (int y = 1;y <= 27;y++)
	{
		gotoXY(5, y);
		cout << "+";
		gotoXY(100, y);
		cout << "+";
	}

}
void khoi_tao_ran()	// để có tọa độ ban đầu của rắn
{
	int x = 50, y = 13;// toạ độ của đầu rắn
	for (int i = 0;i < sl;i++)//i ++ là qua đốt sau
	{
		toado_x[i] = x;
		toado_y[i] = y;
		x--;// 48
	}
}
void ve_ran()
{
	for (int i = 0;i < sl;i++)
	{
		if (i == 0)
		{
			gotoXY(toado_x[i], toado_y[i]);
			cout << "0";
		}
		else
		{
			gotoXY(toado_x[i], toado_y[i]);
			cout << "o";
		}
	}
}
void them(int x,int y)
{
	//dời		sl = 5
	//	51 50 49 48 47
	//	13 13 13 13 13
	for (int i = sl;i > 0;i--)
	{
		toado_x[i] = toado_x[i - 1];
		toado_y[i] = toado_y[i - 1];
	}
	//chèn
	toado_x[0] = x;
	toado_y[0] = y;
	sl++;
}
void xoa()
{
	//dời		sl = 4
	//	51 50 49 48 47
	//	13 13 13 13 13
	sl--;
}
void khoi_tao_toa_do_cu()
{
	for (int i = 0;i < sl;i++)
	{
		toado_xcu[i] = toado_x[i];
		toado_ycu[i] = toado_y[i];
	}
}
void cap_nhat_du_lieu_cu()
{
	for (int i = 0;i < sl;i++)
	{
		toado_xcu[i] = toado_x[i];
		toado_ycu[i] = toado_y[i];
	}
}
void xoa_du_lieu_cu()
{
	for (int i = 0;i < sl;i++)
	{
		gotoXY(toado_xcu[i], toado_ycu[i]);
		cout << " ";
	}
}
void tao_qua()
{
	//----- random ra vi tri qua ---------
	xqua = rand() % (99 - 6 + 1)+ 6;// [6-99]
	yqua = rand()%(26-2+1)+2;//[2-26]
	//----------- ve qua --------
	gotoXY(xqua, yqua);
	cout << "$";
}
bool gameover()
{
	//nếu rắn chạm tường
	if (toado_x[0] == 5 || toado_x[0] == 100, toado_y[0] == 1, toado_y[0] == 27)
	{
		return true;
	}
	//rắn cắn đuôi
	for (int i = 1;i < sl;i++)//xét mình rắn
	{
		//lấy tọa độ đầu kiểm tra nếu trùng là cắn thân
		if (toado_x[0] == toado_x[i] && toado_y[0] == toado_y[i])
		{
			return true;
		}
	}
}