// warCardGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<queue>

using namespace std;
const int NUM_CARDS=52;
const int NUM_TRIALS=10000;
const int WAR_SIZE=2;

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));

	int numR[NUM_TRIALS];
	for(int i=0; i<NUM_TRIALS; i++)
		numR[i]=0;
	int Awins=0;
	int Bwins=0;

	for(int i=0; i<NUM_TRIALS; i++)
	{
		queue<int> handA;
		queue<int> handB;
		int deck[NUM_CARDS];
		for(int j=0; j<NUM_CARDS; j++)
			deck[j] = j/4;
//		deck[52]=13;
//		deck[53]=13;
		for(int j=0; j<NUM_CARDS; j++)
		{
			int ind = rand() % NUM_CARDS;
			int tmp = deck[j];
			deck[j]=deck[ind];
			deck[ind]=tmp;
		}
		for(int j=0;j<NUM_CARDS/2; j++)
			handA.push(deck[j]);
		for(int j=NUM_CARDS/2;j<NUM_CARDS; j++)
			handB.push(deck[j]);

		//cards are dealt, now play the game
		int numRounds=0;
		while(handA.size()>0 && handB.size()>0)
		{
			int cardA = handA.front();
			handA.pop();
			int cardB = handB.front();
			handB.pop();
			if(cardA > cardB)
			{
				handA.push(cardA);
				handA.push(cardB);
			}
			if(cardB > cardA)
			{
				handB.push(cardB);
				handB.push(cardA);
			}
			if(cardB == cardA && handA.size()>0 && handB.size()>0)
			{
				//WAR!!!
				queue<int> prize;
				prize.push(cardA);
				prize.push(cardB);
				while(cardB == cardA && handA.size()>0 && handB.size()>0)
				{
					int w = WAR_SIZE;
					if(handA.size() < w+1)
						w=handA.size()-1;
					if(handB.size() < w+1)
						w=handB.size()-1;
					int bb=handB.size();
					int aa=handA.size();
					for(int j=0; j<w; j++)
					{
						prize.push(handA.front());
						handA.pop();
						prize.push(handB.front());
						handB.pop();
					}
					cardA = handA.front();
					handA.pop();
					prize.push(cardA);
					cardB = handB.front();
					handB.pop();
					prize.push(cardB);
				}
				if(cardA > cardB)
					while(prize.size()>0)
					{
						handA.push(prize.front());
						prize.pop();
					}
				if(cardA < cardB)
					while(prize.size()>0)
					{
						handB.push(prize.front());
						prize.pop();
					}

			}
			numRounds++;
		}
		if(handA.size()>0)
			Awins++;
		if(handB.size()>0)
			Bwins++;
		numR[i]=numRounds;
		cout << numRounds << endl;
	}
	cout << Awins << " " << Bwins << endl;
	int totRounds = 0;
	for(int i=0; i<NUM_TRIALS; i++)
	{
		totRounds += numR[i];
		cout << numR[i] << endl;
	}
	cout << totRounds/(1.0*NUM_TRIALS) << endl;
	int a;
	cin >> a;
	return 0;
}

