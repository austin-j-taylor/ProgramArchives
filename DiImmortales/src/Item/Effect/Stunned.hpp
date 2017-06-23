
using namespace std;

class Stunned : public Effect {
public:
    Stunned(double, short);

};
Stunned::Stunned(double potency = 0, short turnsLeft = 1)
    : Effect("stunned", potency, turnsLeft) {
	ID = 1;
	setStat(Stats::None);
}
