#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include"raylib.h"
#include <cstdlib>
#include <ctime>
using namespace std;

#include "Monke.h"
#include "trainer.h"
#include "battle.h"


//GLOBALI


//GLOBALI ZA MENI

float blinkT = 0.0f;
bool showT = true;




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


	if (IsKeyPressed(KEY_A))
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

	

	DrawText("Press ESC to QUIT", 330, 330, 20, BLACK);

	EndDrawing();
}





int main()
{
	InitWindow(900, 500, "Monkemon");
	fireTex = LoadTexture("assets/FireMonke.png");
	waterTex = LoadTexture("assets/WaterMonke.png");
	earthTex = LoadTexture("assets/EarthMonke.png");
	TraceLog(LOG_INFO, "FireTex id: %d", fireTex.id);
	TraceLog(LOG_INFO, "WaterTex id: %d", waterTex.id);
	TraceLog(LOG_INFO, "EarthTex id: %d", earthTex.id);


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
			DrawBattle();
			UpdateBattle();

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