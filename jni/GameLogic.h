/*
 * GameLogic.h
 *
 *  Created on: May 10, 2021
 *      Author: Zachary Emmons
 */

#ifndef JNI_GAMELOGIC_H_
#define JNI_GAMELOGIC_H_


#include <iostream>
#include <random>
#define DEFAULT_INT 0
#define MIN_DIFFICULTY 1
#define MAX_DIFFICULTY 5

class Game {

private:
	int* code;
	int difficulty;
	int multiple;
	int sum;
public:
	Game(int);
	~Game();
	void start();
	int getCodeAt(int) const;
	int getDiff() const;
	int getMultiple() const;
	int getSum() const;

};

int promptDifficulty();
bool promptContinue();
bool guess(Game*);


#endif /* JNI_GAMELOGIC_H_ */
