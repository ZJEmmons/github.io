/**
* Author: Zachary Emmons 040959178
* Course Code: CST8219
* Section: 303
* Project: Final Project
* Description: This is a header for the Card class. It declares
*			   the variables and functions that define each card
*				during play.
*/

#pragma once

/* INCLUDES */
#include "Image.h"
#include <nana/gui/widgets/button.hpp>


/* DEFINES */

//intializing constant for new Cards
#define INITIAL -1

//card states on board
#define FACE_UP 1
#define FACE_DOWN 0
#define OFF_BOARD -1

/* CLASS */
namespace FinalProject {
	class Card {

		/* VARIABLES */
		private:
			//position on board
			button* btn;
			//image on card
			int symbol;
			//current state on board
			int state;

		public:
			/* CONSTRUCTORS */
			Card();
			Card(button* button, int image);
			~Card();
			
			/* FUNCTIONS */
			int getState();
			int getSymbol();
			button* getButton();
			void setButton(button* button);
			void changeState(int state);

	};
}