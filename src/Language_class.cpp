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

			vector<string> vec_for_block = split(for_block);

			

			for (string for_word : vec_for_block) {
				Word next_word(for_word);
				if (next_word.word_type == this->word_blocks.back().word_type) { // Append to existing block
					this->word_blocks.back().append_word(next_word);
				}
				else { // Print the previous block and create th next one
					this->word_blocks.back().print_words();
					this->word_blocks.emplace_back();
					this->word_blocks.back().append_word(next_word);
				}
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