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

<<<<<<< HEAD
#define gameSize 1	// set to 1 for debuging purposes
=======
#define gameSize 1  // set to 1 for debuging purposes
>>>>>>> 89e39b31ecef3062167e915917601bc0e0e76053
//#define gameSize 5

class game
{
	public:
		int playing;
		game();
		~game();
		int showBoard(void);
		int showScore(void);
	private:
		int loadQuestions(void);
		int showQuestion(int prompt);
		int clearScreen(void);
		int score;
	struct questionSet {
			string category;// stores category name
			int price;	// price of the question
			string question;// stores the question to be displayed
			string a,b,c,d;	// stores the answers
			int correct;	// strores number of correct answer
			int played;	// whether this has been played or not
		} questionSet[gameSize][gameSize]; 	// 5x5 board size
};

#endif
