// ldecode.cpp

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <cstring>

bool is_number(const std::string& s);

int main(int argc, char** argv) {

	// used for -l 
	std::vector<std::vector<stf::string> > table;
	std::map<int,std::string> dictionary;
	std::vector<std::string> output;
	// init dictionary
	int index = 256;
	for (int i = 0; i < index; i++) {
		dictionary[i] = std::string(1,i);
	}

	std::string k;
	std::cin >> k;
	output.push_back(k);
	std::string w = k;

	// setup initial 
	std::string temp[] = {"NIL",k, k};
	std::vector<std::string> v (temp, temp+sizeof(temp)/sizeof(std::string));
	table.push_back(v);
	
	// while(std::getline(std::cin,k,' ')) {
	while(std::cin >> k) {
		temp = ["x"];
		// std::
		// input.push_back(k);
		if(is_number(k)) {
			if(dictionary.count(std::stoi(k))) {
				// if found in dictionary, get the symbol stored
				k = dictionary[std::stoi(k)];
			} 
			// std::cout << std::stoi(k) << std::endl;
		}

		// output k
		output.push_back(k);
		// add w + k[0] to dictionary
		dictionary[index++] = w + k[0];
		w = k;

	}
	
	if (argv[1]) {
		// -l specified


	} else {
		for (int i = 0; i < output.size(); ++i) {
			std::cout << output[i];
		}
		std::cout << std::endl;
	}

	

	return 0;
}

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}