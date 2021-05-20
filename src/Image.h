/**
* Author: Zachary Emmons 040959178
* Course Code: CST8219
* Section: 303
* Project: Final Project
* Description: This is a header for the Image class. It declares
*			   the variables and functions that handle loading and
*			   accessing each image.
*/

#pragma once

/* INCLUDES */

#include <nana/paint/image.hpp>

/* DEFINES */

//total number of symbols on cards
#define SYMBOL_TTL 10

//index locations for each image
#define CARD_BACK -1
#define FIRST_IMG 0
#define SECOND_IMG 1
#define THIRD_IMG 2
#define FOURTH_IMG 3
#define FIFTH_IMG 4
#define SIXTH_IMG 5
#define SEVENTH_IMG 6
#define EIGHTH_IMG 7
#define NINTH_IMG 8
#define TENTH_IMG 9
#define EMPTY_IMG 10
#define BG_IMG 11

/* NAMESPACES */

using namespace nana;
using namespace paint;

/* CLASS */

namespace FinalProject {
	class Image {

		/* VARIABLES */
		private:
			//backs of all cards
			image back;
			//symbols by number
			image first;
			image second;
			image third;
			image fourth;
			image fifth;
			image sixth;
			image seventh;
			image eighth;
			image ninth;
			image tenth;
			//form background image
			image bg;
			//empty image for cards out of play
			image empty;
		public:
			/* CONSTRUCTORS */
			Image();
			~Image();

			/* FUNCTIONS */
			image getImage(int index);
	};
}