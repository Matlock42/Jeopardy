all: jgame

debug: jgamedebug

jgamedebug:
	g++  jgame.cpp jgameClass.cpp jQuestion.cpp -o jgame -g

jgame: 
	g++ jgame.cpp jgameClass.cpp jQuestion.cpp -o jgame

clean:
	rm -rf *o jgame
