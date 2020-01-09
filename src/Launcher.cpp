#include "main.h"

using namespace std;
namespace fs = filesystem;

int main() {
	setlocale(LC_ALL, "Russian");
	
	Language russian("res/language/input/data.txt");
	russian.print_data();

	/*
	string for_block = "верхолаз	сущ одуш ед муж им	127523\n\
		верхолаза	сущ одуш ед муж род	226781\n\
		верхолазу	сущ одуш ед муж дат	226782\n\
		верхолаза	сущ одуш ед муж вин	226783\n\
		верхолазом	сущ одуш ед муж тв	226784\n\
		верхолазе	сущ одуш ед муж пр	226785\n\
		верхолазы	сущ одуш мн им	1273054\n\
		верхолазов	сущ одуш мн род	1273055\n\
		верхолазам	сущ одуш мн дат	1273056\n\
		верхолазов	сущ одуш мн вин	1273057\n\
		верхолазами	сущ одуш мн тв	1273058\n\
		верхолазах	сущ одуш мн пр	1273059";

	Word_family my_word_family(for_block);
	my_word_family.print_words();

	
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

	return 0;
}