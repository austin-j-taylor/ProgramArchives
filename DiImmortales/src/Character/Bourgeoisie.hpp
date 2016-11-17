
using namespace std;

class Bourgeoisie : public Human {
public:
	Bourgeoisie();
	Bourgeoisie(string, string, string, short, int, int, int, int, int);
//    int attack(Character*, Item*, Style);
    // does not override takeDamage/Effect()
    
private:
};
Bourgeoisie::Bourgeoisie()
    : Human() {
}
Bourgeoisie::Bourgeoisie(string nName = "Bourgeoisie", string nIntro = "Bourgeoisie wants to play (with your tax dollars).", string nAnalyze = "", short nGender = 0, int nHp = 30, int nStr = 11, int nDef = 10, int nDex = 5, int nAgil = 5)
    : Human(nName, nIntro, nAnalyze, nGender, nHp, nStr, nDef, nDex, nAgil) {
	// short-cut for having a default value that can access the Bourgeoisie's gender.
	setAnalyze( (nAnalyze.size() != 0) ? nAnalyze :  "A filthy, capitalist pig; " + getPsub() + "appears to hold some means of production. Take them back." );

}
