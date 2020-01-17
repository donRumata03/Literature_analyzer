#pragma once

#include "pch.h"
#include <sstream>

int count_sentensies(string& s);
int count_points(string& s);

std::string readFile(const char filename []);

bool is_russian(char c);
bool is_english(char c);
bool is_digit(char c);
bool is_spaceive(char c);
bool is_big(char c);


bool is_word_divider(char c);
bool is_sentence_divider(char c);
bool from_word(char c);


template<class T> void fill_ms(T* beg, T* end, T val);
template<class T> void fill_ms(T* beg, long long len, T val);

template<class T> void fill_ms(T* beg, const T* end, T val) {
	while (beg != end) {
		(*beg) = val;
		++beg;
	}
}

template<class T>
void fill_ms(T* beg, long long len, T val) {
	for (long _ = 0; _ < len; _++) {
		(*beg) = val;
		++beg;
	}
}

template<class T>
bool is_in(const char& c, T resource) {
	for (auto symb : resource) {
		if (symb == c) {
			return true;
		}
	}
	return false;
}


template<class C, class T>
bool in(T &val, C &container) noexcept
{
	for(auto& el : container)
	{
		if(el == val)
		{
			return true;
		}
	}
	return false;
}





template<class T> void print(initializer_list<T> &ilist) noexcept {
	for (T el : ilist) {
		cout << el << " ";
	}
	cout << endl;
}


template<class T> vector<T> to_vector(initializer_list<T> &ilist) noexcept {
	vector<T> result;
	for (T el : ilist) {
		result.push_back(el);
	}
	return result;
}


template<class T>
string join(string splitter, T& container) {
	string res = "";
	int counter = 0;
	for (auto i : container) { res += i; if (counter != container.size() - 1) { res += splitter; } counter++; }
	return res;
}

template<class T>
string Join(string splitter, T container) {
	string res = "";
	uint counter = 0;
	for (auto i : container) { res += i; if (counter != container.size() - 1) { res += splitter; } counter ++; }
	return res;
}

template<>
string join<vector<string>>(string splitter, vector<string>& container);


template<class T> T Slice(const T& container, uint idx_beg, uint idx_end) {
	T result;
	for (uint idx = idx_beg; idx < idx_end; idx++) {
			result.push_back(container.at(idx));
	}
	return result;
}


// Strings:

string cut_spaces(string& s);
string cut_bad_symbols(string& s);
vector<string> split(const string& s, const initializer_list<char>&& split_by = initializer_list{ ' ', '\n', '\t', '\r' });
inline vector<string> split(const string& s, const vector<char>& split_by);
vector<string> split_lines(string& s);

size_t find_first_not_english(string& s, size_t offset = 0);
size_t find_first_russian(string& s, size_t offset = 0);


template<class T> auto find_first_for_which_true(string& ss, T function, size_t offset = 0)
{
	for (size_t index = offset; index < ss.length(); index++)
	{
		if (function(ss[index]))
		{
			return index;
		}
	}
	return string::npos;
}


template<class T, class E>
auto my_lang_extract(string& s, T index_type_descriptor, E data_type_descriptor) -> map<string, vector<string>>
{
	auto string_splitters = { '\n' };
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
				char_index++; c = s[char_index];
			}
			char_index = s.find_first_not_of(string_splitters, char_index);
		}
		else if (is_english(c))
		{
			// It`s the name of block
			const size_t prev_index = char_index;
			char_index = min(find_first_for_which_true(s, [&](auto& param) { return !index_type_descriptor(param); }, char_index), s.find('}', char_index));
			c = s[char_index];
			string this_name = Slice(s, prev_index, char_index);
			size_t data_beg = find_first_for_which_true(s, data_type_descriptor, char_index);
			size_t data_end = s.find('}', char_index);
			auto data_to_split = Slice(s, data_beg, data_end);
			auto data = split(data_to_split);

			result[this_name] = data;

			char_index = data_end;
			c = s.at(char_index);
		}
		else {
			char_index++;
		}
	}
	return result;
}


map<string, vector<string>> common_mylang_parse(string& s, initializer_list<char>&& additioonal_data_ignore_symbols = { ';', ',' }, initializer_list<char>&& space_ignore = {';', ','});
map<string, vector<double>> double_mylang_parse(string& s, initializer_list<char>&& additioonal_data_ignore_symbols = { ';', ',' }, initializer_list<char>&& space_ignore = { ';', ',' });
