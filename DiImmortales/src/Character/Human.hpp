
using namespace std;

class Human : public Character {
public:
    Human();
    Human(string, string, string, short, int, int, int, int, int, Item*);

private:
};
Human::Human()
    : Character() {
}
Human::Human(string nName, string nIntro, string nAnalyze, short nGender, int nHp, int nStr, int nDef, int nDex, int nAgil, Item* EHE = new HumanFist())
    : Character(nName, nIntro, nAnalyze, nGender, nHp, nStr, nDef, nDex, nAgil, EHE) {
	setArmCount(2);
}
