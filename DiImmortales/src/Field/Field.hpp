
using namespace std;

class Field {
public:
	Field() {}
    static int choice(vector<string> options, string message, bool isBackAnOption);
    static string choice(string message);
	virtual int choice(vector<Character*>& enemies) { return 0;	}
private:
    
};
// returned value is player's numerical choice (zero-based, 1 to 5)
int Field::choice(vector<string> options, string message = "", bool isBackAnOption = true) {
    if(message.size() != 0) cout << message << endl;
    
//    if(isBackAnOption) options.push_back("Back");
    for(int i = 0; i < options.size(); i++) {
    	options[i] = capitalize(options[i]); // capitalizes the first letter of each option for printing
        cout << "> " << i + 1 << ") " << options[i] << endl;
    }
    if(isBackAnOption) cout << "> 0) Back" << endl;
    // converts options into uppercase for comparing w/ user input (also converted into uppercase)
    vector<string> optionsUp = options;
    for(int i = 0; i < optionsUp.size(); i++) {
        for(string::size_type j = 0; j < optionsUp[i].length(); j++) {
            optionsUp[i][j] = toupper(options[i][j]);
        }
    }
    // accepts user input
    string choice;
    int parsedChoiceToInt;
    while(true) {
        getline(cin, choice);
        if(choice.size() == 0) continue;
        // converts choice to uppercase for comparing
        for(string::size_type i = 0; i < choice.length(); i++) {
            choice[i] = toupper(choice[i]);
        }
        // tests user choice to be alphabetically or numerically the same as the options
        stringstream convert(choice);
        convert >> parsedChoiceToInt;
        // (first, tests if the user said "Back")
        if(isBackAnOption) if(choice == "BACK" || choice.at(0) == '0') return -2;
        // (then, tests other options)
        for(int i = 0; i < optionsUp.size(); i++) {
            if(choice == optionsUp[i] || ((i == parsedChoiceToInt-1))) {
                return i; // zero-based
            }
        }
//        for(int i = 0; i < optionsUp.size(); i++) {
//            if(choice == optionsUp[i] || (/*(parsedChoiceToInt >= 0) && (parsedChoiceToInt < (sizeof(options)/sizeof(options[0])))
//                        && */(i == parsedChoiceToInt)/* && (options[parsedChoiceToInt] != "")*/)) {
////                cout << "(debug) you decide to " << options[i] << endl;
//                return i;
//            }
//        }
    }
    println("error: Field::choice(arg, arg)");
    return -999;
}
string Field::choice(string message = "") {
    if(message.size() != 0) cout << message << endl;
    string input;
    getline(cin, input);
    return input;
}
