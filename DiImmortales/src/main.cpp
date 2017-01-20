
#include "Headers.hpp"

using namespace std;

// ~~~~~~~~~~~~~~~~TODO~~~~~~~~~~~~~~~~~
/*
// ESSENTIALS
 *
 *
// HIGH-PRIORITY
 *
 * create numberical ID system for items. This way, they can be saved and re-initialized from save files.
 * allow stats within character creation
 * save effects with items
 *
 * finish usages functions for Character and Item, consumables
 * make all-encompassing effect that induces an instant change to a STAT that decays over TIME to be used by consumables, etc.
 * 		-takes the Stat enum as an argument?
 * finish Effect system
	 * change Stunned effect in attack() to have potency based on affBlock or something
	 * have there be differed verbs for effects (artemis BLED to death, artemis took 3 damage from BLEEDING, etc)
	 * print details of effects in Analyze
 * chance- and affinity-based Block and Parry
 *
// PRIORITY
 * create armor integration; integrate its stats into attacks
 * have different death quotes: "name bled to death" "name died from poison"
 *
// LONG TERM
 * delete pointers when done with them ♥
 *
 */


int main() {


    start:
    Menu::printLogo1();
    int choice;
    vector<string> choices = {};

    Bourgeoisie* foe1 = new Bourgeoisie("Hades", "An angry old Lord of the Underworld crawled up from below.");
    Bourgeoisie* foe2 = new Bourgeoisie("Apollo (the Greek one)", "Artemis's angsty twin brother appeared.");
    Bourgeoisie* foe3 = new Bourgeoisie("Adam Smith", "Adam Smith, author of \"The Wealth of Nations,\" arose as well.");
    Dagger* bd2 = new Dagger(Bronze(), "Communi-cutter", 3, "A bronze, anti-socialist device.", false);
    Longsword* ls2 = new Longsword(Steel());
    foe2->equip(bd2, false);
    foe3->equip(ls2, false);
    vector<Character*> foes { foe1, foe2, foe3 };
    vector<Item*> items { bd2, ls2 };

    Player* player = new Player();
	choices = { "Start New Game", "Load File", "Delete File" };
	choice = Field::choice(choices, "", false);
	switch(choice) {
		case 0: { // new character
			entername:
			string name = Field::choice("Enter a name.");
			// checks to see if file already exists
			ifstream savesIndex;
			string str;
			savesIndex.open("fileData/savesIndex.txt");
			while(getline(savesIndex, str)) {
				if(str == name) {
					println("Name already in use.");
					goto entername;
					savesIndex.close();
				}
			}
			savesIndex.close();

			// name is a valid name; now create save file
			string intro = "\"" + Field::choice("Enter an introduction for your character.") + "\"";
			string analyze = Field::choice("How do you describe yourself?");
			vector<string> genders = { "Male", "Female", "mmmm nah, nah" };
			int gender = Field::choice(genders, "Gender?", false);

			player = new Player(name, intro, analyze, gender, 70, 10, 10, 10, 15); // temporary default values
			// save file to disk
			Menu::createFile(player);

			break;
		}
		case 1: { // load character
			// loads names of saves
			ifstream savesIndex;
			string str;
			savesIndex.open("fileData/savesIndex.txt");
			vector<string> saveNames;
			while(getline(savesIndex, str)) {
				saveNames.push_back(str);
			}
			// selects save
			int saveNameChoice = Field::choice(saveNames, "Select Character Name", true);
			if(saveNameChoice == -2) { // back
				savesIndex.close();
				goto start;
			}
			string fileDir = "fileData/saves/" + saveNames.at(saveNameChoice) + "/";
			savesIndex.close();
			player = new Player(fileDir);

			break;
		}
		default: {
			// delete file

			// loads names of saves
			fstream savesIndex;
			string str;
			savesIndex.open("fileData/savesIndex.txt");
			vector<string> saveNames;
			while(getline(savesIndex, str))
				saveNames.push_back(str);

			// selects save
			int saveNameChoice = Field::choice(saveNames, "Select Character Name", true);
			if(saveNameChoice == -2) { // back
				savesIndex.close();
				goto start;
			}
			string characterName = saveNames.at(saveNameChoice);
			// verifies
			choices = { "YES", "NO" };
			int choice = Field::choice(choices, "Really delete file?", false);
			if(choice == 1)
				return -2;
			// deletes selected save
			ofstream names;
			names.open("fileData/savesIndex.txt", ios::trunc);
			saveNames.erase(find(saveNames.begin(), saveNames.end(), characterName));
			for(unsigned int i = 0; i < saveNames.size(); i++) {
				names.write(saveNames.at(i).c_str(), saveNames.at(i).size());
				if(i < saveNames.size() - 1)
					names.write("\n", 1);
			}

			remove(("fileData/saves/" + characterName + "/stats.txt").c_str());
			remove(("fileData/saves/" + characterName + "/arms.txt").c_str());
			remove(("fileData/saves/" + characterName + "/bag.txt").c_str());
			RemoveDirectory(("fileData\\saves\\" + characterName + "\\").c_str());

			savesIndex.close();
			println("File deleted.");
			goto start;
		}
	}

	Apple* app = new Apple();
	player->getBag()->addItem(app);

	CombatField combatfield = CombatField(player);
    int playAgain = combatfield.startCombat(foes);
    if(playAgain == -3) {
    	for(Character* foe : foes)
    		delete foe;
    	for(Item* item : items)
    		delete item;
    	delete player;
    	goto start;
    }
    
    return 0;
}
