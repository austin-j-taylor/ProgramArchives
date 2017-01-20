class Consumable : public Item {
private:
	vector<Style> getStyles();
	vector<Usage> getUsages();
public:
	Consumable(string name, Stats* effStats, int* effPotencies, int statCount = 0, bool nIsEaten = true)
			: Item(Basic(), name) {
		setIsEatenRatherThanDrank(nIsEaten);
    	setaHurl(.5);
    	setMaterialNameToDisplay(false);
    	setEffStats(effStats);
//    	println("Effect 0: " + effects.at(0)->getName());
    	setEffPotencies(effPotencies);
    	setStatCount(statCount);
	}
	Consumable(Item*&) {

	}
};

vector<Style> Consumable::getStyles() {
return vector<Style> { Style(Styles::Hurl) };
}
vector<Usage> Consumable::getUsages() {
return vector<Usage> { Usage(Usages::Eat), Usage(Usages::Examine) };
}
