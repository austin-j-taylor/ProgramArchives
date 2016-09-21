
#include "Headers.hpp"

using namespace std;

// ~~~~~~~~~~~~~~~~TODO~~~~~~~~~~~~~~~~~
/*
// ESSENTIALS
 *
 *
// HIGH-PRIORITY
 *
 *
 * finish usages functions for Character and Item, consumables
 * finish Effect system
	 * change Stunned effect in attack() to have potency based on affBlock or something
	 * have there be differed verbs for effects (artemis BLED to death, artemis took 3 damage from BLEEDING, etc)
	 * print details of effects in Analyze
 * chance- and affinity-based Block and Parry
 *
 * main many/game over - some semblance of a plot
 *
// PRIORITY
 * create armor integration; integrate its stats into attacks
 * have different death quotes: "name bled to death" "name died from poison"
 *
// LONG TERM
 * create main screen, game over screen
 * 		have data be written to a file when saved
 * 		have data be loaded from a file onto a Player
 * 		create OptionField for option functions (quit, view stats, etc)
 *
 * delete pointers when done with them
 *
 */


int main() {

	MainMenu::printLogo1();

    Player* player = new Player("Diana", "playermessage", 1, 70, 10, 10, 10, 15);
    Bourgeoisie* foe1 = new Bourgeoisie("Hades", "An angry old Lord of the Underworld crawled up from below.");
    Bourgeoisie* foe2 = new Bourgeoisie("Apollo", "Diana's angsty twin brother appeared.");
    Bourgeoisie* foe3 = new Bourgeoisie("Adam Smith", "Adam Smith, author of \"The Wealth of Nations,\" arose as well.");

    //creates and adds initial test items to bag
    Dagger* bd1 = new Dagger(Bronze(), "hunting knife", 3, "a long, sharp knife used for carving animal hide. Useful for throwing.", false);
    Dagger* bd2 = new Dagger(Bronze(), "Communi-cutter", 3, "A bronze, anti-socialist device.", false);
    Dagger* bd3 = new Dagger(Steel());
    Longsword* ls1 = new Longsword(Steel());
    Longsword* ls2 = new Longsword(Steel());
    Buckler* bw = new Buckler(Wooden());
    Rock* rock = new Rock();
//    bd1->setArticle(1);
    player->putInBag(bd1);
    player->putInBag(bd3);
    player->putInBag(ls1);
    player->putInBag(bw);
	player->putInBag(rock);
    player->equip(bd1, false);
    player->equip(bw, false);
    foe2->equip(bd2, false);
    foe3->equip(ls2, false);
    CombatField combatfield = CombatField(player);
    vector<Character*> foes { foe1, foe2, foe3 };
    combatfield.startCombat(foes);
    
    
    return 0;
}
