#pragma once

#include "pch.h"
#include "utils.h"
#include "Language.h"


enum class free_properties : int // Независимые свойства слова
{
	unknown = -1,
	modal,
	predicate
};


enum class word_types : int {	// Части речи:
	unknown = -1,
	noun,						// Существительное
	verb,							// Глагол
	adjective,						// Прилагательное
	adverb,							// Наречие
	preposition,					// Предлог
	particle,						// Частича
	interjection,					// Междометие
	conjunction,					// Союз
	communion,						// Причастие
	verb_communion,					// Деепричастие
	count,							// Числительное
	pronoun,						// Местоимение
	introduce,						// Вводное слово
	pretext
};


enum class word_case : int { // Падеж:
	unknown = -1,
	nominative,						// Именительный
	parent,							// Родительный
	accusative,						// Винительный
	dative,							// Дательный
	ablative,						// Творитльный
	prepositional					// Предложный
};


enum class gender : int { // Род:
	unknown = -1,
	male = 0,							// Мужкой род
	female,								// Женский род
	neuter								// Средний род
};


enum class quantity : int { // Число:
	unknown = -1,
	single = 0,							// Единственное число
	multiple							// Множественное число
};


enum class soulness : int { // Одушевлённость:
	unknown = -1,
	ensouled = 0,	// Одушевлённое
	non_ensouled	// Неодушевлённое
};

enum class tence : int { // Время:
	unknown = -1,
	past = 0,	// Прошедшее
	present,	// Настоящее
	future		// Будущее
};


extern map<string, free_properties> string_to_free_properties_converter;
extern map<string, word_types> string_to_word_type_converter;
extern map<string, gender> string_to_gender_converter;
extern map<string, quantity> string_to_quantity_converter;
extern map<string, soulness> string_to_soulness_converter;
extern map<string, tence> string_to_tence_converter;

#define HAS_word_type_to_string_converter
extern map<word_types, string> word_type_to_string_converter;
extern map<free_properties, string> free_properties_to_string_converter;
extern map<gender, string> gender_to_string_converter;
extern map<quantity, string> quantity_to_string_converter;
extern map<soulness, string> soulness_to_string_converter;
extern map<tence, string> tence_to_string_converter;
extern map<word_case, string> case_to_string_converter;



struct word_properties {
	virtual void print_data() { cout << "Property of unknown type..." << endl; }
	virtual vector<string> make_properties(vector<string>& properties) { cout << "ERROR" << endl; return vector<string>(); }
};


struct noun_properties : public word_properties {
public:
	word_case word_case = word_case::unknown;
	gender word_gender = gender::unknown;
	quantity word_quantity = quantity::unknown;
	soulness word_soulness = soulness::unknown;

	noun_properties(vector<string>& properties);
	noun_properties() = default;
	vector<string> make_properties(vector<string>& properties);

	void print_data() {
		cout << "Noun properties: {";

		cout << "Gender: " << gender_to_string_converter[this->word_gender] << \
			"; Soulness: " << soulness_to_string_converter[this->word_soulness] << \
			"; Quantity: " << quantity_to_string_converter[this->word_quantity] << \
			"; Case: " << case_to_string_converter[this->word_case];
	}
};


struct adjective_properties : public word_properties {
public:
	word_case word_case = word_case::unknown;
	gender word_gender = gender::unknown;
	quantity word_quantity = quantity::unknown;
	soulness word_soulness = soulness::unknown;

	adjective_properties(vector<string>& properties);
	adjective_properties() = default;
	vector<string> make_properties(vector<string>& properties);

	void print_data() {
		cout << "Adjective properties: {";

		cout << "Gender: " << gender_to_string_converter[this->word_gender] << \
			"; Soulness: " << soulness_to_string_converter[this->word_soulness] << \
			"; Quantity: " << quantity_to_string_converter[this->word_quantity] << \
			"; Case: " << case_to_string_converter[this->word_case];
	}
};


struct verb_properties : public word_properties {
public:
	tence word_tence = tence::unknown;

	verb_properties(vector<string>& properties);
	verb_properties() = default;

	vector<string> make_properties(vector<string>& properties);

	void print_data() {
		cout << "Verb properties: {";
		cout << "\tTence: " << tence_to_string_converter[word_tence] << "}";
	}
};






class Word {
public:
	string raw_data;
	vector<string> raw_properties;

	string data;
	word_types word_type = word_types::unknown;
	word_properties* properties;
	free_properties free_property = free_properties::unknown;
	long long frequency = -1;

	Word() = default;
	Word(string &s);
	void print_data();
	string get_type() const;
};


