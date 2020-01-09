#include "Word_family.h"

Word_family::Word_family(string &s) {
	vector<string> lines = split_lines(s);

	bool taken_first = false;

	for (string s : lines) {

		if (!taken_first) {
			this->main_form = Word(s);
			taken_first = true;
		}

		words.emplace_back(s);
		this->word_type = words.back().word_type;
	}
	word_type = words.at(0).word_type;
}


bool Word_family::append_word(Word &word)
{
	if (this->word_type == word_types::unknown) { this->words.push_back(word); this->word_type = word.word_type; this->main_form = word; return; }
	if (word.word_type != this->word_type) {
		throw "Bad word type \"" + word_type_to_string_converter[word.word_type] \
			+ "\" for block with word type \"" + word_type_to_string_converter[this->word_type];
		return false;
	}
	this->words.push_back(word);
}

void Word_family::print_words() {
	cout << "Word family: Word type: " << word_type_to_string_converter[word_type] << " { " << endl;
	for (Word this_word : words)
		this_word.print_data("\t");
	cout << endl;
	cout << "}" << endl;
}




