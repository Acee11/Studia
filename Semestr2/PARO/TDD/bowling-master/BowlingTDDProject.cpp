// BowlingTDDProject.cpp : Defines the entry point for the console application.
//
#define BOOST_TEST_MAIN
#if !defined( WIN32 )
    #define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include "BowlingGame.h"

namespace
{
	BOOST_AUTO_TEST_SUITE(BowlingGameTests)

	BOOST_AUTO_TEST_CASE(testcase1)
	{
		int x = 10;
		int y = 0;
	    BOOST_CHECK( 0 == x/y ); // proste porównanie
	}

	BOOST_AUTO_TEST_CASE(testcase2)
	{
		int F = 250;
	    int m = 25;
	    int a = 10; // przyśpieszenie
	    BOOST_CHECK( F == m * a ); // proste porównanie
	}

	BOOST_AUTO_TEST_SUITE_END()
}

