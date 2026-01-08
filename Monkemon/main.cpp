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


// TESTIRAMO ----------------------------------------------------------------
/*
//GLOBALI ZA TRENERE
Player player;
CPUTrainer cpu;

//GLOBALI ZA BATTLE
bool playerTurn = true;
bool battleOver = false;
string battleMessage = "TTTTTT TVOJ POTEZZ!! "; //YUGIOH REFERENCE ;)
*/
// TESTIRAMO ----------------------------------------------------------------



//GLOBALI ZA MENI

float blinkT = 0.0f;
bool showT = true;



// TESTIRAMO ----------------------------------------------------------------
/*
enum GameState {

	MENU,
	BATTLE,
	TOURNAMENT,
	EXIT

};

GameState currentState = MENU;
*/
// TESTIRAMO ----------------------------------------------------------------

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

	DrawText("Tournament mode", 270, 270, 30, DARKBLUE);

	if (showT)
	{
		DrawText("Press B", 150, 270, 20, DARKGREEN);
	}

	DrawText("Press ESC to QUIT", 330, 330, 20, BLACK);

	EndDrawing();
}



// TESTIRAMO ----------------------------------------------------------------

/*
//RANDOM MAJMUNI

Monke* CreateRandomMonke()
{
	int type = rand() % 3;   

	switch (type)
	{
	case 0:
		return new FireMonke("FireMonke", 100, 20);
	case 1:
		return new WaterMonke("WaterMonke", 110, 18);
	case 2:
		return new EarthMonke("EarthMonke", 130, 15);
	default:
		return new FireMonke("FireMonke", 100, 20);
	}
}
*/

/*
void InitBattle()
{
	static bool seeded = false;
	if (!seeded)
	{
		srand((unsigned int)time(nullptr));
		seeded = true;
	}

	
	player = Player();
	cpu = CPUTrainer();

	
	for (int i = 0; i < 3; i++)
	{
		player.AddMonke(CreateRandomMonke());
	}

	// Random CPU team
	for (int i = 0; i < 3; i++)
	{
		cpu.AddMonke(CreateRandomMonke());
	}


	playerTurn = true;
	battleOver = false;
	battleMessage = "TTTTTT TVOJ POTEZZ!!";

	cout << "Random tim generiran TEST" <<endl;
}
*/


/*

void UpdateBattle()
{
	//VRACA NA MAIN MENI
	if(battleOver)
	{
		if (IsKeyPressed(KEY_ENTER))
		{
			currentState = MENU;
		}
		return;
	}

	Monke* playerMonke = player.GetActiveMonke();
	Monke* cpuMonke = cpu.GetActiveMonke();

	// IGRAC RED
	if (playerTurn)
	{
		if (IsKeyPressed(KEY_ONE))   // NORMALNI NAPAD
		{
			int dmg = playerMonke->NormalAttack();
			cpuMonke->TakeDamage(dmg);
			battleMessage = "You attacked!";

			// ODMAH PROVJERI ENEMY
			if (cpuMonke->IsFainted())
			{
				battleMessage = "Enemy fainted!";
				cpu.SwitchToNextMonke();

				if (!cpu.HasRemainingMonkes())
				{
					battleMessage = "YOU WIN!";
					battleOver = true;
				}

				return; 
			}

			// IDUCI RED
			playerTurn = false;
			return;
		}


		// ELEMENTALNI NAPAD SVAKI 3 NAPADA
		if (IsKeyPressed(KEY_TWO))
		{
			int dmg = playerMonke->ElementalAttack(*cpuMonke);
			if (dmg == 0)
			{
				battleMessage = "Elemental attack not ready!";
			}
			else
			{
				battleMessage = "You used ELEMENTAL attack!";
				playerTurn = false;
			}
		}

		// BIZI VAN
		if (IsKeyPressed(KEY_Q))
		{
			battleMessage = "You fled the battle!";
			battleOver = true;
		}


	}

	// CPU REED
	else
	{
		int dmg = cpuMonke->NormalAttack();
		playerMonke->TakeDamage(dmg);
		battleMessage = "CPU attacked!";

		//ODMAH PROVJERI PLAYERA
		if (playerMonke->IsFainted())
		{
			battleMessage = "You fainted!";
			player.SwitchToNextMonke();

			if (!player.HasRemainingMonkes())
			{
				battleMessage = "YOU LOSE!";
				battleOver = true;
			}

			return; 
		}

		// IDUCI TURN
		playerTurn = true;
		return;
	}
}


*/



/*
void DrawBattle()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);

	Monke* playerMonke = player.GetActiveMonke();
	Monke* cpuMonke = cpu.GetActiveMonke();

	
	DrawText("PLAYER", 50, 30, 20, BLUE);
	DrawText(playerMonke->GetName().c_str(), 50, 60, 20, BLACK);
	DrawText(TextFormat("HP: %d", playerMonke->GetHP()), 50, 90, 20, DARKGREEN);

	
	DrawText("CPU", 650, 30, 20, RED);
	DrawText(cpuMonke->GetName().c_str(), 650, 60, 20, BLACK);
	DrawText(TextFormat("HP: %d", cpuMonke->GetHP()), 650, 90, 20, MAROON);

	
	DrawRectangle(150, 180, 600, 80, LIGHTGRAY);
	DrawText(battleMessage.c_str(), 170, 210, 20, BLACK);

	
	if (!battleOver)
	{
		DrawText("1 - Normal Attack", 50, 300, 20, DARKGRAY);
		DrawText("2 - Elemental Attack (after 3 hits)", 50, 330, 20, ORANGE);
		DrawText("Q - Quit Battle", 50, 360, 20, DARKGRAY);
	}
	else
	{
		DrawText("Press ENTER to return to menu", 250, 320, 20, DARKBLUE);
	}

	EndDrawing();
}

*/

// TESTIRAMO ----------------------------------------------------------------


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