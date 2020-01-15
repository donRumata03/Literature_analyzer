#include "Language_class.h"


Language::Language(const char filename[]) {
	single_data = readFile(filename);

	map<string, size_t> postfixes_counter;
	map<string, size_t> prefixes_counter;
	vector<Word_family> _word_blocks;
	char last = single_data[0], pre_last = single_data[0];
	uint64_t last_block_beg = 0;
	bool seeking_block = true;
	bool previous_block_empty = true, this_block_empty = true;
	uint char_index = 0;
	vector<pair<string, free_properties>> free_properties_to_add;

	
	for (char c : single_data) {
		this_block_empty = true;
		if (seeking_block && !is_spaceive(c)) {
			seeking_block = false;
			last_block_beg = char_index;
		}
		else if (c == '\n' && pre_last == '\n' || char_index == single_data.length() - 1) {
			seeking_block = true;
			string for_block;
			bool first_part_flag = true;
			

			for_block.reserve(char_index - static_cast<uint>(last_block_beg));
			for (size_t i = last_block_beg; i < char_index - 1; i++) {
				for_block.push_back(single_data[i]);
			}
			vector<string> vec_for_block = split_lines(for_block);

			for (string for_word : vec_for_block) {
				for_word = cut_bad_symbols(for_word);
				// Check if it`s word definition or adding free properties
				bool is_free_prop = false;
				string this_word_data;
				auto spl = split(for_word);
				size_t this_word_index = 0;
				free_properties free_property;
				for (string& possible_free_prop : spl)
				{
					if(string_to_free_properties_converter.find(possible_free_prop) != string_to_free_properties_converter.end())
					{
						is_free_prop = true;
						free_property = string_to_free_properties_converter[possible_free_prop];
						this_word_data = Join(" ", Slice(spl, 0, this_word_index));
						free_properties_to_add.emplace_back(this_word_data, free_property);
						break;
					}
					this_word_index++;
				}
				if (is_free_prop) { continue; }
				
				Word next_word(for_word); // If it`s the first block
				if (next_word.word_type == word_types::unknown) { continue; }

				++word_type_counter[next_word.word_type];

				if (_word_blocks.empty()) {
					_word_blocks.emplace_back();
				}
				else if ((next_word.word_type != _word_blocks.back().word_type) || first_part_flag && !previous_block_empty) { // Save the previous block and create the next one
					// Old block:
					string this_root = _word_blocks.back().count_root();
					// Get prefix and postfix:
					size_t first_pos = next_word.data.find(this_root);
					string this_prefix, this_postfix;

					if (first_pos != next_word.data.npos) {
						this_prefix = Slice(next_word.data, 0, first_pos);
						this_postfix = Slice(next_word.data, first_pos + this_root.length(), next_word.data.length());

						// cout << this_prefix << "- ; -" << this_postfix << "\n";

						if (first_pos != 0) ++prefixes_counter[this_prefix];
						if (first_pos + this_root.length() != next_word.data.length()) {
							++postfixes_counter[this_postfix];
						}
					}
					// New block:
					_word_blocks.emplace_back();
				}
				_word_blocks.back().append_word(next_word);
				first_part_flag = false;
				this_block_empty = false;
			}

			// cout << "Block: " << for_block << " ; IS "<< (this_block_empty ? "EMPTY" : "NOT EMPTY");
			
		}

		char_index++;
		
		if(char_index == single_data.size()) {
			string temp = _word_blocks.back().count_root();
		}

		previous_block_empty = this_block_empty;
		pre_last = last;
		last = c;
	}


	// Test of generating free properties;
	/*
	cout << "Test of generating free properties:" << endl;
	for(auto& i : free_properties_to_add)
	{
		cout << i.first << " " << free_properties_to_string_converter[i.second] << endl;
	}

	cout << "End of test of generating free properties : " << endl;
	*/

	
	// So, here we already have a Word blocks.
	// We should merge the ones with this same ROOTS
	// Firstable, sort them by root:
	sort(_word_blocks.begin(), _word_blocks.end(), [&](auto& a, auto& b) {return a.root < b.root; });

	// After that: merging
	size_t block_index = 0;
	long long prev_index = -1;
	
	Word_family* flying_block = nullptr;
	for(Word_family &temp : _word_blocks)	{
		// Create next block if required
		if(this->word_blocks.empty() || word_blocks.back()->root != temp.root || word_blocks.back()->word_type != temp.word_type) {
			if(!word_blocks.empty())
			{
				word_blocks.back()->root = _word_blocks.at(prev_index).root;
			}
			flying_block = new Word_family();
			word_blocks.push_back(flying_block);
			flying_block->root = temp.root;
		}

		// Copy this block to the top of the vector
		
		for (Word& temp_word : temp.words) {
			word_blocks.back()->append_word(temp_word);
			// Make dictionary : for each word: put address of its`s block
			this->family_getter[temp_word.data] = flying_block;
		}
		block_index++;
		prev_index++;
		if(block_index == _word_blocks.size())
		{
			word_blocks.back()->root = temp.root;
		}
	}

	// Free temporary memory
	vector<Word_family>().swap(_word_blocks);


	/*ADDING FREE PROPERTIES*/
	
	// Go through all blocks and add pointers to word_getter
	for(auto& this_block : this->family_getter)
	{
		for (Word& this_word : this_block.second->words) {
			this->word_getter[this_word.data] = &this_word;
		}
	}

	// this->family_getter["��������"]->words[0].free_property = free_properties::predicate;
	
	// Now watch all free properties and add to them
	// Go through free_properties_to_add and add them to the words
	//

	for(auto& free_property : free_properties_to_add)
	{
		if (this->word_getter.find(free_property.first) != this->word_getter.end()) {
			this->word_getter[free_property.first]->free_property = free_property.second;
			Word* w = this->word_getter[free_property.first];
			free_properties fr_test = w->free_property;
		}
	}

	// Sort prefixes and postfixes
	for(auto& p : prefixes_counter) if(p.second > MAX_IGNORE_NUMBER_OF_PREFIXES_AND_POSTFIXES) this->sorted_prefixes.emplace_back(p.first, p.second);
	for(auto& p : postfixes_counter) if (p.second > MAX_IGNORE_NUMBER_OF_PREFIXES_AND_POSTFIXES) this->sorted_postfixes.emplace_back(p.first, p.second);
	sort(sorted_prefixes.begin(), sorted_prefixes.end(), [](auto& a, auto& b) { return a.second > b.second; });
	sort(sorted_postfixes.begin(), sorted_postfixes.end(), [](auto& a, auto& b) { return a.second > b.second; });

	this->load_prestfixes();
}

word_common_struct Language::analyze_word(string& word)
{
	auto [success, root] = get_root(word);
	if(success)
	{
		const size_t first_pos = word.find(root);

		if (first_pos != string::npos) {
			const string this_prefix = Slice(word, 0, first_pos);
			const string this_postfix = Slice(word, first_pos + root.length(), word.length());

			word_common_struct res {"", root, ""};
			
			if (first_pos != 0) res.prefix = this_prefix;
			if (first_pos + root.length() != word.length()) res.postfix = this_postfix;

			return res;
		}
	}

	return {"", "", ""};

}

string Language::cut_prestfixes(string& word)
{
	string root = word;
	size_t index = 0;

	short times_no_success = 0;
	
	while(!root.empty() && !(is_main_form(root)) && times_no_success <= 3) // If root in roots: return
	{
		// For all frequent prefixes try to understand if they exist
		// If they do, we add 1 to their frequency rating
		// We should re - count frequent verbs in oder to understand their real percent
		//
		// Each time we renew it we sort all known, good enough prepositions and find best ones
		// But if we see something good it`s not necessary to wait re-counting

		bool this_success = false;
		
		if(index == 0) // ending
		{
			for(auto& ending_type : endings)
			for(string& ending : ending_type.second)
			{
				if(ends_with(root, ending))
				{
					if (root.size() >= 4 || ending.size() <= 2 || (static_cast<double>(root.size()) / ending.size() > 2.5)) {
						root = root.substr(0, root.size() - ending.size());
						this_success = true;
					}
				}
			}
		}

		else if(index % 2) // Postfixes (before prefixes)
		{
			for(auto& postfix_type : postfixes)
			for(string& postfix : postfix_type.second)
			{
				if(ends_with(root, postfix) && static_cast<double>(root.size()) / static_cast<double>(postfix.size()) > 1.8)
				{
					root = root.substr(0, root.size() - postfix.size());
					this_success = true;
				}
			}
		}

		else // Prefixes
		{
			for (auto& prefix_type : prefixes)
			for (string& prefix : prefix_type.second)
			{
				if (starts_with(root, prefix) && static_cast<double>(root.size()) / static_cast<double>(prefix.size()) > 1.3)
				{
					root = Slice(root, prefix.size(), root.size());
					this_success = true;
				}
			}
		}
		if (!this_success) times_no_success++;
		index++;
	}

	return  root;
}

void Language::print_data() {
	cout << "THIS LANGUAGE: {" << endl << "Blocks: " << endl;
	for (auto block : word_blocks) {
		block->print_data();
	}
}


pair<bool, Word_family*> Language::get_family(string& word) {
	bool success = true;
	if (family_getter.find(word) == family_getter.end()) {
		success = false;
		Word_family* f = nullptr;
		return { success, f };
	}
	return { success, this->family_getter[word] };
}

pair<bool, Word*> Language::get_word(string& word)
{
	if (family_getter.find(word) == family_getter.end()) {
		Word* f = nullptr;
		return { false, f };
	}
	return { true, this->word_getter[word] };
}

pair<bool, string> Language::get_root(string& word)
{
	auto [success, block] = this->get_family(word);
	if(!success)
	{
		return { false, "" };
	}
	return { true, block->root };
}

void Language::print_word_type_stat()
{
	size_t sum = 0;
	for (auto& p : word_type_counter) sum += p.second;
	cout << "Word type statistics: \n";
	for(auto &el : this->word_type_counter)
	{
		cout << word_type_to_string_converter[el.first] << "(" << el.second << ") : " << static_cast<double>(el.second) / static_cast<double>(sum / 100) << "%" << endl;
	}
}

void Language::print_frequent_prefixes(size_t num)
{
	cout << "Frequent prefixes : \n";
	for(pair<string, size_t>& p : sorted_prefixes)
	{
		if (p.second >= num)	cout << p.first << " : " << p.second << endl;
		else break;
	}
}

void Language::print_frequent_postfixes(size_t num)
{
	cout << "Frequent postfixes : \n";
	for (pair<string, size_t>& p : sorted_postfixes)
	{
		if (p.second >= num)	cout << p.first << " : " << p.second << endl;
		else break;
	}
}

bool Language::ends_with(string& s, string& postfix) noexcept
{
	if (postfix.size() > s.size()) return false;
	const size_t offset = s.size() - postfix.size();
	for(size_t i = 0; i < postfix.size(); i++)
	{
		if(s[i + offset] != postfix[i])
		{
			return false;
		}
	}
	return true;
}

bool Language::starts_with(string& s, string& prefix) noexcept
{
	if (prefix.size() > s.size()) return false;
	for(size_t i = 0; i < prefix.size(); i ++)
	{
		if(s.at(i) != prefix.at(i))
		{
			return false;
		}
	}
	
	return true;
}

void Language::load_prestfixes()
{
	// File_paths:
	const char endings_path[] = "res/language/input/endings.txt";
	const char postfixes_path[] = "res/language/input/postfixes.txt";
	const char prefixes_path [] = "res/language/input/prefixes.txt";
	
	string raw_endings_data = readFile(endings_path);
	string raw_postfixes_data = readFile(postfixes_path);
	string raw_prefixes_data = readFile(prefixes_path);

	endings = extract(raw_endings_data);
	postfixes = extract(raw_postfixes_data);
	prefixes = extract(raw_prefixes_data);
}
