/*
 * jQuestion.h
 *
 *  Created on: Jul 26, 2013
 *      Author: Ryan Sutton
 */

#ifndef JQUESTION_H_
#define JQUESTION_H_


class Question {

	public:
		Question(std::string, int, std::string);
		~Question();
		bool addAnswer(int, std::string);
		bool hasBeenPlayed(void);
		std::string category(void);
		int getCorrectAns(void);
		int price(void);
		bool play(int);
		int setCorrectAns(int);
		int askQuestion(void);
		int showAnswers(void);

	private:
		std::string mCategory;// stores category name
		int mPrice;	// price of the question
		std::string mQuestion;// stores the question to be displayed
		std::string mAns[4];	// stores the answers
		int mCorrect;	// stores number of correct answer
		bool mPlayed;	// whether this has been played or not
	};

#endif /* JQUESTION_H_ */
