#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

class Pokemon
{
public:
	Pokemon(int type, string name, int weight,int HP, int Attack, 
		    int Defense, int AttackGap, string moveName);
	~Pokemon(){}
	void setType(int type) {
		this->type = type;
	}
	void setName(string name) {
		this->name = name;
	}
	void setWeight(int weight) {
		this->weight = weight;
	}
	void setLevel(int level) {
		this->level = level;
	}
	void setExp(int Exp) {
		this->Exp = Exp;
	}
	void setHP(int HP) {
		this->HP = HP;
	}
	void setCurrentHP(int HP) {
		this->currentHP = HP;
	}
	void setAttack(int Attack) {
		this->Attack = Attack;
	}
	void setDefense(int Defense) {
		this->Defense = Defense;
	}
	void setAttackGap(int AttackGap) {
		this->AttackGap = AttackGap;
	}
	void setMoveName(string moveName) {
		this->moveName = moveName;
	}
	int getType() {
		return type;
	}
	string getName() {
		return name;
	}
	int getWeight() {
		return weight;
	}
	int getLevel() {
		return level;
	}
	int getExp() {
		return Exp;
	}
	int getHP(int HP) {
		return HP;
	}
	int getAttack() {
		return Attack;
	}
	int getDefense() {
		return Defense;
	}
	int getHP() {
		return HP;
	}
	int getCurrentHP() {
		return currentHP;
	}
	int getAttackGap() {
		return AttackGap; 
	}
	int getAbility() {
		return Ability = HP + Attack + Defense;
	}
	string getMoveName() {
		return moveName;
	}
	void display() {
		cout << "Your " << name << " current state:" << endl
			<< "Level: " << getLevel() << endl
			<< "Exp: " << getExp() << endl
			<< "HP: " << getCurrentHP() << endl;
	}
	void damage(int damage) {
		currentHP -= damage * damage / (damage + getDefense());
		if (currentHP < 0)
			currentHP = 0;
	}
	void addExp(int Exp) {
		this->Exp += Exp;
	}
	void upgrade() {
		int i, p, s;
		for (i = 1, p = 200, s = 0; s < getExp(); p += 10)
			s += p;
		if (i > getLevel()) {//if upgrate then propertyVal += levelVal
			setLevel(i);
			setHP(getHP() + i);
			setAttack(getAttack() + i);
			setDefense(getDefense() + i);
		}
	}
	virtual int move(Pokemon opponent);

private:
	int type;
	string name;
	int weight;
	int level; // initial = 1, top = 15;
	int Exp; // initial = 0;
	int HP;
	int currentHP;
	int Attack;
	int Defense;
	int AttackGap;
	int Ability;//ablility = HP + Attack + Defense
	string moveName;
};

Pokemon::Pokemon(int type, string name, int weight, int HP, int Attack, 
	             int Defense, int AttackGap, string moveName)
{
	setType(type);
	setName(name);
	setWeight(weight);
	setLevel(1);
	setExp(0);
	setHP(HP);
	setCurrentHP(HP);
	setAttack(Attack);
	setDefense(Defense);
	setAttackGap(AttackGap);
	setMoveName(moveName);
}

int Pokemon::move(Pokemon opponent) {
	/*  GENERAL DAMAGE OF ATTACK 
	 *  damage = Attack * Attack / (Defense of your opponent + Attack)
	 */
	return Attack * Attack / (opponent.getDefense() + Attack);
}

class Primeape : public Pokemon //1
{
public:
	Primeape() : Pokemon(1, "Primeape", 32, 65, 105, 60, 6, "Low Kick"){}
	~Primeape(){}
	int move(Pokemon opponent) {//return the Hit to opponent
		//setMoveName("Low Kick");
		if (opponent.getWeight() < 10)
			return 20;
		else if (opponent.getWeight() < 25)
			return 40;
		else if (opponent.getWeight() < 50)
			return 60;
		else if (opponent.getWeight() < 100)
			return 80;
		else
			return 100;
	}

};
class Heracross : public Pokemon //2
{
public:
	Heracross() : Pokemon(1, "Heracross", 54, 80, 125, 75, 8, "Fury Attack"){}
	~Heracross(){}
	int move(Pokemon opponent) {
		//setMoveName("Fury Attack");
		srand((unsigned)time(NULL));
		return (rand() % 6 + 5) / 10 * getAttack();
	}
};
class Hitmonlee : public Pokemon //3
{
public:
	Hitmonlee() : Pokemon(1, "Hitmonlee", 50, 50, 120, 53, 8, "Reversal"){}
	~Hitmonlee(){}
	int move(Pokemon opponent) {
		//setMoveName("Reversal");
		int curHP = 64 * getCurrentHP() / getHP();
		if (curHP < 2)
			return 200;
		else if (curHP < 6)
			return 150;
		else if (curHP < 13)
			return 100;
		else if (curHP < 22)
			return 80;
		else if (curHP < 43)
			return 40;
		else return 20;
	}
};

class Chansey : public Pokemon //4
{
public:
	Chansey() : Pokemon(2, "Chansey", 35, 250, 5, 5, 10, "Egg Bomb"){}
	~Chansey(){}
	int move(Pokemon opponent) {
		//setMoveName("Egg Bomb");
		return 10;
	}
};
class Blissey : public Pokemon //5
{
public:
	Blissey() : Pokemon(2, "Blissey", 47, 255, 10, 10, 10, "Double Slap"){}
	~Blissey(){}
	int move(Pokemon opponent) {
		//setMoveName("Double Slap");
		srand((unsigned)time(NULL));
		int attackTime = rand() % 2 + 1;
		return attackTime * getAttack();
	}
};
class Wobbuffet : public Pokemon //6
{
public:
	Wobbuffet() : Pokemon(2, "Wobbuffet", 29, 190, 33, 58, 13, "Charm") {}
	~Wobbuffet(){}
	int move(Pokemon opponent) {
		//setMoveName("Charm");
		return 10;// HP += 10
	}
};

class Shuckle : public Pokemon //7
{
public:
	Shuckle() : Pokemon(3, "Shuckle", 20, 30, 10, 230, 15, "Rock Throw") {}
	~Shuckle(){}
	int move(Pokemon opponent) {
		//setMoveName("Rock Throw");
		return 15;
	}
};
class Steelix : public Pokemon //8
{
public:
	Steelix() : Pokemon(3, "Steelix", 400, 75, 85, 200, 13, "Harden"){}
	~Steelix(){}
	int move(Pokemon opponent) {
		//setMoveName("Harden");//Defense++
		return getAttack();
	}
};
class Aggron : public Pokemon //9
{
public:
	Aggron() : Pokemon(3, "Aggron", 360, 70, 110, 180, 10, "Tackle"){}
	~Aggron(){}
	int move(Pokemon opponent) {
		//setMoveName("Tackle");
		return (int)(getAttack() * 0.9);
	}
};

class Accelgor : public Pokemon //10
{
public:
	Accelgor() : Pokemon(4, "Accelgor", 25, 80, 70, 40, 3, "Toxic"){}
	~Accelgor(){}
	int move(Pokemon opponent) {
		//setMoveName("Toxic");
		return getAttack() * 2;
	}
};
class Ninjask : public Pokemon //11
{
public:
	Ninjask() : Pokemon(4, "Ninjask", 12, 61, 90, 45, 2, "Hidden Power"){}
	~Ninjask(){}
	int move(Pokemon opponent) {
		//setMoveName("Hidden Power");
		srand((unsigned)time(NULL));
		return getAttack() + rand() % 21;
	}
};
class Deoxys : public Pokemon //12
{
public:
	Deoxys() : Pokemon(4, "Deoxys", 60, 50, 150, 50, 3, "Flash Cannon"){}
	~Deoxys(){}
	int move(Pokemon opponent) {
		//setMoveName("Flash Cannon");
		return getAttack() + 10;
	}
};