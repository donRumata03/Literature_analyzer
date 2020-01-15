#include "Scenery.h"


void Scenery::doOld()
{

	/*
	Timer language_load_tim("Language load: ", true);
	Language russian(russian_path);

	language_load_tim.~Timer(); // Prints name


	russian.print_word_type_stat();
	russian.print_frequent_prefixes(100);
	russian.print_frequent_postfixes(100);

	*/

	// russian.print_data();

	// Benchmark: (outdated)
	/*
	int max_word_index = russian.main_form_getter.size();
	cout << max_word_index << endl;

	luint number_of_runnings = 10;

	double time_counter = 0;

	for (int i = 0; i < number_of_runnings; i++) {
		luint this_word_index = (static_cast<luint>(rand()) << 8 | static_cast<luint>(rand())) % max_word_index;
		string this_word;
		int index = 0;
		for (auto j : russian.main_form_getter) {
			if (index == this_word_index) {
				this_word = j.first;
				break;
			}
			index++;
		}
		cout << "This word = " << this_word << endl;
		Timer t("", false);
		auto[success, this__word]  = russian.get_main_form(this_word);
		double time_took = t.get_time();
		cout << "This_time: " << time_took << " ms" << endl;
		time_counter += time_took;
	}

	cout << "Average time of getting: " << time_counter / number_of_runnings << " ms" << endl;

	*/

	// User interface: family getter

	/*
	string my_string;

	while (cin >> my_string) {
		auto [success, word_block] = russian.get_family(my_string);
		cout << (success ? ("Well, I know this word... It`s root is") : ("I don`t know this word!")) << endl;
		if (success) { word_block->print_words(); }
		else cout << "Try again!!!!" << endl;
	}

	*/

	// User interface: word divider

	/*
	string user_word;
	while(cin >> user_word)
	{
		// russian.analyze_word(user_word).print();
		cout << russian.cut_prestfixes(user_word);
	}
	*/

	/*

	const fs::path workdir = fs::current_path();
	cout << workdir;


	str war_and_piece, dads_and_kids;
	double reading_time, time_stat;

	Timer tim_read("");
	war_and_piece.from_file("res/Books/War_and_piece.txt");
	dads_and_kids.from_file("res/Books/Dads_and_kids.txt");

	reading_time = tim_read.get_time("ms");

	cout << "Read!" << " (Time took: " << reading_time << " ms)" << endl;

	Timer tim_stat("Stat");
	word_top top_wap(war_and_piece);
	word_top top_dak(dads_and_kids);
	time_stat = tim_stat.get_time();
	cout << "Statistics took: " << time_stat << " ms" << endl;
	top_wap.print_first(50);
	top_dak.print_first(50);

	cout << endl;
	cout << word_top::dist(top_dak, top_wap) << endl;
	*/

}


void Scenery::load_language()
{
	Timer tim("Loading language...");
	this->lang = Language(russian_path);
}

void Scenery::perstfix_cutter()
{
	Language russian;
	russian.load_prestfixes();
	string user_string;
	while(cin >> user_string)
	{
		string s = russian.cut_prestfixes(user_string);
		cout << s << endl;
	}
}


void Scenery::clever_prefix_cutter()
{
	load_language();
	string user_string;
	while (cin >> user_string)
	{
		string s = lang.cut_prestfixes(user_string);
		cout << s << endl;
	}
}


void Scenery::fs_test()
{
	vector<string> paths = find_files("res/");
	for(auto& p : paths)
	{
		cout << p << endl;
		string s = readFile(&p[0]);
		if(filesystem::file_size(filesystem::path(p)) < 10000)
		cout << s << endl;
	}
}