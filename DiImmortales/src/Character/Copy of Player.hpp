
using namespace std;

class Player : public Human {
public:
    Player(string, string, short, int, int, int, int, int);
	Player(ifstream& file, string fileDir);
    
    void die(Character*, Effect* effect, string);
    void winGame();
    
    
private:
    
};
Player::Player(string nName, string nIntro, short nGender, int nHp, int nStr, int nDef, int nDex, int nAgil)
    : Human(nName, nIntro, "", nGender, nHp, nStr, nDef, nDex, nAgil) {
}
Player::Player(ifstream& file, string fileDir) : Human() { // import data from file: stats, items in bag, equipped weapon/armor
	// atoi() and c_str() functions are used to convert from string to int/double/whatever
	string bs; // bufferString
	string name, intro, analyze;
	short gender;
	int hp, maxHp, str, def, dex, agil, hpMod, strMod, defMod, dexMod, agilMod;
	bool isBlocking, isParrying;

	getline(file, bs);
	name = bs;
	println(bs);
	getline(file, bs);
	intro = bs;
	println(bs);
	getline(file, bs);
	analyze = bs;
	println(bs);
	getline(file, bs);
	gender = atoi(bs.c_str());
	println(bs);
	getline(file, bs);
	hp = atoi(bs.c_str());
	println(bs);
	getline(file, bs);
	maxHp = atoi(bs.c_str());
	println(bs);
	getline(file, bs);
	str = atoi(bs.c_str());
	println(bs);
	getline(file, bs);
	def = atoi(bs.c_str());
	println(bs);
//	getline(file, bs);
//	dex = atoi(bs.c_str());
//	println(bs);
//	getline(file, bs);
//	agil = atoi(bs.c_str());
//	println(bs);
//	getline(file, bs);
//	hpMod = atoi(bs.c_str());
//	println(bs);
//	getline(file, bs);
//	strMod = atoi(bs.c_str());
//	println(bs);
//	getline(file, bs);
//	defMod = atoi(bs.c_str());
//	println(bs);
//	getline(file, bs);
//	dexMod = atoi(bs.c_str());
//	println(bs);
//	getline(file, bs);
//	agilMod = atoi(bs.c_str());
//	println(bs);
//	getline(file, bs);
//	isBlocking = atoi(bs.c_str());
//	println(bs);
//	getline(file, bs);
//	isParrying = atoi(bs.c_str());
//	println(bs);
	println();

	println("setting");

	setName(name); // name
	setIntro(intro); // intro
	setAnalyze(analyze); // analyze
	setGender(gender); // gender
	setPronouns(gender); // pronouns
//
	setHp(hp); // hp
	setMaxHp(maxHp); // maxHp
	setDef(43); // def
	setStr(54); // str
//	setDex(dex); // dex
//	setAgil(agil); // agil
//	setHpMod(hpMod); // hpmod
//	setStrMod(strMod); // strmod
//	setDefMod(defMod); // defmod
//	setDexMod(dexMod); // dexmod
//	setAgilMod(agilMod); // agilmod
//	setIsBlocking(isBlocking); // isblocking
//	setIsParrying(isParrying); // isparrying

	println("printing actualys");

	println(getName());
	println(getIntro());
	println(getAnalyze());
	println(tostring(getHp()));
	println(tostring(getMaxHp()));
	println(tostring(getStr()));
	println(tostring(getDef()));
//	println(tostring(getDex()));
//	println(tostring(getAgil()));
//	println(tostring(getHpMod()));
//	println(tostring(getStrMod()));
//	println(tostring(getDefMod()));
//	println(tostring(getDexMod()));
//	println(tostring(getAgilMod()));
//	println(tostring(getIsBlocking()));
	//..open file to directory with bag.txt, etc.
}

void Player::die(Character* enemy = nullptr, Effect* effect = nullptr, string message = "") {
	Character::die(enemy, effect, message);

    println("GAME OVER");
    println("Press [Enter] to close the game.");
    cin.sync(); // awaits keypress
    cin.get();
    exit(0); // replace with game over screen later
}
void Player::winGame() {
    println("You conquered capitalism!");
    println("Press [Enter] to end the game.");
    println("Thanks for playing this game. Please like, comment, and subscribe if you want to see more games like this in the future.");
    cin.sync();
    cin.get();
    exit(0); // replace with game over screen later
}
