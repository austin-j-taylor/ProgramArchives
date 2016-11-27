
using namespace std;

class Wooden : public Material {
public:
    Wooden();

private:
};
Wooden::Wooden()
    : Material("wooden") {
	ID = 2;
	setaSlash(.4);
	setaStab(.2);
	setaCrush(.6);
	setaBash(.6);
	setaBlock(.7);
	setaParry(1.5);
	setaHurl(.7);
	setaWeight(.5);
}
