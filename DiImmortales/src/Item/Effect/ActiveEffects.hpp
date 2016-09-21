
using namespace std;

class ActiveEffects {
public:
    ActiveEffects(vector<Effect*> nEffects);
    short getCount() { return count; }
    vector<Effect*> getEffects() { return effects; }
    short indexOf(string);
//    void decrementTurn(Effect*);
//    void decrementTurn(string);
//    void decrementTurn();

    Effect* addEffect(Effect*);
    void removeEffect(Effect*);
    void removeEffect(string);
private:
    short count;
    vector<Effect*> effects;
};

ActiveEffects::ActiveEffects(vector<Effect*> nEffects = {})
    : count(0)  {
    for(auto effect : nEffects) {
        addEffect(effect);
    }
}
short ActiveEffects::indexOf(string effectName) {
	for(int i = 0; i < count; i++) {
		if(effects[i]->getName() == effectName) {
			return i;
		}
	}
	return -1;
}

Effect* ActiveEffects::addEffect(Effect* effect) {

    effects.push_back(effect);
    count++;
    return effect;
}
//void ActiveEffects::decrementTurn(Effect* effect) {
//	if(effect->decrementTurn() == 0) {
//		removeEffect(effect);
//		return;
//	}
//}
//void ActiveEffects::decrementTurn(string effectName) {
//	int i = indexOf(effectName);
//	decrementTurn(effects[i]);
//}
//void ActiveEffects::decrementTurn() {
//	for(Effect* effect : effects) {
//		decrementTurn(effect);
//	}
//}
void ActiveEffects::removeEffect(Effect* effect) {
	if(find(effects.begin(), effects.end(), effect) == effects.end()) {
		println("[ERROR: Effect " + effect->getName() + " not found]");
		return;
	}
	effects.erase(find(effects.begin(), effects.end(), effect));
	count--;
}
void ActiveEffects::removeEffect(string effectName) {
	int i = indexOf(effectName);
	removeEffect(effects[i]);
}
