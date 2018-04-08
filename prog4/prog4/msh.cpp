#include <iostream>
#include <string>
#include <vector>
#define DN "0"
using namespace std; 

int setvar(vector <string> tokens) {
	if (tokens[3] != "0") {
		return 1; 
	}
	return 0;
}
int setprompt(vector <string> tokens) {
	return 0;
}
int setdir(vector <string> tokens) {
	return 0;
}
int showprocs(vector <string> tokens) {
	return 0;
}
int done(vector <string> tokens) {
	int retval;
	if (tokens[1] == DN) {
		return -1;

	}
	else {
		if (stoi(tokens[1])) {
			retval = stoi(tokens[1]);
			cout << retval;
			return retval;
		}
		else {
			cout << "Parameter to done must be a non-negative integer";
		}
	}
}
int run(vector <string> tokens) {
	return 0;
}
int fly(vector <string> tokens) {
	return 0;
}
int tovar(vector <string> tokens) {
	return 0;

}
string read() {
	string input;
	getline(cin, input);
	return input;
}
vector <string> tokenizer(string input) {
	int count = 0;
	string token = "";
	vector <string> tokens;
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
			while (temp != '"' && temp != NULL) {
				token = token + temp;
				count++;
				temp = input[count];
			}
			tokens.push_back(token);
			token = "";

		
			
		}
		else if (temp != ' ') {
			while ((temp != ' ') && (temp != NULL)) {
				token = token + temp;	
				count++;
				temp = input[count];
			}
			tokens.push_back(token);
			token = "";
			
			
			temp = input[count];
		}
		if (temp == NULL || temp == '#') {
			cont = false;
		}
	}
	tokens.push_back(DN); 
	return tokens; 


}
int functions(vector <string> tokens) {
	int error; 
	if (tokens[0] == "setvar") {
		error = setvar(tokens);
		if (!error) {
			cout << "expected 3 tokens, got" << tokens.size() << "tokens.";
		}
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
	vector <string> tokens;
	int status = -1;
	while (status < 0) {
		cout << "> ";
		input = read();
		tokens = tokenizer(input);
		status = functions(tokens);
		tokens.clear();
	}
}

int main(int argc, char **argv) {
	loop();
	return 0; 
}
