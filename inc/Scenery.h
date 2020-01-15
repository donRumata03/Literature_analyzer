#pragma once
#include "main.h"

class Scenery
{
private:
	inline static char russian_path [] = "res/language/input/data.txt";
	inline static char test_path [] = "res/language/input/little_test_data.txt";
	void load_language();
	Language lang;
public:

	Scenery() = default;
	
	static void perstfix_cutter();
	void clever_prefix_cutter();
	static void fs_test();
	void doOld();
};
