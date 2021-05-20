/**
* Author: Zachary Emmons 040959178
* Course Code: CST8219
* Section: 303
* Project: Final Project
* Description: This source file defines the functions and
*			   constructors declared in Sound header.
*/

/* INCLUDES */

#include "Sound.h"

/* NAMESPACES */

using namespace FinalProject;
using namespace nana;

/* CONSTRUCTORS */

Sound::Sound() {
	bgm.open("bgm.wav");
	click.open("click.wav");
	match.open("match.wav");
	nomatch.open("nomatch.wav");
	shuffle.open("shuffle.wav");
	startup.open("startup.wav");
	victory.open("victory.wav");
}//default constructor, paths to audio and loads

Sound::~Sound() {
	bgm.close();
	click.close();
	match.close();
	nomatch.close();
	shuffle.close();
	startup.close();
	victory.close();
}//destructor, closes players for memory leak

/* FUNCTIONS */

/**
* Function: getSound
* Param-in: int index - the index using constant values to return
*						appropriate player
* Param-out: player& - the referenced loaded player to return
* Purpose: a switch controlled method to allow fetching loaded player
*		   from variables in class
*/

audio::player& Sound::getSound(int index) {

	switch (index) {
		case M_BGM:
			return bgm;
			break;

		case M_CLICK:
			return click;
			break;

		case M_MATCH:
			return match;
			break;

		case M_NOMATCH:
			return nomatch;
			break;

		case M_SHUFFLE:
			return shuffle;
			break;

		case M_STARTUP:
			return startup;
			break;

		case M_VICTORY:
			return victory;
			break;

		default: 
			return click;
			break;
	}

}