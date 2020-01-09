#pragma once

#include "pch.h"
#include "utils.h"


class str
{
public:
	uint64_t len;
	char* data;

	// Constructors
	str();
	str(long length);
	str(char[]);
	str(string);
	str(vector<string> v, char splitter = '\n');
	void from_file(const char filename []);
	void from_string(string);

	// Methods
	void print();
	bool is_word_beg(uint64_t pos);
	bool is_word_end(uint64_t pos);
};

