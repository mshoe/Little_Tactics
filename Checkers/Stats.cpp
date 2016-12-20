#include "Stats.h"
#include <iostream>

Stats::Stats() {
	baseATK = 0; baseHP = 0; baseSPD = 0; baseMOV = 0; baseJMP = 0;
	ATK = baseATK; HP = baseHP; SPD = baseSPD; MOV = baseMOV, JMP = baseJMP;

}

Stats::Stats(int hp, int atk, int spd, int mov, int jmp) {
	baseATK = atk; baseHP = hp; baseSPD = spd; baseMOV = mov; baseJMP = jmp;
	ATK = baseATK; HP = baseHP; SPD = baseSPD; MOV = baseMOV; JMP = baseJMP;
}

void Stats::changeStats(int hp, int atk, int spd, int mov, int jmp) {
	HP = hp; ATK = atk; SPD = spd; MOV = mov; JMP = jmp;
}

void Stats::hpLose(int hp) {
	HP -= hp;
}

void Stats::printHP() {
	std::cout << HP << "/" << baseHP << "HP";
}

void Stats::printStats() {
	std::cout << HP << "/" << baseHP << "HP" << std::endl;
	std::cout << ATK << "ATK" << std::endl;
	std::cout << SPD << "SPD" << std::endl;
}

int Stats::getBaseHP()
{
	return baseHP;
}
