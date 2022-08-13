#define TEST
#include <iostream>
#include <map>
#include "map.hpp"
#include "vector.hpp"
#include <string>
#include <list>
#include "tests.hpp"

template< class T1, class T2 >
std::ostream &operator<<(std::ostream &os, const std::pair<T1,T2>& rhs )
{
	os << "(" << rhs.first << ", " << rhs.second << ")";
	return os;
}

template <class M>
void	print(const M& m)
{
	for (typename M::const_iterator i = m.begin(); i != m.end(); i++)
		std::cout << *i << " ";
	std::cout << std::endl;
	std::cout << "size    :" << m.size() << std::endl;
	std::cout << "empty   :" << m.empty() << std::endl;
	std::cout << "maxSize :" << m.max_size() << std::endl;
}

int main(void)
{
	std::string stab[6] = {"zero", "un", "deux", "trois", "quatre", "cinq"};
	std::list<std::pair<int, std::string> > lst;
	std::list<ft::pair<int, std::string> > lft;

	for (size_t i = 0; i < 6; i++)
	{
		lst.push_back(std::pair<int, std::string>(i, stab[i]));
		lft.push_back(ft::pair<int, std::string>(i, stab[i]));
	}

	std::map<int, std::string> m;
	m.insert(std::pair<int, std::string>(1, "dsada"));
	std::cout << "test : " << m.at(1) << std::endl;

	ft::map<int, std::string> mf;
	mf.insert(ft::pair<int, std::string>(1, "dsada"));
	std::cout << "test : " << mf.at(1) << std::endl;
	std::cout << "begin" << std::endl;

	ft::map<int, std::string> ml0;
	ft::map<int, std::string> ml(lft.begin(), lft.end());
	ft::map<int, std::string> ml2(ml.begin(), ml.end());
	ft::map<int, std::string> ml3(ml2);
	ft::map<int, std::string> ml4 = ml3;
	const ft::map<int, std::string> ml5 = ml3;

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

	std::cout << "TEST   :" << ml[5] << std::endl;
	std::cout << "TEST   :" << ml.at(5) << std::endl;
	// std::cout << "TEST   :" << ml.at(10) << std::endl;

	ml[23] = "dnksjajdak";
	ml.print();
	std::cout << "end" << std::endl;

	printTitle("ml5");
	ml5.print();
	{
		ft::map<int, std::string> tmp = ml5;
		std::map<int, std::string> tmps(lst.begin(), lst.end());

		printTitle("tmp.begin(), tmp.end()");
		tmp.erase(tmp.begin(), tmp.end());
		tmps.erase(tmps.begin(), tmps.end());
		print(tmp);
		print(tmps);
	}
	{
		ft::map<int, std::string> tmp = ml5;
		std::map<int, std::string> tmps(lst.begin(), lst.end());

		printTitle("tmp.end(), tmp.end()");
		tmp.erase(tmp.end(), tmp.end());
		tmps.erase(tmps.end(), tmps.end());
		print(tmp);
		print(tmps);
	}
	{
		ft::map<int, std::string> tmp = ml5;
		std::map<int, std::string> tmps(lst.begin(), lst.end());

		printTitle("--tmp.end(), tmp.end()"); // une faute ici voir --tmp
		std::cout << "TEST ftpair : " << *(--tmp.end()) << std::endl;
		std::cout << "TEST stdpair : " << *(--tmps.end()) << std::endl;
		
		tmp.erase(--tmp.end(), tmp.end());
		tmps.erase(--tmps.end(), tmps.end());

		print(tmp);
		print(tmps);
	}
	{
		ft::map<int, std::string> tmp = ml5;
		std::map<int, std::string> tmps(lst.begin(), lst.end());

		printTitle("++tmp.begin(), tmp.end()");
		tmp.erase(++tmp.begin(), tmp.end());
		tmps.erase(++tmps.begin(), tmps.end());
		print(tmp);
		print(tmps);
	}
	{
		ft::map<int, std::string> tmp = ml5;
		std::map<int, std::string> tmps(lst.begin(), lst.end());

		printTitle("tmp.begin(), ++tmp.begin()");
		tmp.erase(tmp.begin(), ++tmp.begin());
		// tmp.erase(tmp.begin(), ++tmp.begin());
		tmps.erase(tmps.begin(), ++tmps.begin());
		print(tmp);
		print(tmps);
	}

	std::map<int, std::string> mstd(lst.begin(), lst.end());
	for (std::map<int, std::string>::iterator it = mstd.begin() ; it != mstd.end(); it++)
	{
		std::cout << *it << std::endl;
	}
	ft::map<int, std::string> mft(lft.begin(), lft.end());
	for (ft::map<int, std::string>::iterator it = mft.begin() ; it != mft.end(); it++)
	{
		std::cout << *it << std::endl;
	}
	mstd.insert(std::pair<int, std::string>(3, "wewewdsadas"));
	for (ft::map<int, std::string>::iterator it = mft.begin() ; it != mft.end(); it++)
	{
		std::cout << *it << std::endl;
	}
	return 0;
}
