// lencode.cpp

#include <iostream>
#include <map>
#include <string>
#include <vector>

// first, code up the compression
// then, make a 2d array and store the table:
// 		w 	k 	output	index	symbol

std::string findValue(std::map<std::string,int> m, std::string value);


int main (int argc, char** argv) {
	int found = 0;

	// initialise dictionary
	std::map<std::string,int> dictionary;
	int index = 256;
	for (int i = 0; i < index; i++) {
		dictionary[std::string(1,i)] = i;
	}
	// for (std::map<std::string,int>::const_iterator it = dictionary.cbegin(); it != dictionary.cend(); ++it) {
	// 	std::cout << it->first << ' ' << it->second << std::endl;;
	// }
	// std::cout << std::endl;
	// init 2d vector for -l arg
	std::vector<std::vector<std::string> > table;

	std::string w;
	std::vector<std::string> output;
	std::string wk;
	char k;

	// read from stdin until EOF
	// incorrect because it will ignore spaces and tabs
	while (std::cin.get(k)) {
		if (w.empty()) {
			w = k;
			std::string arr[] = {"NIL",std::string(1,k)};
			std::vector<std::string> temp (arr, arr+sizeof(arr)/sizeof(std::string));
			table.push_back(temp);
			continue;
		}
		// check if dictionary already contains this
		if (found == 1) {
			wk = findValue(dictionary, w) + k;
		} else {
			wk = w + k;	
		}
		if (dictionary.count(wk) > 0) {
			// std::cout << wk << std::endl;
			
			// if does exist, set w to be wk
			// at the moment, we set w = index
			// when this carries over to next iteration, wk = index+k 
			// we want value at index instead.
			// separate output and w
			std::vector<std::string> temp;
			if (found == 1) {
				temp.push_back(findValue(dictionary,w));
				temp.push_back(std::string(1,k));
			} else {
				temp.push_back(w);
				temp.push_back(std::string(1,k));
			}
			table.push_back(temp);
			w = std::to_string(dictionary[wk]);
			// set found to indicate found
			found = 1;
		} else {
			output.push_back(w);
			if (found == 1) {
				w = findValue(dictionary,w);
			}
			// add wk to dictionary
			dictionary[wk] = index++;
			std::string arr[] = {w,std::string(1,k),w,std::to_string(index-1),wk};
			std::vector<std::string> temp (arr,arr+sizeof(arr)/sizeof(std::string));
			table.push_back(temp);

			w = std::string(1,k); 
			found = 0;
		}
	}
	output.push_back(w);
	std::string arr[] = {w,"EOF",w};
	std::vector<std::string> temp (arr,arr+sizeof(arr)/sizeof(std::string));
	table.push_back(temp);
	
	
	if (argv[1]) {
		for(int i = 0; i < table.size(); i++) {
			for (int j = 0; j < table[i].size(); j++)
			{

				std::cout << table[i][j] << ' ';
			}
			std::cout << std::endl;
		}
	} else {
		for (std::vector<std::string>::const_iterator i = output.begin(); i != output.end(); ++i) {
			std::cout << *i + ' ';
		}
		std::cout << std::endl;
	}	
	return 0;
}

std::string findValue(std::map<std::string,int> m, std::string value) {
	std::string res;
	for (std::map<std::string,int>::const_iterator it = m.cbegin(); it != m.cend(); ++it) {
		if (std::to_string(it->second) == value) {
			res = it->first;
			break;
		}
	}
	return res;
}
