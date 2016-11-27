
using namespace std;

class Steel : public Material {
public:
	Steel();

private:
};
Steel::Steel()
    : Material("steel") {
	ID = 4;
	setaSlash(1.4);
	setaStab(1.3);
	setaCrush(1.6);
	setaBash(1.5);
	setaBlock(1.4);
	setaParry(1.4);
	setaHurl(.8);
	setaWeight(1.0);
}
