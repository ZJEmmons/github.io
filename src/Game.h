/**
* Author: Zachary Emmons 040959178
* Course Code: CST8219
* Section: 303
* Project: Final Project
* Description: This is a header for the Game class. It declares
*			   the variables and functions that define main gameplay
*			   functions during play.
*/

#pragma once

/* INCLUDES */

#include <iostream>
#include <fstream>
#include <nana/gui/timer.hpp>
#include "Card.h"

/* DEFINES */

//end state of each game
#define END_GAME 0

//default value to intialize integers
#define INT_DEFAULT 0

//return states for card match results
#define INEQUAL_RESULT 1
#define EQUAL_RESULT 0
#define NO_RESULT -1

/* NAMESPACES */

using namespace std;

/* CLASS */

namespace FinalProject {
	class Game {

		/* VARIABLES */
	private:
		//counter to track game progress
		int pairsOnTable;
		//counter to score player on clicks
		int clickCount;
		//store for highest score earned
		int highScore;
		//pointer to last card flipped over
		Card *lastFlipCard;

	public:
		/* CONSTRUCTORS */
		Game();
		~Game();

		/* FUNCTIONS*/
		void incrementClick();
		void decrementPairs();
		int getClickCount();
		int getPairsLeft();
		int getHighScore();
		void initializeHighScore();
		int flipCard(Card* card, Image* imgs, timer* delay);
		void reset();

	};

}