#pragma once
#include "traning.h"
#include "second loc.h"
class Location {
public:
	unsigned char
		startX, startY,
		endX, endY;
	const char** loc;
	const char** dialogs;
	Location(int x, int y, const char* NewLoc[], const char* NewDialogs[]) {
		dialogs = NewDialogs;
		loc = NewLoc;

		for (int i = 0; i < y; i++) {
			for (int j = 0; j < x; j++) {
				if (loc[i][j] == '.') {
					startX = j;
					startY = i;
				}
				else if (loc[i][j] == '/') {
					endX = j;
					endY = i;
				}
			}
		}
	}
};

Location worldMap[] = {
	Location(9, 7, traning, traningDialogs),
	Location(5, 5, secondLoc, NULL)
};