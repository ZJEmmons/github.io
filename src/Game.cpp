/**
* Author: Zachary Emmons 040959178
* Course Code: CST8219
* Section: 303
* Project: Final Project
* Description: This source file defines the functions and
*			   constructors declared in Game header.
*/

/* INCLUDES */

#include "Game.h"

/* NAMESPACES */

using namespace FinalProject;

/* CONSTRUCTORS */

Game::Game() {
	pairsOnTable = SYMBOL_TTL;
	clickCount = INT_DEFAULT;
	highScore = INT_DEFAULT;
	lastFlipCard = NULL;
}//default constructor

Game::~Game() {}//destructor

/* FUNCTIONS */

void Game::incrementClick() {
	clickCount += 1;
}//increment clickCount variable

void Game::decrementPairs() {
	pairsOnTable -= 1;
}//decrement pairsOnTable variable

int Game::getClickCount() {
	return clickCount;
}//return value of ClickCount variable

int Game::getPairsLeft() {
	return pairsOnTable;
}//return value of pairsOnTable variable

int Game::getHighScore() {
	return highScore;
}//return value of highScore variable

/**
* Function: initializeHighScore
* Param-in: none
* Param-out: none
* Purpose: reads file for saved high score values
*/

void Game::initializeHighScore() {

	//string object stores content in file line
	string line;
	//input stream reads file content
	ifstream scoreRead;
	scoreRead.open("score.txt");

	//check for existing file to open
	if (scoreRead.is_open()) {
		//read each file line
		while ( getline(scoreRead,line) ) {
			//convert string content to integer and store
			highScore = stoi(line);
		}
	}
	//if no file found
	else {
		//set high score to zero
		highScore = INT_DEFAULT;
	}

	//close input stream for memory leak
	scoreRead.close();

}

/**
* Function: flipCard
* Param-in:  Card* card - pointer to Card object to compare or store
*		     Image* imgs - pointer to Image object for changing card display
*			 timer* delay - timer to start search for elapsed events, and restrict
*							button click timing
* Param-out: int - the result of card symbol comparison
* Purpose: stores pointer to flipped cards and compares their
*		   symbols to determine their final game state. also
*		   increments score.
*/

int Game::flipCard(Card* card, Image* imgs, timer* delay) {

	//check for timer running and prevents actions
	if (!delay->started() || lastFlipCard) {
		//check if card is in state to flip
		if (card->getState() == FACE_DOWN) {

			//increment score
			incrementClick();
			//flip card face up
			card->changeState(FACE_UP);

			//check if other card is NOT face up
			if (!lastFlipCard) {
				//store pointer to face up card
				lastFlipCard = card;
				//update image to display
				card->getButton()->icon(imgs->getImage(card->getSymbol()));
				//start timer events
				delay->start();
				//return no action to take
				return NO_RESULT;
			}
			else {
				if (lastFlipCard->getSymbol() == card->getSymbol()) {
					//set face up cards to out of game
					lastFlipCard->changeState(OFF_BOARD);
					card->changeState(OFF_BOARD);
					//updates images to display
					card->getButton()->icon(imgs->getImage(card->getSymbol()));
					lastFlipCard->getButton()->icon(imgs->getImage(lastFlipCard->getSymbol()));
					//reset last flipped card pointer
					lastFlipCard = NULL;
					//decrement pairs in play
					decrementPairs();
					//start timer for events
					delay->start();
					//return actions for equal result
					return EQUAL_RESULT;
				}
				else {
					//set face up cards to face down
					card->changeState(FACE_DOWN);
					lastFlipCard->changeState(FACE_DOWN);
					//update images to display
					card->getButton()->icon(imgs->getImage(card->getSymbol()));
					lastFlipCard->getButton()->icon(imgs->getImage(lastFlipCard->getSymbol()));
					//reset last flipped card pointer
					lastFlipCard = NULL;
					//start timer for events
					delay->start();
					//return actions for inequal result
					return INEQUAL_RESULT;
				}

			}

		}
	}

	//return no action to take
	return NO_RESULT;

}

/**
* Function: reset
* Param-in: none
* Param-out: none
* Purpose: sets variables to starting values for a new game instant
*/

void Game::reset() {

	pairsOnTable = SYMBOL_TTL;
	clickCount = INT_DEFAULT;
	lastFlipCard = NULL;
	//read file for high score
	initializeHighScore();

}