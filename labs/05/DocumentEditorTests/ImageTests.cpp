#include "pch.h"

#include "../DocumentEditor/CDocument.h"

BOOST_AUTO_TEST_SUITE(paragraph)

	BOOST_AUTO_TEST_SUITE(can_be)
		BOOST_AUTO_TEST_CASE(construsted_with_right_text)
		{
			auto par = CParagraph("");
			BOOST_CHECK_EQUAL(par.GetText(), "");
			par = CParagraph("Hello");
			BOOST_CHECK_EQUAL(par.GetText(), "Hello");
		}
		BOOST_AUTO_TEST_CASE(changed)
		{
			auto par = CParagraph("Hello");
			BOOST_CHECK_EQUAL(par.GetText(), "Hello");
			par.SetText("Hello world!!!");
			BOOST_CHECK_EQUAL(par.GetText(), "Hello world!!!");
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
