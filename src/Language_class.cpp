#include "Language_class.h"


Language::Language(const char filename[]) {
	single_data = readFile(filename);
	char last = single_data[0], pre_last = single_data[0];
	uint64_t last_block_beg = 0;
	bool seeking_block = true;
	uint char_index = 0;

	for (char c : single_data) {
		if (seeking_block && !is_spaceive(c)) {
			seeking_block = false;
			last_block_beg = char_index;
		}
		else if (c == '\n' && pre_last == '\n' || char_index == single_data.length() - 1) {
			seeking_block = true;
			string for_block;
			for_block.reserve(char_index - (uint)last_block_beg);
			for (uint i = last_block_beg; i < char_index - 1; i++) {
				for_block.push_back(single_data[i]);
			}

			vector<string> vec_for_block = split_lines(for_block);

			

			for (string for_word : vec_for_block) {
				Word next_word(for_word); // If it`s the first block
				if (this->word_blocks.empty()) {
					this->word_blocks.emplace_back();
					this->word_blocks.back().append_word(next_word);
					this->main_form_getter[next_word.data] = (this->word_blocks.back().main_form);
				}
				else if (next_word.word_type == this->word_blocks.back().word_type) { // Append to existing block
					this->word_blocks.back().append_word(next_word);
					this->main_form_getter[next_word.data] = (this->word_blocks.back().main_form);
				}
				else { // Print the previous block and create the next one
					this->word_blocks.emplace_back();
					this->word_blocks.back().append_word(next_word);
					this->main_form_getter[next_word.data] = (this->word_blocks.back().main_form);
				}
				/*
				cout << next_word.data << " -> ";
				this->main_form_getter[next_word.data].print_data();
				cout << endl;
				*/
			}


		}
		char_index++;
		pre_last = last;
		last = c;
	}

}

void Language::print_data() {
	cout << "THIS LANGUAGE: {" << endl << "Blocks: " << endl;
	for (auto block : word_blocks) {
		block.print_words();
	}
}

pair<bool, Word> Language::get_main_form(string &word) {
	bool success;
	if (main_form_getter.find(word) == main_form_getter.end()) {
		success = false;
		return pair(success, Word());
	}
	return pair(success, this->main_form_getter[word]);
}