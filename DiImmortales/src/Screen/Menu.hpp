
class Menu {
public:
	static void printLogo1();
	static string loadFile(ifstream&);
};
void Menu::printLogo1() {

	println("");
	println("                                          @@@@@@@    @@");
	println("                                          @@;;:+@@.  @@");
	println("                                          @@     @@  @@");
	println("                                          @@     @@  @@");
	println("                                          @@     @@  @@");
	println("                                          @@     @@  @@");
	println("                                          @@    .@@  @@");
	println("                                          @@@@@@@@   @@");
	println("                                          @@@@@#,    @@");
	println("");
	println("");
	println("");
	println("  ##: ###     ### +###    ###`   `#@@:    ##++++;   ++++++++    ###    :##      `##+++++#   ;@@+");
	println("  @@  +@@     @@;  @@@    @@@   @@@@@@@   @@@@@@@@, @@@@@@@@    @@@     @@       @@@@@@@@  @@@@@@@");
	println("  @@  +@@@   @@@;  @@@   `@@@  @@;    @@  @@     @@    @@       @@@     @@       @@       ,@     @");
	println("  @@  +@@@  `@:@;  @@@@  @@@@  @@     '@. @@     @@    @@      @@ @@    @@       @@       ,@@.");
	println("  @@  +@ @@ @@`@;  @@@@ :@ @@  @#      @' @@@@@@@@.    @@      @' @@    @@       @@@@@@    @@@@@@;");
	println("  @@  +@ @@;@ `@;  @# @@@@ @@  @@     ,@; @@;;+@#      @@     @@```@@   @@       @@          :'@@@");
	println("  @@  +@  @@@ `@;  @+ @@@  @@  @@     @@  @@   @@      @@     @@@@@@@   @@       @@        `    .@.");
	println("  @@  +@  +@  `@;  @+  @@  @@   @@: .@@+  @@    @@     @@    @@     @@  @@.....+ @@....., ;@@. :@@");
	println("  @@  #@   #  .@'  @#  +   @@    @@@@@,   @@    :@@    @@    @@     @@` @@@@@@@@ @@@@@@@@  ;@@@@@");
	println(string(windowWidth, '-'));
}
string Menu::loadFile(ifstream& saveFile) {

	ifstream savesIndex;
	string str;

	savesIndex.open("fileData/savesIndex.txt");

	vector<string> saveNames;
	while(getline(savesIndex, str))
		saveNames.push_back(str);

	int saveNameChoice = Field::choice(saveNames, "Enter Character Name", true);
	if(saveNameChoice == -2) // back
		return "";
//	string name = saveNames.at(saveNameChoice);
	string fileDir = "fileData/saves/" + tostring(saveNameChoice+1)+ "/";
//	string fileDir = "fileData/saves/1/";
	saveFile.open((fileDir + "stats.txt").c_str(), ios_base::in);// | ios::app);

//	saveFile.close();
	savesIndex.close();

	// do stuff w/ save file; load stats/items into player object, etc.

	return fileDir;
}
