#include "str.h"

str::str() {
	len = 0L;
	data = nullptr;
}

str::str(long length) {
	len = length;
	data = new char[(uint)len];
}

str::str(char _data []) {
	data = _data;
	char c = 'h';
	len = 0;
	while (c != '\0') {
		c = _data[(uint)len];
		len++;
	}
}

str::str(string s) {
	data = (char*)s.c_str();
	len = s.length();
}

void str::from_string(string s) {
	data = (char*)s.c_str();
	len = s.length();
}

str::str(vector<string> v, char splitter) {
	len = 0L;
	for (auto i : v) {
		len += (uint64_t)i.length() + 1L;
	}
	data = new char[(uint)len];
	char *ptr = data;
	
	for (auto i : v) {
		for (char c : i) {
			*ptr = c;
			ptr++;
		}
		*ptr = '\n';
		ptr++;
	}
}

void str::from_file(const char filename[]){
	/*
	ifstream in(filename);
	len = file_length(filename);
	data = new char[(uint)len];
	in.read(data, len);
	*/
	string s = readFile(filename);
	const char * dat = s.c_str();
	data = new char[s.length() + 1];
	len = s.length();
	data[len + 1] = '\0';
	for (uint i = 0; i < s.length(); i++) {
		data[i] = dat[i];
	}
}




/*
map<string, double> Str::get_sentence_stat() {
	map<string, double> res;
	long point_count = 0, excl_mark_count = 0, interr_mark_count = 0, three_dot_count = 0, dotcomma_count = 0, commas_count = 0;
	long l_minus_one = len - 1;
	long russians = 0, englishs = 0, digits = 0, spaces = 0, spacieves = 0;
	long sent_count = 0;

	for (long i = 0; i < len; i++) {
		char c = data[i];
		if (c == ',') { commas_count++; continue; }
		if (c == '.' || c == '?' || c == '!' || c == ';') {
			sent_count++;
		}
		if (c == '?') { interr_mark_count++; continue; }
		if (c == '!') { excl_mark_count++; continue; }
		if (c == ';') { dotcomma_count++; continue; }
		if (c == '.') {
			if ((i == l_minus_one || data[i + 1] != '.') && (i == 0 || data[i - 1] != '.')) {
				point_count++;
				continue;
			}
			else {
				if (i == 1 || data[i - 1] != '.') {
					three_dot_count++;
					continue;
				}
			}
		}
		if (is_english(c)) { englishs++; continue; }
		if (is_russian(c)) { russians++; continue; }
		if (is_digit(c)) { digits++; continue; }
		if (is_spaceive(c)) { spacieves++; continue; }
	}
	long num_splitters = point_count + excl_mark_count + interr_mark_count + three_dot_count + dotcomma_count;
	
	res["sentencies"] = num_splitters + 1;
	
	res["points"] = point_count;
	res["exclamation_marks"] = excl_mark_count;
	res["interrogative_marks"] = interr_mark_count;
	res["tree_dots"] = three_dot_count;
	res["dotcommas"] = dotcomma_count;
	res["commas"] = commas_count;

	res["points_percent"] = 100.0 * point_count / (double)num_splitters;
	res["exclamation_marks_percent"] = 100.0 * excl_mark_count / (double)num_splitters;
	res["interrogative_marks_percent"] = 100.0 * interr_mark_count / (double)num_splitters;
	res["tree_dots_percent"] = 100.0 * three_dot_count / (double)num_splitters;
	res["dotcommas_percent"] = 100.0 * dotcomma_count / (double)num_splitters;

	res["spaceieves"] = spacieves;
	res["digits"] = digits;
	res["russians"] = russians;
	res["englishs"] = englishs;


	res["average_sentence_length"] = len / ((double)num_splitters + 1);
	return res;
}
*/


bool str::is_word_beg(uint64_t pos) {
	return from_word(this->data[pos]) && (pos == 0 || (!from_word(this->data[pos - 1])));
}

bool str::is_word_end(uint64_t pos) {
	return from_word(this->data[pos]) && (pos == len - 1 || (!from_word(this->data[pos + 1])));
}

void str::print() {
	for (int i = 0; i < len; i++) {
		cout << data[i];
	}
}
