#include "ConsoleLib.h"

void ChangeLineColor(BGCOLOR BG, FGCOLOR FG)
{


	switch (FG) {

		case FG_RED:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
			break;
		case FG_BLUE:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
			break;
		case FG_GREEN:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
			break;
		case FG_BLACK:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN & FOREGROUND_RED & FOREGROUND_BLUE & FOREGROUND_INTENSITY);
			break;
	}

	switch (BG) {
	case BG_BLACK:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED & BACKGROUND_GREEN & BACKGROUND_BLUE & BACKGROUND_INTENSITY);
		break;
	case BG_RED:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED);
		
		break;
	case BG_BLUE:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE);
		break;
	case BG_GREEN:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
		break;
	}
}
