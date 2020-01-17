#pragma once


#include "pch.h"
#include "utils.h"
#include "str.h"


class Simple_analitics
{
private:
	string label = "Unknown text";
	uint64_t text_length;
	uint64_t russians = 0, englishs = 0, digits = 0, spaceives = 0;
	uint64_t all_splitters, sentencies = 0, words = 0; // Splitter is something, that divides two sentencies
	uint64_t dots = 0, commas = 0, interrs = 0, excls = 0, three_dots = 0, dotcommas = 0;
	uint64_t all_letters;
	double dots_percent = -1, commas_percent = -1, interrs_percent = -1, excls_percent = -1, three_dots_percent = -1, dotcommas_percent = -1;
	int max_word_length = -1, max_sentence_length = -1;
	int* sentence_length_distribution;

	double russian_percent, english_percent, digit_percent, water_part;
public:
	Simple_analitics() = default;
	Simple_analitics(str &s);
	Simple_analitics(str &s, string _label);
	Simple_analitics(string& s) : Simple_analitics(*new str(s)) {}

	void print_it();
	void visualize_sentence_distribution();
	void print_sentence_distribution();

	static map<string, vector<double>> coeffs;
	static double dist(Simple_analitics& s1, Simple_analitics& s2);
};

