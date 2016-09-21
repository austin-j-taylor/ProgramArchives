
using namespace std;

class Player : public Human {
public:
//    Player(pointer/reference to file); // must import data from file: stats, items in bag, equipped weapon/armor
    Player(string, string, short, int, int, int, int, int);
//    int attack(Character*, Item*, Style);
    
    void die(Character*, Effect* effect, string);
    void winGame();
    
    
private:
    
};
Player::Player(string nName, string nIntro, short nGender, int nHp, int nStr, int nDef, int nDex, int nAgil)
    : Human(nName, nIntro, "", nGender, nHp, nStr, nDef, nDex, nAgil) {
}
//int Player::attack(Character* target, Item* weapon, Style style) {
//    return 1;
//}
    
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
