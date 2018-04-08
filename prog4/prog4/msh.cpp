#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#define DN "0"
using namespace std; 
map<string, string> sub;
int setvar(vector <string> tokens) {
	if (tokens[2] == DN) {
		tokens.push_back(DN);
		return 1;
	}
	else if (tokens[3] != DN) {
		return 1; 
	}
	else {
		sub[tokens[1]] = tokens[2]; 
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
	if (tokens.size() > 3) {
		cout << "Too many parameters to done." << endl;
	}
	else {
		int retval;
		if (tokens[1] == DN) {
			return -1;

		}
		else {
			if (!isdigit(tokens[1][0])) {
				cout << "Parameter to done must be a non-negative integer." << endl;
				return -1;
			}
			else {
				retval = stoi(tokens[1]);
				if (retval < 0) {
					cout << "Parameter to done must be a non-negative integer." << endl;
					return -1;
				}
				else {
					return retval;
				}
			}
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
		else if (temp != ' ' && temp != NULL) {
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
		if (error) {
			cout << "expected 3 tokens, got " << tokens.size() - 2 << " tokens." << endl;
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
		cout << "invalid command: " << tokens[0] << endl;
	}
	return -1;
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
