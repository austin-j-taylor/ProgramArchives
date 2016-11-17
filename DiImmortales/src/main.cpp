
#include "Headers.hpp"


// ~~~~~~~~~~~~~~~~TODO~~~~~~~~~~~~~~~~~
/*
// ESSENTIALS
 * main menu/save/load system
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
 * ~magic~
 */
using namespace std;

int main() {
	string pas = "0.01";
	double square = atof(pas.c_str()) + .0002;
	println(tostring(square));

	Player* player;

	Menu::printLogo1();

	start:
	int choice = Field::choice(vector<string> { "Start New Game", "Load File", "what;s up everybidy it's critikal" }, "", false);
	ifstream saveFile;
	switch(choice) {
		case 0: {
			string name = Field::choice("Enter a name.");
			//save file

		    player = new Player(name, "playermessage", 1, 70, 10, 10, 10, 15); // temporary default values
			break;
		}
		case 1: {
			string fileDir = Menu::loadFile(saveFile);
			if(fileDir == "") // loads file
				goto start;
			player = new Player(saveFile, fileDir);
			break;
		}
		case 2: {
			//testing
			player = nullptr;
			break;
		}
		default: {
			println("Error in player creation");
		    player = nullptr; // let's hope this never happens
		}
	}
	println("burg");
    Bourgeoisie* foe1 = new Bourgeoisie("Hades", "An angry old Lord of the Underworld crawled up from below.");
    println("YEY");
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
    println("here..");
    CombatField combatfield = CombatField(player);
    vector<Character*> foes { foe1, foe2, foe3 };
    combatfield.startCombat(foes);

    
    return 0;
}
