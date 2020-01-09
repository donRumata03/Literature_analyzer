#pragma once

#include "pch.h"
#include "str.h"

class word_top {
	map<string, int> data;
	pms word_length_distr;
	luint max_word_length = 0;
	uint64_t size;
	vector<pair<string, uint64_t>> data_sorted_by_num;
public:
	word_top(str& s);

	void print_first(int n);
	void print_if_more_than(uint64_t num);
	static double dist(word_top t1, word_top t2);
};