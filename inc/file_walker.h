#pragma once
#include "pch.h"

namespace fs = filesystem;


vector<std::string> recursive_lsdir(const string& string_path);
vector<std::string> lsdir(const string& string_path);

vector<string> find_files(const string& path);