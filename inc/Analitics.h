#pragma once

#include "pch.h"
#include "Simple_analitics.h"
#include "word_top.h"

class Analitics
{
public:
	void load_dist_coefficients();
private:
	Simple_analitics simple;
	word_top top;
	
};

