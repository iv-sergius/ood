#include "stdafx.h"
#include "../libpainter/Shape.h"
#include "../libpainter/Elipse.h"
#include "../libpainter/Rectangle.h"
#include "../libpainter/RegularPolygon.h"
#include "../libpainter/Triangle.h"

const double PRECISION = 1e-5;

void CheckFloats(const float f1, const float f2)
{
	BOOST_CHECK_CLOSE(f1, f2, PRECISION);
}

void CheckSPoints(const SPoint & point1, const SPoint & point2)
{
	BOOST_CHECK_CLOSE(point1.x, point2.x, PRECISION);
	BOOST_CHECK_CLOSE(point1.y, point2.y, PRECISION);
}

BOOST_AUTO_TEST_SUITE(Shape)
	BOOST_AUTO_TEST_CASE(get_rigth_color)
	{
		CShape shape(Color::Red);
		BOOST_TEST(shape.GetColor() == Color::Red);
		shape = CShape(Color::Pink);
		BOOST_TEST(shape.GetColor() == Color::Pink);
	}
BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(CShape_inheritor)

	BOOST_AUTO_TEST_SUITE(Elipse)

		BOOST_AUTO_TEST_SUITE(constructor_throw)
			BOOST_AUTO_TEST_CASE(on_negative_horizontal_raidus)
			{
				BOOST_CHECK_THROW(CElipse(SPoint(), -1.f, 1.f, Color()), std::invalid_argument);
			}
			BOOST_AUTO_TEST_CASE(on_negative_vertical_raidus)
			{
				BOOST_CHECK_THROW(CElipse(SPoint(), 1.f, -1.f, Color()), std::invalid_argument);
			}
		BOOST_AUTO_TEST_SUITE_END()

		auto el = CElipse(SPoint{ 1, -2 }, 2.f, 3.f, Color());
		BOOST_AUTO_TEST_CASE(get_rigth_Center)
		{
			CheckSPoints(el.GetCenter(), SPoint{ 1, -2 });
		}
		BOOST_AUTO_TEST_CASE(get_rigth_HorizontalRadius)
		{
			CheckFloats(el.GetHorizontalRadius(), 2.f);
		}
		BOOST_AUTO_TEST_CASE(get_rigth_VerticalRadius)
		{
			CheckFloats(el.GetVerticalRadius(), 3.f);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Rectange)
		auto rec = CRectangle(SPoint{ 1, 2 }, SPoint{ -3, -4 }, Color());
		BOOST_AUTO_TEST_CASE(get_rigth_LeftTop)
		{
			CheckSPoints(rec.GetLeftTop(), SPoint{ -3, 2 });
		}
		BOOST_AUTO_TEST_CASE(get_rigth_RightBottom)
		{
			CheckSPoints(rec.GetRightBottom(), SPoint{ 1, -4 });
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(RegularPolygon)
		
		BOOST_AUTO_TEST_SUITE(constructor_throw)
			BOOST_AUTO_TEST_CASE(on_VertexCount_less_than_3)
			{
				BOOST_CHECK_THROW(CRegularPolygon(0, SPoint(), 1.f, Color()), std::invalid_argument);
				BOOST_CHECK_THROW(CRegularPolygon(2, SPoint(), 1.f, Color()), std::invalid_argument);
				BOOST_CHECK_NO_THROW(CRegularPolygon(3, SPoint(), 1.f, Color()));
			}
			BOOST_AUTO_TEST_CASE(on_negative_raidus)
			{
				BOOST_CHECK_THROW(CRegularPolygon(3, SPoint(), -1.f, Color()), std::invalid_argument);
			}
		BOOST_AUTO_TEST_SUITE_END()
		
		auto regPolygon = CRegularPolygon(4, SPoint{ -3.f, 1.f }, 2.f, Color());
		BOOST_AUTO_TEST_CASE(get_rigth_VertexCount)
		{
			BOOST_CHECK(regPolygon.GetVertexCount() == 4);
		}
		BOOST_AUTO_TEST_CASE(get_rigth_Center)
		{
			CheckSPoints(regPolygon.GetCenter(), SPoint{ -3.f, 1.f });
		}
		BOOST_AUTO_TEST_CASE(get_rigth_Radius)
		{
			CheckFloats(regPolygon.GetRadius(), 2.f);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Triangle)
		BOOST_AUTO_TEST_CASE(get_rigth_vertexes)
		{
			auto triangle = CTriangle(SPoint{ 1.f, -2.f }, SPoint{ -3.f, 5.f }, SPoint{ -4.f, -.1f }, Color());
			CheckSPoints(triangle.GetVertex1(), SPoint{ 1.f, -2.f });
			CheckSPoints(triangle.GetVertex2(), SPoint{ -3.f, 5.f });
			CheckSPoints(triangle.GetVertex3(), SPoint{ -4.f, -.1f });
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
