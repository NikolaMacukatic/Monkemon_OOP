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

//ovi vrag za delay
float turnDelay = 0.0f;
const float TURN_DELAY_TIME = 1.0f; 
bool waitingForTurn = false;



enum GameState { MENU, BATTLE, TOURNAMENT, EXIT };
extern GameState currentState;  

//inicijalizacija tekstura za majmune
Texture2D fireTex;
Texture2D waterTex;
Texture2D earthTex;



Texture2D GetMonkeTexture(Monke* monke)
{
	switch (monke->GetType())
	{
	case ElementType::FIRE:
		return fireTex;
	case ElementType::WATER:
		return waterTex;
	case ElementType::EARTH:
		return earthTex;
	default:
		return fireTex;
	}
}


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

	if (waitingForTurn)
	{
		turnDelay += GetFrameTime();

		if (turnDelay >= TURN_DELAY_TIME)
		{
			waitingForTurn = false;
			turnDelay = 0.0f;
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
			battleMessage = "You attacked";

			
			if (cpuMonke->IsFainted())
			{
				battleMessage = "Enemy monke fainted";
				cpu.SwitchToNextMonke();

				if (!cpu.HasRemainingMonkes())
				{
					battleMessage = "YOU WIN!!!!!!!";
					battleOver = true;
				}

				return; 
			}

			
			playerTurn = false;
			waitingForTurn = true;
			return;
		}


	
		if (IsKeyPressed(KEY_TWO))
		{
			int dmg = playerMonke->ElementalAttack(*cpuMonke);
			if (dmg == 0)
			{
				battleMessage = "Elemental attack not ready";
			}
			else
			{
				battleMessage = "You used elemental attack";
				playerTurn = false;
				waitingForTurn = true;
				return;
			}
		}

		if (IsKeyPressed(KEY_THREE))
		{
			if (player.UseHealingItem(playerMonke))
			{
				battleMessage = "You used a healing item";
				playerTurn = false;
				waitingForTurn = true;
			}
			else
			{
				battleMessage = "No healing items left";
			}
			return;
		}

		
		if (IsKeyPressed(KEY_Q))
		{
			battleMessage = "You fled the battle....weak..";
			battleOver = true;
		}


	}

	
	else
	{



		if (cpu.GetHealingItems() > 0 &&
			cpuMonke->GetHP() <= cpuMonke->GetMaxHP() / 2)
		{
			cpu.UseHealingItem(cpuMonke);
			battleMessage = "CPU used a healing item";
			playerTurn = true;
			waitingForTurn = true;
			return;
		}


		int dmg = 0;

		
		int choice = rand() % 100;

		
		if (choice < 40)
		{
			dmg = cpuMonke->ElementalAttack(*playerMonke);

			if (dmg > 0)
			{
				battleMessage = "Enemy Monke used elemental attack";
			}
			else
			{
				
				dmg = cpuMonke->NormalAttack();
				playerMonke->TakeDamage(dmg);
				battleMessage = "Enemy Monke attacked";
			}
		}
		else
		{
			dmg = cpuMonke->NormalAttack();
			playerMonke->TakeDamage(dmg);
			battleMessage = "Enemy Monke attacked";
		}

		
		if (playerMonke->IsFainted())
		{
			battleMessage = "You fainted...";
			player.SwitchToNextMonke();

			if (!player.HasRemainingMonkes())
			{
				battleMessage = "YOU LOSE!";
				battleOver = true;
			}


			return; 
		}

	
		playerTurn = true;
		waitingForTurn = true;
		return;
	}
}




void DrawBattle()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);

	Monke* playerMonke = player.GetActiveMonke();
	Monke* cpuMonke = cpu.GetActiveMonke();

	Texture2D playerTex = GetMonkeTexture(playerMonke);
	Texture2D cpuTex = GetMonkeTexture(cpuMonke);

	
	DrawText("PLAYER", 40, 20, 20, BLUE);
	DrawText(playerMonke->GetName().c_str(), 40, 45, 20, BLACK);
	DrawText(TextFormat("HP: %d", playerMonke->GetHP()), 40, 70, 20, DARKGREEN);

	
	DrawText("CPU", 780, 20, 20, RED);
	DrawText(cpuMonke->GetName().c_str(), 700, 45, 20, BLACK);
	DrawText(TextFormat("HP: %d", cpuMonke->GetHP()), 700, 70, 20, MAROON);


	DrawText(TextFormat("Items: %d", player.GetHealingItems()),40, 95, 20, GREEN);

	
	Rectangle playerArea = { 80, 110, 220, 200 };
	Rectangle cpuArea = { 600, 110, 220, 200 };

	
	auto DrawTextureFit = [](Texture2D tex, Rectangle target, bool flip)
		{
			float texRatio = (float)tex.width / tex.height;
			float targetRatio = target.width / target.height;

			Rectangle dest = target;

			if (texRatio > targetRatio)
			{
				dest.height = target.width / texRatio;
				dest.y += (target.height - dest.height) / 2;
			}
			else
			{
				dest.width = target.height * texRatio;
				dest.x += (target.width - dest.width) / 2;
			}

			Rectangle src;
			if (flip)
				src = { (float)tex.width, 0, -(float)tex.width, (float)tex.height };
			else
				src = { 0, 0, (float)tex.width, (float)tex.height };

			DrawTexturePro(tex, src, dest, Vector2{ 0, 0 }, 0.0f, WHITE);
		};

	
	DrawTextureFit(playerTex, playerArea, true);   
	DrawTextureFit(cpuTex, cpuArea, false);       

	
	DrawText("VS", 430, 180, 40, DARKGRAY);

	
	DrawRectangle(150, 330, 600, 70, LIGHTGRAY);
	DrawRectangleLines(150, 330, 600, 70, GRAY);
	DrawText(battleMessage.c_str(), 170, 355, 20, BLACK);

	
	if (!battleOver && !waitingForTurn)
	{
		DrawText("1 - Normal Attack", 40, 430, 20, DARKGRAY);
		DrawText("2 - Elemental Attack", 40, 460, 20, ORANGE);
		DrawText("3 - Heal (+50 HP)", 300, 460, 20, GREEN);
		DrawText("Q - Quit Battle", 600, 460, 20, DARKGRAY);
	}
	else if (battleOver)
	{
		DrawText("Press ENTER to return to menu", 260, 460, 20, DARKBLUE);
	}

	EndDrawing();
}




#endif
