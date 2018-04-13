#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <unistd.h>
#include <sys/wait.h> 
#define DN "0"
using namespace std;
map<string, string> sub = { { "ShowTokens", "0" },{ "PATH", "/bin:/usr/bin" } };
int glob;
vector<string> procs, dprocs;
vector<int> pids;

void myHandler(int sig) {
	pid_t p;
	if ((p = waitpid(-1, &sig, WNOHANG)) != -1) {
		glob = p;
		for (unsigned int i = 0; i < pids.size(); i++) {
			if (p == pids[i]) {
				dprocs.push_back(procs[i]);
				pids.erase(pids.begin() + i);
				procs.erase(procs.begin() + i);
			}
		}
	}
}
int startProcess(vector<string> tokens, int fun) {
	char* temp[100];
	pid_t pid;
	string path = sub["PATH"];
	int retval, status;
	string proc = tokens[1];
	for (unsigned int i = 0; i < tokens.size() - 1; i++) {
		temp[i] = const_cast<char*>(tokens[i + 1].c_str());
	}
	temp[tokens.size() - 2] = '\0';
	pid = fork();
	if (pid == 0) {
		retval = execvp(temp[0], temp);
		if (retval == -1) {
			perror("exec");
			exit(0);
		}
		return -1;
	}
	else if (pid > 0) {
		if (fun == 0) {
			do {
				waitpid(pid, &status, WUNTRACED);
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}
		if (fun == 1) {
			do {
				waitpid(pid, &status, WNOHANG);
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
			procs.push_back(proc);
			pids.push_back(pid);
		}
		return -1;
	}
	else {
		return -1;
	}
}

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
	return -1;
}
int setdir(vector <string> tokens) {
	//char* buf;
	//buf = get_current_dir_name();
	//cout << buf << endl;
	if (tokens.size() == 0) {
		fprintf(stderr, "MSH: expected argument to \"cd\"\n");
	}
	else {
		sub["PATH"] = tokens[1];
		char* temp = const_cast<char*>(tokens[1].c_str());
		if (chdir(temp) != 0) {
			perror("MSH");
		}
	}
	//	buf = get_current_dir_name();
	//	cout << buf  << endl;
	//  free(buf);
	return -1;
}
int setprompt(vector <string> tokens, string & prompt) {
	if (tokens.size() > 3) {
		cout << "Too many parameters to setprompt." << endl;
		return -1;
	}
	else {
		prompt = tokens[1];
		return -1;
	}
}
int showprocs() {
	cout << "Background Processes: " << endl;
	for (unsigned int i = 0; i < procs.size(); i++) {
		cout << "         " << procs[i] << endl;
	}

	return -1;
}
int done(vector <string> tokens) {
	if (tokens.size() > 3) {
		cout << "Too many parameters to done." << endl;
		return -1;
	}
	else {
		int retval;
		if (tokens[1] == DN) {
			return 0;

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

int tovar(vector <string> tokens) {
	return 0;

}
string read(string input) {
	string temp, output;

	for (unsigned int i = 0; i<input.size(); i++) {
		if (input[i] == '^') {
			int j = i + 1;
			while (input[j] != ' ' && input[j] != '"' && input[j] != '\0') {
				temp = temp + input[j];
				j++;
			}
			temp = sub.find(temp)->second;
			if (input[j] == ' ') temp = temp + ' ';
			output = output + temp;
			i = j;
		}
		else {
			output = output + input[i];
		}
	}
	return output;
}
vector <string> tokenizer(string input) {
	int count = -1;
	string token = "";
	vector <string> tokens;
	char temp;
	bool cont = true;
	while (cont) {
		count++;
		temp = input[count];

		if (temp == ' ') {
			while (temp == ' ') {
				count++;
				temp = input[count];
			}
		}
		if (temp == '"') {
			count++;
			temp = input[count];
			while (temp != '"' && temp != '\0') {
				token = token + temp;
				count++;
				temp = input[count];
			}
			tokens.push_back(token);
			token = "";



		}
		else if (temp != ' ' && temp != '\0') {
			while ((temp != ' ') && (temp != '\0')) {
				token = token + temp;
				count++;
				temp = input[count];
			}
			tokens.push_back(token);
			token = "";


			temp = input[count];
		}
		if (temp == '\0' || temp == '#') {
			cont = false;
		}

	}
	tokens.push_back(DN);
	return tokens;


}
int functions(vector <string> tokens, string & prompt) {
	int endval;

	if (sub["ShowTokens"] == "1") {
		for (unsigned int i = 0; i < tokens.size() - 1; i++) {
			cout << "Token :  " << tokens[i] << endl;
		}
	}

	if (tokens[0] == "setvar") {
		if (tokens.size() > 4) {
			cout << "expected 3 tokens, got " << tokens.size() - 1 << " tokens." << endl;
		}
		setvar(tokens);
	}
	else if (tokens[0] == "setprompt") {
		setprompt(tokens, prompt);
	}
	else if (tokens[0] == "setdir") {
		setdir(tokens);

	}
	else if (tokens[0] == "showprocs") {
		showprocs();
	}
	else if (tokens[0] == "done") {
		endval = done(tokens);
		return endval;
	}
	else if (tokens[0] == "run") {
		startProcess(tokens, 0);
	}
	else if (tokens[0] == "fly") {
		startProcess(tokens, 1);

	}
	else if (tokens[0] == "tovar") {
		tovar(tokens);
	}
	else if (tokens[0] == "0") {
	}
	else {
		cout << "invalid command: " << tokens[0] << endl;
	}
	signal(SIGCHLD, myHandler);
	while (dprocs.size() > 0) {
		cout << "Completed:    " << dprocs[dprocs.size() - 1] << endl;
		dprocs.pop_back();
	}
	cout << prompt;
	return -1;
}

void loop() {

	string input, prompt = "msh > ";
	vector <string> tokens;
	int status = -1;
	cout << prompt;
	while (status < 0 && getline(cin, input)) {
		input = read(input);
		tokens = tokenizer(input);
		status = functions(tokens, prompt);
		tokens.clear();
	}
}

int main() {
	loop();
	return 0;
}
