#include "main.h"
#include "cpps.h"

using namespace std;


int main() {
	system("chcp 1251");
	system("cls");
	setlocale(LC_ALL, "Russian");

	Scenery s;
	s.clever_prefix_cutter();
	
	return 0;
}