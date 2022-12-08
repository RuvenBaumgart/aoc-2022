#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
std::vector<std::string> readLinesFromFile(std::string filename);
void split(const std::string& str, const char c, std::vector<std::string>& res);
int count_occurenc_of(const char c, std::string s);
void group(std::vector<std::string>& input, std::vector<std::vector<std::string>>& result);
std::vector<int> getNumbersFromString(std::string str);
