
using namespace std;

class Style {
public:
    
    Style();
    Style(Styles);

    string getName();
    string getVerb();
    Styles getStyle() { return style; }
    bool operator==(Style);
    bool operator!=(Style);
    void setSty(Styles s) { style = s; }
    
//private:
    Styles style;
    
};
Style::Style()
    : style(Styles::Slash) {
}
Style::Style(Styles nStyle)
    : style(nStyle) {
}
string Style::getName() {
    switch(style) {
        case 0: return "Slash";
        case 1: return "Stab";
        case 2: return "Crush";
        case 3: return "Bash";
        case 4: return "Block";
        case 5: return "Parry";
        case 6: return "Hurl";
        default: return "";
    }
}
string Style::getVerb() {
    switch(style) {
        case 0: return "slashed";
        case 1: return "stabbed";
        case 2: return "crushed";
        case 3: return "bashed";
        case 4: return "blocked";
        case 5: return "parried";
        case 6: return "threw";
        default: return "";
    }
}
bool Style::operator==(Style u2) {
    return (this->getStyle() == u2.getStyle());
}
bool Style::operator!=(Style u2) {
    return (this->getStyle() != u2.getStyle());
}
