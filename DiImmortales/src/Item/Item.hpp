
using namespace std;

class Item {
private:
    string name;
    string specialName;
    string examineText;
    bool usesMaterialName;
	bool isEatenRatherThanDrank;
    Material material;
    Effect* specialEffect;

	Stats* effectedStatsWhenEaten;
	vector<Effect*> effectsWhenEaten;
	int* effectedPotenciesWhenEaten;
	int statCountWhenEaten;

    // affinities of an item's (weapon's) to deal damage or effects (stabbing -> bleeding) based on material
    // derived classes will only override those that have special bonuses, such as an extra-stabbing sword
    // basic range: (0, 1]
    double affSlash;
    double affStab;
    double affCrush;
    double affBash;
    double affBlock;
    double affParry;
    double affHurl;
    double affWeight;

    bool hasSpecialName = false;
    bool hasSpecialExamine = false;
    bool hasSpecialSlash = false;
    bool hasSpecialCrush = false;
    bool hasSpecialStab = false;
    bool hasSpecialBlock = false;
    bool hasSpecialBash = false;
    bool hasSpecialParry = false;
    bool hasSpecialHurl = false;
    bool hasSpecialWeight = false;

    string verbSlash;
    string verbStab;
    string verbCrush;
    string verbBash;
    string verbBlock;
    string verbParry;
    string verbHurl;

    Effect* effSlash;
    Effect* effStab;
    Effect* effCrush;
    Effect* effBash;
    Effect* effBlock;
    Effect* effParry;
    Effect* effHurl;

    short Article;
public:
//	Item(Material, string);
//    Item(Material, string, string);
    Item(Material, string, short, string, bool);
    virtual ~Item() {}
    string getName() {
//    	if(hasSpecialName)
//    		return specialName;
    	if(usesMaterialName)
			return material.getName() + " " + name;
    	return name;
    }
    bool getHasSpecialExamine() { return hasSpecialExamine; }
    bool getHasSpecialName() { return hasSpecialName; }
    bool getHasSpecialSlash() { return hasSpecialSlash; }
    bool getHasSpecialCrush() { return hasSpecialCrush; }
    bool getHasSpecialStab() { return hasSpecialStab; }
    bool getHasSpecialBlock() { return hasSpecialBlock; }
    bool getHasSpecialBash() { return hasSpecialBash; }
    bool getHasSpecialParry() { return hasSpecialParry; }
    bool getHasSpecialHurl() { return hasSpecialHurl; }
    bool getHasSpecialWeight() { return hasSpecialWeight; }

    bool getUsesMaterialName() { return usesMaterialName; }
	bool getIsEaten() { return isEatenRatherThanDrank; }
    string getExamineText() { return examineText; }
    virtual double getAffinity(Style style);
    virtual double getWeight() { return affWeight; }
    virtual Material getMaterial() { return material; }
    virtual vector<Usage> getUsages();
    virtual vector<Style> getStyles();
    virtual string getVerb(Style style);
    virtual string article();

    virtual Stats* getEffStats() { return effectedStatsWhenEaten; }
    virtual vector<Effect*> getEffects() { return effectsWhenEaten; }
    virtual int* getEffPotencies() { return effectedPotenciesWhenEaten; }
	virtual int getStatCount() { return statCountWhenEaten; }

    int ID;

    virtual void setName(string ex) { name = ex; }
    virtual void setExamineText(string ex) {
    		examineText = ex;
    }
    // overloaded by subclasses
    virtual void setHasSpecialExamine(bool set) { hasSpecialExamine = set; }
    virtual void setHasSpecialName(bool set) { hasSpecialName = set; }
    virtual void sethasSpecialSlash(bool set) { hasSpecialSlash = set; }
    virtual void sethasSpecialCrush(bool set) { hasSpecialCrush = set; }
    virtual void sethasSpecialStab(bool set) { hasSpecialStab = set; }
    virtual void sethasSpecialBlock(bool set) { hasSpecialBlock = set; }
    virtual void sethasSpecialBash(bool set) { hasSpecialBash = set; }
    virtual void sethasSpecialParry(bool set) { hasSpecialParry = set; }
    virtual void sethasSpecialHurl(bool set) { hasSpecialHurl = set; }
    virtual void sethasSpecialWeight(bool set) { hasSpecialWeight = set; }
    virtual void setIsEatenRatherThanDrank(bool set) { isEatenRatherThanDrank = set; }
    virtual void setMaterialExamine(Material material) {};
    // read "Wooden sword" instead of "Sword" and use default examine text from the weapon's material.
    virtual void setMaterialNameToDisplay(bool set) {
    	usesMaterialName = set;
    }
    virtual void setMaterial(Material nMaterial) {
    	material = nMaterial;
    }
    virtual void setArticle(short a) { Article = a; }

    virtual void setEffStats(Stats* set) { effectedStatsWhenEaten = set; }
    virtual void setEffects(vector<Effect*> set) { effectsWhenEaten = set; }
    virtual void setEffPotencies(int* set) { effectedPotenciesWhenEaten = set; }
    virtual void setStatCount(int set) { statCountWhenEaten = set; }

    virtual void setvSlash(string s) { verbSlash = s; }
    virtual void setvStab(string s) { verbStab = s; }
    virtual void setvCrush(string s) { verbCrush = s; }
    virtual void setvBash(string s) { verbBash = s; }
    virtual void setvBlock(string s) { verbBlock = s; }
    virtual void setvParry(string s) { verbParry = s; }
    virtual void setvHurl(string s) { verbHurl = s; }

    virtual void setaSlash(double n) { affSlash = n; }
    virtual void setaStab(double n) { affStab = n; }
    virtual void setaCrush(double n) { affCrush = n; }
    virtual void setaBash(double n) { affBash = n; }
    virtual void setaBlock(double n) { affBlock = n; }
    virtual void setaParry(double n) { affParry = n; }
    virtual void setaHurl(double n) { affHurl = n; }

    virtual void setaWeight(double n) { affWeight = n; }


    // called when a character uses/eats/etc. this item:
    virtual void use();
    virtual void eat();
    virtual void equip();
    virtual void unequip();
    virtual void examine();

    // parses Effect**s to decide which function to call
    Effect* styleEffect(Style);
    Effect* usageEffect(Usage);
    // returns special effect specific to weapon
    Effect* getSpecialEffect() { return specialEffect; }
    // effects returned when this item is slashed with/used with, etc.
    virtual void seteSlash(Effect* effect) { effSlash = effect; }
    virtual void seteStab(Effect* effect) { effStab = effect; }
    virtual void seteCrush(Effect* effect) { effCrush = effect; }
    virtual void seteBash(Effect* effect) { effBash = effect; }
    virtual void seteBlock(Effect* effect) { effBlock = effect; }
    virtual void seteParry(Effect* effect) { effParry = effect; }
    virtual void seteHurl(Effect* effect) { effHurl = effect; }
//    virtual Effect* slashEffect();
//    virtual Effect* stabEffect();
//    virtual Effect* crushEffect();
//    virtual Effect* bashEffect();
//    virtual Effect* blockEffect();
//    virtual Effect* parryEffect();
//    virtual Effect* hurlEffect();
    
    virtual Effect* useEffect();
    virtual Effect* eatEffect();
    virtual Effect* equipEffect();
    virtual Effect* unequipEffect();
};

Item::Item(Material nMaterial = Basic(), string nName = "Item", short nArticle = 0, string nExamine = "it's an Item.", bool nMaterialName = true)
    : ID(0), name(nName), usesMaterialName(nMaterialName), Article(nArticle), examineText(nExamine), material(nMaterial), specialEffect(nullptr),
	  affSlash(1), affCrush(1), affStab(1), affBlock(1), affBash(1), affParry(1), affHurl(1), affWeight(1.0),
	  verbSlash(""), verbStab(""), verbCrush(""), verbBash(""), verbBlock(""), verbParry(""), verbHurl(""),
	  effSlash(nullptr), effStab(nullptr), effCrush(nullptr), effBash(nullptr), effBlock(nullptr), effParry(nullptr), effHurl(nullptr) {
	hasSpecialExamine = false;
	hasSpecialName = false;
	specialName = "";
}

void Item::use() {
    
}
void Item::eat() {
    
}
void Item::equip() {
    
}
void Item::unequip() {

}
void Item::examine() {
	println(examineText);
}

vector<Usage> Item::getUsages() {
    return vector<Usage> { Usage(Usages::Use), Usage(Usages::Eat), Usage(Usages::Equip), Usage(Usages::Unequip), Usage(Usages::Examine) };
}
vector<Style> Item::getStyles() {
    return vector<Style> { Style(Styles::Slash), Style(Styles::Stab), Style(Styles::Crush), Style(Styles::Bash), Style(Styles::Block), Style(Styles::Parry), Style(Styles::Hurl) };
}
string Item::article()  {
	switch(Article) {
		case 0: return "a ";
		case 1: return "the ";
		case 2: return " "; // unique/legendary things that are like proper nouns
		case 3: return ""; // replaced by character's possessive pronoun
	}
}
Effect* Item::styleEffect(Style style) {
	switch(style.getStyle()) {
	case Styles::Slash: return effSlash;
	case Styles::Stab: return effStab;
	case Styles::Crush: return effCrush;
	case Styles::Bash: return effBash;
	case Styles::Block: return effBlock;
	case Styles::Parry: return effParry;
	case Styles::Hurl: return effHurl;
	}
}
Effect* Item::usageEffect(Usage usage) {
	switch(usage.getUsage()) {
	case Usages::Use: return useEffect();
	case Usages::Eat: return eatEffect();
	case Usages::Equip: return equipEffect();
	case Usages::Unequip: return unequipEffect();
	}
}
string Item::getVerb(Style style) {
	switch (style.getStyle()) {
		case Styles::Slash: {
				return (verbSlash == "") ? style.getVerb() : verbSlash;
				break;
			}
			case Styles::Stab: {
				return (verbStab == "") ? style.getVerb() : verbStab;
				break;
			}
			case Styles::Crush: {
				return (verbCrush == "") ? style.getVerb() : verbCrush;
				break;
			}
			case Styles::Bash: {
				return (verbBash == "") ? style.getVerb() : verbBash;
				break;
			}
			case Styles::Block: {
				return (verbBlock == "") ? style.getVerb() : verbBlock;
				break;
			}
			case Styles::Parry: {
				return (verbParry == "") ? style.getVerb() : verbParry;
				break;
			}
			case Styles::Hurl: {
				return (verbHurl == "") ? style.getVerb() : verbHurl;
				break;
			}
		}
	}
//Effect* Item::slashEffect() {
////	return Effect*();
//	return nullptr;
//}
//Effect* Item::stabEffect() {
//	return nullptr;
//}
//Effect* Item::crushEffect() {
//	return nullptr;
//}
//Effect* Item::blockEffect() {
//	return nullptr;
//}
//Effect* Item::bashEffect() {
//	return nullptr;
//}
//Effect* Item::parryEffect() {
//	return nullptr;
//}
//Effect* Item::hurlEffect() {
//	return nullptr;
//}

Effect* Item::useEffect() {
	return nullptr;
}
Effect* Item::eatEffect() {
	return nullptr;
}
Effect* Item::equipEffect() {
	return nullptr;
}
Effect* Item::unequipEffect() {
	return nullptr;
}

double Item::getAffinity(Style style) {
	switch(style.getStyle()) {
		case Styles::Slash: return affSlash;
		case Styles::Stab: return affStab;
		case Styles::Crush: return affCrush;
		case Styles::Bash: return affBash;
		case Styles::Block: return affBlock;
		case Styles::Parry: return affParry;
		case Styles::Hurl: return affHurl;
		default: cout << "error: Item::getAffinity()";
	}
}

