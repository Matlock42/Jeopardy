/*
 * jQuestion.cpp
 *
 *  Created on: Jul 26, 2013
 *      Author: Ryan Sutton
 */

#include <string>
#include "jQuestion.h"

Question::Question(std::string aCat, int aPrice, std::string aQuestion, int aCorrectAns)
{
	this->mCategory = aCat;
	this->mPrice = aPrice;
	this->mCorrect = aCorrectAns;
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
