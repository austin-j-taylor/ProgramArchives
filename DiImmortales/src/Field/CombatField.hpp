
Character* attacker;

using namespace std;

class CombatField : public Field {
public:
    CombatField(Character*);
    void startCombat(vector<Character*>& enemies);
    int turnOfBattle(vector<Character*>& enemies);
    
//    virtual int choice(vector<Character*>& enemies) {}
    
    Field* parseField(string choice);
//    void parseUsage(string choice);
private:
    const vector<string> options { "Fight", "Act", "Item", "Seek Mercy" };
};
CombatField::CombatField(Character* loadedAttacker = new Character()) {
    attacker = loadedAttacker;
    
}
// initiates start of combat
void CombatField::startCombat(vector<Character*>& enemies) {
	// first turn of the battle, print out intros:
	println(string(windowWidth, '-'));
	println(attacker->getIntro());
	println("HP: " + tostring(attacker->getTHp()) + "/" + tostring(attacker->getTMaxHp()));
    for(auto enemy : enemies) {
        println(enemy->getIntro());
    }
	println(string(windowWidth, '-'));
    goto startOfTurn;
    // second, third, etc. turn of battle, print out names and effects:
    notFirstTurn:
	println(string(windowWidth, '-'));
	print("HP: " + tostring(attacker->getTHp()) + "/" + tostring(attacker->getTMaxHp()));

    if(attacker->getActiveEffects()->getCount() != 0) {
		print(" - ");
		for(int i = 0; i < attacker->getActiveEffects()->getCount(); i++) {
			print(attacker->getActiveEffects()->getEffects()[i]->getName());
			if(i != attacker->getActiveEffects()->getCount() - 1)
				print(", ");
		}
    }
    println();
    for(auto enemy : enemies) {
        print(enemy->getName());
//		print(" - ");
    	print(" (" + tostring(enemy->getTHp()) + "/" + tostring(enemy->getTMaxHp()) + ")");
        if(enemy->getActiveEffects()->getCount() != 0){
			print(" - ");
			for(int i = 0; i < enemy->getActiveEffects()->getCount(); i++) {
				print(enemy->getActiveEffects()->getEffects()[i]->getName());
				if(i != enemy->getActiveEffects()->getCount() - 1)
					print(", ");
			}
        }
        println();
    }
	println(string(windowWidth, '-'));
	// one turn of the fight executes
	startOfTurn:
	turnOfBattle(enemies);


	// tests to see if all enemies are dead after that turn; if anyone's alive, go back to the start of a turn.
	if(attacker->isDead())
		attacker->die(attacker);
	for(auto enemy : enemies) {
		if(!enemy->isDead())
			goto notFirstTurn;
	}
	// all enemies are dead:

};
int CombatField::turnOfBattle(vector<Character*>& enemies) {

	if(attacker->getActiveEffects()->indexOf("stunned") == -1) {
		// fight, act, item, etc
		start:
		int choice = Field::choice(options, "", false);
		Field* field = parseField(options[choice]);
		// subChoice: -1 for if the enemies should react, any other value for if they shouldn't
		// subChoice: -2 if player chose "Back" command
		// fight --> enemy names, item --> items within bag, etc
		int subChoice = field->choice(enemies);
		if(subChoice == 0) return 999; // ignores rest of function, enemyShouldReact was false
		if(subChoice == -2) goto start; // goes back to selecting main options
	} else { // attacker is stunned
		Field::choice(vector<string> { "Stand around dazedly" }, "You are stunned.", false);
	}

	Effect* killEffect;
	for(auto enemy : enemies) {
		if(!enemy->isDead())
			goto enemiesAttack;
	}
	goto wingame;

	enemiesAttack:
    // for each enemy in enemies, enemy->attack;
    // TODO: build more complex AI based on user weakness to certain styles, weapons, etc.
    // for now, enemies simply attack using their first equipped weapon and the weapon's first style (usually therefore slash)
    for(int i = 0; i < enemies.size(); i++) {
    	Character* enemy = enemies[i];
    	Item* weapon = enemies[i]->getEquippedArms()->itemAt(0);
    	Style style = weapon->getStyles()[0];
        int outcome = enemies.at(i)->attack(attacker, weapon, style);

        switch(outcome) {
    		case 0: { // player killed
    			attacker->die(enemies[i]);
    			break;
    		}
    		case 1: { // player still alive

    			break;
    		}
    		case 2: { // enemy was stunned beforehand

    			break;
    		}
    		case 3: { // player parried; killed enemy.
    			enemy->die(attacker);
    			enemies.erase(enemies.begin() + i);
    			delete enemy;
    			if(enemies.size() == 0)
    				goto wingame;
    			i--;
    			break;
    		}
    		case 6: { // player parried; killed target by weapon effect
    			enemy->die(attacker);
    			enemies.erase(enemies.begin() + i);
    			delete enemy;
    			if(enemies.size() == 0)
    				goto wingame;
    			i--;
    			break;
    		}
        	default: {}
    	}
    }
	// enemies takes damage from active effects
    for(int i = 0; i < enemies.size(); i++) {
    	Character* enemy = enemies[i];
		if(!enemy->isDead()) {
			killEffect = enemy->decrementTurnOfEffects();
			if(enemy->isDead()) { // enemy died from effect
				enemy->die(nullptr, killEffect);
				enemies.erase(enemies.begin() + i);
				delete enemy;
				if(enemies.size() == 0)
					goto wingame;
				i--;
			}
		}
    }
	// player takes damage from active effects
    killEffect = attacker->decrementTurnOfEffects();
	if(attacker->isDead())
		attacker->die(nullptr, killEffect);

    attacker->setIsBlocking(false);
    attacker->setIsParrying(false);

    return -999;

    wingame:
	attacker->winGame();

	return 123 * 456 * 789 * 10 * 987 * 654 * 321;
}

class FightField : public Field {
public:
    FightField() {}
    int choice(vector<Character*>& enemies);
    static int attack(Character*, Item*, Style, vector<Character*>&, int, bool);
};
int FightField::choice(vector<Character*>& enemies) {
    // initialization of enemies' names and the attacker's equipped weapons comes first
    // then, those names are used in Field's choice...
    // then, the names of the styles of the chosen weapon are initialized and Field's choiced...
    // then, attack(target, weapon, style)
    
    vector<string> enemyNames;
    for(auto enemy : enemies)
        enemyNames.push_back(enemy->getName());
    vector<string> weaponNames;
    for(auto item : (attacker->getEquippedArms()->getItems()))
        weaponNames.push_back(item->getName());
    
    //choose weapon (choose from equippedArms)
    weapon:
    int choiceWeapon = Field::choice(weaponNames, "Choose a weapon.");
    if(choiceWeapon == -2) return -2;

    //find potential style names based on weapon for choice
    vector<string> styleNames;
    for(Style style : attacker->getEquippedArms()->getItems()[choiceWeapon]->getStyles())
        styleNames.push_back(style.getName());
    Item* weapon = attacker->getEquippedArms()->getItems()[choiceWeapon];

    style:
    //choose style of attack (use, throw, SLASH, CRUSH, etc)
    int choiceStyle = Field::choice(styleNames);
    if(choiceStyle == -2) goto weapon;
    Style style = attacker->getEquippedArms()->getItems()[choiceWeapon]->getStyles()[choiceStyle];

	Character* target = nullptr;
	int choiceEnemy;
	if(style != Styles::Block) {
		//choose single enemy

		choiceEnemy = Field::choice(enemyNames, "Choose a target.");
		if(choiceEnemy == -2) goto style;
		target = enemies[choiceEnemy];
	}

    //now, attack!
    int outcome = attack(target, weapon, style, enemies, choiceEnemy, true);

    return outcome;
}
int FightField::attack(Character* target, Item* weapon, Style style, vector<Character*>& enemies, int enemyIndex, bool isEquipped) {

    int outcome = attacker->attack(target, weapon, style, isEquipped);
    switch(outcome) {
		case 0: { // single target, killed
			target->die(attacker);
			delete target;
			enemies.erase(enemies.begin() + enemyIndex);
			break;
		}
		case 1: { // single target, still alive

			break;
		}
		case 2: { // multiple targets, state of life unknown

		    Character::sortOutCorpses(enemies); // enemies that are dead (null pointers) are deleted from array
			break;
		}
		case 3: { // target parried; killed attacker.

			break;
		}
		case 4: { // target dead by style effect

			target->die(attacker, weapon->styleEffect(style));
			delete target;
			enemies.erase(enemies.begin() + enemyIndex);
			break;
		}
		case 5: { // target dead by weapon effect

			target->die(attacker, weapon->getSpecialEffect());
			delete target;
			enemies.erase(enemies.begin() + enemyIndex);
			break;
		}
    	default: {}
	}
    return 1;

}

class ActField : public Field {
public:
    ActField() {}
    int choice(vector<Character*>& enemies);
    void analyze(vector<Character*>&);
    string rel(double, double);
    void killself();
};
int ActField::choice(vector<Character*>& enemies) {
//    println("You chose to act. Unfortunately, that does not do anything yet. You lost a turn." + endl;
	vector<string> choices = { "Analyze", "Kill Yourself" };
	int result = Field::choice(choices);
	//-1 for enemy should react, 0 if not
    switch(result) {
		case 0: {
			analyze(enemies);
			return -1;
		}
		case 1: {
			killself();
			return 0;
		}
    }
    return 1;
}
void ActField::analyze(vector<Character*>& enemies) {
    vector<string> enemyNames;
    for(auto enemy : enemies)
        enemyNames.push_back(enemy->getName());
	int choice = Field::choice(enemyNames);
	Character* target = enemies[choice];
	print(target->getName());
    if(target->getActiveEffects()->getCount() != 0) {
		print(" - ");
		for(int i = 0; i < target->getActiveEffects()->getCount(); i++) {
			print(target->getActiveEffects()->getEffects()[i]->getName());
			if(i != target->getActiveEffects()->getCount() - 1)
				print(", ");
		}
    }
    println();
    println(target->getAnalyze());
    println();
	println("Health (" + tostring(target->getTHp())+ "/" + tostring(target->getTMaxHp()) + "): " + rel(attacker->getTHp(), target->getTHp()));
	println("Strength: " + rel(attacker->getTStr(), target->getTStr()));
	println("Defense: " + rel(attacker->getTDef(), target->getTDef()));
	println("Dexterity: " + rel(attacker->getTDex(), target->getTDex()));
	println("Agility: " + rel(attacker->getTAgil(), target->getTAgil()));
	println("Weight: " + rel(attacker->getTWeight(), target->getTWeight()));
	println();
	print("Equipped arms: ");
	if(target->getEquippedArms()->itemAt(0) != target->getEHE()) {
		for(int i = 0; i < target->getEquippedArms()->getSize(); i++) {
			print(target->getEquippedArms()->itemAt(i)->getName());
			if(i != target->getEquippedArms()->getSize() - 1) {
				print(", ");
			}
		}
	}
	else print("None.");
	println("\n");

}
string ActField::rel(double n1, double n2) {
	double ratio = n1/n2;
//	cout << "ratio: " << tostring(ratio) << "d1: " << tostring(n1) << " " << tostring(n2);
	if(ratio >= 2.0) return "Very low.";
	if(ratio >= 1.80) return "Much lower.";
	if(ratio >= 1.60) return "Lower.";
	if(ratio >= 1.40) return "Somewhat lower.";
	if(ratio >= 1.25) return "Slightly lower.";

	if(ratio >= .9) return "Equally matched.";

	if(ratio >= .85) return "Slightly higher.";
	if(ratio >= .75) return "Somewhat higher.";
	if(ratio >= .65) return "Higher.";
	if(ratio >= .55) return "Much higher.";
	if(ratio >= .45) return "Dangerously higher.";
	if(ratio < .45) return "Very high.";
	return "ERROR: ActField::analyze()";
}
void ActField::killself() {
	println("\n\nOh please, You're far too beautiful to die.");
}

class ItemField : public Field {
public:
    ItemField() {}
    int choice(vector<Character*>& enemies);
};
int ItemField::choice(vector<Character*>& enemies) {

    vector<Item*> items = (attacker->getBag())->getItems();
    vector<string> names;
    for(int i = 0 ; i < attacker->getEquippedArms()->getSize(); i++) {
    	names.push_back("(E) " + capitalize(attacker->getEquippedArms()->getItems()[i]->getName()));
    }
    for(int i = 0 ; i < (attacker->getBag())->getSize(); i++) {
    	names.push_back(attacker->getBag()->getItems()[i]->getName());
    }
//    cout << names[0];
    item:
    int itemChoice = Field::choice(names);
    if(itemChoice == -2) return -2;
    /*
     example:
     * (E) Bronze Sword
     * (E) Bronze Dagger
     * Rock
     * Sandwich
     * Bronze Mace
     
     * choice "2" or "Bronze Dagger" returns 1 into itemChoice
     * choice "3" or "Rock" returns 2
     * equippedArms->getSize = 2
     
     */
    Item* itemInQuestion;
    vector<string> usages;
    // if the weapon is equipped
    bool isEquipped = itemChoice < attacker->getEquippedArms()->getSize();
    if(isEquipped) {
        itemInQuestion = attacker->getEquippedArms()->getItems()[itemChoice];
        for(Usage usage : itemInQuestion->getUsages())
        	// prints out everything EXCEPT equip; thus, prints out UNEQUIP. If the chosen item is the EHE, then it will not print out UNEQUIP.
            if(usage.getUsage() != Usages::Equip && ((usage.getUsage() != Usages::Unequip) || (attacker->getEHE() != itemInQuestion)))
            	usages.push_back(usage.getName());
        if(attacker->getEHE() != itemInQuestion)
        	usages.push_back("Hurl");
    }
    else { // if the weapon is unequipped
        itemInQuestion = items[itemChoice - attacker->getEquippedArms()->getSize()];
        for(Usage usage : itemInQuestion->getUsages())
        	if(usage.getUsage() != Usages::Unequip)
        		usages.push_back(usage.getName());
        if(attacker->getEquippedArms()->getSize() < attacker->getEquippedArms()->getMaxSize()) { // if the attacker has an open hand
        	usages.push_back("Hurl");
        }
    }
    chooseUsage:
    int usageChoice = Field::choice(usages);
    if(usageChoice == -2) goto item;
    // execute usage function; also decides enemy to attack after this choice (default value: 1 (true)).
    bool enemyShouldReact = true;

    if(usages[usageChoice] == "Use") {
    	enemyShouldReact = attacker->use(itemInQuestion);
    } else if(usages[usageChoice] == "Eat") {
    	enemyShouldReact = attacker->eat(itemInQuestion);
    } else if(usages[usageChoice] == "Equip") {
    	enemyShouldReact = attacker->equip(itemInQuestion);
    } else if(usages[usageChoice] == "Unequip") {
    	enemyShouldReact = attacker->unequip(itemInQuestion);
    } else if(usages[usageChoice] == "Examine") {
    	enemyShouldReact = attacker->examine(itemInQuestion) && false;
	} else if(usages[usageChoice] == "Hurl") {
	    vector<string> enemyNames;
	    for(auto enemy : enemies)
	        enemyNames.push_back(enemy->getName());
	    int choiceEnemy = Field::choice(enemyNames, "Choose a target.");
	    if(choiceEnemy == -2) goto chooseUsage;
	    int outcome = FightField::attack(enemies[choiceEnemy], itemInQuestion, Styles::Hurl, enemies, choiceEnemy, isEquipped);
    	enemyShouldReact = true;
	} else println("\n\nsomething bad happened. ItemField::choice.\n");

    return (enemyShouldReact) ? -1 : 0; // -1 for true, 0 for false. don't question my boolean logic.
}

class MercyField : public Field {
public:
    MercyField() {}
    int choice(vector<Character*>& enemies);
};
int MercyField::choice(vector<Character*>& enemies) {
    println("You chose to give mercy. Unfortunately, horizontally integrated corporations give no mercy in the real world. You lost a turn.");
    
    return 1;
}

Field* CombatField::parseField(string choice) {
    Field* field;
    if(choice == "Fight") {
        field = new FightField;
    } else if(choice == "Act") {
        field = new ActField;
    } else if(choice == "Item") {
        field = new ItemField;
    } else if(choice == "Seek Mercy") {
        field = new MercyField;
    }
    
    return field;
}
