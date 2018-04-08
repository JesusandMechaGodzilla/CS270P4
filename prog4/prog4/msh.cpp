#include <iostream>
#include <string>
using namespace std; 

string read() {

}
string* tokenizer(string input) {

}
int functions(string* tokens) {

}

void loop() {
	string input; 
	string* tokens;
	int status = 1;
	while (status) {
		input = read();
		tokens = tokenizer(input);
		status = functions(tokens);
		delete tokens; 
	}
}

int main(int argc, char **argv) {
	loop();
	return 0; 
}
