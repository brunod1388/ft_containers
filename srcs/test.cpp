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

	lst.push_back(std::pair<int, std::string>(7, "sept"));
	lst.push_back(std::pair<int, std::string>(10, "dix"));
	lft.push_back(ft::pair<int, std::string>(7, "sept"));
	lft.push_back(ft::pair<int, std::string>(10, "dix"));

	std::map<int, std::string> mstd(lst.begin(), lst.end());
	ft::map<int, std::string> mft(lft.begin(), lft.end());

	for (int i = -5; i < 10; i++)
	{
		std::cout << "ft::lower_bound(begin(" << i << "))  : " << *mft.lower_bound(i) << std::endl;
		std::cout << "std::lower_bound(begin(" << i << ")) : " << *mstd.lower_bound(i) << std::endl;
		std::cout << "ft::upper_bound(begin(" << i << "))  : " << *mft.upper_bound(i) << std::endl;
		std::cout << "std::upper_bound(begin(" << i << ")) : " << *mstd.upper_bound(i) << std::endl;

		std::cout << "ft::equal_range(begin(" << i << "))  : " << "(" << *mft.equal_range(i).first << ", " << *mft.equal_range(i).second << ")" << std::endl;
		std::cout << "std::equal_range(begin(" << i << ")) : " << "(" << *mstd.equal_range(i).first << ", " << *mstd.equal_range(i).second << ")" << std::endl;
		std::cout << std::endl;
	}
	std::cout << "ft::lower_bound(begin(int()))  : " << *mft.lower_bound(int()) << std::endl;
	std::cout << "std::lower_bound(begin(int())) : " << *mstd.lower_bound(int()) << std::endl;
	std::cout << std::endl;
	std::cout << "ft::upper_bound(begin(int()))  : " << *mft.upper_bound(int()) << std::endl;
	std::cout << "std::upper_bound(begin(int())) : " << *mstd.upper_bound(int()) << std::endl;
	std::cout << std::endl;
	std::cout << "ft::equal_range(begin(" << int() << "))  : " << "(" << *mft.equal_range(int()).first << ", " << *mft.equal_range(int()).second << ")" << std::endl;
	std::cout << "std::equal_range(begin(" << int() << ")) : " << "(" << *mstd.equal_range(int()).first << ", " << *mstd.equal_range(int()).second << ")" << std::endl;
	std::cout << std::endl;

	std::map<int, std::string> mstd2;
	ft::map<int, std::string> mft2;
	std::map<int, std::string>::iterator istd2 = mstd.begin();
	ft::map<int, std::string>::iterator ift2 = mft.begin();

	std::cout << "std : "<< *mstd2.insert(*mstd.begin()).first << std::endl;
	std::cout << "ft  : "<< *mft2.insert(*mft.begin()).first << std::endl;

	for (size_t i = 0; i < 10; i++)
	{
		std::cout << "std:return value (testing boolean): " << mstd2.insert(*(istd2)).second << std::endl;

		typename std::map<int, std::string>::value_type pa(istd2->first, istd2->second);
		mstd2.erase(mstd2.begin());
		std::cout << "std:return value (testing iterator, the mapped content): " << mstd2.insert(pa).first->second;

		std::cout << std::endl;

		std::cout << "ft :return value (testing boolean): " << mft2.insert(*(ift2)).second << std::endl;

		typename ft::map<int, std::string>::value_type pa2(ift2->first, ift2->second);
		mft2.erase(ift2);

		// print(mstd2);
		// print(mft2);
		std::cout << "ft :return value (testing iterator, the mapped content): " << mft2.insert(pa2).first->second;
		std::cout << std::endl;

		istd2++;
		ift2++;
	}

	
	return 0;
}
