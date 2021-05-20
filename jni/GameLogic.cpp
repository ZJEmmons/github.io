//include for auto-generated JNI header
#include "CodeGame.h"
//main Game class header
#include "GameLogic.h"

//namespace for iostream
using namespace std;

/**
 * Game class intial constructor
 *
 * initializes all member variables
 */
Game::Game(int amt) {
	_difficulty = amt;
	_multiple = DEFAULT_INT+1;
	_sum = DEFAULT_INT;
	_code = new int[_difficulty];
}

/**
 * Game class destructor
 *
 * clears member of code array
 */
Game::~Game() {
	delete[] _code;
}

/**
 * Game class func getCodeAt
 *
 * takes in index parameter and returns value at array index
 */
int Game::getCodeAt(int index) const {
	return _code[index];
}

/**
 * Game class func getDiff
 *
 * returns difficulty value
 */
int Game::getDiff() const{
	return _difficulty;
}

/**
 * Game class func getMultiple
 *
 * returns mulitplication value
 */
int Game::getMultiple() const{
	return _multiple;
}

/**
 * Game class func getSum
 *
 * returns sum value
 */
int Game::getSum() const{
	return _sum;
}

/**
 * Game class func start
 *
 * seeds randomizer and sets random values to code
 * multiplies values and stores to _multiple
 * sums values and stores to _sum
 */
void Game::start() {

	//randomizer object
	std::random_device rand;
	//establish range of values from 1 to 9 inclusive
	std::uniform_int_distribution<int> distrib(1,9);

	//set seed
	srand((unsigned)time(NULL));

	//iterate through code array
	for (int i=DEFAULT_INT; i < _difficulty; i++) {
		//store random value
		_code[i] = distrib(rand);
		//multiply to prior sum
		_multiple *= _code[i];
		//add to prior sum
		_sum += _code[i];
	}

}

/**
 * func promptDifficulty
 *
 * console input prompt for difficulty level of game
 */
int promptDifficulty() {
	//store input value
	int difficulty = DEFAULT_INT;

	//prompt
	cout << "\nEnter a difficulty from 1 to 5\n>";

	//loop for valid entry value
	while (true) {

		//input
		cin >> difficulty;

		//check if in range
		if (difficulty >= MIN_DIFFICULTY && difficulty <= MAX_DIFFICULTY) {
			return difficulty;
		}
		//error prompt
		else {
			cout << "\nMust be between 1 and 5 inclusive!\n>";
		}
	}
}

/**
 * func promptContinue
 *
 * prompts for input on game completion
 * returns true to continue game loop
 * returns false to exit game loop
 */
bool promptContinue() {

	//store for input
	char input = 'a';

	//prompt
	cout << "\nWould you like to continue? Y/N\n>";

	//loop for valdi input
	while (true) {

		//input
		cin >> input;

		//check for yes value
		if (input == 'Y' || input == 'y') {
			return true;
		}
		//check for no value
		else if (input == 'N' || input == 'n') {
			return false;
		}
		//error prompt
		else {
			cout << "\nMust Enter Y or N\n>";
		}

	}
}

/**
 * func guess
 *
 * takes in Game object parameter for values and functions
 * input loop for guesses by player during game
 * prompts if guesses are right or wrong
 * returns true for successful guess
 * returns false for wrong guess
 */
bool guess(Game* game) {

	//store input
	int input = DEFAULT_INT;
	//track correct guesses
	bool guess = true;

	//prompt
	cout << "\nEnter Your Guesses:" << endl;

	//iterate through number of code digits
	for (int i = DEFAULT_INT; i < game->getDiff(); i++) {

		//prompt for input
		cout << "\tCode Slot #" << i+1 << " = ";
		//input
		cin >> input;

		//check for guess state
		if (input != game->getCodeAt(i)) {
			guess = false;
		}

	}

	//prompt for wrong guess
	if (!guess) {
		cout << "xx WRONG! Try Again. xx" << endl;
	}
	//prompt for right guess
	else {
		cout << "~~ CORRECT! ~~" << endl;
	}

	//return guess state
	return guess;

}

/**
 * func Java_CodeGame_runGame
 *
 * native function takes in java environment and java class as parameters
 * acts as a main menu and game loop function for program
 *
 * returns java int for program exit value
 */
JNIEXPORT jint JNICALL Java_CodeGame_runGame (JNIEnv *env, jclass jClass){

	//Game class object
	Game* gamePnt;
	//game loop
	bool loopCtrl = true;
	//state of last input guess
	bool guessState;

	//clear console window
	system("CLS");

	//TITLE HEADER
	cout << "CODE GAME" << endl;
	cout << "~~~~~~~~~" << endl;

	//main game loop
	while (loopCtrl) {

		//intialize variables
		guessState = false;
		//new game instance and pointer
		gamePnt = new Game(promptDifficulty());
		gamePnt->start();

		//Hint prompt for user
		cout << "*\tThere are " << gamePnt->getDiff() << " numbers in the code." << endl;
		cout << "*\tThe codes multiply to give " << gamePnt->getMultiple() << endl;
		cout << "*\tThe codes add up to " << gamePnt->getSum() << endl;

		//loops while guess is incorrect
		while (!guessState) {
			//sets the last guessed state
			guessState = guess(gamePnt);
		}

		//prompt to continue or end game loop
		loopCtrl = promptContinue();
	}

	//exit prompt
	cout << "\nExiting, Goodbye! . . ." << endl;
	return 0;
}
