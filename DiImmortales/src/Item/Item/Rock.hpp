#include <vector>

using namespace std;

class Rock : public Item {
public:
	Rock(Material nMaterial = Basic(), string nName = "rock", string nExamine = "A blank-faced rock.")
		: Item(nMaterial, nName, 1, nExamine, false) {
		setaCrush(1.2);
		setaHurl(1.8);
		setaWeight(1.6);
	}
    vector<Usage> getUsages();
    vector<Style> getStyles();
};

vector<Style> Rock::getStyles() {
    return vector<Style> { Style(Styles::Crush), Style(Styles::Block), Style(Styles::Hurl) };
}
vector<Usage> Rock::getUsages() {
    return vector<Usage> {Usage(Usages::Equip), Usage(Usages::Unequip), Usage(Usages::Examine) };
}
