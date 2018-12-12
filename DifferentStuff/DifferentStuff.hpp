#pragma once
#include <vector>
#include <sstream>
#include <numeric>
#include <string>
#include <Windows.h>

std::vector<std::string> stringParser(const std::string& input);
bool toUnsigned(std::string& input, unsigned& val);
unsigned menu(const std::string& input, HANDLE h);
void centerAlign(std::string);