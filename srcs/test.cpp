#define TEST
#include <iostream>
#include <map>
#include "map.hpp"
#include <string>
#include <list>
#include "tests.hpp"

int main(void)
{
	std::string stab[6] = {"zero", "un", "deux", "trois", "quatre", "cinq"};
	std::list<ft::pair<int, std::string> > lst;

	for (size_t i = 0; i < 6; i++)
		lst.push_back(ft::pair<int, std::string>(i, stab[i]));

	std::map<int, std::string> m;
	m.insert(std::pair<int, std::string>(1, "dsada"));
	std::cout << "test : " << m.at(1) << std::endl;

	ft::map<int, std::string> mf;
	mf.insert(ft::pair<int, std::string>(1, "dsada"));
	std::cout << "test : " << mf.at(1) << std::endl;
	std::cout << "begin" << std::endl;

	ft::map<int, std::string> ml0;
	ft::map<int, std::string> ml(lst.begin(), lst.end());
	ft::map<int, std::string> ml2(ml.begin(), ml.end());
	ft::map<int, std::string> ml3(ml2);
	ft::map<int, std::string> ml4 = ml3;

	stab[0] = "dsds";
	// ml2.insert(ft::pair<int, std::string>(10, "ml2"));
	printTitle("ml0");
	ml0.print();
	printTitle("ml");
	ml.print();
	printTitle("ml2");
	ml2.print();
	printTitle("ml3");
	ml3.print();
	printTitle("ml4");
	ml4.print();
	
	// ml2.print();

	// std::cout << "end" << std::endl;

	return 0;
}
