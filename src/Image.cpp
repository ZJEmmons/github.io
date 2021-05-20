/**
* Author: Zachary Emmons 040959178
* Course Code: CST8219
* Section: 303
* Project: Final Project
* Description: This source file defines the functions and
*			   constructors declared in Image header.
*/

/* INCLUDES */

#include "Image.h"
#include <iostream>

/* NAMESPACES */

using namespace FinalProject;

/* CONSTRUCTORS */

Image::Image() {
	back.open("CardBack.bmp");
	first.open("CardOne.bmp");
	second.open("CardTwo.bmp");
	third.open("CardThree.bmp");
	fourth.open("CardFour.bmp");
	fifth.open("CardFive.bmp");
	sixth.open("CardSix.bmp");
	seventh.open("CardSeven.bmp");
	eighth.open("CardEight.bmp");
	ninth.open("CardNine.bmp");
	tenth.open("CardTen.bmp");
	bg.open("Background.bmp");
}//default constructor, paths to images and loads

Image::~Image() {
	back.close();
	first.close();
	second.close();
	third.close();
	fourth.close();
	fifth.close();
	sixth.close();
	seventh.close();
	eighth.close();
	ninth.close();
	tenth.close();
}//destructor, closes images for memory leak

/* FUNCTIONS */

/**
* Function: getImage
* Param-in: int index - the index using constant values to return 
						appropriate image 
* Param-out: image - the referenced loaded image to return
* Purpose: a switch controlled method to allow fetching loaded image
*		   from variables in class
*/

image Image::getImage(int index) {
	switch (index) {

	case CARD_BACK:
		return back;
		break;

	case FIRST_IMG:
		return first;
		break;

	case SECOND_IMG:
		return second;
		break;

	case THIRD_IMG:
		return third;
		break;

	case FOURTH_IMG:
		return fourth;
		break;

	case FIFTH_IMG:
		return fifth;
		break;

	case SIXTH_IMG:
		return sixth;
		break;

	case SEVENTH_IMG:
		return seventh;
		break;

	case EIGHTH_IMG:
		return eighth;
		break;

	case NINTH_IMG:
		return ninth;
		break;

	case TENTH_IMG:
		return tenth;
		break;

	case EMPTY_IMG:
		return empty;
		break;

	case BG_IMG:
		return bg;
		break;

	default:
		return back;
	}

}