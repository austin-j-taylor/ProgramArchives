
using namespace std;

class Player : public Human {
public:
	Player();
    Player(string, string, short, int, int, int, int, int);
	Player(string fileDir); // load from file
    
    void die(Character*, Effect* effect, string);
    void winGame();
    
    
private:
    
};
Player::Player()
	: Human() {}
Player::Player(string nName, string nIntro, short nGender, int nHp, int nStr, int nDef, int nDex, int nAgil)
    : Human(nName, nIntro, "", nGender, nHp, nStr, nDef, nDex, nAgil) {
}
Player::Player(string fileDir) { // load from file
	ifstream save;
	save.open((fileDir + "stats.txt").c_str(), ios_base::in);

	string name, intro, analyze, gender, hp, maxHp, str, def, dex, agil, hpMod, strMod, defMod, dexMod, agilMod, isBlocking, isParrying;
	getline(save, name);
	getline(save, intro);
	getline(save, analyze);
	getline(save, gender);
	getline(save, hp);
	getline(save, maxHp);
	getline(save, str);
	getline(save, def);
	getline(save, dex);
	getline(save, agil);
	getline(save, hpMod);
	getline(save, strMod);
	getline(save, defMod);
	getline(save, dexMod);
	getline(save, agilMod);
	getline(save, isBlocking);
	getline(save, isParrying);

	setName(name);
	setIntro(intro);
	setAnalyze(analyze);
	setGender(atoi(gender.c_str()));
	setPronouns(atoi(gender.c_str()));

	setHp(atoi(hp.c_str()));
	setMaxHp(atoi(maxHp.c_str()));
	setStr(atoi(str.c_str()));
	setDef(atoi(def.c_str()));
	setDex(atoi(dex.c_str()));
	setAgil(atoi(agil.c_str()));
	setHpMod(atoi(hpMod.c_str())); // hpmod
	setStrMod(atoi(strMod.c_str())); // strmod
	setDefMod(atoi(defMod.c_str())); // defmod
	setDexMod(atoi(dexMod.c_str())); // dexmod
	setAgilMod(atoi(agilMod.c_str())); // agilmod
	setIsBlocking(atoi(isBlocking.c_str())); // isblocking
	setIsParrying(atoi(isParrying.c_str())); // isparrying
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
