#ifndef BATTLE_H
#define BATTLE_H
#include "trainer.h"
#include "Monke.h"

Player player;
CPUTrainer cpu;

//GLOBALI ZA BATTLE
bool playerTurn = true;
bool battleOver = false;
string battleMessage = "TTTTTT TVOJ POTEZZ!! "; //YUGIOH REFERENCE ;)


enum GameState { MENU, BATTLE, TOURNAMENT, EXIT };
extern GameState currentState;  




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

	cout << "Random tim generiran TEST" << endl;
}






void UpdateBattle()
{
	if (battleOver)
	{
		if (IsKeyPressed(KEY_ENTER))
		{
			currentState = MENU;
		}
		return;
	}

	Monke* playerMonke = player.GetActiveMonke();
	Monke* cpuMonke = cpu.GetActiveMonke();

	
	if (playerTurn)
	{
		if (IsKeyPressed(KEY_ONE))  
		{
			int dmg = playerMonke->NormalAttack();
			cpuMonke->TakeDamage(dmg);
			battleMessage = "You attacked!";

			
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

			
			playerTurn = false;
			return;
		}


	
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

		
		if (IsKeyPressed(KEY_Q))
		{
			battleMessage = "You fled the battle!";
			battleOver = true;
		}


	}

	// CPU RUNDA
	else
	{
		int dmg = cpuMonke->NormalAttack();
		playerMonke->TakeDamage(dmg);
		battleMessage = "CPU attacked!";

		
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

	
		playerTurn = true;
		return;
	}
}




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


#endif
