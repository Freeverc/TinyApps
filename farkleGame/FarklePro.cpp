// farkleGame
// 2019.5.20
//

#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>

using namespace std;

class Player
{
public:
	string playerName = "  Player ";
	bool instantWin = false;
	bool isComputer = false;
	char type = 'e';
	int minPoints = 0;
	bool roundFlag = false;
	int playerFlag =0;
	int scoreAll = 0;
	int scoreTurn = 0;
	int scoreNow = 0;
	int pointList1[6] = { 100,0,0,0,50,0 };
	int pointList2[6] = { 1000,200,300,400,500,600 };

	int diceValues[6] = { 0 };
	bool diceChosen[6];
	bool diceChoiceNow[6];

	bool farkleFlag;
	int farkleTime = 0;

	void rollDices()
	{
		srand(time(0)+rand());
		for (int i = 0; i < 6; i++)
		{
			if (diceChosen[i] == false)
			{
				diceValues[i] = rand() % 6 + 1;
			}
		}
	}

	void printValues()
	{
		cout << endl;
		cout << "    ";
		for (int i = 0; i < 6; i++)
		{
			if (diceChosen[i] == false)
				cout << " [" << diceValues[i] << "] ";
			else
				cout << " [" << "x" << "] ";
		}
		cout << endl;
		cout << "    ";
		for (int i = 0; i < 6; i++)
		{
			cout << "  " << i + 1 << "  ";
		}
		cout << endl;
		cout << endl;
	}

	void printValuesAsc()
	{
		cout << endl;
		cout << "    ";
		for (int i = 0; i < 6; i++)
		{
			if (diceChosen[i] == false)
			{
				char c = 7;
				string s;
				switch (diceValues[i])
				{
				case 1:
					s = " · ";
					break;
				case 2:
					s = " :  ";
					break;
				case 3:
					s = " … ";
					break;
				case 4:
					s = " :: ";
					break;
				case 5:
					s = ":·:";
					break;
				case 6:
					s = "::: ";

					break;
				}
				cout << "  " << s << "  ";
			}
			else
				cout << "  " << " x  " << "  ";
		}
		cout << endl;
		cout << endl;
		cout << "    ";
		for (int i = 0; i < 6; i++)
		{
			cout << "   " << i + 1 << "    ";
		}
		cout << endl;
		cout << endl;
	}
	
	void getScore()
	{
		int tripleFlag = 0;
		int doubleFlag = 0;
		int diceFreq[6] = { 0 };
		int pointFreq[7] = { 0 };
		for (int i = 0; i < 6; i++)
		{
			if (diceChoiceNow[i] == true)
			{
				diceFreq[diceValues[i] - 1]++;
			}
		}
		for (int i = 0; i < 6; i++)
		{
			pointFreq[diceFreq[i]]++;
		}
		if (pointFreq[6] == 1)
			instantWin = true;
		else if (pointFreq[3] == 2)
			scoreNow += 2000;
		else if (pointFreq[1] == 6)
			scoreNow += 1500;
		else if (pointFreq[2] == 3)
			scoreNow += 1000;
		else
		{
			for (int i = 0; i < 6; i++)
			{
				if (diceFreq[i] == 5)
					scoreNow += 3 * pointList2[i];
				else if (diceFreq[i] == 4)
					scoreNow += 2 * pointList2[i];
				else if (diceFreq[i] == 3)
					scoreNow += pointList2[i];
				else
				{
					scoreNow += diceFreq[i] * pointList1[i];
				}
			}
		}
	}
	
	void exeTurn()
	{
		// Initialize
		for (int i = 0; i < 6; i++)
		{
			diceChosen[i] = { false };
			diceValues[i] = { 0 };
		}
		scoreTurn = 0;
		farkleFlag = false;
		while (true)
		{
			if (scoreTurn >= minPoints)
			{
				cout << "Your score in this turn(" << scoreTurn << ") is over the minimum points(" << minPoints << ")~" << endl;
				cout << "Do you want to [q]uit [r]oll or [s]core:";
			}
			else
			{
				cout << "Your score in this turn(" << scoreTurn << ") is under minimum points(" << minPoints << ")!" << endl;
				cout << "Do you want to[q]uit or [r]oll:";
			}
			char c;
			cin >> c;
			if (c == 'q')
			{
				break;
			}
			else if ((scoreTurn >= minPoints) && (c == 's'))
			{
				scoreAll += scoreTurn;
				break;
			}
			else if (c == 'r')
			{
				rollDices();
				printValuesAsc();
				scoreNow = 0;
				for (int i = 0; i < 6; i++)
				{
					diceChoiceNow[i] = !diceChosen[i];
				}
				getScore();
				if (scoreNow == 0)
				{
					farkleFlag = true;
					farkleTime++;
					if (farkleTime == 3)
					{
						cout << "Opps,you have farkled three consecutive times, " << playerName << playerFlag << endl;
						cout << "You will lose 1000 points!" << endl;
						scoreAll -= 1000;
						if (scoreAll < 0)
							scoreAll = 0;
					}
					scoreTurn = 0;
					cout << "Opps,you have farkled, " << playerName << playerFlag << endl;
					break;
				}
				cout << "Please input the dice using the number under \nthe die,do not include spaces" << endl << endl;
				cout << "The dice you want are:";
				int choisenNum;
				cin >> choisenNum;
				for (int i = 0; i < 6; i++)
				{
					diceChoiceNow[i] = false;
				}
				while (choisenNum != 0) {
					int n = choisenNum % 10 - 1;
					if ((n < 6) && (n >= 0))
					{
						diceChosen[choisenNum % 10 - 1] = true;
						diceChoiceNow[choisenNum % 10 - 1] = true;
					}
					choisenNum /= 10;
				}
				scoreNow = 0;
				getScore();
				while (scoreNow == 0)
				{
					cout << endl << "Please enter only scoring values" << endl;
					cout << "The dice you want are:";
					int choisenNum;
					cin >> choisenNum;
					for (int i = 0; i < 6; i++)
					{
						diceChoiceNow[i] = false;
					}
					while (choisenNum != 0) {
						int n = choisenNum % 10 - 1;
						if ((n < 6) && (n >= 0))
						{
							diceChosen[choisenNum % 10 - 1] = true;
							diceChoiceNow[choisenNum % 10 - 1] = true;
						}
						choisenNum /= 10;
					}
					scoreNow = 0;
					getScore();
				}
				scoreTurn += scoreNow;
			}
			else
			{
				continue;
			}
		}
	}

	char dc1;
	int dc2;
	
	void initialCpu()
	{
		playerName = "Computer ";
		isComputer = true;
	}
	
	void makeDecision1()
	{
		if (type == 'a')
		{
			int m = 0;
			for (int i = 0; i < 6; i++)
			{
				if (diceChosen[i] == false)
					m++;
			}
			if ((scoreTurn >= minPoints)&&(m<=1))
				dc1 = 's';
			else
				dc1 = 'r';
		}
		else if (type == 'c')
		{
			if (scoreTurn >= minPoints)
				dc1 = 's';
			else
				dc1 = 'r';
		}
		else
		{
			if (scoreTurn >= minPoints)
				dc1 = 's';
			else
				dc1 = 'r';
		}
	}
	
	void makeDecision2()
	{
		dc2 = 0;
		if (type == 'a')
		{
			for (int i = 0; i < 6; i++)
			{
				if ((diceChosen[i] == false) && ((diceValues[i] == 5) || (diceValues[i] == 1)))
					dc2 = dc2 * 10 + i + 1;
			}
			if (dc2 == 0)
				dc2 == 123456;
		}
		else if (type == 'c')
		{
			dc2 = 123456;
		}
		else
		{
			for (int i = 0; i < 6; i++)
			{
				if ((diceChosen[i] == false) && ((diceValues[i] == 5) || (diceValues[i] == 1)))
					dc2 = dc2 * 10 + i + 1;
			}
			if (dc2 == 0)
				dc2 == 123456;
		}
	}
	
	void exeTurnCpu()
	{
		// Initialize
		for (int i = 0; i < 6; i++)
		{
			diceChosen[i] = { false };
			diceValues[i] = { 0 };
		}
		scoreTurn = 0;
		farkleFlag = false;
		while (true)
		{
			if (scoreTurn >= minPoints)
			{
				cout << "Your score in this turn(" << scoreTurn << ") is over the minimum points(" << minPoints << ")~" << endl;
				cout << "Do you want to [q]uit [r]oll or [s]core:";
			}
			else
			{
				cout << "Your score in this turn(" << scoreTurn << ") is under minimum points(" << minPoints << ")!" << endl;
				cout << "Do you want to[q]uit or [r]oll:";
			}
			char c;
			makeDecision1();
			c = dc1;
			cout << c << endl;
			if (c == 'q')
			{
				break;
			}
			else if ((scoreTurn >= minPoints) && (c == 's'))
			{
				scoreAll += scoreTurn;
				break;
			}
			else if (c == 'r')
			{
				rollDices();
				printValuesAsc();
				scoreNow = 0;
				for (int i = 0; i < 6; i++)
				{
					diceChoiceNow[i] = !diceChosen[i];
				}
				getScore();
				if (scoreNow == 0)
				{
					farkleFlag = true;
					farkleTime++;
					if (farkleTime == 3)
					{
						cout << "Opps,you have farkled three consecutive times, " << playerName << playerFlag << endl;
						cout << "You will lose 1000 points!" << endl;
						scoreAll -= 1000;
						if (scoreAll < 0)
							scoreAll = 0;
						farkleTime = 0;
					}
					scoreTurn = 0;
					cout << "Opps,you have farkled, " << playerName << playerFlag << endl;
					break;
				}
				cout << "Please input the dice using the number under \nthe die,do not include spaces" << endl << endl;
				cout << "The dice you want are:";
				int choisenNum;
				makeDecision2();
				choisenNum = dc2;
				cout << choisenNum << endl;
				for (int i = 0; i < 6; i++)
				{
					diceChoiceNow[i] = false;
				}
				while (choisenNum != 0) {
					int n = choisenNum % 10 - 1;
					if ((n < 6) && (n >= 0))
					{
						diceChosen[choisenNum % 10 - 1] = true;
						diceChoiceNow[choisenNum % 10 - 1] = true;
					}
					choisenNum /= 10;
				}
				scoreNow = 0;
				getScore();
				while (scoreNow == 0)
				{
					cout << endl << "Please enter only scoring values" << endl;
					cout << "The dice you want are:";
					int choisenNum;
					makeDecision2();
					choisenNum = dc2;
					for (int i = 0; i < 6; i++)
					{
						diceChoiceNow[i] = false;
					}
					while (choisenNum != 0) {
						int n = choisenNum % 10 - 1;
						if ((n < 6) && (n >= 0))
						{
							diceChosen[choisenNum % 10 - 1] = true;
							diceChoiceNow[choisenNum % 10 - 1] = true;
						}
						choisenNum /= 10;
					}
					scoreNow = 0;
					getScore();
				}
				scoreTurn += scoreNow;
			}
			else
			{
				continue;
			}
		}
	}
};

int main()
{
	cout << "******************************************************************************" << endl;
	cout << "                     FARKLE:a dice game for 1-4 players                       " << endl;
	cout << "******************************************************************************" << endl;
	cout << endl;

	bool instantOver = false;
	bool continueFlag = true;
	char computerFlag = 'n';
	int playerNum = 2;
	int maxScoreTurn = 0;
	int winnerTurn = 0;
	int targetScore = 1000;
	int inputMinPoints = 0;
	int turnNum = 0;
	cout << "Please input player numbers(1-4, without computer):";
	cin >> playerNum;
	Player players[5];
	cout << "Do you want to play with a computer?[y]es or [n]o: ";
	cin >> computerFlag;
	if (computerFlag == 'y')
	{
		players[playerNum].initialCpu();
		cout << "Please choose computer type [e]asy player, [c]autious player, or [a]ggressive player: ";
		char c;
		cin >> c;
		players[playerNum].type = c;
		playerNum++;
	}
	cout << "Please input the target score(5000, 10000 or 15000):";
	cin >> targetScore;
	cout << "Please input the minimum points required to roll before saving points(350,500,750 or 1000): ";
	cin >> inputMinPoints;
	cout << endl;

	
	
	while ((maxScoreTurn < targetScore) || (continueFlag))
	{
		if ((maxScoreTurn >= targetScore))
		{
			continueFlag = false;
			if(playerNum == 1)
				break;
		}
		turnNum++;
		cout << "******************************************************************************" << endl;
		cout << "Turn " << turnNum << endl;
		for (int i = 0; i < playerNum; i++)
		{
			players[i].playerFlag = i + 1;
			players[i].minPoints = inputMinPoints;
			cout << players[i].playerName << i + 1 << " Score: " << players[i].scoreAll;
			if ((continueFlag == false) && (i + 1 == winnerTurn))
			{
				cout << "  (The winner at present)" ;
			}
			cout << endl;
		}

		for (int i = 0; i < playerNum; i++)
		{
			if ((continueFlag == false) && (i == winnerTurn - 1))
				continue;
			//cout << endl;
			cout << "***************************************************************" << endl;
			cout << "It's your turn, "<< players[i].playerName << i + 1 << ":" << endl;
			if (players[i].isComputer)
				players[i].exeTurnCpu();
			else
				players[i].exeTurn();

			if (players[i].instantWin)
			{
				winnerTurn = i + 1;
				instantOver = true;
				break;
			}
		}
		
		if (instantOver)
			break;
		for (int i = 0; i < playerNum; i++)
		{
			if (maxScoreTurn < players[i].scoreAll)
			{
				maxScoreTurn = players[i].scoreAll;
				winnerTurn = i + 1;
			}
		}
	}

	turnNum++;
	cout << endl;
	cout << "******************************************************************************" << endl;
	cout << "Result list: " << endl;

	for (int i = 0; i < playerNum; i++)
	{
		cout << players[i].playerName << i + 1 << " Score: " << players[i].scoreAll<<endl;
	}
	cout << "******************************************************************************" << endl;
	cout << endl;
	cout << endl;

	cout << "------------------------------------------------------------------------------" << endl;
	cout << "                The winner is: "<< players[winnerTurn - 1].playerName << winnerTurn << ",  Score: " << players[winnerTurn - 1].scoreAll << endl;
	cout << "------------------------------------------------------------------------------" << endl;
	return 0;
}