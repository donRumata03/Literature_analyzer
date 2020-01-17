#include "Analitics.h"


Analitics::Analitics(string& text, Language& language) : lang (language), simple(Simple_analitics(text)), top(word_top(text))
{}

void Analitics::load_dist_coefficients()
{
	constexpr char path [] = "res/system/coeff.txt";
	string s = readFile(path);
	coeffs = double_mylang_parse(s);
}

double Analitics::dist(Analitics& a1, Analitics& a2)
{
	assert(coeffs.find("simple_analoitics") != coeffs.end() && "No Simple analitics coeffs");
	assert(coeffs.find("word_top") != coeffs.end() && "No word top coeffs");

	assert(coeffs["simple_anailtics"].size() == 1 && "Invalid SA coeff number");
	assert(coeffs["word_top"].size() == 1 && "Invalid word top coeff number");
	
	return square(coeffs["simple_anailtics"][0] * Simple_analitics::dist(a1.simple, a2.simple)) + \
		square(coeffs["word_top"][0] * word_top::dist(a1.top, a2.top));
}


