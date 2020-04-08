#include <iostream>
#include "Pokemon.h"
using namespace std;
int main() {
	//int choice;
	//cout << "Please choose your Pok¨¦mon from 1 to 12: ";
	//cin >> choice;
	cout << "TestProgramme:" << endl << '\t'
		 << "We choose Primeape and Aggron as test objects" << endl;
	Primeape Player; // as Player
	Aggron System; // as System
	//Player.display();
	//System.display();

	bool PlayerCanAttack = true;
	bool SystemCanAttack = true;
	int PlayerDamage;
	int SystemDamage;
	clock_t PlayerStart, PlayerCheck;
	clock_t SystemStart, SystemCheck;
	int PlayerHitSystem, SystemHitPlayer;
	while (Player.getCurrentHP() > 0 && System.getCurrentHP() > 0) {
		if (PlayerCanAttack) {
			PlayerStart = clock();
			PlayerHitSystem = Player.move(System);
			Player.display();
			cout << "Player's move: " << Player.getMoveName() << endl << endl;
			PlayerCanAttack = false;

			if (Player.getMoveName() == "Charm")
				Player.setCurrentHP(Player.getCurrentHP() + 10);
			else if (Player.getMoveName() == "Harden")
				Player.setDefense(Player.getDefense() + 1);
			else
				System.damage(PlayerHitSystem);
			cout << "SystemCurrentHP = " << System.getCurrentHP() << endl << endl;
			//cout << "PlayerHitSystem = " << PlayerHitSystem << endl;
		}
		if (SystemCanAttack) {
			SystemStart = clock();
			SystemHitPlayer = System.move(Player);
			System.display();
			cout << "System's move: " << System.getMoveName() << endl << endl;
			SystemCanAttack = false;

			if (System.getMoveName() == "Charm")
				System.setCurrentHP(System.getCurrentHP() + 10);
			else if (System.getMoveName() == "Harden")
				System.setDefense(System.getDefense() + 1);
			else
				Player.damage(SystemHitPlayer);
		}

		PlayerCheck = clock();
		if ((PlayerCheck - PlayerStart) / CLOCKS_PER_SEC > Player.getAttackGap())
			PlayerCanAttack = true;
		//cout << (PlayerCheck - PlayerStart) / CLOCKS_PER_SEC << endl;
		SystemCheck = clock();
		if ((SystemCheck - SystemStart) / CLOCKS_PER_SEC > System.getAttackGap())
			SystemCanAttack = true;
		//cout << (SystemCheck - SystemStart) / CLOCKS_PER_SEC << endl;
		//Player.display();
	}
	if (Player.getCurrentHP()) { // player won
		cout << endl << "Player won!" << endl;
		Player.addExp(System.getAbility());
		Player.upgrade();
	}
	else {
		cout << endl << "Player failed!" << endl;
		System.addExp(Player.getAbility());
		System.upgrade();
	}
	system("pause");
	return 0;
 }