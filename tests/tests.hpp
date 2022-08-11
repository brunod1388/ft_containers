/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunodeoliveira <brunodeoliveira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 01:33:32 by brunodeoliv       #+#    #+#             */
/*   Updated: 2022/08/11 01:39:18 by brunodeoliv      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_HPP
# define TESTS_HPP

#define OK			"\U0001F91F"
#define NOTOK		"\U0001F44E"

#define	NOFLAG		0
#define	SIZE		1
#define	CAPACITY	2
#define	DATA		4
#define	FRONT		8
#define	BACK		16
#define	BEGIN		32
#define	END			64
#define	ENDMIN1		128
#define	ALL			1023
#define MAX_RAM 	4294967296

#define STR_RESET   "\033[0m"
#define STR_BLACK   "\033[30m"      /* Black */
#define STR_RED     "\033[31m"      /* Red */
#define STR_GREEN   "\033[32m"      /* Green */
#define STR_YELLOW  "\033[33m"      /* Yellow */
#define STR_BLUE    "\033[34m"      /* Blue */
#define STR_MAGENTA "\033[35m"      /* Magenta */
#define STR_CYAN    "\033[36m"      /* Cyan */
#define STR_WHITE   "\033[37m"      /* White */
#define STR_BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define STR_BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define STR_BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define STR_BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define STR_BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define STR_BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define STR_BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define STR_BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

#include <string>
#include <iostream>

std::string
centered( std::string const& original, size_t targetSize )
{
    size_t padding = targetSize - original.length();
    if (padding > 0)
        return std::string( padding / 2, ' ' )  + original + std::string( padding - (padding / 2), ' ' );
    return original;
}

void printTitle(std::string title, std::string color = STR_MAGENTA, int height = 0)
{
	std::cout << color;
	std::cout << "==================================================================" << std::endl;
	for (int i = 0; i < height; i++)
		std::cout << "===                                                            ===" << std::endl;
	std::cout << "===" << centered(title, 60) << "===" <<std::endl;
	for (int i = 0; i < height; i++)
		std::cout << "===                                                            ===" << std::endl;
	std::cout << "==================================================================";
	std::cout << STR_RESET << std::endl;
}

#endif