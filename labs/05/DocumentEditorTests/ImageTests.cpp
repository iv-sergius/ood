#include "pch.h"

#include "../DocumentEditor/CDocument.h"

BOOST_AUTO_TEST_SUITE(paragraph)

	BOOST_AUTO_TEST_SUITE(allow)
		BOOST_AUTO_TEST_CASE(construsting_from_text)
		{
			auto par = CParagraph("");
			BOOST_CHECK_EQUAL(par.GetText(), "");
			par = CParagraph("Hello");
			BOOST_CHECK_EQUAL(par.GetText(), "Hello");
		}
		BOOST_AUTO_TEST_CASE(changing_text)
		{
			auto par = CParagraph("Hello");
			BOOST_CHECK_EQUAL(par.GetText(), "Hello");
			par.SetText("Hello world!!!");
			BOOST_CHECK_EQUAL(par.GetText(), "Hello world!!!");
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

string RESOURCE_DIR = "%SolutionDir%\\resources\\";
string IMAGE_FILE = "test.png";
const int FILE_WIDHT = 30;
const int FILE_HEIGHT = 20;

BOOST_AUTO_TEST_SUITE(image)
	BOOST_AUTO_TEST_SUITE(allow)
		BOOST_AUTO_TEST_CASE(construsting_from_path)
		{
			auto im = CImage(Path(RESOURCE_DIR).append(IMAGE_FILE));
			BOOST_CHECK_EQUAL(im.GetPath(), Path(RESOURCE_DIR).append(IMAGE_FILE));
		}
		BOOST_AUTO_TEST_CASE(get_size)
		{
			auto im = CImage(Path(RESOURCE_DIR).append(IMAGE_FILE));
			BOOST_CHECK_EQUAL(im.GetWidth(), FILE_WIDHT);
			BOOST_CHECK_EQUAL(im.GetHeight(), FILE_HEIGHT);
		}
		BOOST_AUTO_TEST_CASE(change_size)
		{
			auto im = CImage(Path(RESOURCE_DIR).append(IMAGE_FILE));
			BOOST_CHECK_EQUAL(im.GetWidth(), FILE_WIDHT);
			BOOST_CHECK_EQUAL(im.GetHeight(), FILE_HEIGHT);
			im.Resize(50, 40);
			BOOST_CHECK_EQUAL(im.GetWidth(), 50);
			BOOST_CHECK_EQUAL(im.GetHeight(), 40);
		}
		BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
