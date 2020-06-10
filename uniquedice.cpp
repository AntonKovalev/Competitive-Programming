//============================================================================
// Name        : uniquedice.cpp
// Author      : Anton Kovalev
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>      // std::pair
using namespace std;

enum CUBEROTATION
{
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX
	};

struct Dice
{
	Dice(int top, int bottom, int front, int back, int left, int right)
	: m_top(top)
	, m_bottom(bottom)
	, m_front(front)
	, m_back(back)
	, m_left(left)
	, m_right(right)
	, one(top)
	, two(right)
	, three(front)
	, four(left)
	, five(back)
	, six(bottom)
	, m_current(ONE)
	{

	}

	bool compare(Dice dice)
	{
		return m_top == dice.getTop() && m_bottom == dice.getBottom() && m_front == dice.getFront() && m_back == dice.getBack() && m_left == dice.getLeft() && m_right == dice.getRight();
	}

	bool compareRotation(Dice dice)
	{
		return one == dice.getOne() && two == dice.getTwo() && three == dice.getThree() && four == dice.getFour() && five == dice.getFive() && six == dice.getSix();
	}

	int getTop()
	{
		return m_top;
	}
	int getBottom()
	{
		return m_bottom;
	}
	int getFront()
	{
		return m_front;
	}
	int getBack()
	{
		return m_back;
	}
	int getLeft()
	{
		return m_left;
	}
	int getRight()
	{
		return m_right;
	}

	int getOne()
	{
		return one;
	}
	int getTwo()
	{
		return two;
	}
	int getThree()
	{
		return three;
	}
	int getFour()
	{
		return four;
	}
	int getFive()
	{
		return five;
	}
	int getSix()
	{
		return six;
	}

	//! Rotates the cube one step on clockwise direction as seen from the top.
	void rotateClockWiseOneStep()
	{
		int right_temp = two;
		int front_temp = three;
		int left_temp = four;
		int back_temp = five;

		three = right_temp;
		four = front_temp;
		five = left_temp;
		two = back_temp;
	}

	void rotateWholeCube(CUBEROTATION rotation)
	{
		if(rotation == ONE)
		{
			m_current = ONE;

			one = m_top;
			two = m_right;
			three = m_front;
			four = m_left;
			five = m_back;
			six = m_bottom;
		}
		if(rotation == TWO)
		{
			m_current = TWO;

			six = m_top;
			four = m_right;
			three = m_front;
			two = m_left;
			five = m_back;
			one = m_bottom;
		}

		if(rotation == THREE)
		{
			m_current = THREE;

			four = m_top;
			five = m_right;
			one = m_front;
			three = m_left;
			six = m_back;
			two = m_bottom;
		}

		if(rotation == FOUR)
		{
			m_current = FOUR;

			three = m_top;
			two = m_right;
			six = m_front;
			four = m_left;
			one = m_back;
			five = m_bottom;
		}

		if(rotation == FIVE)
		{
			m_current = FIVE;

			four = m_top;
			one = m_right;
			three = m_front;
			six = m_left;
			five = m_back;
			two = m_bottom;
		}

		if(rotation == SIX)
		{
			m_current = SIX;

			two = m_top;
			six = m_right;
			three = m_front;
			one = m_left;
			five = m_back;
			four = m_bottom;
		}
	}

	CUBEROTATION getCurrentRotation()
	{
		return m_current;
	}

private:
	int m_top,m_bottom,m_front,m_back,m_left,m_right;

	// Original side numbers. Should never be changed.
	int one, two, three, four, five, six;

	CUBEROTATION m_current;

};

// Generates all 24 rotations for a given cube.
void generateAllRotations(Dice dice, vector<vector<int>>& rotations)
{
	vector<CUBEROTATION> cuberotations = {TWO,THREE,FOUR,FIVE,SIX,ONE};
	for(int i = 0; i < 6; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			vector<int> rotation1(6);
			rotation1[0] = dice.getOne();
			rotation1[1] = dice.getTwo();
			rotation1[2] = dice.getThree();
			rotation1[3] = dice.getFour();
			rotation1[4] = dice.getFive();
			rotation1[5] = dice.getSix();
			rotations.push_back(rotation1);
			dice.rotateClockWiseOneStep();

		}

		dice.rotateWholeCube(cuberotations[i]);
	}
	// Here, the dice should be in the same position as before this function was called.
}

string vectorToString(vector<int>& vec)
{
	string str;
	for(int i = 0; i < vec.size(); ++i)
	{
		str += vec[i] + 48; // 48 is due to ascii.
	}
	return str;
}


int main()
{
	int n;
	unordered_map<string, int> map;

	scanf ("%d",&n);
	for(int i = 0; i < n; ++i)
	{
		vector<vector<int>> rotationsOfACube;

		vector<int> d;
		for( int i = 0; i < 6; ++i)
		{
			int side;
			//cin >> side;
			scanf ("%d",&side);
			d.push_back(side);
		}

		Dice dice(d[0], d[1], d[2], d[3], d[4], d[5]);

		generateAllRotations(dice, rotationsOfACube);

		unordered_map<string, int> rotationsInThisSet;

		for(auto it = rotationsOfACube.begin(); it != rotationsOfACube.end(); ++it)
		{
			string rotation(vectorToString(*it));

			unordered_map<string,int>::iterator got = map.find( rotation );

			if ( got == map.end() )
			{
				map.insert( make_pair( rotation, 1 ) );

				rotationsInThisSet.insert( make_pair( rotation, 1 ) );
			}
			else
			{
				unordered_map<string,int>::iterator got2 = rotationsInThisSet.find( rotation );

				if(got2 == map.end()) // Means we have not seen this variation in this dice. Only possible if dice's side numbers are not unique.
				{
					got->second = got->second + 1;

					rotationsInThisSet.insert( make_pair( rotation, 1 ) );// Value does not matter.
				}
			}
		}
	}

	int maximum = 0;
	for (auto& it: map)
	{
		if(it.second > maximum)
		{
			maximum = it.second;
		}
	}
	printf("%d", maximum);
	//cout << maximum;

	return 0;
}
