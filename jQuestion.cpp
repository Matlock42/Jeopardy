/*
 * jQuestion.cpp
 *
 *  Created on: Jul 26, 2013
 *      Author: Ryan Sutton
 */

#include <iostream>
#include <string>		// std::string
#include <vector>		// std::vector
#include "jQuestion.h"

using namespace std;

Question::Question(std::string aCat, int aPrice, std::string aQuestion)
{
	this->mCategory = aCat;
	this->mPrice = aPrice;
	this->mQuestion = aQuestion;
	this->mPlayed = false;
	for(int i = 0; i < 4; i++)
		mAns[i] = "";
}

Question::~Question() {}

bool Question::addAnswer(int aPos, std::string aAns)
{
	if(aPos > 3 || aPos < 0)
		return false;
	if(this->mAns[aPos] != "")
		return false;
	this->mAns[aPos] = aAns;
	return true;
}

bool Question::hasBeenPlayed()
{
	return this->mPlayed;
}

bool Question::play(int aAns)
{
	mPlayed = true;
	return aAns == this->mCorrect;
}

std::string Question::category()
{
	return mCategory;
}

int Question::price()
{
	return mPrice;
}

int Question::askQuestion()
{
	cout << this->mQuestion;
	return 0;
}

int Question::showAnswers()
{
	int i;
	// There are 4 possible answers loop through them
	for (i = 0; i < 4; i++)
	{
		cout << (i+1) << ". " << this->mAns[i] << "\n";
	}
	return 0;
}

int Question::setCorrectAns(int a)
{
	this->mCorrect = a;
	return 0;
}
int Question::getCorrectAns()
{
	return this->mCorrect;
}