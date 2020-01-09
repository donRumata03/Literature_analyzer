#include "utils.h"



bool is_sentence_divider(const char& c) {
	return is_in(c, string(".;!?"));
}

bool is_point(const char& c) {
	return c == '.';
}

inline bool is_excl_mark(const char& c) {
	return c == '!';
}
bool is_interr_mark(const char& c) {
	return c == '?';
}
bool is_point_with_comma(const char& c) {
	return c == ';';
}

int count_points(string &s) {
	return count_if(begin(s), end(s), is_point);
}

int count_excl_marks(string& s) {
	return count_if(begin(s), end(s), is_excl_mark);
}

int count_interr_mark(string& s) {
	return count_if(begin(s), end(s), is_interr_mark);
}

int count_point_with_commas(string& s) {
	return count_if(begin(s), end(s), is_interr_mark);
}



bool is_russian(char c) {
	return (c >= 'À' && c <= 'ß') || (c >= 'à' && c <= 'ÿ');
}
bool is_english(char c) {
	return (c >= 'A'&& c <= 'Z') || (c >= 'a' && c <= 'z');
}
bool is_digit(char c) {
	return (c >= '0' && c <= '9');
}
bool is_spaceive(char c) {
	return (c == '\n' || c == '\t' || c == '\r' || c == ' ');
}

bool from_word(char c) {
	return is_digit(c) || is_russian(c) || is_english(c) || (c == '`');
}


std::string readFile(const char filename []) {
	std::ifstream in(filename, std::ios::in | std::ios::binary);;
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize((const unsigned int)in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	cout << "Can`t find file!!!" << endl;
	return "-1";
}





bool is_word_divider(char c) {
	return !(is_russian(c) || is_english(c) || is_digit(c) || (c == '`'));
}

bool is_sentence_divider(char c) {
	return (c == '.') || (c == ';') || (c == '!') || (c == '?');
}


bool is_big(char c) {
	return (c >= 'A' && c <= 'Z') || ((c >= 'À') && (c <= 'ß'));
}



string cut_spaces(string &s) {
	const char* forbidden{ " \n\t\r" };
	const auto idx_start(s.find_first_not_of(forbidden));
	const auto idx_end(s.find_last_not_of(forbidden));

	return s.substr(idx_start, idx_end - idx_start + 1);
}


vector<string> split(string &s, initializer_list<char> &split_by) {
	vector<string> result;
	uint last_word_beg = 0;
	bool in_word = false;
	uint index = 0, len = s.length();
	uint this_length;
	for (char c : s) {
		if (in(c, split_by)) { // Word spliter detected!
			if (in_word) { // end word
				in_word = false;
				this_length = index - last_word_beg;
				string this_word;
				this_word.reserve(this_length + 1);
				for (int i = last_word_beg; i < index; i++) {
					this_word.push_back(s[i]);
				}
				result.push_back(this_word);
			}
			else { // Still rubbish

			}
		}
		else { // Non word_splitter (letter)
			if (in_word) { // In word => continue cheeling

			}
			else { // Letter => word beginnning
				last_word_beg = index;
				in_word = true;
			}
		}
		index++;
	}

	if (!in(s[len], split_by)) { // // add last word
		this_length = index - last_word_beg;
		string this_word;
		this_word.reserve(this_length);
		for (int i = last_word_beg; i < len; i++) {
			this_word.push_back(s[i]);
		}
		result.push_back(this_word);
	} 

	return result;
}

template<>
string join<vector<string>>(string splitter, vector<string>& container) {
	string res = "";
	int counter = 0;
	res.reserve(2 * container.size() * max(container.at(0).length(), container.at(1).length()));
	for (auto i : container) { res += i; if (counter != container.size() - 1) { res += splitter; } counter++; }
	return res;
}


vector<string> split_lines(string& s) {
	return split(s, *(new initializer_list<char>{ '\n' }));
}

