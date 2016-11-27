
using namespace std;

class Material {
public:
    Material(string);
    int ID;
    
    bool operator==(Material);
    string getName() { return material; }
    virtual double getAffinity(Style style);
    virtual void setaSlash(double n) { affSlash = n;}
    virtual void setaStab(double n) { affStab = n; }
    virtual void setaCrush(double n) { affCrush = n; }
    virtual void setaBash(double n) { affBash = n; }
    virtual void setaBlock(double n) { affBlock = n; }
    virtual void setaParry(double n) { affParry = n; }
    virtual void setaHurl(double n) { affHurl = n; }
    virtual void setaWeight(double n) { affWeight = n; }
    
    virtual double getaWeight() { return affWeight; }
    virtual int getID() { return ID; }

private:
    string material;
    
    double affSlash;
    double affStab;
    double affCrush;
    double affBash;
    double affBlock;
    double affParry;
    double affHurl;
    double affWeight;
};
Material::Material(string nMaterial = "basic")
    : material(nMaterial), affSlash(1), affStab(1), affCrush(1), affBash(1), affBlock(1), affParry(1), affHurl(1), affWeight(1), ID(0) {
}
bool Material::operator==(Material e2) {
    return (this->getName().compare(e2.getName()) == 0);
}
double Material::getAffinity(Style style) {
	switch(style.getStyle()) {
		case Styles::Slash: return affSlash;
		case Styles::Stab: return affStab;
		case Styles::Crush: return affCrush;
		case Styles::Bash: return affCrush;
		case Styles::Block: return affBlock;
		case Styles::Parry: return affParry;
		case Styles::Hurl: return affCrush;
	}
}
