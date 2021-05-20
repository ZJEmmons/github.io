#include "CodeGame.h"
#include "GameLogic.h"

using namespace std;

Game::Game(int amt) {
	difficulty = amt;
	multiple = DEFAULT_INT+1;
	sum = DEFAULT_INT;
	code = new int[difficulty];
}

Game::~Game() {
	delete[] code;
}

int Game::getCodeAt(int index) const {
	return code[index];
}

int Game::getDiff() const{
	return difficulty;
}

int Game::getMultiple() const{
	return multiple;
}

int Game::getSum() const{
	return sum;
}

void Game::start() {
	std::random_device rand;
	std::uniform_int_distribution<int> distrib(1,9);

	srand((unsigned)time(NULL));
	for (int i=DEFAULT_INT; i < difficulty; i++) {
		code[i] = distrib(rand);
		multiple *= code[i];
		sum += code[i];
	}

}

int promptDifficulty() {
	int difficulty = DEFAULT_INT;

	cout << "\nEnter a difficulty from 1 to 5\n>";

	while (true) {
		cin >> difficulty;

		if (difficulty >= MIN_DIFFICULTY && difficulty <= MAX_DIFFICULTY) {
			return difficulty;
		}
		else {
			cout << "\nMust be between 1 and 5 inclusive!\n>";
		}
	}
}

bool promptContinue() {
	char input = 'a';

	cout << "\nWould you like to continue? Y/N\n>";

	while (true) {
		cin >> input;

		if (input == 'Y' || input == 'y') {
			return true;
		}
		else if (input == 'N' || input == 'n') {
			return false;
		}
		else {
			cout << "\nMust Enter Y or N\n>";
		}

	}
}

bool guess(Game* game) {

	int input = DEFAULT_INT;
	bool guess = true;

	cout << "\nEnter Your Guesses:" << endl;

	for (int i = DEFAULT_INT; i < game->getDiff(); i++) {
		cout << "\tCode Slot #" << i+1 << " = ";
		cin >> input;

		if (input != game->getCodeAt(i)) {
			guess = false;
		}

	}

	if (!guess) {
		cout << "xx WRONG! Try Again. xx" << endl;
	}
	else {
		cout << "~~ CORRECT! ~~" << endl;
	}

	return guess;

}

JNIEXPORT jint JNICALL Java_CodeGame_runGame (JNIEnv *env, jclass jClass){

	Game* gamePnt;
	bool loopCtrl = true;
	bool guessState;

	system("CLS");

	//TITLE HEADER
	cout << "CODE GAME" << endl;
	cout << "~~~~~~~~~" << endl;

	while (loopCtrl) {
		guessState = false;
		gamePnt = new Game(promptDifficulty());
		gamePnt->start();

		cout << "*\tThere are " << gamePnt->getDiff() << " numbers in the code." << endl;
		cout << "*\tThe codes multiply to give " << gamePnt->getMultiple() << endl;
		cout << "*\tThe codes add up to " << gamePnt->getSum() << endl;


		while (!guessState) {
			guessState = guess(gamePnt);
		}

		loopCtrl = promptContinue();
	}

	cout << "\nExiting, Goodbye! . . ." << endl;
	return 0;
}
