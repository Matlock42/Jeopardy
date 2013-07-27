/**********************************
* Jeopardy Game v. 3.0
* 
* Complete rewrite of version 2.0

  @author:      Joel Cranmer <42.joel.cranmer@gmail.com>
  @created:     2013/06/23
  @modified:    
  @version:     3

*
**********************************/
#ifndef jgame_H
#define jgame_H

class Question;

class Game
{
	public:
		bool playing(void);
		Game(int);
		~Game();
		int showBoard(void);
		int showScore(void);

	private:
		int loadQuestions(void);
		int showQuestion(int prompt);
		int clearScreen(void);
		bool mPlaying;
		int mScore;
		int mSize;
	    Question***  mQuestionSet; 	// 5x5 board size
};

#endif
