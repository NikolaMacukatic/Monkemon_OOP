#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include"raylib.h"
using namespace std;

#include "Monke.h"




float blinkT = 0.0f;
bool showT = true;


enum GameState {

	MENU,
	BATTLE,
	TOURNAMENT,
	EXIT

};

GameState currentState = MENU;


void InitBattle();
void UpdateMneu();
void DrawMenu();
void UpdateBattle();
void DrawBattle();

//MENI



void UpdateMenu()
{
	blinkT += GetFrameTime();
	if (blinkT >= 0.5f)
	{
		showT = !showT;
		blinkT = 0.0f;
	}


	if (IsKeyPressed(KEY_ENTER))
	{
		InitBattle();

		currentState = BATTLE;
	}

	if (IsKeyPressed(KEY_ESCAPE))
	{
		currentState = EXIT;
	}
}

void DrawMenu() {

	BeginDrawing();
	ClearBackground(LIGHTGRAY);
	

	DrawText("MAIN MENU", 280, 50, 50, BLUE);

	DrawText("Random battle mode", 270, 200, 30, DARKBLUE);
	
	if (showT)
	{
		DrawText("Press A", 150, 200, 20, RED);
	}

	DrawText("Tournament mode", 270, 270, 30, DARKBLUE);

	if (showT)
	{
		DrawText("Press B", 150, 270, 20, DARKGREEN);
	}

	DrawText("Press ESC to QUIT", 330, 330, 20, BLACK);

	EndDrawing();
}

void InitBattle()
{
	cout << "Radi lmao" << endl;
}


int main()
{
	InitWindow(900, 500, "Monkemon");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		switch (currentState)
		{
		case MENU:
			UpdateMenu();
			DrawMenu();
			break;

		case BATTLE:
			break;


		case TOURNAMENT:
			break;

		case EXIT:
			CloseWindow();
			return 0;
			
		}

	}




	CloseWindow();
	return 0;
}