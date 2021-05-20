/**
* Author: Zachary Emmons 040959178
* Course Code: CST8219
* Section: 303
* Project: Final Project
* Description: This source file defines the functions and
*			   constructors declared in Card header.
*/

/* INCLUDES */

#include "Card.h"

/* NAMESPACES */
using namespace FinalProject;

/* CONSTRUCTORS */

Card::Card() {
	state = FACE_DOWN;
	btn = NULL;
	symbol = INITIAL;
} //default constructor

Card::Card(button* button, int image) {
	
	state = FACE_DOWN;
	btn = button;
	symbol = image;

}//initial constructor

Card::~Card() {}//destructor

/* FUNCTIONS */

int Card::getState() {
	return state;
}//returns value of state variable

int Card::getSymbol() {
		return symbol;
}//returns value of symbol variable

button* Card::getButton() {
	return btn;
}//returns pointer of btn variable (for position)

void Card::changeState(int pos) {
	state = pos;
}//modify the state variable

void Card::setButton(button* button) {
	btn = button;
}//modify where btn variable points