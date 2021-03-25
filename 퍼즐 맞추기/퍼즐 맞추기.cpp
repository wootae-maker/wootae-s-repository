﻿#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <bangtal.h>
#include <time.h>

SceneID scene;
ObjectID start;
ObjectID game_board[9], original_board[9];
int blank = 8;

bool game = false;

TimerID timer;
int mixCount;

int indexToX(int i)
{
	return 353 + 190 * (i % 3);
}

int indexToY(int i) 
{
	return 454 - 190 * (i / 3);
}

int game_index(ObjectID object)
{
	for (int i = 0; i < 9; i++) {
		if (game_board[i] == object) return i;
	}
	return -1;            //error, invalid object
}

int game_move(int i)
{
	// i <--> blank
	ObjectID object = game_board[i];
	game_board[i] = game_board[blank];
	locateObject(game_board[i], scene, indexToX(i), indexToY(i));
	game_board[blank] = object;
	locateObject(game_board[blank], scene, indexToX(blank), indexToY(blank));

	blank = i;

	return i;
}

void game_print()
{
	for (int i = 0; i < 9; i++) {
		printf("%d", game_board[i]);
	}
	printf("\n");
}

bool possible_move(int i) 
{
	if (i % 3 > 0 && blank == i - 1) return true;
	if (i % 3 < 2 && blank == i + 1) return true;
	if (i / 3 > 0 && blank == i - 3) return true;
	if (i / 3 < 2 && blank == i + 3) return true;

	return false;
}

int random_move()
{
	int i = -1;
		while (i == -1) {
			switch (rand() % 3) {
				case 0: if (blank % 3 > 0) i = blank - 1;
				    break;
				case 1: if (blank % 3 < 2) i = blank + 1;
					break;
				case 2: if (blank / 3 > 0) i = blank - 3;
					break;
				case 3: if (blank / 3 > 0) i = blank + 3;
					break;
			}
		}
		return i;
}

bool game_end() {
	for (int i = 0; i < 9; i++) {
		if (game_board[i] != original_board[i]) return false;
	}
	return true;
}

void game_start() 
{
	blank = 8;
	hideObject(game_board[blank]);

	mixCount = 30;

	setTimer(timer, 0.01f);
	startTimer(timer);
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action)
{
	if (game) {
		int i = game_index(object);
		if (possible_move(i)) {
			game_move(i);
		
			if (game_end()) {
				game = false;
				showObject(start);
				showObject(game_board[blank]);
				showMessage("Well played!");
			}
			game_print();
		}
	}
	else {
		if (object == start) {
			game_start();
		}

	}
}

void timerCallback(TimerID timer)
{
	game_move(random_move());
	
	mixCount--;
	if (mixCount > 0) {
		setTimer(timer, 0.01f);
		startTimer(timer);
	}
	else {
		game = true;
		hideObject(start);
	}
}

ObjectID createObject(const char* image, SceneID scene, int x, int y, bool shown = true)
{
	ObjectID object = createObject(image);
	locateObject(object, scene, x, y);
	if (shown) showObject(object);

	return object;

}

SceneID game_init()
{
	scene = createScene("중앙대 퍼즐", "Images/배경.png");

	char path[30];
	for (int i = 0; i < 9; i++) {
		sprintf(path, "Images/%d.png", i + 1);
		game_board[i] = createObject(path);
		locateObject(game_board[i], scene, indexToX(i), indexToY(i));
		showObject(game_board[i]);
		original_board[i] = game_board[i];
	}

	start = createObject("images/start.png", scene, 590, 100);

	timer = createTimer(0.05f);

	return scene;
}

int main()
{
	srand(time(NULL));
	
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	setMouseCallback(mouseCallback);
	setTimerCallback(timerCallback);

	startGame(game_init());
}
