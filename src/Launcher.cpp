#include "main.h"

using namespace std;
namespace fs = filesystem;

int main() {
	setlocale(LC_ALL, "Russian");
	
	Language russian("res/language/input/data.txt");
	russian.print_data();

	/*
	string for_block = "��������	��� ���� �� ��� ��	127523\n\
		���������	��� ���� �� ��� ���	226781\n\
		���������	��� ���� �� ��� ���	226782\n\
		���������	��� ���� �� ��� ���	226783\n\
		����������	��� ���� �� ��� ��	226784\n\
		���������	��� ���� �� ��� ��	226785\n\
		���������	��� ���� �� ��	1273054\n\
		����������	��� ���� �� ���	1273055\n\
		����������	��� ���� �� ���	1273056\n\
		����������	��� ���� �� ���	1273057\n\
		�����������	��� ���� �� ��	1273058\n\
		����������	��� ���� �� ��	1273059";

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