// ldecode.cpp

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <regex>

bool is_number(const std::string& s);
std::string findValue(std::map<int,std::string> m, std::string value);
std::vector<std::string> split_by_whitespace (std::string s);

int main(int argc, char** argv) {

	// used for -l 
	std::vector<std::vector<std::string> > table;
	std::map<int,std::string> dictionary;
	std::vector<std::string> output;
	// init dictionary
	int index = 256;
	for (int i = 0; i < index; i++) {
		dictionary[i] = std::string(1,i);
	}
	std::string s;
	std::getline(std::cin,s);

	std::vector<std::string> input = split_by_whitespace(s);

	std::string k = input[0];
	output.push_back(k);
	std::string w = k;
	std::cout << s << std::endl;

	// setup initial for table  
	std::string temp[] = {"NIL",k, k};
	std::vector<std::string> v (temp, temp+sizeof(temp)/sizeof(std::string));
	table.push_back(v);
	
	for (int i = 1; i < input.size(); i++) {
		k = input[i];
		std::cout << k << std::endl;
		std::vector<std::string> vec;
		std::string z = findValue(dictionary,w);
		if (!z.empty() && std::stoi(z) >= 256) {
			vec.push_back(z);
		} else {
			vec.push_back(w);
		}
		
		vec.push_back(k);
		if(is_number(k)) {
			vec.push_back(dictionary[std::stoi(k)]);
			if(dictionary.count(std::stoi(k))) {
				// if found in dictionary, get the symbol stored
				k = dictionary[std::stoi(k)];
			} 
			// std::cout << std::stoi(k) << std::endl;
		} else {
			vec.push_back(k);
		}
		vec.push_back(std::to_string(index));
		vec.push_back(w + k[0]);

		// output k
		output.push_back(k);
		// add w + k[0] to dictionary
		dictionary[index++] = w + k[0];
		w = k;
		table.push_back(vec);
	}
	
	if (argv[1]) {
		// -l specified
		for (int i = 0; i < table.size(); ++i) {
			for (int j = 0; j < table[i].size(); ++j) {
				std::cout << table[i][j] << ' ';
			}
			std::cout << std::endl;
		}

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

std::string findValue(std::map<int,std::string> m, std::string value) {
	std::string res;
	for (std::map<int,std::string>::const_iterator it = m.cbegin(); it != m.cend(); ++it) {
		// if (std::to_string(it->second) == value) {
		// 	res = it->first;
		// 	break;
		// }
		if (it->second == value) {
			res = std::to_string(it->first);
			break;
		}
	}
	return res;
}

std::vector<std::string> split_by_whitespace (std::string s) {
	int flag = 0;
	std::vector<std::string> v;
	std::string temp;
	for ( std::string::iterator i = s.begin(); i != s.end(); ++i) {
		if ((*i) == ' ') {
			if (flag != 0) {
				// we've already seen a white space, treat this one as own character
				temp = " ";
				flag = 0;
				v.push_back(temp);
				temp = "";
				continue;
			}
			v.push_back(temp);
			temp = "";
			flag++;
			continue;
		}

		temp += *i;
		flag = 0;
	}

	return v;
}