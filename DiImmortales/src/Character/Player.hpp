
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

	string name, intro, analyze;
	getline(save, name);
	getline(save, intro);
	getline(save, analyze);

	setName(name);
	setIntro(intro);
	setAnalyze(analyze);
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
