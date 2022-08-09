#include <iostream>
#include <map>
#include "map.hpp"
#include <string>
#include <list>

int main(void)
{
	std::string stab[5] = {"un", "deux", "trois", "quatre", "cinq"};
	std::list<ft::pair<int, std::string> > lst;

	for (size_t i = 0; i < 5; i++)
		lst.push_back(ft::pair<int, std::string>(i, stab[i]));

	std::map<int, std::string> m;
	m.insert(std::pair<int, std::string>(1, "dsada"));
	std::cout << "test : " << m.at(1) << std::endl;

	ft::map<int, std::string> mf;
	mf.insert(ft::pair<int, std::string>(1, "dsada"));
	std::cout << "test : " << mf.at(1) << std::endl;
	std::cout << "begin" << std::endl;

	ft::map<int, std::string> ml(lst.begin(), lst.end());
	ft::map<int, std::string> ml2(ml.begin(), ml.end());
	ml.print();
	// ml2.print();

	std::cout << "end" << std::endl;

	return 0;
}
