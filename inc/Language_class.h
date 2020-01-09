#pragma once

#include "pch.h"
#include "utils.h"
#include "Word.h"
#include "Word_family.h"

class Language {
	string single_data;
	vector<string> block_data;
	vector<Word_family> word_blocks;


public:
	Language(const char filename[] = "res/");
	void print_data();
	pair<bool, Word> get_main_form(string &word);

	// Main map
	map<string, Word> main_form_getter;
};