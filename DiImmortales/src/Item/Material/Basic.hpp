
using namespace std;

class Basic : public Material {
public:
    Basic();
    
private:
};
Basic::Basic() 
    : Material("basic") {
	ID = 1;
}
