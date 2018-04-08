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
	string* tokens = new string[aSize];
	char temp;
	bool cont = true;		
	temp = input[count];
	while (cont) {
		if (temp == ' ') {
			while (temp == ' ') {
				count++;
				temp = input[count];
			}
		}
		if (temp == '"') {
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
			count++;
			temp = input[count];
		}
		if else (temp != ' ') {
			while (temp != ' ') {
				token = token + temp;
				count++;
				temp = input[count];
			}
			tokens[numToken] = token;
			token = "";
			numToken++;
			count++;
			temp = input[count];
		}
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
