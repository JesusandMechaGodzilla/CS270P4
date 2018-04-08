#include <iostream>
#include <string>
using namespace std; 


string read() {
	string input;
	getline(cin, input);
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
		if (numToken >= aSize) {
			aSize = aSize * 2;
			string* temp = new string[aSize];
			for (int i = 0; i < numToken; i++) {
				temp[i] = token[i];
			}
			delete[] tokens;
			tokens = temp;
		}
		if (temp == ' ') {
			while (temp == ' ') {
				count++;
				temp = input[count];
			}
		}
		if (temp == '"') {
			count++;
			temp = input[count];
			while ((temp != '"') && (temp != NULL)) {
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
		else if (temp != ' ') {
			while ((temp != ' ') && (temp != NULL)) {
				token = token + temp;
				count++;
				temp = input[count];
			}
			tokens[numToken] = token;
			token = "";
			numToken++;
			
			temp = input[count];
		}
		if ((input[count] == NULL) || (input[count] == '#')) {
			cont = false;
		}
	}
	tokens[numToken] = "0";
	return tokens; 


}
int functions(string* tokens) {
	string temp = "";
	int count = 0;
	temp = tokens[count];
	while (temp != "0") {
		

		cout << temp << endl;
		count++; 
		temp = tokens[count];
	}
	return 1;
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
		delete[] tokens; 
	}
}

int main(int argc, char **argv) {
	loop();
	return 0; 
}
