class Apple : public Consumable {
private:
	Stats stats[2] { Hp, StrMod };
	vector<Effect*> effects = { new Stunned(), new Bleeding() };
	int potencies[2] { 20, -5 };
public:
	Apple() : Consumable("Apple", stats, potencies, 2, true) {
		setExamineText("A Golden Delicious apple. The name is a lie. Eating it will heal 20 hp but stun you and cause lacerations of the throat. It also decreases your strength.\nYou know, this is actually a pretty terrible healing item.");
    	setEffects(effects);
	}
};
