#include <vector>

using namespace std;

class Dagger : public Weapon {
public:
    Dagger(Material nMaterial = Basic(), string nName = "dagger", short nArticle = 3, string nExamine = "a basic dagger.", bool materialExamine = true)
        : Weapon(nMaterial, nName, nArticle, nExamine, materialExamine) {
    	ID = 3;
    	setMaterialExamine(nMaterial);
    	setvHurl("fired");
    	setaSlash(1.2);
    	setaStab(1.8);
    	setaCrush(.7);
    	setaParry(.8);
    	setaHurl(3);
    	setaWeight(0.7);
    	seteStab(new Bleeding(-2));
    }
    void setMaterialExamine(Material);
};
void Dagger::setMaterialExamine(Material material) {
	switch(material.getID()) {
		case 1: {
			// do nothing
			break;
		}
		case 2: {
			setExamineText("a lame, wooden dagger.");
			break;
		}
		case 3: {
			setExamineText("A crude yet surreptitious bronze dagger with rough, ancient decor. Flakes of sea-green patina oxidation cover its surface. "
            "In a different time, it may have been an elegant weapon.");
			break;
		}
		case 4: {
			setExamineText("An elegant steel dagger.");
			break;
		}
	}
}
