
using namespace std;

class Human : public Character {
public:
    Human();
    Human(string, string, string, short, int, int, int, int, int, Item*, int, int, int, int, int);

private:
};
Human::Human() : Character() {
	setArmCount(2);
}
Human::Human(string nName, string nIntro, string nAnalyze, short nGender, int nHp, int nStr, int nDef, int nDex, int nAgil,
		Item* EHE = new HumanFist, int nHpMod = 0, int nStrMod = 0, int nDefMod = 0, int nDexMod = 0, int nAgilMod = 0)
    : Character(nName, nIntro, nAnalyze, nGender, nHp, nStr, nDef, nDex, nAgil, EHE, nHpMod, nStrMod, nDefMod, nDexMod, nAgilMod) {
	setArmCount(2);
}
