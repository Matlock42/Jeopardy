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
		int updateStatus(void);

	private:
		int loadQuestions(void);	// load questions from xml files in ./Data
		bool showQuestion(int prompt);	// display the question and answer prompt
		int clearScreen(void);		// clear the screen of text
		std::vector<std::string> findXML( const char *path ); // return vector of all .xml files in the given directory
		bool mPlaying;				// True-game goes on; False-No more questions
		int mScore;					// Current score
		int mSize;					// size of the game board
	    Question***  mQuestionSet; 	// 5x5 board size
};

#endif
