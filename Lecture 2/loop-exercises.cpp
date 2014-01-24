#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iterator>
#include <math.h>

// http://jessicarbrown.com/images/ft-cpp-loop.gif
int main()
{
	{
		// non-c++11 syntax:
		std::cout << "+++++\tNon-c++11 syntax:\n";
		
		// 1. create a for loop that prints numbers from 1 to 5
		std::cout << "\n1. Loop that prints numbers 1 to 5\n";
		for (int i = 1; i < 6; i++)	{
			std::cout << i << "\t";
		}

		// 2. create a for loop that iterates through a vector of strings and print
		// them
		std::cout << "\n\n2. Loop that iterates through a vector of string and prints them:\n";				
		std::vector<std::string> vec_strings;
		vec_strings.push_back("Monday");
		vec_strings.push_back("Tuesday");
		vec_strings.push_back("Wednesday");
		vec_strings.push_back("Thursday");
		vec_strings.push_back("Friday");
		for(std::vector<std::string>::iterator it = vec_strings.begin(); it != vec_strings.end(); it++) {
			std::cout << *it << "\t";		
		}
		
		// 3. create a for loop that gets a map of <string, float> and returns a
		// new map of of (char*, int)
		std::cout << "\n3. Loop that gets a map of <string, float> and returns a new map of (char*, int)";				
		std::map<std::string, float> input_map;
		input_map["pi"] = 3.1415f;
		input_map["e"] = 2.7182f;
		input_map["sqrt 2"] = 1.4142f;
		input_map["ln 2"] = 0.6931f;
		std::map<const char*, int> output_map;		
		std::cout << "\nMap of <string, float>:\n";
		for(std::map<std::string, float>::iterator input_it = input_map.begin(); input_it != input_map.end(); input_it++) {
			std::cout << input_it->first << "\t" << input_it->second << std::endl;
			const char* my_char = input_it->first.c_str();
			output_map[my_char] = (int) input_it->second;			
		}				
		std::cout << "\nConverted Map of <char*, int>:\n";
		for(std::map<const char*, int>::iterator output_it = output_map.begin(); output_it != output_map.end(); output_it++) {
			std::cout << output_it->first << "\t" << output_it->second << std::endl;		
		}
		
		// (3.) 4. create a for loop that gets a map of <string, float> and updates the
		// same map so that it adds "yeah!" to each string and rounds the float
		// number. transform it in place.
		std::cout << "\n4. Loop that gets a map of <string, float> and updates the same map " 
			<< "\n   so that it adds ""yeah!"" to each string and rounds the float number."
			<< "\n   Transformation is done in place.";
		std::map<std::string, float> transform_map;
		transform_map["pi"] = 3.1415f;
		transform_map["e"] = 2.7182f;
		transform_map["sqrt 2"] = 1.4142f;
		transform_map["ln 2"] = 0.6931f;		
		std::cout << "\nMap of <string, float> before transformation:\n";
		std::map<std::string, float>::iterator transform_it = transform_map.begin();
		for(; transform_it != transform_map.end(); transform_it++) {
			std::cout << transform_it->first << "\t" << transform_it->second << std::endl;
		}			
		
		std::cout << "\nMap of <string, float> after transformation with const_cast: DANGEROUS METHOD!!!\n";
		transform_it = transform_map.begin();
		for(; transform_it != transform_map.end(); transform_it++) {
			const_cast<std::string &>(transform_it->first) = transform_it->first + " yeah!";
			transform_it->second = trunc(transform_it->second);
			std::cout << transform_it->first << "\t" << transform_it->second << std::endl;			
		}
		
		// (3.) 4. (cont) reset the map to change it with a good method
		transform_map.clear();
		transform_map["pi"] = 3.1415f;
		transform_map["e"] = 2.7182f;
		transform_map["sqrt 2"] = 1.4142f;
		transform_map["ln 2"] = 0.6931f;		
		std::cout << "\nMap of <string, float> before transformation: \"Good method\" \n";
		//std::map<std::string, float>::iterator transform_it = transform_map.begin();
		transform_it = transform_map.begin();
		for(; transform_it != transform_map.end(); transform_it++) {
			std::cout << transform_it->first << "\t" << transform_it->second << std::endl;
		}		
		std::map<std::string, float>::iterator transform_end = transform_map.end();
		transform_it = transform_map.begin();		
		for(; transform_it != transform_end; transform_it++) {
			std::string my_string = transform_it->first + " yeah!";
			int temp = trunc(transform_it->second);
			transform_map.erase(transform_it);
			
			transform_map.insert( std::pair<std::string, float>(my_string,temp));
			//transform_map[my_string] = temp; // Esta linea se puede utilizar como alternativa a la anterior.
		}		
		std::cout << "\nMap of <string, float> after transformation:\n";
		for(transform_it = transform_map.begin(); transform_it != transform_map.end(); transform_it++) {
			std::cout << transform_it->first << "\t" << transform_it->second << std::endl;		
		}
		//----------------------------------------------------------------------		
	}

	
	{
		// 4. transform every previous exercise to ranged for loops. use as much
		// c++11 syntax as you can
		std::cout << "\n\n\n+++++\tC++11 syntax:\n";

		std::cout << "\n1. Loop that prints numbers 1 to 5\n";
		for (int i = 1; i < 6; i++)	{
			std::cout << i << "\t";
		}

		std::cout << "\n\n2. Loop that iterates through a vector of string and prints them:\n";			
		std::vector<std::string> vec_strings = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};		
		for(auto v: vec_strings) {
			std::cout << v << "\t";		
		}

		std::cout << "\n3. Loop that gets a map of <string, float> and returns a new map of of (char*, int)";	
		std::map<std::string, float> input_map = {{"pi", 3.1415f}, {"e", 2.7182f}, {"sqrt2", 1.4142f}, {"ln2", 0.6931f}};		
		std::map<const char*, int> output_map;
		std::cout << "\nMap of <string, float>:\n";
		for(auto kv: input_map) {
			std::cout << kv.first << "\t" << kv.second << std::endl;
			const char* my_char = kv.first.c_str();
			output_map[my_char] = (int) kv.second;
		}		
		std::cout << "\nConverted Map of <const char*, int>:\n";
		for(auto kv: output_map) {
			std::cout << kv.first << "\t" << kv.second << std::endl;		
		}
		
		std::cout << "\n4. Loop that gets a map of <string, float> and updates the same map " 
				<< "\n\t so that it adds ""yeah!"" to each string and rounds the float"
				<<	"number. transform it in place";
		std::map<std::string, float> transform_map = {{"pi", 3.1415f}, {"e", 2.7182f}, {"sqrt2", 1.4142f}, {"ln2", 0.6931f}};
				
		std::cout << "\nMap of <string, float> before transformation:\n";
		std::map<std::string, float>::iterator transform_it = transform_map.begin();
		for(auto kv: transform_map) {
			std::cout << kv.first << "\t" << kv.second << std::endl;
		}		
		std::cout << "\nMap of <string, float> after transformation with const_cast: DANGEROUS METHOD!!!\n";		
		for(auto kv: transform_map) {
			const_cast<std::string &>(kv.first) = kv.first + " yeah!";
			kv.second = trunc(kv.second);
			std::cout << kv.first << "\t" << kv.second << std::endl;			
		}
		
		// (3.) 4. (cont) reset the map to change it with a good method
		transform_map.clear();
		transform_map = {{"pi", 3.1415f}, {"e", 2.7182f}, {"sqrt2", 1.4142f}, {"ln2", 0.6931f}};		
		std::cout << "\nMap of <string, float> before transformation: \"Good method\" \n";		
		for(auto kv: transform_map) {
			std::cout << kv.first << "\t" << kv.second << std::endl;
		}		
		std::map<std::string, float>::iterator transform_end = transform_map.end();
		transform_it = transform_map.begin();		
		for(auto it11 = transform_map.cbegin(); it11 != transform_map.cend(); ++it11) {
			std::string my_string = it11->first + " yeah!";
			int temp = trunc(it11->second);
			transform_map.erase(it11);
			
			//transform_map.insert( std::pair<std::string, float>(my_string,temp));
			transform_map[my_string] = temp; // Esta linea se puede utilizar como alternativa a la anterior.
		}		
		std::cout << "\nMap of <string, float> after transformation:\n";
		for(auto kv: transform_map) {
			std::cout << kv.first << "\t" << kv.second << std::endl;
		}
	}
	
	// 5. write a for loop that prints a pyramid of height N, like this:    
	//	
	//	               **
	//	              ****
	//	             ******
	//	            ********
	//	           **********
	//	          ************
	std::cout << "\n\n+++++Loop that prints a pyramid of height N:\n";	
	int  N = 0;		
	while( N > 40 || N < 1)	{
		std::cout << "\tPlease, enter N [1, 40]:\n";	
		std::cin >> N;
	}
	std::cout << "N = " << N << std::endl;	
	const int half_wide = 45;	
	for( int n = 1; n <= N; ++n){
		std::string blank (half_wide - n, ' ');
		std::string stars (2 * n, '*');
		std::cout << blank << stars << std::endl;

	}	

	return 0;	
}
