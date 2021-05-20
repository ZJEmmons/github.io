/**
* Author: Zachary Emmons 040959178
* Course Code: CST8219
* Section: 303
* Project: Final Project
* Description: This program is a gui driven memory match game made using
*              nana libraries. The game runs in events loops to update
*              frame elements, allowing the user to reveal pairs on click
*              and remove them from the board. The game scores the player
*              on quantity of clicks to remove all pairs. Stores high
*              scores (lowest click counts).
*/

//compile read once
#pragma once

/* INCLUDES */
#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/button.hpp>
#include "Game.h"
#include "Sound.h"

/* DEFINES */

//Card Button Constants
#define BUTTON_AMT 20
#define POP_BUTTON_AMT 2

//Pop-Up Button Constants
#define YES_OPT 0
#define EXIT_OPT 1

//Mod Loop Control Constants
#define MOD_EVENS 2
#define MOD_TRUE 0

/* NAMESPACES */
using namespace nana;
using namespace FinalProject;


/* FUNCTIONS */

/**
* Function: timerEvent
* Param-in: timer* pTimer - pointer to timer object for stopping events
*           Card** pCard - pointer to array of Card pointers for card states
*           Image* pImgs - pointer to Image object to change card faces
*           Game* pGame - pointer to Game object to call main game functions
*           form* pop - pointer to form object to display pop-up window
*           label* pHighScore - pointer to label object high score values
*           Sound* pSound - pointer to Sond object to call players for audio
*           int matchState - return from Game functions confirming for matching cards
* Param-out: none
* Purpose: local function defines nana events for elapsed timer 
*/
void timerEvent(timer* pTimer, Card** pCard, Image* pImgs, Game* pGame,form* pop, label* pHighScore, Sound* pSound, int matchState) {

    //loop to set image by card state
    for (int i = INT_DEFAULT; i < BUTTON_AMT; i++) {

        //if not in play
        if (pCard[i]->getState() == OFF_BOARD)
            pCard[i]->getButton()->icon(pImgs->getImage(EMPTY_IMG));
        //if in play face down
        else if (pCard[i]->getState() == FACE_DOWN)
            pCard[i]->getButton()->icon(pImgs->getImage(CARD_BACK));

    }

    //check for last match results
    //if check was equal
    if (matchState == EQUAL_RESULT) {
        //successful pair audio
        pSound->getSound(M_MATCH).play();
    }
    //if check was inequal
    else if (matchState == INEQUAL_RESULT) {
        //unsuccessful pair audio
        pSound->getSound(M_NOMATCH).play();
    }

    //check for end of current game
    if (pGame->getPairsLeft()==END_GAME) {
        
        //check to store highscore in file
        if (pGame->getClickCount() < pGame->getHighScore() || pGame->getHighScore()==INT_DEFAULT) {
            
            //output stream for writing file
            ofstream scoreFile;
            scoreFile.open("score.txt");
            scoreFile << pGame->getClickCount();
            //stream close for memory leak
            scoreFile.close();
            //set current high score label
            pHighScore->caption("<bold black size=14>High Score: " + std::to_string(pGame->getHighScore()) + "</>");
        }
        //successful game audio
        pSound->getSound(M_VICTORY).play();
        
        //display pop-up window for reset or exit
        pop->show();
    }

    //stop timer loop for elapsed events
    pTimer->stop();

}

/**
* Function: clickEvent
* Param-in: timer* delay - pointer to timer object for starting events
*           Card* pCard - pointer to Card object for card states
*           Image* pImgs - pointer to Image object to change card faces
*           Game* pGame - pointer to Game object to call main game functions
*           label* score - pointer to label object current score value
* Param-out: int - match results of Game flipCard function
* Purpose: local function defines nana events for card button single clicks
*/

int clickEvent(Game* pGame, Card* pCard, label* score, Image* imgs, timer* delay) {

    //result value of flipCard method
    int flipReturn;
    //call flipCard for selected card at button
    flipReturn = pGame->flipCard(pCard, imgs, delay);
    //update current score label
    score->caption("<bold black size=14>Score: " + std::to_string(pGame->getClickCount()) + "</>");
    
    return flipReturn;

}

/**
* Function: shuffleCards
* Param-in: button** btns - pointer to array of button pointers to assign to Cards
*           vector<Card> cards - reference to vector of Card objects for shuffling
* Param-out: none
* Purpose: local function shuffles the vector of Card objects, and reassigns 
           button pointers
*/
void shuffleCards(vector<Card> &cards, button** btns) {
   
    //random generated seed value based on system time
    std::srand(unsigned(std::time(INT_DEFAULT)));
    //shuffle vector using seed
    std::random_shuffle(cards.begin(), cards.end());

    //set new button pointers for randomized cards
    for (int i = 0; i < BUTTON_AMT; i++) {
        cards.at(i).setButton(btns[i]);
        //resets card state for new game
        cards.at(i).changeState(FACE_DOWN);
    }

}

/**
* Function: resetGame
* Param-in: Image* pImgs - pointer to Image object to change card faces
*           button** - pointer to array of button pointers for reseting images
*           Game* pGame - pointer to Game object to call main game functions
*           label* score - pointer to label object current score value to reset
*           label* score - pointer to label object for high score
* Param-out: none
* Purpose: local function defines function calls for resetting the game loop variables
*          for a new game.
*/
void resetGame(Game* pGame, button** pBtn, label* score, label*pHighScore,Image* pImgs) {

    //call function to reset variables of Game
    pGame->reset();
    //update current score labels
    score->caption("<bold black size=14>Score: " + std::to_string(pGame->getClickCount()) + "</>");
    pHighScore->caption("<bold black size=14>High Score: " + std::to_string(pGame->getHighScore()) + "</>");

    for (int i = 0; i < BUTTON_AMT; i++) {
        //displays button icons as face down cards
        pBtn[i]->icon(pImgs->getImage(CARD_BACK));
    }

}

/* MAIN */

/**
* Function: main
* Param-in: none
* Param-out: int - return to end program, 0 for success, -1 for failure
* Purpose: entry function for program. Establishes nana objects, forms for
*          drawing nana elements (and their layouts), and establishes lamba
*          functions for game loop events.
*/
int main()
{
    //Sound object
    Sound sounds;
    Sound* pSound = &sounds;

    //timer object
    timer delay(chrono::milliseconds(800));
    timer* pTimer = &delay;

    //appearance object - for form
    appearance app(true,true,false,false,true,false,false);

    //rectangle objects for form and button dimensions
    rectangle recForm(20, 30, 1000, 700);
    rectangle rec(60, 150, 30, 60);

    //string object - store place format for form
    string div;
    
    //form - main game window
    form fm(recForm,app);

    //form - pop-up window
    form pop;
    form* pPop = &pop;

    //Game object
    Game newGame;
    Game* pGame = &newGame;
    pGame->initializeHighScore();

    //Image object
    Image images;
    Image* pImgs = &images;

    //thread pool - for audio
    threads::pool pool(1);

    //int counter controller for loops 
    int counter = INT_DEFAULT;
    //int store of Game flipCard match results
    int matchState = INT_DEFAULT - 1;
    //int index for For loops
    int i = INT_DEFAULT;

    //label objects
    //Game Title Header
    label lab{ fm, "<bold green size=16>Memory Match Game</>" };
    //Pop-up Window Header
    label win{ pop, "<bold green size=16>CONGRATS! Play Again?</>"  };
    //current score
    label score{ fm, "<bold black size=14>Score: " + std::to_string(pGame->getClickCount()) + "</>" };
    label* pScore = &score;
    //high score
    label highScore{fm, "<bold black size=14>High Score: " + std::to_string(pGame->getHighScore()) + "</>" };
    label* pHighScore = &highScore;

    //set formatting options for labels
    lab.format(true);
    win.format(true);
    score.format(true);
    highScore.format(true);

    /* Pop-Up Buttons */
    button popBtns[POP_BUTTON_AMT]{
        { pop, "Yes", true },
        { pop, "Exit",true }
    };

    //set pointers
    button* pPopBtn[POP_BUTTON_AMT];
        pPopBtn[YES_OPT] = &popBtns[YES_OPT];
        pPopBtn[EXIT_OPT] = &popBtns[EXIT_OPT];

    /* Card Buttons Array */
    button btns[BUTTON_AMT]{
    { fm, rec, true },
    { fm, rec, true },
    { fm, rec, true },
    { fm, rec, true },
    { fm, rec, true },
    { fm, rec, true },
    { fm, rec, true },
    { fm, rec, true },
    { fm, rec, true },
    { fm, rec, true },
    { fm, rec, true },
    { fm, rec, true },
    { fm, rec, true },
    { fm, rec, true },
    { fm, rec, true },
    { fm, rec, true },
    { fm, rec, true },
    { fm, rec, true },
    { fm, rec, true },
    { fm, rec, true } };

    button* pBtn[BUTTON_AMT];
    for (i = INT_DEFAULT; i < BUTTON_AMT; i++)
        //set pointers
        pBtn[i] = &btns[i];


    /* Card vector */
    vector<Card> cards;
    //size vector to card amount
    cards.resize(BUTTON_AMT);
    Card* pCard[BUTTON_AMT];

    for (i = INT_DEFAULT; i < BUTTON_AMT; i++) {
        
        //set pointers
        pCard[i] = &cards.at(i);
        
        //define card symbols, two of each for the set
        if (i % MOD_EVENS == MOD_TRUE) {
            counter++;
            if (counter == SYMBOL_TTL)
                counter = INT_DEFAULT;
        }

        //initialize cards
        cards.at(i) = Card(pBtn[i],counter);
    
    }

    /* EVENTS & MODS */

    //Card buttons
    for (i = INT_DEFAULT; i < BUTTON_AMT; i++) {
        pBtn[i]->icon(pImgs->getImage(CARD_BACK));
        pBtn[i]->edge_effects(false);
        pBtn[i]->transparent(true);
        pBtn[i]->events().click([&pCard, &pGame, &pScore, &pImgs, &pTimer, &pSound, &pool, &matchState, i]() {
            matchState = clickEvent(pGame, pCard[i], pScore, pImgs, pTimer);
            });
    }

    //Pop-up Buttons
    pPopBtn[YES_OPT]->events().click([&pGame, &pop, &cards, &pBtn, &pScore, &pHighScore, &pImgs, &pSound]() { pSound->getSound(M_SHUFFLE).play(); shuffleCards(cards, pBtn); resetGame(pGame, pBtn, pScore, pHighScore, pImgs); pop.hide(); });
    pPopBtn[EXIT_OPT]->events().click([&fm, &pop, &pSound]() { pop.close(); fm.close(); });

    //Timer Events
    delay.elapse([&pTimer, &pCard, &pImgs, &pGame, &pPop, &pHighScore, &pSound, &matchState] { timerEvent(pTimer, pCard, pImgs, pGame, pPop, pHighScore, pSound, matchState); });

    //Closing Form
    fm.events().destroy([&pop]() { pop.close(); });


    /* FORMAT MAIN FORM */

    //place formatting for form
    div = "vert< <HEADER> >< <A1 > <A2> <A3> <A4> >< <B1> <B2> <B3> <B4> >";
    div += "< <C1> <C2> <C3> <C4> >< <D1> <D2> <D3> <D4> >< <E1> <E2> <E3> <E4> >";
    div += "< <SCORE> <HIGHSCORE> > ";   
    
    //apply div place format
    fm.div(div);

    //set background image
    fm.icon(pImgs->getImage(BG_IMG));

    //place labels
    fm["HEADER"] << lab;
    fm["SCORE"] << score;
    fm["HIGHSCORE"] << highScore;

    //place buttons
    fm["A1"] << btns[counter];
    counter++;
    fm["A2"] << btns[counter];
    counter++;
    fm["A3"] << btns[counter];
    counter++;
    fm["A4"] << btns[counter];
    counter++;

    fm["B1"] << btns[counter];
    counter++;
    fm["B2"] << btns[counter];
    counter++;
    fm["B3"] << btns[counter];
    counter++;
    fm["B4"] << btns[counter];
    counter++;

    fm["C1"] << btns[counter];
    counter++;
    fm["C2"] << btns[counter];
    counter++;
    fm["C3"] << btns[counter];
    counter++;
    fm["C4"] << btns[counter];
    counter++;

    fm["D1"] << btns[counter];
    counter++;
    fm["D2"] << btns[counter];
    counter++;
    fm["D3"] << btns[counter];
    counter++;
    fm["D4"] << btns[counter];
    counter++;

    fm["E1"] << btns[counter];
    counter++;
    fm["E2"] << btns[counter];
    counter++;
    fm["E3"] << btns[counter];
    counter++;
    fm["E4"] << btns[counter];
    counter++;
    
    //conform window to layout
    fm.collocate();


    /* FORMAT POP UP FORM */
    pop.div(div);
    
    //place label
    pop["HEADER"] << win;
    
    //place buttons
    pop["C2"] << popBtns[YES_OPT];
    pop["C3"] << popBtns[EXIT_OPT];

    //conform window to layout
    pop.collocate();

    //draw the form
    fm.show();

    //hide pop-up
    pop.hide();

    //initial card shuffle
    shuffleCards(cards, pBtn);

    //play startup sound
    pSound->getSound(M_STARTUP).play();

    //Start to event loop process, it blocks until the form is closed.
    exec();

}