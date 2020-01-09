#include "Language.h"

using namespace std;



string get_root(string &word) {
	return word;
}


string get_common_form(string &root, map<string, string> dict) {
	// TODO: Improve this function
	return dict[root];
}



bool is_russian(string& word) {
	for (char c : word) {
		if (!is_russian(c)) {
			return false;
		}
	}
	return true;
}

bool is_english(string& word) {
	for (char c : word) {
		if (!is_english(c)) {
			return false;
		}
	}
	return true;
}

bool is_digital(string &word) {
	for (char c : word) {
		if (!is_digit(c)) {
			return false;
		}
	}
	return true;
}


bool is_preposition(string &word, vector<string> &preposes) {
	if (word.length() == 1) return true;
	for (string prepos : preposes) {
		if (prepos == word) return true;
	}
	return false;
}

bool is_preposition(string& word, initializer_list<string> preposes) {
	if (word.length() == 1) return true;
	for (string prepos : preposes) {
		if (prepos == word) return true;
	}
	return false;
}


bool is_noun() {
	return false;
}


map<string, string> load_prepositions() {
	const string path = "res/language/input/prepositions.txt";
	return map<string, string>();
}