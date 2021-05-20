/**
* Author: Zachary Emmons 040959178
* Course Code: CST8219
* Section: 303
* Project: Final Project
* Description: This is a header for the Sound class. It declares
*			   the variables and functions that handle loading and
*			   playing each audio file.
*/

#pragma once

/* INCLUDES */

#include <nana/threads/pool.hpp>
#include <nana/audio/player.hpp>

/* DEFINES */

//constants to index audio files, .wav
#define M_BGM 0
#define M_CLICK 1
#define M_MATCH 2
#define M_NOMATCH 3
#define M_SHUFFLE 4
#define M_STARTUP 5
#define M_VICTORY 6

/* CLASS */

namespace FinalProject {
	class Sound {

		/* VARIABLES */
		private:
			//player objects to load audio
			nana::audio::player bgm;
			nana::audio::player click;
			nana::audio::player match;
			nana::audio::player nomatch;
			nana::audio::player shuffle;
			nana::audio::player startup;
			nana::audio::player victory;
		public:
			/* CONSTRUCTORS */
			Sound();
			~Sound();

			/* FUNCTIONS */
			nana::audio::player& getSound(int index);
	};

}