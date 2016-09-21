
using namespace std;

class Buckler : public Shield {
public:
	Buckler(Material nMaterial = Basic(), string nName = "buckler", short nArticle = 3, string nExamine = "It's a buckler shield.", bool materialExamine = true)
		: Shield(nMaterial, nName, nArticle, nExamine, materialExamine) {
		setMaterialExamine(nMaterial);
		setaBash(1.3);
		setaBlock(1.8);
		setaHurl(.5);
		setaWeight(0.5);
}

    void setMaterialExamine(Material);
};

void Buckler::setMaterialExamine(Material material) {
	switch(material.getID()) {
		case 1: {
			// do nothing
			break;
		}
		case 2: {
			setExamineText("It's a classic yellow and green wooden buckler shield. Its paint is divided into quarters, with each opposing pair having the same color.");
			break;
		}
		case 3: {
			break;
		}
		case 4: {
			break;
		}
	}
}
