#include "file_walker.h"


vector<std::string> recursive_lsdir(const string& string_path)
{
	vector<string> res;
	vector<fs::path> subdirs;
	const fs::path path = string_path;

	fs::recursive_directory_iterator start("res");
	fs::recursive_directory_iterator _end;
	
	copy_if(start, _end, back_inserter(subdirs), [](const fs::path& p) {
		return fs::is_directory(p);
	});

	for(auto& p : subdirs)
	{
		res.push_back(p.string());
	}
	
	return res;
}

vector<std::string> lsdir(const string& string_path)
{
	vector<string> res;
	vector<fs::path> subdirs;
	const fs::path path = string_path;

	fs::directory_iterator start("res");
	fs::directory_iterator _end;

	copy_if(start, _end, back_inserter(subdirs), [](const fs::path& p) {
		return fs::is_directory(p);
		});

	for (auto& p : subdirs)
	{
		res.push_back(p.string());
	}

	return res;
}

vector<string> find_files(const string& string_path)
{
	vector<string> res;
	vector<fs::path> subdirs;
	const fs::path path = string_path;

	fs::recursive_directory_iterator start("res");
	fs::recursive_directory_iterator _end;

	copy_if(start, _end, back_inserter(subdirs), [](const fs::path& p) {
		return fs::is_regular_file(p);
	});

	for (auto& p : subdirs)
	{
		res.push_back(p.string());
	}

	return res;
}
