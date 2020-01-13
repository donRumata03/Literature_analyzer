#pragma once

#include "pch.h"
#include "utils.h"
#include "Word.h"



class Word_family {
public:
	vector<Word> words;
	word_types word_type = word_types::unknown;
	Word main_form;
	string root;

	Word_family() = default;
	Word_family(string &s);

	string get_root();
	string count_root();
	bool append_word(Word& word);
	void print_data();
	void print_words();
};
