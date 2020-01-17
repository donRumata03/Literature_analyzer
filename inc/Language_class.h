#pragma once

#include "pch.h"
#include "utils.h"
#include "Word.h"
#include "Word_family.h"


constexpr auto MAX_IGNORE_NUMBER_OF_PREFIXES_AND_POSTFIXES = 200;
constexpr auto MAX_PREFIX_NUMBER = 4;


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

struct word_dividing_struct
{
	vector<string> prefixes;
	string root;
	vector<string> postfixes;
	string ending;

	void print() const
	{
		if (root.empty())
		{
			cout << "We have mo ideas about this word...\n";
			return;
		}
		cout << "I suppose, the root is: " << root << endl;

		if (!postfixes.empty()) {
			cout << "Postfixes: ";
			for(auto& p : postfixes)
			{
				cout << p << " ";
			}
			cout << endl;
		}

		if (!prefixes.empty()) {
			cout << "Prefixes: ";
			for (auto& p : prefixes)
			{
				cout << p << " ";
			}
			cout << endl;
		}

		if(!ending.empty())
		{
			cout << "Ending: " << ending;
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
	word_dividing_struct analyze_word(string& word);
	string cut_prestfixes(string& word);
	string recursive_cut_prestfixes(string& word);

	// Getting functions
	pair<bool, Word_family*> get_family(string& word);
	pair<bool, Word*> get_word(string& word);
	pair<bool, string> get_root(string& word);
	bool is_main_form(string word) noexcept
	
	{
		auto [success, block] = this->get_family(word);
		if (!success) return false;
		return word == block->main_form.data;
	}
	bool word_exists(const string& word) noexcept 
	{
		return this->word_getter.find(word) != this->word_getter.end();
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

	static bool ends_with(const string& s, string& postfix) noexcept;
	static bool starts_with(const string& s, string& prefix) noexcept;

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
	void recursive_step(const string& root, int type, vector<string> & to_append, set<string>& root_set);
	vector<string> simple_parse_step(const string& root, int type);
	void mem_recursive_step(const string& root, int type, vector<string>& to_append, set<string>& root_set, vector<string>& history);
	pair<string, string> simple_mem_step(const string& root, int type);
};
