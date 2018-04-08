#include <iostream>
#include <string>
using namespace std; 

int setvar(string* tokens) {
	return 0;
}
int setprompt(string* tokens) {
	return 0;
}
int setdir(string* tokens) {
	return 0;
}
int showprocs(string* tokens) {
	return 0;
}
int done(string* tokens) {
	return 0;
}
int run(string* tokens) {
	return 0;
}
int fly(string* tokens) {
	return 0;
}
int tovar(string* tokens) {
	return 0;

}
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
			while (temp != '"' && temp != NULL) {
				token = token + temp;
				count++;
				temp = input[count];
			}
			tokens[numToken] = token;
			token = "";
			numToken++;
		
			
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
		if (temp == NULL || temp == '#') {
			cont = false;
		}
	}
	tokens[numToken] = "0";
	return tokens; 


}
int functions(string* tokens) {
	if (tokens[0] == "setvar") {
		setvar(tokens);
	}
	else if (tokens[0] == "setprompt") {
		setprompt(tokens);
	}
	else if (tokens[0] == "setdir") {
		setdir(tokens);

	}
	else if (tokens[0] == "showprocs") {
		showprocs(tokens);
	}
	else if (tokens[0] == "done") {
		done(tokens);
	}
	else if (tokens[0] == "run") {
		run(tokens);
	}
	else if (tokens[0] == "fly") {
		fly(tokens);

	}
	else if (tokens[0] == "tovar") {
		tovar(tokens);
	}
	else {
		cout << "invalid command: " << tokens[0]; 
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
