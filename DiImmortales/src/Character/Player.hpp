
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
Player::Player(ifstream& file, string fileDir) { // import data from file: stats, items in bag, equipped weapon/armor
	// atoi() and c_str() functions are used to convert from string to int/double/whatever
	string bs; // bufferString
	string name, intro, analyze;
	short gender;
	int hp, maxHp, str, def, dex, agil, hpMod, strMod, defMod, dexMod, agilMod;
	bool isBlocking, isParrying;

	vector<string> vals;
	while(getline(file, bs))
		vals.push_back(bs);

	file.close();

//  assignment to locals

//	name = vals.at(0);
//	intro = vals.at(1);
//	analyze = vals.at(2);
//	gender = atoi(vals.at(3).c_str());
//	hp = atoi(vals.at(4).c_str());
//	maxHp = atoi(vals.at(5).c_str());
//	str = atoi(vals.at(6).c_str());
//	def = atoi(vals.at(7).c_str());
//	dex = atoi(vals.at(8).c_str());
//	agil = atoi(vals.at(9).c_str());
//	hpMod = atoi(vals.at(10).c_str());
//	strMod = atoi(vals.at(11).c_str());
//	defMod = atoi(vals.at(12).c_str());
//	dexMod = atoi(vals.at(13).c_str());
//	agilMod = atoi(vals.at(14).c_str());
//	isBlocking = atoi(vals.at(15).c_str());
//	isParrying = atoi(vals.at(16).c_str());
	println("predicted values:");
	for(string si : vals)
		println(si);
	println();

//	assignment to stats

//	setName(name); // name
//	setIntro(intro); // intro
//	setAnalyze(analyze); // analyze
//	setGender(gender); // gender
//	setPronouns(gender); // pronouns
//
//	setHp(atoi(vals.at(4).c_str())); // hp
//	setMaxHp(atoi(vals.at(5).c_str())); // maxHp
//	setStr(atoi(vals.at(6).c_str())); // str
//	setDef(atoi(vals.at(7).c_str())); // def
//	setDex(atoi(vals.at(8).c_str())); // dex
//	setAgil(atoi(vals.at(9).c_str())); // agil
//	setHpMod(atoi(vals.at(10).c_str())); // hpmod
//	setStrMod(atoi(vals.at(11).c_str())); // strmod
//	setDefMod(atoi(vals.at(12).c_str())); // defmod
//	setDexMod(atoi(vals.at(13).c_str())); // dexmod
//	setAgilMod(atoi(vals.at(14).c_str())); // agilmod
//	setIsBlocking(atoi(vals.at(15).c_str())); // isblocking
//	setIsParrying(atoi(vals.at(16).c_str())); // isparrying

	println("actual values:");

	println(getName());
	println(getIntro());
	println(getAnalyze());
	println(tostring(getHp()));
	println(tostring(getMaxHp()));
	println(tostring(getStr()));
	println(tostring(getDef()));
	println(tostring(getDex()));
	println(tostring(getAgil()));
	println(tostring(getHpMod()));
	println(tostring(getStrMod()));
	println(tostring(getDefMod()));
	println(tostring(getDexMod()));
	println(tostring(getAgilMod()));
	println(tostring(getIsBlocking()));
	println();
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
