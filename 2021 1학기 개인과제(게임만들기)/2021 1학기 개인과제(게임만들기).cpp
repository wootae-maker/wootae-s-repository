#include <bangtal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

SceneID scene1, scene2;
ObjectID startButton, endButton, endButton2, kickerButton, ball, left, right, middle, keeperMiddle, keeperLeft, keeperRight;
int ballX = 610;
int ballY = 30;
int rand_move();
int passleft();
int clickleft();
int passmiddle();
int clickmiddle();
int passright();
int clickright();
void result();
int n = 0;
int save = 0;
int goal = 0;
int m = 0;
int o = 0;
int p = 0;


void mousetCallback(ObjectID object, int x, int y, MouseAction action)
{
	if (object == endButton)
		endGame();

	else if (object == startButton) {

		hideObject(startButton);
		hideObject(endButton);

		showObject(kickerButton);
	}
	else if (object == kickerButton)
	{
		enterScene(scene2);
		showObject(keeperMiddle);
	}

	else if (object == middle)
	{
		rand_move();
		ballX = 610;
		ballY = 250;
		locateObject(ball, scene2, ballX, ballY);
		passmiddle();
		result();
		n+=1;
	}

	else if (object == left)
	{
		rand_move();
		ballX = 320;
		ballY = 265;
		locateObject(ball, scene2, ballX, ballY);
		passleft();
		result();
		n+=1;
	}
	else if (object == right)
	{
		rand_move();
		ballX = 910;
		ballY = 265;
		locateObject(ball, scene2, ballX, ballY);
		passright();
		result();
		n+=1;
	}

	if (n > 4)
	{
		(save > goal) ? showMessage("골키퍼 승! 아쉽네요ㅠㅠ") : showMessage("키커 승! 축하합니다*^^*");
		hideObject(left);
		hideObject(right);
		hideObject(middle);

		showObject(endButton2);
	}

	if (object == endButton2)
		endGame();
	

} 

int passmiddle() {
	m = m + 1;
	return 0;
}


int clickmiddle() {
	if (m == 1)
	{
		m = m - 1;
		return 0;
	}
	else
		return 4109;
}

int passleft() {
	o = o + 1;
	return 0;

}

int clickleft()
{
	if (o == 1)
	{
		o = o - 1;
		return 1;
	}
	else
		return 1298;
	
	}

int passright() {
	p = p + 1;
	return 0;

}

int clickright()
{
	if (p == 1)
	{
		p = p - 1;
		return 2;
	}
	else
		return 1230;
}
 int rand_move()
	{
		srand((unsigned)time(NULL));

		int i = rand() % 3;
		switch (i) {
		case 0: hideObject(keeperLeft); hideObject(keeperRight); showObject(keeperMiddle); break;
		case 1: hideObject(keeperMiddle); hideObject(keeperRight);  showObject(keeperLeft); break;
		case 2: hideObject(keeperMiddle); hideObject(keeperLeft);  showObject(keeperRight); break;
		}

		return i;
	}

 void result()
 {
	
	 if (rand_move()==clickmiddle()||rand_move()==clickleft()||rand_move()==clickright())
	 {	
		 showMessage("막힘..");
 		 save += 1;
	 }
	 else
	 {
		 showMessage("Goal!!");
		 goal += 1;
	 }
	 
	 
}

int main()
{
	setMouseCallback(mousetCallback);

	scene1 = createScene("산티아고 베르나베우", "images/축구장배경.jpg");
	scene2 = createScene("승부차기", "images/골대배경.jpg");

	startButton = createObject("images/start.png");
	locateObject(startButton, scene1, 590, 130);
	showObject(startButton);

	endButton = createObject("images/end.png");
	locateObject(endButton, scene1, 590, 80);
	showObject(endButton);
	
	endButton2 = createObject("images/end.png");
	locateObject(endButton2, scene2, 590, 60);
	showObject(endButton);

	kickerButton = createObject("images/키커.png");
	locateObject(kickerButton, scene1, 515, 310);

	ball = createObject("images/축구공.png");
	locateObject(ball, scene2, ballX, ballY);
	showObject(ball);

	left = createObject("images/play2.png");
	locateObject(left, scene2, 340, 500);
	showObject(left);

	right = createObject("images/play.png");
	locateObject(right, scene2, 920, 500 );
	showObject(right);

	middle = createObject("images/play3.png");
	locateObject(middle, scene2, 630, 500);
	showObject(middle);

	keeperMiddle = createObject("images/골키퍼 대기.png");
	locateObject(keeperMiddle, scene2, 520, 100);
	showObject(keeperMiddle);

	keeperRight = createObject("images/골키퍼 몸날림.png");
	locateObject(keeperRight, scene2, 700, 180);
	

	keeperLeft = createObject("images/골키퍼 몸날림(왼).png");
	locateObject(keeperLeft, scene2, 340, 180);


	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	showMessage("승부차기 게임");
    startGame(scene1);

	printf("save: %d, goal: %d, total: %d", save, goal, n);


	}