#include <iostream>
#include <string>
using namespace std; 


string read() {
	string input;
	cin >> input; 
	return input; 
}
string* tokenizer(string input) {
	int numToken = 0, aSize = 10, count = 0;
	string token = "";
	string* tokens = new string[size];
	char temp;
	bool cont = true;
	while (cont) {
		temp = input[count];
		if (temp == " ") {
			tokens[numToken] = token;
			token = "";
			numToken++;
		}
		if else (temp == '"') {
			count++;
			temp = input[count];
			while (temp != '"') {
				token = token + temp;
				count++;
				temp = input[count];
			}
			tokens[numToken] = token;
			token = "";
			numToken++;
		}
		token = token + temp;
		count++;
	}



}
int functions(string* tokens) {

}

void loop() {
	string input; 
	string* tokens;
	int status = 1;
	while (status) {
		cout << "> ";
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
