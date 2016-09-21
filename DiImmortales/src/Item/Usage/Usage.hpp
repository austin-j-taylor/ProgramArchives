
using namespace std;

class Usage {
public:
    
    Usage();
    Usage(Usages);
    
    Usages getUsage() { return usage; }
    string getName();
    bool operator==(Usage);
    
private:
    Usages usage;
    
};
Usage::Usage()
    : usage(Usages::Use) {
}
Usage::Usage(Usages nUsage)
    : usage(nUsage) {
}
string Usage::getName() {
    switch(usage) {
        case 0: return "Use";
        case 1: return "Eat";
        case 2: return "Equip";
        case 3: return "Unequip";
        case 4: return "Examine";
        default: return "";
    }
}
bool Usage::operator==(Usage u2) {
    return (this->getUsage() == u2.getUsage());
}
