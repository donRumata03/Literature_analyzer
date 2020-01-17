#include "word_top.h"

using namespace std;

word_top::word_top(str& s) {
	bool in_word = false;
	uint64_t word_count = 0;
	uint64_t word_begining = 0;
	size = s.len;

	for (uint64_t i = 0i64; i < s.len; i++) {
		if (in_word) {
			if (s.is_word_end(i)) {
				goto end_word;
			}
		}
		else {
			if (s.is_word_beg(i)) {
				in_word = true;
				word_begining = i;
			}
			
			if (s.is_word_end(i)) {
				goto end_word;
			}
			
		}
		if (false) {
		end_word:
			in_word = false;
			luint this_length = i - word_begining + 1;
			string this_word;
			this_word.reserve(this_length);
			for (int i = 0; i < this_length; i++) {
				this_word.push_back(s.data[word_begining + i]);
			}
			max_word_length = max(max_word_length, this_length);
			if (this_length >= 4 && !is_big(this_word[0])) { ++data[this_word]; }
			word_count++;
		}
	}
	cout << "Words: " << word_count << endl;
	cout << "Max word length: " << max_word_length << endl;
	
	for (auto it : data) {
		data_sorted_by_num.push_back(it);
	}
	sort(data_sorted_by_num.begin(), data_sorted_by_num.end(), [](auto a, auto b) {return a.second > b.second; });
}


void word_top::print_first(int n) {
	cout << endl << "Stat; first " << n << endl;
	for (int i = 0; i < n; i++) {
		cout << data_sorted_by_num[i].first << ": " << data_sorted_by_num[i].second << endl;
	}
	cout << endl;
}

void word_top::print_if_more_than(uint64_t num)
{
	cout << endl << "Stat; more than :" << num << endl;
	for (auto i : data) {
		if (i.second > num) {
			cout << i.first << ": " << i.second << endl;
		}
	}
	cout << endl;
}


double word_top::dist(word_top& t1, word_top &t2)
{
	set<string> words;
	for (auto p : t1.data) {
		words.insert(p.first);
	}
	for (auto p : t2.data) {
		words.insert(p.first);
	}

	double difference = 0;

	for (string word : words) {
		uint64_t times_in_1 = (t1.data.find(word) == t1.data.end()) ? (0) : (t1.data[word]);
		uint64_t times_in_2 = (t2.data.find(word) == t2.data.end()) ? (0) : (t2.data[word]);
		
		double percent_in_1 = static_cast<double>(times_in_1) / t1.size;
		double percent_in_2 = double(times_in_2) / t2.size;
		if (square(percent_in_1 - percent_in_2) > pow(10, (-7))) { cout << word << " " \
			<< percent_in_1 << " " << times_in_1 << " " << percent_in_2 << " " << times_in_2 << endl; }
		difference += square(percent_in_1 - percent_in_2);
	}
	return difference;
}