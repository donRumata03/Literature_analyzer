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

string Word_family::get_root() {
	// cout << "Counting root........" << endl;
	vector<string> data;
	for(Word& w : this->words) {
		data.push_back(w.data);
		// cout << data[data.size() - 1] << " ";
	}
	// cout << endl;
	string res = LCS(data);
	if(res.empty())
	{
		res = this->main_form.data;
		cout << "Interesting word: " << res << endl;
		this->print_words();
		cout << endl;
	}
	// cout << "Root is: " << res << endl;
	return res;
}

string Word_family::count_root()
{
	this->root = get_root();
	return root;
}


bool Word_family::append_word(Word &word)
{
	if (this->word_type == word_types::unknown) { 
		this->words.push_back(word); 
		this->word_type = word.word_type; 
		this->main_form = word; 
		return true; 
	}
	if (word.word_type != this->word_type) {
		volatile Word this_word = word;
		throw "Bad word type \"" + word_type_to_string_converter[word.word_type] \
			+ "\" for block with word type \"" + word_type_to_string_converter[this->word_type];
		return false;
	}
	this->words.push_back(word);
	return true;
}

void Word_family::print_data() {
	cout << "Word family: \nWord type: " << word_type_to_string_converter[word_type] << \
	"; " << "Root: " << this->root << "; Main form: ";
	this->main_form.print_data();
	cout << "{ " << endl;
	for (Word this_word : words)
		this_word.print_data();
	cout << endl;
	cout << "}" << endl;
}

void Word_family::print_words()
{
	cout << "Word block with word type : " << word_type_to_string_converter[this->word_type] << " ; Root: " << this->root << " ; Main form: " << main_form.data << "\n";
	cout << "Words: {";
	for(Word& w : words)
	{
		cout << "\t" << w.data << endl;
	}
	cout << "}\n\n";
}




