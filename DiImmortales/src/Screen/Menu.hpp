
class Menu {
public:
	static void printLogo1();
//	static string loadFile(ifstream&);
	static void createFile(Character*);
	static void writeToFile(Item*, ofstream*);
	static void overriteSaveArms(Character*, ofstream*);
	static void overriteSaveBag(Character*, ofstream*);
	static void overriteSaveStats(Character*, ofstream*);
    static vector<Item*> parseItems(string);
};
void Menu::printLogo1() {
	println(string(windowWidth, '-'));
	println("");
	println("                                          @@@@@@@    @@");
	println("                                          @@;;:+@@.  @@");
	println("                                          @@     @@  @@");
	println("                                          @@     @@  @@");
	println("                                          @@     @@  @@");
	println("                                          @@     @@  @@");
	println("                                          @@    .@@  @@");
	println("                                          @@@@@@@@   @@");
	println("                                          @@@@@#,    @@");
	println("");
	println("");
	println("");
	println("  ##: ###     ### +###    ###`   `#@@:    ##++++;   ++++++++    ###    :##      `##+++++#   ;@@+");
	println("  @@  +@@     @@;  @@@    @@@   @@@@@@@   @@@@@@@@, @@@@@@@@    @@@     @@       @@@@@@@@  @@@@@@@");
	println("  @@  +@@@   @@@;  @@@   `@@@  @@;    @@  @@     @@    @@       @@@     @@       @@       ,@     @");
	println("  @@  +@@@  `@:@;  @@@@  @@@@  @@     '@. @@     @@    @@      @@ @@    @@       @@       ,@@.");
	println("  @@  +@ @@ @@`@;  @@@@ :@ @@  @#      @' @@@@@@@@.    @@      @' @@    @@       @@@@@@    @@@@@@;");
	println("  @@  +@ @@;@ `@;  @# @@@@ @@  @@     ,@; @@;;+@#      @@     @@```@@   @@       @@          :'@@@");
	println("  @@  +@  @@@ `@;  @+ @@@  @@  @@     @@  @@   @@      @@     @@@@@@@   @@       @@        `    .@.");
	println("  @@  +@  +@  `@;  @+  @@  @@   @@: .@@+  @@    @@     @@    @@     @@  @@.....+ @@....., ;@@. :@@");
	println("  @@  #@   #  .@'  @#  +   @@    @@@@@,   @@    :@@    @@    @@     @@` @@@@@@@@ @@@@@@@@  ;@@@@@");
	println(string(windowWidth, '-'));
}
void Menu::createFile(Character* player) {
	// puts player name in save index
	ofstream savesIndex;
	savesIndex.open("fileData/savesIndex.txt", ofstream::app);
	savesIndex << "\n" << player->getName();
	// creates folder for player files
	CreateDirectory(("fileData\\saves\\" + player->getName() + "\\").c_str(), NULL);

	ofstream stats;
	stats.open(("fileData/saves/" + player->getName() + "/stats.txt").c_str());
	overriteSaveStats(player, &stats);
	stats.close();

	ofstream arms;
	arms.open(("fileData/saves/" + player->getName() + "/arms.txt").c_str());
	overriteSaveArms(player, &arms);
	arms.close();

	ofstream bag;
	bag.open(("fileData/saves/" + player->getName() + "/bag.txt").c_str());
	overriteSaveBag(player, &bag);
	bag.close();

	savesIndex.close();
}
void Menu::overriteSaveStats(Character* player, ofstream* file) {
	//assuming file is open
	file->write((player->getName() + "\n").c_str(), player->getName().size() + 1);
	file->write((player->getIntro() + "\n").c_str(), player->getIntro().size() + 1);
	file->write((player->getAnalyze() + "\n").c_str(), player->getAnalyze().size() + 1);

	file->write((tostring(player->getGender()) + "\n").c_str(), tostring(player->getGender()).size() + 1);
	file->write((tostring(player->getHp()) + "\n").c_str(), tostring(player->getHp()).size() + 1);
	file->write((tostring(player->getMaxHp()) + "\n").c_str(), tostring(player->getMaxHp()).size() + 1);
	file->write((tostring(player->getStr()) + "\n").c_str(), tostring(player->getStr()).size() + 1);
	file->write((tostring(player->getDef()) + "\n").c_str(), tostring(player->getDef()).size() + 1);
	file->write((tostring(player->getDex()) + "\n").c_str(), tostring(player->getDex()).size() + 1);
	file->write((tostring(player->getAgil()) + "\n").c_str(), tostring(player->getAgil()).size() + 1);
	file->write((tostring(player->getHpMod()) + "\n").c_str(), tostring(player->getHpMod()).size() + 1);
	file->write((tostring(player->getStrMod()) + "\n").c_str(), tostring(player->getStrMod()).size() + 1);
	file->write((tostring(player->getDefMod()) + "\n").c_str(), tostring(player->getDefMod()).size() + 1);
	file->write((tostring(player->getDexMod()) + "\n").c_str(), tostring(player->getDexMod()).size() + 1);
	file->write((tostring(player->getAgilMod()) + "\n").c_str(), tostring(player->getAgilMod()).size() + 1);
	file->write((player->getIsBlocking()) ? ("1") : ("0"), 1);
}
void Menu::overriteSaveArms(Character* player, ofstream* file) {
	Item* item;
	for(int i = 0; i < player->getEquippedArms()->getSize(); i++) {
		item = player->getEquippedArms()->itemAt(i);
		if(item != player->getEHE()) {
			writeToFile(item, file);
		}
	}
	//indicates end of file
	file->write("end", 3);
}
void Menu::overriteSaveBag(Character* player, ofstream* file) {
	Item* item;
	for(int i = 0; i < player->getBag()->getSize(); i++){
		item = player->getBag()->itemAt(i);
		writeToFile(item, file);
		if(i < player->getBag()->getSize() - 1)
			file->write("-------", 7);
	}
	//indicates end of file
	file->write("end", 3);
}
void Menu::writeToFile(Item* item, ofstream* file) {
	file->write("\n", 1);
	file->write((tostring(item->ID) + "\n").c_str(), tostring(item->ID).size() + 1);
	file->write((tostring(item->getMaterial().ID) + "\n").c_str(), tostring(item->getMaterial().ID).size() + 1);
	file->write(item->getUsesMaterialName() ? ("1") : ("0"), 1);
	file->write("\n", 1);
	file->write(item->getHasSpecialExamine() ? ("1") : ("0"), 1);
	file->write("\n", 1);
	if(item->getHasSpecialExamine())
		file->write((item->getExamineText() + "\n").c_str(), item->getExamineText().size() + 1);
	else
		file->write("\n", 1);
	file->write(item->getHasSpecialName() ? ("1") : ("0"), 1);
	file->write("\n", 1);
	if(item->getHasSpecialName())
		file->write((item->getName() + "\n").c_str(), item->getName().size() + 1);
	else
		file->write("\n", 1);

	bool currentSpecialAffinity;
	// writes special affinities of weapon to file; if the weapon doesn't have a special affinity for that style, the line for the affinity is empty.
	currentSpecialAffinity = item->getHasSpecialSlash();
	file->write(currentSpecialAffinity ? ("1") : ("0"), 1);
	file->write("\n", 1);
	if(currentSpecialAffinity)
		file->write((tostring(item->getAffinity(Styles::Slash)) + "\n").c_str(), tostring(item->getAffinity(Styles::Slash)).size() + 1);
	else
		file->write("\n", 1);
	currentSpecialAffinity = item->getHasSpecialCrush();
	file->write(currentSpecialAffinity ? ("1") : ("0"), 1);
	file->write("\n", 1);
	if(currentSpecialAffinity)
		file->write((tostring(item->getAffinity(Styles::Crush)) + "\n").c_str(), tostring(item->getAffinity(Styles::Crush)).size() + 1);
	else
		file->write("\n", 1);
	currentSpecialAffinity = item->getHasSpecialStab();
	file->write(currentSpecialAffinity ? ("1") : ("0"), 1);
	file->write("\n", 1);
	if(currentSpecialAffinity)
		file->write((tostring(item->getAffinity(Styles::Stab)) + "\n").c_str(), tostring(item->getAffinity(Styles::Stab)).size() + 1);
	else
		file->write("\n", 1);
	currentSpecialAffinity = item->getHasSpecialBlock();
	file->write(currentSpecialAffinity ? ("1") : ("0"), 1);
	file->write("\n", 1);
	if(currentSpecialAffinity)
		file->write((tostring(item->getAffinity(Styles::Block)) + "\n").c_str(), tostring(item->getAffinity(Styles::Block)).size() + 1);
	else
		file->write("\n", 1);
	currentSpecialAffinity = item->getHasSpecialBash();
	file->write(currentSpecialAffinity ? ("1") : ("0"), 1);
	file->write("\n", 1);
	if(currentSpecialAffinity)
		file->write((tostring(item->getAffinity(Styles::Bash)) + "\n").c_str(), tostring(item->getAffinity(Styles::Bash)).size() + 1);
	else
		file->write("\n", 1);
	currentSpecialAffinity = item->getHasSpecialParry();
	file->write(currentSpecialAffinity ? ("1") : ("0"), 1);
	file->write("\n", 1);
	if(currentSpecialAffinity)
		file->write((tostring(item->getAffinity(Styles::Parry)) + "\n").c_str(), tostring(item->getAffinity(Styles::Parry)).size() + 1);
	else
		file->write("\n", 1);
	currentSpecialAffinity = item->getHasSpecialHurl();
	file->write(currentSpecialAffinity ? ("1") : ("0"), 1);
	file->write("\n", 1);
	if(currentSpecialAffinity)
		file->write((tostring(item->getAffinity(Styles::Hurl)) + "\n").c_str(), tostring(item->getAffinity(Styles::Hurl)).size() + 1);
	else
		file->write("\n", 1);
	currentSpecialAffinity = item->getHasSpecialWeight();
	file->write(currentSpecialAffinity ? ("1") : ("0"), 1);
	file->write("\n", 1);
	if(currentSpecialAffinity)
		file->write((tostring(item->getWeight()) + "\n").c_str(), tostring(item->getWeight()).size() + 1);
	else
		file->write("\n", 1);
	//end of item in file

}
vector<Item*> Menu::parseItems(string fileDir) {
	ifstream file;
	vector<Item*> items = {};
	file.open(fileDir.c_str(), ios_base::in);
	string confirm, ID, matID, usesMatInName, hasSpecialExamine, specialExamine, hasSpecialName, specialName,
			specialSlash, slash, specialCrush, crush, specialStab, stab, specialBlock, block, specialBash, bash, specialParry, parry,
			specialHurl, hurl, specialWeight, weight;
	getline(file, confirm); // dummy to reach EOF if no items in there
	while(confirm != "end") { // for however many items may exist in the file
		getline(file, ID);
		getline(file, matID);
		getline(file, usesMatInName);
		getline(file, hasSpecialExamine);
		getline(file, specialExamine);
		getline(file, hasSpecialName);
		getline(file, specialName);
		getline(file, specialSlash);
		getline(file, slash);
		getline(file, specialCrush);
		getline(file, crush);
		getline(file, specialStab);
		getline(file, stab);
		getline(file, specialBlock);
		getline(file, block);
		getline(file, specialBash);
		getline(file, bash);
		getline(file, specialParry);
		getline(file, parry);
		getline(file, specialHurl);
		getline(file, hurl);
		getline(file, specialWeight);
		getline(file, weight);
		getline(file, confirm);

		Item* item;
		switch(atoi(ID.c_str())) {
			case 1: {
				item = new HumanFist;
				break;
			}
			case 2: {
				item = new Longsword;
				break;
			}
			case 3: {
				item = new Dagger;
				break;
			}
			case 4: {
				item = new Rock;
				break;
			}
			case 5: {
				item = new Buckler;
				break;
			}
			default: {
				item = nullptr;
			}
		}
		Material material;
		switch(atoi(matID.c_str())) {
			case 1: {
				material = Basic();
				break;
			}
			case 2: {
				material = Wooden();
				break;
			}
			case 3: {
				material = Bronze();
				break;
			}
			case 4: {
				material = Steel();
				break;
			}
			default: {
			}
		}
		item->setMaterial(material);
		item->setMaterialNameToDisplay(atoi(usesMatInName.c_str()));
		// item has a special examine text
		if(atoi(hasSpecialExamine.c_str())) {
			item->setExamineText(specialExamine);
			item->setHasSpecialExamine(true);
		}
		else // item doesnt have a special examine text
			item->setMaterialExamine(material);
		//if item has a special name
		if(atoi(hasSpecialName.c_str())) {
			item->setName(specialName);
			item->setHasSpecialName(true);
		}
		if(atoi(specialSlash.c_str())) {
			item->setaSlash(atof(slash.c_str()));
			item->sethasSpecialSlash(true);
		}
		if(atoi(specialCrush.c_str())) {
			item->setaCrush(atof(crush.c_str()));
			item->sethasSpecialCrush(true);
		}
		if(atoi(specialStab.c_str())) {
			item->setaStab(atof(stab.c_str()));
			item->sethasSpecialStab(true);
		}
		if(atoi(specialBlock.c_str())) {
			item->setaBlock(atof(block.c_str()));
			item->sethasSpecialBlock(true);
		}
		if(atoi(specialBash.c_str())) {
			item->setaBash(atof(bash.c_str()));
			item->sethasSpecialBash(true);
		}
		if(atoi(specialParry.c_str())) {
			item->setaParry(atof(parry.c_str()));
			item->sethasSpecialParry(true);
		}
		if(atoi(specialHurl.c_str())) {
			item->setaHurl(atof(hurl.c_str()));
			item->sethasSpecialHurl(true);
		}
		if(atoi(specialWeight.c_str())) {
			item->setaWeight(atof(weight.c_str()));
			item->sethasSpecialWeight(true);
		}
		items.push_back(item);
	}
	return items;
}
