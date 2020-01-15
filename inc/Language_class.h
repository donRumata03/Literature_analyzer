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
	Language() = default;
	Language(const char filename[]);

	// Anal functions:
	word_common_struct analyze_word(string& word);
	string cut_prestfixes(string& word);

	// Getting functions
	pair<bool, Word_family*> get_family(string& word);
	pair<bool, Word*> get_word(string& word);
	pair<bool, string> get_root(string& word);
	bool is_main_form(string word)
	{
		auto [success, block] = this->get_family(word);
		if (!success) return false;
		return word == block->main_form.data;
	}
	// Print Statistics:
	void print_data();
	void print_word_type_stat();
	void print_frequent_prefixes(size_t num);
	void print_frequent_postfixes(size_t num);
	
	map<string, vector<string>> prefixes;
	map<string, vector<string>> postfixes;
	map<string, vector<string>> endings;


	void load_prestfixes();
	static map<string, vector<string>> extract(string& s)
	{
		return my_lang_extract(s, [](auto& param) { return is_english(param); }, \
			[](auto& param) { return is_russian(param); });
	}
private:
	// Main maps
	unordered_map<string, Word_family*> family_getter;
	unordered_map<string, Word*> word_getter;

	// Statistics:
	map<word_types, size_t> word_type_counter;

	vector<pair<string, size_t>> sorted_prefixes;
	vector<pair<string, size_t>> sorted_postfixes;

	
	// System

	static bool ends_with(string& s, string& postfix) noexcept;
	static bool starts_with(string& s, string& prefix) noexcept;

	template <class T> static size_t find_first_for_which_true(string& s, T function, size_t offset = 0)
	{
		for(size_t index = offset; index < s.length(); index++)
		{
			if(function(s[index]))
			{
				return index;
			}
		}
		return string::npos;
	}
	static size_t find_first_not_english (string& s, size_t offset = 0)
	{
		return find_first_for_which_true(s, [](char c) {	return !is_english(c); }, offset);
	}
	static size_t find_first_russian(string& s, size_t offset = 0)
	{
		return find_first_for_which_true(s, [](char c) {	return is_russian(c); }, offset);
	}

	
	
};
