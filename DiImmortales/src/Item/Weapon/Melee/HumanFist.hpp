class HumanFist : public Weapon {
public:
	HumanFist(string, string);
	vector<Style> getStyles();
private:

};
HumanFist::HumanFist(string nName = "fist", string nExamine = "It's a fist.")
	: Weapon(Basic(), nName, 3, nExamine, false) {
	setvCrush("punched");
	setaCrush(.7);
	setaParry(.2);
	setaWeight(0.5);
}
vector<Style> HumanFist::getStyles() {
    return vector<Style> { Style(Styles::Crush), Style(Styles::Parry) };
}
