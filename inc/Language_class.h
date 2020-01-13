#pragma once

#include "pch.h"
#include "utils.h"
#include "Word.h"
#include "Word_family.h"


constexpr auto MAX_IGNORE_NUMBER_OF_PREFIXES_AND_POSTFIXES = 200;


struct word_common_struct
{
	string prefix;
	string root;
	string postfix;

	void print() const
	{
		if(root.empty())
		{
			cout << "We have mo ideas about this word...\n";
			return;
		}
		cout << "I suppose, the root is: " << root << endl;

		if(!postfix.empty()) {
			cout << "Postfix: " << postfix << endl;
		}

		if (!prefix.empty()) {
			cout << "Prefix: " << prefix << endl;
		}
	}
};


class Language {
	string single_data;
	vector<string> block_data;
	
	vector<Word_family*> word_blocks;

public:
	Language(const char filename[] = "res/");

	// Anal functions:
	word_common_struct analyze_word(string& word);
	string cut_prestfixes(string& word);

	// Getting functions
	pair<bool, Word_family*> get_family(string& word);
	pair<bool, Word*> get_word(string& word);
	pair<bool, string> get_root(string& word);

	// Print Statistics:
	void print_data();
	void print_word_type_stat();
	void print_frequent_prefixes(size_t num);
	void print_frequent_postfixes(size_t num);
	
	
	set<string> prefixes;
	set<string> postfixes;
	
private:
	// Main maps
	unordered_map<string, Word_family*> family_getter;
	unordered_map<string, Word*> word_getter;

	// Statistics:
	map<word_types, size_t> word_type_counter;

	vector<pair<string, size_t>> sorted_prefixes;
	vector<pair<string, size_t>> sorted_postfixes;

	
	// System
	size_t last_renewing_number_of_words; // To control frequent postfixes
};
