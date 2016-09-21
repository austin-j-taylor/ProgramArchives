
using namespace std;

class Weapon : public Item {
public:
	Weapon(Material nMaterial = Basic(), string nName = "weapon", short nArticle = 0, string nExamine = "It's a weapon.", bool materialExamine = true)
	    : Item(nMaterial, nName, nArticle, nExamine, materialExamine) {
	}
    vector<Style> getStyles();
    vector<Usage> getUsages();
    
private:
};
vector<Style> Weapon::getStyles() {
    return vector<Style> { Style(Styles::Slash), Style(Styles::Stab), Style(Styles::Crush), Style(Styles::Parry), Style(Styles::Hurl) };
}
vector<Usage> Weapon::getUsages() {
    return vector<Usage> { Usage(Usages::Equip), Usage(Usages::Unequip), Usage(Usages::Examine) };
}
