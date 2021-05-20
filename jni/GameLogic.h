/*
 * GameLogic.h
 *
 * Header file declares functional methods for game operation
 *
 *  Created on: May 10, 2021
 *      Author: Zachary Emmons
 */

#ifndef JNI_GAMELOGIC_H_
#define JNI_GAMELOGIC_H_

//iostream for console io
#include <iostream>
//randomizer for code values
#include <random>

//defines
#define DEFAULT_INT 0
#define MIN_DIFFICULTY 1
#define MAX_DIFFICULTY 5

class Game {
//member variables
private:
	int* _code;
	int _difficulty;
	int _multiple;
	int _sum;
//member functions
public:
	Game(int);
	~Game();
	void start();
	int getCodeAt(int) const;
	int getDiff() const;
	int getMultiple() const;
	int getSum() const;

};

//method declarations for main input functions
int promptDifficulty();
bool promptContinue();
bool guess(Game*);


#endif /* JNI_GAMELOGIC_H_ */
