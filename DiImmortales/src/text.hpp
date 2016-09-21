#include <string.h>
#include <stdio.h>

using namespace std;

class text {
public:
//	static void print(string);
//	static void println(string);
	static string word_wrap (char*, string, int);
	/*
	   This function takes a string and an output buffer and a desired width. It then copies
	   the string to the buffer, inserting a new line character when a certain line
	   length is reached.  If the end of the line is in the middle of a word, it will
	   backtrack along the string until white space is found.
	 */

	/*
	 * when printing something out using the wrapping function, CAPITALIZE:
	 * at START OF BUFFER or NEWLINE
	 * after a PERIOD, SEMICOLON, COLON
	 * when in Field::choice's options (will simply use another function from here)
	 *
	 *
	 */
};
string tostring(int i)
{
    stringstream ss;
    ss << i;
    return ss.str();
}
string tostring(long i)
{
    stringstream ss;
    ss << i;
    return ss.str();
}
string tostring(float i)
{
    stringstream ss;
    ss << i;
    return ss.str();
}
string tostring(double i)
{
    stringstream ss;
    ss << i;
    return ss.str();
}
string tostring(short i)
{
    stringstream ss;
    ss << i;
    return ss.str();
}
string tostring(bool i)
{
    return (i) ? "true" : "false";
}
// capitalizes the first letter of word
string capitalize(string word) {
	word[0] = toupper(word[0]);
	return word;
}
void print(string string = "") {
	if(string == "")
		return;
	// buffer for storing the resultant string - make sure its large enough!
	char* buffer;
	buffer = new char[string.size()+1];
	cout << text::word_wrap(&buffer[0], capitalize(string), windowWidth);

}
void println(string string = "") {
	print(string);
	cout << endl;
}

string text::word_wrap (char* buffer, string string, int line_width) {
	int i;
	int k;
	int counter;

	i = 0;
	while(i < string.size()) {

		// copy string until the end of the line is reached
		for (counter = 1; counter <= line_width; counter++) {
			// check if end of string reached
			if (i == string.size()) {
				buffer[i] = 0;
				return buffer;
			}
			buffer[i] = string[i];
			// check for newlines embedded in the original input
			// and reset the index
			if (buffer[i] == '\n') {
				counter = 1;
			}
			i++;
		}
		// check for nearest whitespace back in string
		for (k = i; k > 0; k--) {
			if (isspace(string[k])) {
				buffer[k] = '\n';
				// set string index back to character after this one
				i = k + 1;
				break;
			}
		}
	}
	buffer[i] = 0;

	return buffer;
}
