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
		contents.resize(static_cast<const unsigned int>(in.tellg()));
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	cout << "Can`t find file!!! " << endl;
	cout << "( " << filename << " )" << endl;
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

string cut_bad_symbols(string& s)
{
	size_t idx_first = 0, idx_last = s.size();
	for(size_t i = 0; i < s.length(); i++)
	{
		char c = s.at(i);
		if (is_digit(c) || is_russian(c) || is_english(c))
		{
			idx_first = i;
			break;
		}
	}

	for (long long i = s.length() - 1; i >= 0; i--)
	{
		char c = s.at(i);
		if (is_digit(c) || is_russian(c) || is_english(c)) {
			idx_last = i + 1;
			break;
		}
	}

	return Slice(s, idx_first, idx_last);
}


vector<string> split(const string &s, const initializer_list<char> &&split_by) {
	return split(s, vector(split_by));
}

vector<string> split(const string& s, const vector<char>& split_by)
{
	vector<string> result;
	uint last_word_beg = 0;
	bool in_word = false;
	uint index = 0, len = s.length();
	size_t this_length;
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

	if (!s.empty() && !in(s[len - 1], split_by)) { // // add last word
		this_length = index - last_word_beg;
		string this_word;
		this_word.reserve(this_length);
		for (int i = last_word_beg; i < len; i++) {
			this_word.push_back(s[i]);
		}
		result.push_back(this_word);
	}
	if (!result.empty())	return result;
	return vector<string>();
}


template<>
string join<vector<string>>(const string splitter, vector<string>& container) {
	string res;
	uint counter = 0;
	res.reserve(2 * container.size() * max(container.at(0).length(), container.at(1).length()));
	for (const auto &i : container) { res += i; if (counter != container.size() - 1) { res += splitter; } counter++; }
	return res;
}


vector<string> split_lines(string& s) {
	return split(s, { '\n' });
}



size_t find_first_not_english(string& s, size_t offset)
{
	return find_first_for_which_true(s, [](char c) {	return !is_english(c); }, offset);
}
size_t find_first_russian(string& s, size_t offset)
{
	return find_first_for_which_true(s, [](char c) {	return is_russian(c); }, offset);
}

map<string, vector<string>> common_mylang_parse(string& s, initializer_list<char>&& data_ignore, initializer_list<char>&& space_ignore)
{
	vector<char> resultive_data_ignore = {' ', '\n', '\t', '\r'};
	for(auto& p : data_ignore) resultive_data_ignore.push_back(p);
	auto string_splitters = {'\n'};
	size_t char_index = 0;
	char c = s[0];

	map<string, vector<string>> result;

	while (char_index < s.size())
	{
		c = s[char_index];
		if (c == '/') // It`s a comment string => find the next one
		{
			while (!in(c, string_splitters))
			{
				char_index++;
				c = s[char_index];
			}
			char_index = s.find_first_not_of(string_splitters, char_index);
		}
		else if (!is_spaceive(c) && !in(c, space_ignore))
		{
			// It`s the name of block
			const size_t prev_index = char_index;
			size_t name_end_index = s.find('{', char_index);
			string raw_name = Slice(s, prev_index, name_end_index);
			assert((split(raw_name).size() == 1) && "Invalid syntax: name contains spacieve symbols!");
			string this_name = cut_spaces(raw_name);
			size_t data_beg = name_end_index + 1;
			size_t data_end = s.find('}', name_end_index);
			auto data_to_split = Slice(s, data_beg, data_end);
			auto data = split(data_to_split, resultive_data_ignore);

			result[this_name] = data;

			char_index = data_end + 1;
		}
		else
		{
			char_index++;
		}
	}
	return result;
}

map<string, vector<double>> double_mylang_parse(string& s, initializer_list<char>&& additioonal_data_ignore_symbols, initializer_list<char>&& space_ignore)
{
	auto raw_coeff = common_mylang_parse(s);
	map<string, vector<double>> fried_coeff;

	stringstream ss;
	
	for (auto& p : raw_coeff)
	{
		vector<double> this_vals;
		for (auto v: p.second) {
			// ss << Join("", v);
			ss << v;
			double this_val;
			ss >> this_val;
			ss.clear();
			this_vals.push_back(this_val);
		}
		fried_coeff[p.first] = move(this_vals);
	}
	return fried_coeff;
}


