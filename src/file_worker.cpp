#include "file_worker.h"

using namespace std;

vector<wstring> stream_to_string_vector(wistream& in) {
    vector<wstring> res;
    wstring buff;
    while (!in.eof()) {
        getline(in, buff);
        res.push_back(buff);
    }
    return res;
}

vector<string> stream_to_string_vector(istream& in) {
    vector<string> res;
    string buff;
    while (!in.eof()) {
        getline(in, buff);
        res.push_back(buff);
    }
    return res;
}



string filter_punctuation(const string& s)
{
    const char* forbidden{ ".,:; " };
    const auto idx_start(s.find_first_not_of(forbidden));
    const auto idx_end(s.find_last_not_of(forbidden));

    return s.substr(idx_start, idx_end - idx_start + 1);
}


vector<string> file_to_string_vector(const char fname []) {
    ifstream file(fname);
    vector<string> res = stream_to_string_vector(file);
    return res;
}

vector<wstring> file_to_wstring_vector(const char fname[]) {
    wifstream file(fname);
    vector<wstring> res = stream_to_string_vector(file);
    return res;
}


string file_to_string(const char fname[]) {
    auto strs = file_to_string_vector(fname);

    string res;
    for (string s : strs) {
        res += s + '\n';
    }
    return res;
}

