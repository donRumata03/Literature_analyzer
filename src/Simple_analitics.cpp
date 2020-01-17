#include "Simple_analitics.h"


Simple_analitics::Simple_analitics(str& s) {
	this->text_length = s.len;
	long last_word_beg = -1, last_sent_beg = -1;
	for (long i = 0; i < s.len; i++) {
		char c = s.data[i];

		bool _is_english = is_english(c), _is_russian = is_russian(c), \
			_is_spacieve = is_spaceive(c), _is_digit = is_digit(c);

		// Big Classes 
		if (_is_english) { englishs++; }
		if (_is_russian) { russians++; }
		if (_is_digit) { digits++; }
		if (_is_spacieve) { spaceives++; }

		// Words:
		if(i == 0 || is_word_divider(s.data[i - 1])){
			words++;
			max_word_length = max(max_word_length, (int)(i - last_word_beg - 1));
			last_word_beg = i;
		}
		
		// Special symbols count:
		bool is_bad_three_dot = false;
		if (c == ',') { commas++; }
		else if (c == '?') { interrs++; }
		else if (c == '!') { excls++; }
		else if (c == ';') { dotcommas++; }
		else if (c == '.') {
			if (((i == s.len - 1) || s.data[i + 1] != '.') && (i == 0 || s.data[i - 1] != '.')) {
				dots++;
			}
			else {
				if (i == 1 || s.data[i - 1] != '.') {
					three_dots++;
				}
				else {
					is_bad_three_dot = true;
				}
			}
		}
		
		if (is_sentence_divider(c) && !is_bad_three_dot) {
			sentencies++;
			max_sentence_length = max(max_sentence_length, (int)(i - last_sent_beg - 1));
			last_sent_beg = i;
		}
	}
	all_splitters = dots + commas + three_dots + dotcommas + interrs + excls;

	dots_percent = 100.0 * dots / all_splitters; commas_percent = 100.0 * commas / all_splitters;
	three_dots_percent = 100.0 * three_dots / all_splitters; dotcommas_percent = 100.0 * dotcommas / all_splitters;
	excls_percent = 100.0 * excls / all_splitters; interrs_percent = 100.0 * interrs / all_splitters;
	all_letters = russians + englishs + digits;
	russian_percent = 100.0 * russians / all_letters; english_percent = 100.0 * englishs / all_letters; digit_percent = 100.0 * digits/ all_letters;
	water_part = (double)spaceives / all_letters;

	
	sentence_length_distribution = new int[max_sentence_length];

	// Initializing
	
	fill_ms(sentence_length_distribution, max_sentence_length, 0);

	// Getting word and sentence length dist0x00A7F350ribution:
	last_word_beg = -1;
	last_sent_beg = -1;
	for (int i = 0; i < s.len; i++) {
		
		bool is_bad_three_dot{ false };
		char c = s.data[i];
		if (c == '.') {
			if (((i == s.len - 1) || s.data[i + 1] != '.') && (i == 0 || s.data[i - 1] != '.')) {
				dots++;
			}
			else {
				if (i == 1 || s.data[i - 1] != '.') {
					three_dots++;
				}
				else {
					is_bad_three_dot = true;
				}
			}
		}

		// Sents:
		if (is_sentence_divider(c) && !is_bad_three_dot) {
			int length_of_this_sent = static_cast<int>(i - last_sent_beg - 1);
			last_sent_beg = i;
			sentence_length_distribution[length_of_this_sent]++;
		}

		// Words:
		/*
		if (i == 0 || is_word_divider(s.data[i - 1])) {
			int length_of_this_word = static_cast<int>(i - last_word_beg - 1);
			last_word_beg = i;
			word_length_distribution[length_of_this_word]++;
		}
		*/
	}

}


Simple_analitics::Simple_analitics(str &s, string _label) : Simple_analitics::Simple_analitics(s) {
	this->label = _label;
}

void Simple_analitics::print_it() {
	cout << "-----------------------------------------" << endl;
	cout << "Simple_analitics of " << label << ": " << endl;
	cout << "-----------------------------------------" << endl << endl;

	cout << "Total length of text: " << text_length << " symbols" << endl;
	cout << "Points: " << dots << "; Commas: " << commas << "; Ellipsis: " << three_dots \
		<< "; Dot_commas: " << dotcommas << "; Exclamation marks: " << excls << "; Interrogative marks: " << interrs << endl;
	cout << "Points percent: " << dots_percent << "% ; Commas percent: " << commas_percent << "% ; Ellipsis percent: " << three_dots_percent  \
		<< "% ; Dot_commas percent: " << dotcommas_percent << "% ; Exclamation marks percent: " << excls_percent << "% ; Interrogative marks percent: " << interrs_percent << "%" << endl;

	cout << "Max sentence length: " << max_sentence_length << "; Max word length:  " << max_word_length << endl;
	
	cout << "Russian letters: " << russians << " ; English letters: " << englishs << " ; Digits: " << digits << " ; Water: " << spaceives << endl;
	cout << "Percent of Russian letters: " << russian_percent << "% ; Perscent of English letters: " << english_percent << "% ; Percent of digits: " << digit_percent << "%" << endl;
	
	if (3 * russian_percent > 200) {
		cout << "Всё ясно. Автор русский!" << endl;
	}
	if (3 * english_percent > 200) {
		cout << "Всё ясно. Автор НеРУССkИj!" << endl;
	}
	if (3 * digit_percent > 200) {
		cout << "Всё ясно. Автор РоБоТ!" << endl;
	}
	if (3 * water_part > 1) {
		cout << "Всё ясно! Автор - водолей. (Либо это дз по физике)" << endl;
	}

	this->print_sentence_distribution();
	// this->print_word_distribution();

	cout << "That`s all for now" << endl;
}

double Simple_analitics::dist(Simple_analitics& s1, Simple_analitics &s2) {
	return 1;
}

/*
void Simple_analitics::visualize_word_distribution() {
	add_to_plot(word_length_distribution, max_word_length);
	show_plot();
}
*/

void Simple_analitics::visualize_sentence_distribution() {
	pms simple_distr;
	for (int i = 0; i < max_sentence_length; i++) {
		simple_distr.push_back(point(i + 1, sentence_length_distribution[i]));
	}
	// print(simple_distr);
	for (uint i = 0; i < simple_distr.size(); i++) {
		simple_distr.at(i).print();
		cout << endl;
	}
	logarifmate_function(simple_distr);
	pms smoothed_distr = smooth(simple_distr, 0.03);
	
	add_to_plot(simple_distr);
	add_to_plot(smoothed_distr);
	show_plot();
}

/*
void Simple_analitics::print_word_distribution()
{
	cout << "Word length distribution:" << endl;
	for (int i = 0; i < this->max_word_length; i+= max(1, (int)((i) * max_word_length / (30)))) {
		if (i >= max_word_length) { break; }
		cout << i << " " << this->word_length_distribution[i] << endl;
	}
	cout << endl;
}
*/

void Simple_analitics::print_sentence_distribution()
{
	cout << "Sentence length distribution:" << endl;
	for (int i = 0; i < this->max_sentence_length; i+= max(1, (int)(i * max_sentence_length / 500))) {
		if (i >= max_sentence_length) { break; }
		// cout << i << " " << (int)(i * max_sentence_length / 30) << endl;
		cout << i << " " << this->sentence_length_distribution[i] << endl;
	}
	cout << endl;
}


