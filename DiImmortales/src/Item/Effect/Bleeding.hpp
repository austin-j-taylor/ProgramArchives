
using namespace std;

class Bleeding : public Effect {
public:
	Bleeding(double, short);//, int);

};
Bleeding::Bleeding(double potency = -3, short turnsLeft = 3)//, int DOT = 3)
    : Effect("bleeding", potency, turnsLeft, true, false, true) { //, DOT) {
	ID = 3;
	setStat(Stats::Hp);
}
