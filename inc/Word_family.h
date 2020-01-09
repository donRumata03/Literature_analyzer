#pragma once

#include "pch.h"
#include "utils.h"
#include "Word.h"



class Word_family {
public:
	vector<Word> words;
	word_types word_type = word_types::unknown;
	Word main_form;

	Word_family() = default;
	Word_family(string &s);
	
	
	bool append_word(Word& word);
	void print_words();
};
