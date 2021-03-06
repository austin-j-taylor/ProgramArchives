#include <vector>

using namespace std;

class Rock : public Item {
public:
	Rock(Material nMaterial = Basic(), string nName = "rock", string nExamine = "According to all known laws of aviation, there is no way a bee should be able to fly. Its wings are too small to get its fat little body off the ground. The bee, of course, flies anyway  because bees don't care what humans think is impossible.")//"A smooth, fist-sized river rock. She is also the president of Night Vale Community College.")
		: Item(nMaterial, nName, 1, nExamine, false) {
		ID = 4;
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
