#include <vector>

using namespace std;

class Longsword : public Weapon {
public:
	Longsword(Material nMaterial = Basic(), string nName = "longsword", short nArticle = 3, string nExamine = "a basic longsword.", bool materialExamine = true)
        : Weapon(nMaterial, nName, nArticle, nExamine, materialExamine) {
		ID = 2;
		setMaterialExamine(nMaterial);
    	setaSlash(1.8);
    	setaStab(1.4);
    	setaCrush(1.1);
    	setaParry(2.0);
    	setaHurl(1.2);
    	setaWeight(1.2);
    	seteSlash(new Bleeding(-1));
    	seteStab(new Bleeding(-3));
    }
	void setMaterialExamine(Material);
};

void Longsword::setMaterialExamine(Material material) {
	switch(material.getID()) {
		case 1: {
			// do nothing
			break;
		}
		case 2: {
			setExamineText("a lame, wooden sword.");
			break;
		}
		case 3: {
			setExamineText("A pretty bronze sword. It's pretty pretty.");
			break;
		}
		case 4: {
			setExamineText("An elegant steel longsword. It's got a dragon or some RYUJIN NO KEN O KURAE!! around the hilt.");
			break;
		}
	}
}
