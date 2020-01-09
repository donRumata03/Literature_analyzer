#pragma once

#include "pch.h"

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
		beg++;
	}
}

template<class T>
void fill_ms(T* beg, long long len, T val) {
	for (long _ = 0; _ < len; _++) {
		(*beg) = val;
		beg++;
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

template<class T>
bool in(T val, initializer_list<T>& lis) noexcept {
	for (T i : lis) {
		if (val == i) {
			return true;
		}
	}
	return false;
}


template<class T>
bool in(T &val, vector<T> &vec) noexcept {
	for (T this_el : vec) {
		if (this_el == val) {
			return true;
		}
	}
	return false;
}



template<class T, class E> 
bool in(T& val, E& container) {
	for (T el : container) {
		if (el == val) {
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


template<class T> T Slice(T& container, uint idx_beg, uint idx_end) {
	T result;
	for (uint idx = idx_beg; idx < idx_end; idx++) {
			result.push_back(container.at(idx));
	}
	return result;
}


// Strings:

string cut_spaces(string& s);
vector<string> split(string &s, initializer_list<char> &split_by = *(new initializer_list({' ', '\n', '\t', '\r'})));
vector<string> split_lines(string& s);
