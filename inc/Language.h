#pragma once

#include "pch.h"
#include "utils.h"

vector<string> get_word_relatives(string word);
string get_main_form(string word);

bool is_russian(string &word);
bool is_english(string &word);
bool is_digital(string &word);

bool is_preposition(string &word, vector<string> &preposes);

