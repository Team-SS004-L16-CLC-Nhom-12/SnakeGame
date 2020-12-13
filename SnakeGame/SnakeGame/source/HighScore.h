#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include"Additional_function.h"
using namespace std;
class HighScore
{
public:
	char name[50];
	int score;
	HighScore() { strcpy_s(name, ""); score = 0; }
	~HighScore() {}
	void inputFile(ifstream& inputfile)
	{
		inputfile.open("score.txt");
		inputfile >> name >> score;
		inputfile.close();

	}
	void set(const char name[], int score)
	{
		strcpy_s(this->name, name);
		this->score = score;
	}
	void outputfile(ofstream& outputfile)
	{
		outputfile.open("score.txt");
		outputfile << name << " " << score;
		outputfile.close();
	}
	void print()
	{
		cout << "name :" << name << " and  score :" << score;
	}
};

class HighScoreList
{
	int amount;
	vector<HighScore> list;
public:
	HighScoreList() { amount = 3; }
	~HighScoreList() {}
	void inputFile(ifstream& inputfile)
	{
		inputfile.open("score.txt");
		for (int i = 0; i < amount; i++)
		{
			char name[50];
			int score;
			inputfile >> name >> score;
			if (strlen(name) != 0 || score != 0)
			{
				HighScore temp;
				temp.set(name, score);
				list.push_back(temp);
			}
		}
		inputfile.close();
	}
	void outputfile(ofstream& outputfile)
	{
		outputfile.open("score.txt");
		for (int i = 0; i < amount; i++)
		{
			outputfile << list.at(i).name << " " << list.at(i).score << "\n";
		}
		outputfile.close();
	}
	void newhighscore(char name[], int score) {
		for (int i = 0; i < amount; i++)
		{
			if (score > list.at(i).score)
			{
				for (int j = i; j < amount - 1; j++)
				{
					strcpy_s(list.at(i + 1).name, list.at(i).name);
					list.at(i + 1).score = list.at(i).score;
				}
				strcpy_s(list.at(i).name, name);
				list.at(i).score = score;

				return;
			}
		}
	}
	void print()
	{
		for (int i = 0; i < amount; i++)
		{
			if (strlen(list.at(i).name) != 0)
			{
				gotoxy(20 + 5, 5 + 11+i);
				cout << i + 1 << ". Name  : " << list.at(i).name;

				gotoxy(20 + 5+40, 5 + 11 + i);
				cout << "Score : " << list.at(i).score << endl;
			}

		}
		gotoxy(20 + 5, 5 + 11 + amount);
		cout << " Press any key but not enter to continue.";
	}
};
