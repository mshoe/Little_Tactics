#pragma once
#include "Classes.h"

class Stats {
public:
	Stats();
	Stats(int hp, int atk, int spd, int mov, int jmp);
	int HP, ATK, SPD;
	int MOV, JMP;
	void changeStats(int hp, int atk, int spd, int mov, int jmp);
	void hpLose(int hp);
	void printHP();
	void printStats();
	int getBaseHP();
private:
	int baseHP, baseATK, baseSPD;
	int baseMOV, baseJMP;
};