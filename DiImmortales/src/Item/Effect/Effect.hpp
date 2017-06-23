
using namespace std;

class Effect {
public:
	Effect(string, double, short, bool, bool, bool);
//    Effect(string, double, short, int);
//    Effect(string, double, short, double, int);
    
    virtual string getName() { return effectName; }
    virtual double getPotency() { return potency; }
    virtual int getTurnsLeft() { return turnsLeft; }
    void decrementTurn();
    void incrementTurn();
    virtual Stats getStat() { return stat; }
    virtual bool getIsConstant() { return isConstant; }
    virtual bool getIsPercent() { return isPercent; }
    virtual bool getHasDOT() { return hasDOT; }
    virtual void setStat(Stats n) { stat = n; }
    bool operator==(Effect);
    int ID;
    
private:
    string effectName;
    double potency;
    short turnsLeft;
    bool isConstant; // e.g. deals 15 damage
    bool isPercent; // e.g. deals 15% of health
    bool hasDOT; // deals damage every turn rather than just once
//    bool typeOfDOT;
//    double amountDOT;
//    double percentDOT;
    Stats stat;
};
//Effect::Effect(string nEffect = "effected", double nPotency = 0.10, short nTurnsLeft = 1)
//	: Effect(nEffect, nPotency, nTurnsLeft, 0.0, 0) {
//}
//Effect::Effect(string nEffect, double nPotency, short nTurnsLeft, int nAmountDOT)
//    : Effect(nEffect, nPotency, nTurnsLeft, 0.0, nAmountDOT) {
//}
Effect::Effect(string nEffect = "Effect", double nPotency = 0, short nTurnsLeft = 0, bool nHasConstant = true, bool nHasPercent = false, bool nHasDOT = false)
    : ID(0), effectName(nEffect), potency(nPotency), turnsLeft(nTurnsLeft), stat(Stats::None), isConstant(nHasConstant), isPercent(nHasPercent), hasDOT(nHasDOT) {
//	if(percentDOT == 0.0)
//		typeOfDOT = true; // integral
//	else
//		typeOfDOT = false; // percentage
}
bool Effect::operator==(Effect e2) {
    return (this->getName().compare(e2.getName()) == 0);
}
void Effect::decrementTurn() {
	--turnsLeft;
}
void Effect::incrementTurn() {
	++turnsLeft;
}
