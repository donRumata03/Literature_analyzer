#include "Word.h"

// Word to enums convertors:


// Free characteristics



// Type:
map<string, word_types> string_to_word_type_converter{
	{"����", word_types::conjunction},
	{"���", word_types::noun},
	{"������", word_types::predicate},
	{"����", word_types::particle},
	{"����", word_types::interjection},
	{"���", word_types::adjective},
	{"��", word_types::verb},
	{"���", word_types::communion},
	{"���", word_types::adverb},
	{"���", word_types::noun},
	{"���", word_types::noun},
	{"����", word_types::verb_communion},
	{"����", word_types::count},
	{"����", word_types::pronoun},
	{"����", word_types::introduce},
	{"�����", word_types::pretext}
};

// Backward converter:
map<word_types, string> word_type_to_string_converter{
	{word_types::unknown, "����������� ����� ����"},
	{word_types::conjunction, "����"},
	{word_types::noun, "���������������"},
	{word_types::predicate, "����������" },
	{word_types::particle, "�������" },
	{word_types::interjection, "����������" },
	{word_types::adjective, "��������������" },
	{word_types::verb, "�������" },
	{word_types::communion, "���������" },
	{word_types::adverb, "�������" },
	{word_types::verb_communion, "������������"},
	{word_types::count, "������������"},
	{word_types::introduce, "������� �����"},
	{word_types::pretext, "�������"}
};


// Gender
map<string, gender> string_to_gender_converter {
	{"���", gender::male},
	{"���", gender::male},
	{"��", gender::male}
};

// Backward converter:
map<gender, string> gender_to_string_converter{
	{gender::male, "�������" },
	{gender::female, "�������" },
	{gender::neuter, "�������" },
	{gender::unknown, "WARNING: ������������ ������" }
};


// Quantity
map<string, quantity> string_to_quantity_converter {
	{"��", quantity::single},
	{"��", quantity::multiple}
};

// Backward converter:
map<quantity, string> quantity_to_string_converter{
	{quantity::unknown, "WARNING!!! ��� ������������. �� ���������� ����������."},
	{quantity::single, "������������"},
	{quantity::multiple, "�������������"}
};


// Soulness
map<string, soulness> string_to_soulness_converter {
	{"����", soulness::ensouled},
	{"����", soulness::non_ensouled}
};

// Backward converter:
map<soulness, string> soulness_to_string_converter{
	{soulness::ensouled, "�����������"},
	{soulness::non_ensouled, "�������������"},
	{soulness::unknown, "����������, ����� ���� ��� �����"}
};


// Tence
map<string, tence> string_to_tence_converter {
	{"����", tence::past},
	{"����", tence::past},
	{"���", tence::past}
};

// Backward converter
map<tence, string> tence_to_string_converter{
	{tence::unknown, "����������� �����"},
	{tence::future, "�������"},
	{tence::past, "���������"},
	{tence::present, "���������"}
};


map<word_case, string> case_to_string_converter{
	{word_case::unknown, "������������ �����, ����� ����, ����������?)"},
	{word_case::nominative, "������������"},
	{word_case::parent, "�����������"},
	{word_case::dative, "���������"},
	{word_case::accusative, "�����������"},
	{word_case::ablative, "������������"},
	{word_case::prepositional, "����������"}
};



map<string, word_case> string_to_case_converter{
	{"��", word_case::nominative },
	{"���", word_case::parent },
	{ "���", word_case::dative},
	{"���", word_case::accusative },
	{"��", word_case::ablative},
	{"��", word_case::prepositional}
};


Word::Word(string &s) {
	raw_data = s;
	vector<string> props = split(raw_data);
	int type_index = -1;
	for (uint i = 0; i < props.size(); i++) {
		for (auto prop : string_to_word_type_converter) {
			if (prop.first == props.at(i)) {
				type_index = i;
				break;
			}
		}
	}
	if (type_index == -1) { cout << "Unknown word type here: " << raw_data << endl; return; }
	data = Join(" ", Slice(props, 0, type_index));
	raw_properties = Slice(props, type_index + 1, props.size());
	word_type = string_to_word_type_converter[props.at(type_index)];
	
	if (is_digital(raw_properties.back())) {
		frequency = stoll(raw_properties.back());
		raw_properties = Slice(raw_properties, 0, raw_properties.size() - 1);
	}

	bool has_easy_type = true;

	switch (word_type) {
	case word_types::noun:
		this->properties = new noun_properties();
		break;
	case word_types::adjective:
		this->properties = new adjective_properties();
		break;
	case word_types::verb:
		this->properties = new verb_properties();
		break;
	default:
		this->properties = new word_properties();
		has_easy_type = false;
		break;
	}
	if (has_easy_type) {
		this->raw_properties = this->properties->make_properties(raw_properties);
	}
}


void Word::print_data(string tab) {
	cout << "Word: " << data << "; ";
	cout << "Type: " << this->get_type() << "; ";
	cout << "Frequency: " << this->frequency << "; ";
	cout << "Known properties: " << endl;
	properties->print_data();
	cout << endl << "}; ";
	cout << "Unknown properties: {" << endl;
	print(raw_properties, "\n", "", "\t");
	cout << "}" << endl;
}

string Word::get_type() {
#ifndef HAS_word_type_to_string_converter
	for (auto p : string_to_word_type_converter) {
		if (p.second == word_type) {
			return p.first;
		}
	}
#else
	return word_type_to_string_converter[word_type];
#endif
}



verb_properties::verb_properties(vector<string>& properties) {
	for (string prop : properties) {
		if (string_to_tence_converter.find(prop) != string_to_tence_converter.end()) {
			this->word_tence = string_to_tence_converter[prop];
		}
	}
}

adjective_properties::adjective_properties(vector<string>& properties) {
	for (string prop : properties) {
		if (string_to_case_converter.find(prop) != string_to_case_converter.end()) {
			this->word_case = string_to_case_converter[prop];
		}
		else if (string_to_gender_converter.find(prop) != string_to_gender_converter.end()) {
			this->word_gender = string_to_gender_converter[prop];
		}
		else if (string_to_soulness_converter.find(prop) != string_to_soulness_converter.end()) {
			this->word_soulness = string_to_soulness_converter[prop];
		}
		else if (string_to_quantity_converter.find(prop) != string_to_quantity_converter.end()) {
			this->word_quantity = string_to_quantity_converter[prop];
		}
	}
}



noun_properties::noun_properties(vector<string>& properties) {
	for (string prop : properties) {
		if (string_to_case_converter.find(prop) != string_to_case_converter.end()) {
			
			this->word_case = string_to_case_converter[prop];
		}
		else if (string_to_gender_converter.find(prop) != string_to_gender_converter.end()) {
			this->word_gender = string_to_gender_converter[prop];
		}
		else if (string_to_soulness_converter.find(prop) != string_to_soulness_converter.end()) {
			this->word_soulness = string_to_soulness_converter[prop];
		}
		else if (string_to_quantity_converter.find(prop) != string_to_quantity_converter.end()) {
			this->word_quantity = string_to_quantity_converter[prop];
		}
	}
}

vector<string> noun_properties::make_properties(vector<string>& properties) {
	vector<string> res;
	for (string prop : properties) {
		if (string_to_case_converter.find(prop) != string_to_case_converter.end()) {
			this->word_case = string_to_case_converter[prop];
		}
		else if (string_to_gender_converter.find(prop) != string_to_gender_converter.end()) {
			this->word_gender = string_to_gender_converter[prop];
		}
		else if (string_to_soulness_converter.find(prop) != string_to_soulness_converter.end()) {
			this->word_soulness = string_to_soulness_converter[prop];
		}
		else if (string_to_quantity_converter.find(prop) != string_to_quantity_converter.end()) {
			this->word_quantity = string_to_quantity_converter[prop];
		}
		else {
			res.push_back(prop);
		}
	}
	return res;
}

vector<string> adjective_properties::make_properties(vector<string>& properties) {
	vector<string> res;
	for (string prop : properties) {
		if (string_to_case_converter.find(prop) != string_to_case_converter.end()) {
			this->word_case = string_to_case_converter[prop];
		}
		else if (string_to_gender_converter.find(prop) != string_to_gender_converter.end()) {
			this->word_gender = string_to_gender_converter[prop];
		}
		else if (string_to_soulness_converter.find(prop) != string_to_soulness_converter.end()) {
			this->word_soulness = string_to_soulness_converter[prop];
		}
		else if (string_to_quantity_converter.find(prop) != string_to_quantity_converter.end()) {
			this->word_quantity = string_to_quantity_converter[prop];
		}
		else {
			res.push_back(prop);
		}
	}
	return res;
}

vector<string> verb_properties::make_properties(vector<string>& properties) {
	vector<string> res;
	for (string prop : properties) {
		if (string_to_tence_converter.find(prop) != string_to_tence_converter.end()) {
			this->word_tence = string_to_tence_converter[prop];
		}
	}
	return res;
}

