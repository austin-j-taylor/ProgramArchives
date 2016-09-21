
using namespace std;

class Shield : public Item {
public:
	Shield(Material nMaterial = Basic(), string nName = "shield", short nArticle = 0, string nExamine = "It's a shield.", bool materialExamine = true)
		: Item(nMaterial, nName, nArticle, nExamine, materialExamine) {
}

    vector<Style> getStyles();
    vector<Usage> getUsages();


private:
};
vector<Style> Shield::getStyles() {
    return vector<Style> { Style(Styles::Bash), Style(Styles::Block), Style(Styles::Hurl) };
}
vector<Usage> Shield::getUsages() {
    return vector<Usage> { Usage(Usages::Equip), Usage(Usages::Unequip), Usage(Usages::Examine) };
}
