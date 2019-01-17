// libpainter-tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../lwtask/Adapters.h"

using namespace modern_graphics_lib;
using namespace graphics_lib;

struct ModernLibRenderer
{
	std::ostringstream outString;
	CModernGraphicsRenderer renderer = CModernGraphicsRenderer(outString);
	CGraphicLibObjectAdapter adapter = CGraphicLibObjectAdapter(renderer);
};

BOOST_FIXTURE_TEST_SUITE(ModernLibAdapter, ModernLibRenderer)
	BOOST_AUTO_TEST_SUITE(draw_single_line)
		// undefined behavior
		//BOOST_AUTO_TEST_CASE(after_lineto)
		//{
		//}
		BOOST_AUTO_TEST_CASE(after_moveto_lineto)
		{
			{
				adapter.MoveTo(1, 2);
				adapter.LineTo(3, 4);
			}
			BOOST_CHECK_EQUAL(outString.str(),
				"<draw>\n"
				"  <line fromX=\"1\" fromY=\"2\" toX=\"3\" toY=\"4\"/>\n"
				"</draw>\n"
			);
}
		BOOST_AUTO_TEST_CASE(after_moveto_moveto_lineto)
		{
			{
				adapter.MoveTo(1, 2);
				adapter.MoveTo(3, 4);
				adapter.LineTo(5, 6);
			}
			BOOST_CHECK_EQUAL(outString.str(),
				"<draw>\n"
				"  <line fromX=\"1\" fromY=\"2\" toX=\"3\" toY=\"4\"/>\n"
				"</draw>\n"
			);
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE(draw_two_line)
		// undefined behavior
		//BOOST_AUTO_TEST_CASE(after_lineto_lineto)
		//{
		//}
		BOOST_AUTO_TEST_CASE(after_moveto_lineto_lineto)
		{
			{
				adapter.MoveTo(1, 2);
				adapter.LineTo(3, 4);
				adapter.LineTo(5, 6);
			}
			BOOST_CHECK_EQUAL(outString.str(),
				"<draw>\n"
				"  <line fromX=\"1\" fromY=\"2\" toX=\"3\" toY=\"4\"/>\n"
				"  <line fromX=\"3\" fromY=\"4\" toX=\"5\" toY=\"6\"/>\n"
				"</draw>\n"
			);
		}
		BOOST_AUTO_TEST_CASE(after_moveto_moveto_lineto_lineto)
		{
			{
				adapter.MoveTo(1, 2);
				adapter.MoveTo(3, 4);
				adapter.LineTo(5, 6);
				adapter.LineTo(7, 8);
			}
			BOOST_CHECK_EQUAL(outString.str(),
				"<draw>\n"
				"  <line fromX=\"3\" fromY=\"4\" toX=\"5\" toY=\"6\"/>\n"
				"  <line fromX=\"5\" fromY=\"6\" toX=\"7\" toY=\"8\"/>\n"
				"</draw>\n"
			);
		}
		BOOST_AUTO_TEST_CASE(after_moveto_lineto_moveto_lineto)
		{
			{
				adapter.MoveTo(1, 2);
				adapter.LineTo(3, 4);
				adapter.MoveTo(5, 6);
				adapter.LineTo(7, 8);
			}
			BOOST_CHECK_EQUAL(outString.str(),
				"<draw>\n"
				"  <line fromX=\"1\" fromY=\"2\" toX=\"3\" toY=\"4\"/>\n"
				"  <line fromX=\"3\" fromY=\"4\" toX=\"5\" toY=\"6\"/>\n"
				"</draw>\n"
			);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
