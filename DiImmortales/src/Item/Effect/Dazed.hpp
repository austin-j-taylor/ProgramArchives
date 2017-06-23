
using namespace std;

class Dazed : public Effect {
public:
	Dazed(double, short);

};
Dazed::Dazed(double potency = -.10, short turnsLeft = 2)
    : Effect("dazed", potency, turnsLeft, false, true) {//, 0, 0) {
	ID = 2;
	setStat(Stats::DexMod);
}
