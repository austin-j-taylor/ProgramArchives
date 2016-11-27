
using namespace std;

class Character {
private:
    Bag* equippedArms;
    ActiveEffects* activeEffects;
    Bag* bag;
    string name;
    string intro;
    string analyze;
    Item* emptyHandedEquip;
    Character* parryTarget;

    //true stats: hp, str, ETC.
    //modifiers for stats via items, armor, effects, etc: hpMod, strMod, ETC.
    //if you've got 10 base hp and an amulet with +3 hp, hp == 10 and hpMod == 3
    // note: int hp corresponds to current hp; int maxHp and int hpMod are used for potential maximum health. getTHp() returns (hp + hpMod).
    //		-> if you have 30 hp and 10 hpMod, THp is 40; if you get hit for 35 points, hp is -5 and hpMod is still 10.
    //			-> if you remove whatever armor/item/etc. is buffing your hpMod, you'll immediately die.
    short gender; // used in constructors
    int hp;
    int maxHp;
    int str;
    int def;
    int dex;
    int agil;
    int hpMod;
    int strMod;
    int defMod;
    int dexMod;
    int agilMod;
    bool isBlocking;
    bool isParrying;
    string psub; // subject: he, she, it
    string pobj; // object: him, her, it
    string ppos; // possessive: his, her, its
public:
//    Character(); // must give starting stats
//    Character(pointer/reference to file); // must import data from file: stats, items in bag, equipped weapon/armor
    Character(string, string, string, short, int, int, int, int, int, Item*, int, int, int, int, int);
    virtual ~Character() {}

    virtual int getHp() { return hp; }
    virtual int getMaxHp() { return maxHp; }
    virtual int getStr() { return str; }
    virtual int getDef() { return def; }
    virtual int getDex() { return dex; }
    virtual int getAgil() { return agil; }
    virtual int getHpMod() { return hpMod; }
    virtual int getStrMod() { return strMod; }
    virtual int getDefMod() { return defMod; }
    virtual int getDexMod() { return dexMod; }
    virtual int getAgilMod() { return agilMod; }
    virtual int getTHp() { return hp + hpMod; }
    virtual int getTMaxHp() { return maxHp + hpMod; }
    virtual int getTStr() { return str + strMod; }
    virtual int getTDef() { return def + dexMod; }
    virtual int getTDex() { return dex + dexMod; }
    virtual int getTAgil() { return agil + agilMod; }
    virtual double getTWeight() {
    	double w = 0.0;
		for(Item* item : equippedArms->getItems()) {
			w += (item->getWeight() * item->getMaterial().getaWeight());
		}
		if(w == 0.0) return -999;

		return w; // the sum of all weapon weights
    }
    bool isDead() { return (getTHp() <= 0); }
    virtual string getName() { return name; }
    virtual string getIntro() { return intro; }
    virtual string getAnalyze() { return analyze; }
    virtual string getItemTitle(Item* item) {
    	if(item->article() == "")
    		return ppos;
    	return item->article();
    }
    bool getIsBlocking();
    bool getIsParrying(Character*);
    Character* getParryTarget() { return parryTarget; }
    virtual Item* getEHE() { return emptyHandedEquip; }
    virtual Bag* getBag() { return bag; }
    virtual Bag* getEquippedArms() { return equippedArms; }
    virtual ActiveEffects* getActiveEffects() { return activeEffects; }

    // strings for properly gendered examine(), analyze, etc.
    // the private variables for pronouns and articles have the first letter capitalized; the public getters are all lowercase.
    virtual short getGender() { return gender; }
    virtual string getPsub() { return psub; }
    virtual string getPobj() { return pobj; }
    virtual string getPpos() { return ppos; }
    
    virtual void setGender(short nGender) { gender = nGender; }
    virtual void setPronouns(short nGender) {
		psub = (gender == 0) ? "he " : (gender == 1) ? "she " : "it ";
		pobj = (gender == 0) ? "him" : (gender == 1) ? "her" : "it";
		ppos = (gender == 0) ? "his " : (gender == 1) ? "her " : "its ";
    }

    virtual void setHp(int nHp) { hp = nHp; }
    virtual void setMaxHp(int nMaxHp) { maxHp = nMaxHp; }
    virtual void setStr(int nStr) { str = nStr; }
    virtual void setDef(int nDef) { def = nDef; }
    virtual void setDex(int nDex) { dex = nDex; }
    virtual void setAgil(int nAgil) { agil = nAgil; }
    virtual void setHpMod(int nHpMod) { hpMod = nHpMod; }
    virtual void setStrMod(int nStrMod) { strMod = nStrMod; }
    virtual void setDefMod(int nDefMod) { defMod = nDefMod; }
    virtual void setDexMod(int nDexMod) { dexMod = nDexMod; }
    virtual void setAgilMod(int nAgilMod) { agilMod = nAgilMod; }
    virtual void setName(string nName) { name = nName; }
    virtual void setIntro(string nIntro) { intro = nIntro; }
    virtual void setAnalyze(string nAnalyze) { analyze = nAnalyze; }
    virtual void setIsBlocking(bool isBlock);
    virtual void setIsParrying(bool isBlock, Character*);
    virtual void setArmCount(int c) { equippedArms->setMaxSize(c); }
    virtual void setEHE(Item* item) {
    	if(equippedArms->getSize() == 1) {
    		equippedArms->removeItem(emptyHandedEquip);
        	equippedArms->addItem(item);
    	}
    	emptyHandedEquip = item;
    }

    virtual int use(Item* item);
    virtual int eat(Item* item);
    virtual int equip(Item* item, bool);
    virtual int unequip(Item* item, bool);
    virtual int examine(Item* item);

    virtual void hurl(Item* item, bool);

    virtual void putInBag(Item* item);


    virtual int attack(Character* target, Item* weapon, Style style, bool);
//    virtual void takeDamage(Character* attacker);
//    virtual int takeEffect(Item* weapon, Style style);
//    virtual int takeEffect(Effect*);
    virtual int gainEffect(Effect* effect);
    virtual int loseEffect(Effect* effect);
    virtual void gain(Stats, int);
    virtual void lose(Stats, int);
    virtual void gain(Stats, double);
    virtual void lose(Stats, double);

    Effect* decrementTurnOfEffects();
//    virtual int takeDOT() {}
//    virtual int takeUseEffect(Item* item) {}
//    virtual int takeEatEffect(Item* item) {}
//    virtual int takeEquipEffect(Item* item) {}
//    virtual int takeDefendingEffect(Item* item) {}
    
    virtual void die(Character*, Effect*, string);
    virtual void winGame() {}
    static void sortOutCorpses(vector<Character*>);
    
};
Character::Character(string nName = "Character", string nIntro = "a Character appears.", string nAnalyze = "an untamed Character.",
		short nGender = 0, int nHp = 10, int nStr = 10, int nDef = 10, int nDex = 10, int nAgil = 10,
		Item* EHE = new Item(), int nHpMod = 0, int nStrMod = 0, int nDefMod = 0, int nDexMod = 0, int nAgilMod = 0)
    : name(nName), intro(nIntro), analyze(nAnalyze), gender(nGender), /*emptyHandedEquip(EHE),*/ isBlocking(false), isParrying(false),
	  hp(nHp), maxHp(nHp), str(nStr), def(nDef), dex(nDex), agil(nAgil), hpMod(nHpMod), strMod(nStrMod), defMod(nDefMod), dexMod(nDexMod), agilMod(nAgilMod) {

	psub = (gender == 0) ? "he " : (gender == 1) ? "she " : "it ";
	pobj = (gender == 0) ? "him" : (gender == 1) ? "her" : "it";
	ppos = (gender == 0) ? "his " : (gender == 1) ? "her " : "its ";

    emptyHandedEquip = EHE;
    bag = new Bag();
    activeEffects = new ActiveEffects();
    equippedArms = new Bag();
    equippedArms->addItem(getEHE());
    setArmCount(2);
}

bool Character::getIsBlocking() {
	return isBlocking;
}
bool Character::getIsParrying(Character* target) {
	if(isParrying)
		if(parryTarget == target)
			return true;
	return false;
}
void Character::setIsBlocking(bool isBlock) {
	isBlocking = isBlock;
}
void Character::setIsParrying(bool isParry, Character* target = nullptr) {
	isParrying = isParry;
	if(target != nullptr) {
		parryTarget = target;
	}
}
int Character::use(Item* item) {
	return 0;
}
int Character::eat(Item* item) {
	return 0;
}
int Character::equip(Item* item, bool printOut = true) {
	if(equippedArms->getSize() == 1)
		equippedArms->removeItem(getEHE()); // attempts to remove EHE (if it's there)
    if(equippedArms->getSize() == equippedArms->getMaxSize()) {
        println(name + "'s arms are full.");
        return 0;
    }
    equippedArms->addItem(item);
    if(printOut) println(name + " equipped the " + item->getName() + ".");
    bag->removeItem(item);
	return 1;
}
int Character::unequip(Item* item, bool printOut = true) {
    if(bag->getSize() == bag->getMaxSize()) {
        println(name + "'s bag is full.");
        return 0;
    }
    bag->addItem(item);
    equippedArms->removeItem(item);
    if(equippedArms->getSize() == 0)
    	equippedArms->addItem(emptyHandedEquip);
    if(printOut) println(name + " removed the " + item->getName() + ".");
	return 1;
}
int Character::examine(Item* item) {
    item->examine();
	return 0;
}
void Character::hurl(Item* item, bool isEquipped = true) {
	if(isEquipped) {
		equippedArms->removeItem(item);
		if(equippedArms->getSize() == 0) {
			equippedArms->addItem(emptyHandedEquip);
		}
	} else {
		bag->removeItem(item);
	}
}

void Character::putInBag(Item* item) {
	bag->addItem(item);
}

int Character::attack(Character* target, Item* weapon, Style style, bool isEquipped = true) { // return 0 if target is dead, 1 if alive
	if(activeEffects->indexOf("stunned") != -1) {// attacker is stunned and can do nothing (only applies to enemies; player is checked for being stunned beforehand.)
		println(name + " is still recovering.");
		return 2;
	}
	equippedArms->sort(weapon);
	/*

	    // PLAYERNAME PLAYERVERBOFSTYLE [ARTICLEOFDESCRIPTION] [ENEMYTITLE] ENEMYNAME with the WEAPON NAME.
	    // -> Artemis struck the Absolute Ruler Capitalist with the Gilded Broadsword.

	    // RNG
	    // -> player Missed (dex), Did Damage, Was Blocked (block() and armor), Was Parried(parry() and dex), Was Dodged (dodge() + dex), etc

	    // Test if Enemy is Alive or Dead; if Alive, return takeEffect();
	    // if dead, return 1
	    if(hp > 0) {
	        return takeEffect(target);
	    }

	    return 1;
	}
	 */
	double weaponModifier = weapon->getAffinity(style) * weapon->getMaterial().getAffinity(style);

	if(style == Styles::Slash || style == Styles::Stab || style == Styles::Crush || style == Styles::Hurl || style == Styles::Bash) {
		double hitChance = ((getTDex() * target->getTWeight()) / (target->getTAgil() * getTWeight()));
		double randHit = rand() % 100 / 100.0;
//		if(hitChance > 1.0)
//			println("(Accuracy: 100%)");
//		else
//			println("(Accuracy: " + tostring((int) (hitChance * 100)) + "%)");
		if(hitChance > randHit) {
			// Base Damage = attacker.Strength^2 / (2 * target.Defence)
			// if Strength = 30 and Defense = 30, Damage = 15
			// 				 30				  40		   11.25
			// 				 30				  15		   30
			// 				 100			  500	 	   10
			double baseDamage = (getTStr()) * (getTStr()) / (2 * (target->getTDef()));
			int damage = (int) (baseDamage * weaponModifier); // multiplies and floors the results
			if(!target->getIsBlocking() && !target->getIsParrying(this)) {
				if(style == Styles::Hurl) { // hurling
					println(name + " " + weapon->getVerb(Styles::Hurl) + " " + getItemTitle(weapon) + weapon->getName() + " at " + target->getName() + " for " + tostring(damage) + " damage.");
					hurl(weapon, isEquipped);
				} else if(style == Styles::Bash){ // bashing; target is dazed for two turns
					println(name + " " +  weapon->getVerb(Styles::Bash) + " " + target->getName() + " with " + getItemTitle(weapon) + weapon->getName() + ", dazing " + target->getPobj() + " and dealing " + tostring(damage) + " damage.");
				target->gainEffect(new Dazed(-0.30, 2));
				} else {
					// neither hurling nor bashing
					println(name + " " + weapon->getVerb(style) + " " + target->getName() + " with " + getItemTitle(weapon) + weapon->getName() + " for " + tostring(damage) + " damage.");
				}
				target->lose(Stats::Hp, damage);
				if(target->isDead()) {
					return 0; // target is dead from attack
				}

				// target gains weapon effects
				if(target->gainEffect(weapon->styleEffect(style)) == 0) {
					return 4; // target is dead from style Effect
				}
				if(target->gainEffect(weapon->getSpecialEffect()) == 0) {
					return 5; // target is dead from weapon Effect
				}
			} else if(target->getIsBlocking()) { // target is blocking
				Item* targetWeapon = target->getEquippedArms()->itemAt(0);
				// *** IF SUCCESSFUL:***
				// target is blocking; target does not take Effects but does take a calculated lesser damage from melee attacks.
				// If the attacker did not throw the weapon, attacker gains the STUNNED effect, unable to do anything the next turn and loses dexterity for three turns.
				int damageBlock = (int) (baseDamage / (targetWeapon->getAffinity(Styles::Block) + targetWeapon->getMaterial().getAffinity(Styles::Block) + 1/2 * target->getTDef()));
				if(style != Styles::Hurl) { // not hurling
					println(name + " " + weapon->getVerb(style) + " " + target->getName() + " with " + getItemTitle(weapon) + weapon->getName()
							+ ", but " + target->getName() + " blocked the blow with " + target->getPpos() + targetWeapon->getName()
							+ ", stunning " + getPobj() + " but still receiving " + tostring(damageBlock) + " damage.");
					target->lose(Stats::Hp, damageBlock);
					gainEffect(new Stunned(0, 1));
					gainEffect(new Dazed(-0.20, 3));
				} else { // hurling
					println(name + " threw "+ getItemTitle(weapon) + weapon->getName() + " at " + target->getName()
							+ ", but " + target->getPsub() + "deflected the blow with " + target->getItemTitle(targetWeapon) + targetWeapon->getName() + ".");
					hurl(weapon, isEquipped);
				}
				target->setIsBlocking(false);

			} else { // target is parrying the attacker
				Item* targetWeapon = target->getEquippedArms()->itemAt(0);
				// *** IF SUCCESSFUL:***
				// target is parrying towards THIS; target does not take Effects and does not take damage.
				// target deals damage to attacker in a counterattack based off of affParry.
				int damageParried = (int) (baseDamage * (targetWeapon->getAffinity(Styles::Parry) + targetWeapon->getMaterial().getAffinity(Styles::Parry)));
				double parryChance = ((getTDex() * target->getTStr()) / (target->getTAgil() * target->getTWeight()));
//				println("[Chance of parrying: " + tostring(parryChance) + "]");
				if(true) { // target successfully parried
					if(style != Styles::Hurl) { // not hurling
						println(name + " " + weapon->getVerb(style) + " " + target->getName() + " with " + getItemTitle(weapon) + weapon->getName()
								+ ", but " + target->getName() + " parried the blow with " + getItemTitle(targetWeapon) + targetWeapon->getName()
								+ ", turning and counterattacking " + getPobj() + " for " + tostring(damageParried) + " damage.");
						lose(Stats::Hp, damageParried);
						if(isDead()) {
							return 3; // ATTACKER died from attacking a parrying target
						}
						gainEffect(target->getEquippedArms()->itemAt(0)->getSpecialEffect());
						if(isDead()) {
							return 6; // ATTACKER died from weapon effect
						}
					} else { // hurling, attacker suffers no recoil damage
						println(name + " threw " + getItemTitle(weapon) + weapon->getName() + " at " + target->getName()
								+ " but " + target->getPsub() + "deflected the blow with " + getItemTitle(targetWeapon) + targetWeapon->getName() + ".");
						hurl(weapon, isEquipped);
					}
				} else { // target failed to parry
					damageParried = 999;

					if(style != Styles::Hurl) { // not hurling

						println(name + " " + weapon->getVerb(style) + " " + target->getName() + " with " + getItemTitle(weapon) + weapon->getName()
								+ ", breaking through " + target->getPpos() + " parry, for " + tostring(damageParried) + " damage.");
						lose(Stats::Hp, damageParried);
						if(isDead()) {
							return 3; // if ATTACKER died from attacking a parrying target
						}
						gainEffect(target->getEquippedArms()->itemAt(0)->getSpecialEffect());
					} else { // hurling, attacker suffers no recoil damage
						println(name + " threw " + getItemTitle(weapon) + weapon->getName() + " at " + target->getName()
								+ " but " + target->getPsub() + "deflected the blow with " + getItemTitle(targetWeapon) + targetWeapon->getName() + ".");
						hurl(weapon, isEquipped);


					}
				}
				target->setIsParrying(false);
			}
//			if(target->isDead()) {
//				return 0; // target is dead
//			}
		} else { // attacker missed
			if(style == Styles::Hurl) {
				hurl(weapon, isEquipped);
				println(name + " threw " + getItemTitle(weapon) + weapon->getName() + " at " + target->getName() + " but missed.");
			} else
				println(name + " attacked " + target->getName() + " with " + getItemTitle(weapon) + weapon->getName() + " but missed.");
		}
	} else if(style == Styles::Block) {
		// towards no enemy in particular
		println(getName() + " raised " + getPpos() + weapon->getName() + ", waiting for an attack.");
		setIsBlocking(true);
    } else if (style == Styles::Parry) {
		// towards target
    	println(getName() + " focused " + getPpos() + weapon->getName() + " at " + target->getName() + ", waiting for an attack.");
		setIsParrying(true, target);
    }
//	if(target->isDead()) {
//		return 0; // target is dead
//	}
    return 1;
}

Effect* Character::decrementTurnOfEffects() {
	for(int i = 0; i < activeEffects->getCount(); i++) {
		Effect* effect = activeEffects->getEffects()[i];
		if(effect->getTurnsLeft() <= 0) {
			activeEffects->removeEffect(effect);
			i--;
		} else {
			if(effect->getHasDOT()) { // if effect deals damage
				double damage = effect->getPotency();
				if(effect->getIsConstant()) { // if effect has constant damage over time
					println(name + " took " + tostring(-damage) + " damage from being " + effect->getName() + ".");
					gain(effect->getStat(), (int) damage);
				}
				if(effect->getIsPercent()) { // percentage of stat lost each turn; only works with health for now
					println(name + " took " + tostring((int) (-damage * maxHp)) + " damage from being " + effect->getName() + ".");
					gain(effect->getStat(), damage);
				}
				if(isDead())
					return effect;
			}
			effect->decrementTurn();
		}
	}
	return nullptr;
}
int Character::gainEffect(Effect* effect) {
	if(effect == nullptr)
		return 1;
	int index = activeEffects->indexOf(effect->getName());
	if(index == -1)// no duplicate effect of same name already in there
	{
		activeEffects->addEffect(effect);
		//cout << "\nAdded effect: " << effect->getName() << ".\n";
	}
	else // is a duplicate effect; simply increase turns left by one
		activeEffects->getEffects()[index]->incrementTurn();

	if(!effect->getHasDOT()) { // if the effect doesn't have a DOT, then take damage now rather then after every turn
		if(effect->getIsPercent()) // if the effect should change the stat by a percent
			gain(effect->getStat(), effect->getPotency());
		else // is a constant value
			gain(effect->getStat(), (int) effect->getPotency());
	}

	if(this->isDead())
		return 0;
	return 1;
}
int Character::loseEffect(Effect* effect) {
	if(!effect->getHasDOT()) {
		if(effect->getIsPercent()) // if the effect should change the stat by a percent
			lose(effect->getStat(), effect->getPotency());
		else // is a constant value
			lose(effect->getStat(), (int) effect->getPotency());
	}

	activeEffects->removeEffect(effect);
	if(this->isDead())
		return 0;
	return 1;
}
void Character::gain(Stats stat, int amount) {
	switch(stat) {
		case Stats::None: {
			// do nothing
			break;
		}
		case Stats::Hp: {
			hp += amount;
			break;
		}
		case Stats::HpMod: {
			hpMod += amount;
			break;
		}
		case Stats::MaxHp: {
			maxHp += amount;
			break;
		}
		case Stats::Str: {
			str += amount;
			break;
		}
		case Stats::StrMod: {
			strMod += amount;
			break;
		}
		case Stats::Def: {
			def += amount;
			break;
		}
		case Stats::DefMod: {
			defMod += amount;
			break;
		}
		case Stats::Dex: {
			dex += amount;
			break;
		}
		case Stats::DexMod: {
			dexMod += amount;
			break;
		}
		case Stats::Agil: {
			agil += amount;
			break;
		}
		case Stats::AgilMod: {
			agilMod += amount;
			break;
		}
	}
}
void Character::gain(Stats stat, double percentage) {
	switch(stat) {
		case Stats::None: {
			// do nothing
			cout <<"NoneStat\n";
			break;
		}
		case Stats::Hp: {
			hp += (int) (maxHp * percentage); //special!

			break;
		}
		case Stats::HpMod: {
			hpMod += (int) (hpMod * percentage);
			break;
		}
		case Stats::MaxHp: {
			maxHp += (int) (maxHp * percentage);
			break;
		}
		case Stats::Str: {
			str += (int) (str * percentage);
			break;
		}
		case Stats::StrMod: {
			strMod += (int) (str * percentage);
			break;
		}
		case Stats::Def: {
			def += (int) (def * percentage);
			break;
		}
		case Stats::DefMod: {
			defMod += (int) (def * percentage);
			break;
		}
		case Stats::Dex: {
			dex += (int) (dex * percentage);
			break;
		}
		case Stats::DexMod: {
			dexMod += (int) (dex * percentage);
			break;
		}
		case Stats::Agil: {
			agil += (int) (agil * percentage);
			break;
		}
		case Stats::AgilMod: {
			agilMod += (int) (agil * percentage);
			break;
		}
	}
}
void Character::lose(Stats stat, int amount) {
	gain(stat, -amount);
}
void Character::lose(Stats stat, double percentage) {
	gain(stat, -percentage);
}

void Character::die(Character* enemy = nullptr, Effect* effect = nullptr, string message = "") {
	if(enemy == nullptr && effect == nullptr) {
		println(getName() + " died.");
	} else if(enemy != nullptr && effect != nullptr) {
		// TODO: variety... if effect == bleeding -> stuff........ if effect == burning -> stuff.....
	    println(getName() + " was killed by " + enemy->getName() + " by means of " + effect->getName() + ".");
	} else if(enemy != nullptr && effect == nullptr) {
		println(getName() + " was killed by " + enemy->getName() + ".");
	} else if(enemy == nullptr && effect != nullptr) {
	    println(getName() + " died from being " + effect->getName() + ".");
	} else {
		println("[ERROR: Character::die mathematical laws of binary logic broken]");
	}

    if(message != "")
    	println(message);
}
void Character::sortOutCorpses(vector<Character*> characters) {
	for(int i = 0; i < characters.size(); i++) {
		if(characters.at(i) == nullptr) {
			delete characters.at(i);
			characters.erase(characters.begin() + i);
		}
	}
}
