
using namespace std;

class Bronze : public Material {
public:
    Bronze();
    
private:
};
Bronze::Bronze() 
    : Material("bronze") {
	ID = 3;
	setaSlash(1.2);
	setaStab(1.3);
	setaCrush(1.0);
	setaBash(1);
	setaBlock(.9);
	setaParry(.9);
	setaHurl(1);
	setaWeight(.7);
}
