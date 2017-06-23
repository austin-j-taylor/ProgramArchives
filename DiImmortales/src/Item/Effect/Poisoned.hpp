
using namespace std;

class Poisoned : public Effect {
public:
	Poisoned(double, short);//, double);

};
Poisoned::Poisoned(double potency = -0.10, short turnsLeft = 3)//, double DOT = 0.15)
    : Effect("poisoned", potency, turnsLeft, false, true, true) { //, DOT) {
	ID = 4;
	setStat(Stats::Hp);
}
