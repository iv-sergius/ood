#include "stdafx.h"
#include "TestUtils.h"
#include "../libpainter/CShapeFactory.h"
#include "../libpainter/Shape.h"
#include "../libpainter/Ellipse.h"
#include "../libpainter/Rectangle.h"
#include "../libpainter/RegularPolygon.h"
#include "../libpainter/Triangle.h"

#include <iostream>

struct SEllipseParameters
{
	SPoint center;
	float horizontalRadius;
	float verticalRadius;
	Color color;
};
void CheckEllipse(const CEllipse &ellipsePtr, const SEllipseParameters & params)
{
	CheckSPoints(ellipsePtr.GetCenter(), params.center);
	CheckFloats(ellipsePtr.GetHorizontalRadius(), params.horizontalRadius);
	CheckFloats(ellipsePtr.GetVerticalRadius(), params.verticalRadius);
	BOOST_CHECK_EQUAL(ellipsePtr.GetColor(), params.color);
}

struct SRectangleParameters
{
	SPoint leftTop;
	SPoint rightBottom;
	Color color;
};
void CheckRectangle(const CRectangle & rectanglePtr, const SRectangleParameters & params)
{
	CheckSPoints(rectanglePtr.GetLeftTop(), params.leftTop);
	CheckSPoints(rectanglePtr.GetRightBottom(), params.rightBottom);
	BOOST_CHECK_EQUAL(rectanglePtr.GetColor(), params.color);
}

struct SRegularPolygonParameters
{
	uint32_t vertexCount;
	SPoint center;
	float radius;
	Color color;
};
void CheckRegularPolygon(const CRegularPolygon & regPolygonPtr, const SRegularPolygonParameters & params)
{
	CheckSPoints(regPolygonPtr.GetCenter(), params.center);
	CheckFloats(regPolygonPtr.GetRadius(), params.radius);
	BOOST_CHECK_EQUAL(regPolygonPtr.GetVertexCount(), params.vertexCount);
	BOOST_CHECK_EQUAL(regPolygonPtr.GetColor(), params.color);
}

struct STriangleParameters
{
	SPoint vertex1;
	SPoint vertex2;
	SPoint vertex3;
	Color color;
};
void CheckTriangle(const CTriangle & trianglePtr, const STriangleParameters & params)
{
	CheckSPoints(trianglePtr.GetVertex1(), params.vertex1);
	CheckSPoints(trianglePtr.GetVertex2(), params.vertex2);
	CheckSPoints(trianglePtr.GetVertex3(), params.vertex3);
	BOOST_CHECK_EQUAL(trianglePtr.GetColor(), params.color);
}

struct Shape_factory_
{
	CShapeFactory factory;
};

BOOST_FIXTURE_TEST_SUITE(Shape_factory, Shape_factory_)
	BOOST_AUTO_TEST_SUITE(when_construct_any_shape)
		BOOST_AUTO_TEST_SUITE(throw_on)
			BOOST_AUTO_TEST_CASE(invalid_shape_name)
			{
				BOOST_CHECK_NO_THROW(
					auto shape = factory.CreateShape("Ellipse 1 2  5 4  Red")
				);
				BOOST_CHECK_THROW(
					auto shape = factory.CreateShape("Elipse 1 2  5 4  Red"),
					std::invalid_argument
				);
			}
			BOOST_AUTO_TEST_CASE(invalid_color_name)
			{
				BOOST_CHECK_NO_THROW(
					auto shape = factory.CreateShape("Ellipse 1 2  5 4  Red")
				);
				BOOST_CHECK_THROW(
					auto shape = factory.CreateShape("Ellipse 1 2  5 4  Rad"),
					std::invalid_argument
				);
				BOOST_CHECK_THROW(
					auto shape = factory.CreateShape("Ellipse 1 2  5 4  Read"),
					std::invalid_argument
				);
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(when_construct_ellipse)
		BOOST_AUTO_TEST_CASE(return_correct_figure)
		{
			SEllipseParameters params;
			auto shape = factory.CreateShape("Ellipse 1 2  5 4  Red");
			auto ellipse = dynamic_cast<CEllipse&> (*shape);
			params.center = SPoint{ 1, 2 };
			params.horizontalRadius = 5;
			params.verticalRadius = 4;
			params.color = Color::Red;
			CheckEllipse(ellipse, params);
			
			shape = factory.CreateShape("Ellipse    -3.14  2.5 \n  54.001\t\t.4  Black");
			ellipse = dynamic_cast<CEllipse&> (*shape);
			params.center = SPoint{ -3.14f, 2.5f };
			params.horizontalRadius = 54.001f;
			params.verticalRadius = .4f;
			params.color = Color::Black;
			CheckEllipse(ellipse, params);
		}
		BOOST_AUTO_TEST_SUITE(throw_on)
			BOOST_AUTO_TEST_CASE(color_is_missed)
			{
				BOOST_CHECK_THROW(
					auto shape = factory.CreateShape("Ellipse 1 2  3 4 "),
					std::invalid_argument
				);
			}
			BOOST_AUTO_TEST_CASE(char_instead_of_number)
			{
				BOOST_CHECK_THROW(
					auto shape = factory.CreateShape("Ellipse a 2  3 4  Red"),
					std::invalid_argument
				);
				BOOST_CHECK_THROW(
					auto shape = factory.CreateShape("Ellipse 1 b  3 4  Red"),
					std::invalid_argument
				);
				BOOST_CHECK_THROW(
					auto shape = factory.CreateShape("Ellipse 1 2  c 4  Red"),
					std::invalid_argument
				);
				BOOST_CHECK_THROW(
					auto shape = factory.CreateShape("Ellipse 1 2  3 d  Red"),
					std::invalid_argument
				);
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(when_construct_rectange)
		BOOST_AUTO_TEST_CASE(return_correct_figure)
		{
			SRectangleParameters params;
			auto shape = factory.CreateShape("Rectangle 1 4 3 2 Blue");
			auto rectange = dynamic_cast<CRectangle&> (*shape);
			params.leftTop = SPoint{ 1, 2 };
			params.rightBottom = SPoint{ 3, 4 };
			params.color = Color::Blue;
			CheckRectangle(rectange, params);
		}
		BOOST_AUTO_TEST_SUITE(throw_on)
			BOOST_AUTO_TEST_CASE(color_is_missed)
			{
				BOOST_CHECK_THROW(
					auto shape = factory.CreateShape("Rectangle 1 2 3 4"),
					std::invalid_argument
				);
			}
			BOOST_AUTO_TEST_CASE(char_instead_of_number)
			{
				BOOST_CHECK_THROW(
					auto shape = factory.CreateShape("Rectangle a 2 3 4 Blue"),
					std::invalid_argument
				);
				BOOST_CHECK_THROW(
					auto shape = factory.CreateShape("Rectangle 1 b 3 4 Blue"),
					std::invalid_argument
				);
				BOOST_CHECK_THROW(
					auto shape = factory.CreateShape("Rectangle 1 2 c 4 Blue"),
					std::invalid_argument
				);
				BOOST_CHECK_THROW(
					auto shape = factory.CreateShape("Rectangle 1 2 3 d Blue"),
					std::invalid_argument
				);
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(when_construct_regular_polygon)
		BOOST_AUTO_TEST_CASE(return_correct_figure)
		{
			SRegularPolygonParameters params;
			auto shape = factory.CreateShape("RegularPolygon 5 4 3 2 Black");
			auto regularPolygon = dynamic_cast<CRegularPolygon&> (*shape);
			params.vertexCount = 5;
			params.center = SPoint{ 4, 3 };
			params.radius = 2;
			params.color = Color::Black;
			CheckRegularPolygon(regularPolygon, params);
		}
		BOOST_AUTO_TEST_SUITE(throw_on)
			BOOST_AUTO_TEST_CASE(color_is_missed)
			{
				BOOST_CHECK_THROW(
					auto shape = factory.CreateShape("RegularPolygon 5 4 3 2"),
					std::invalid_argument
				);
			}
			BOOST_AUTO_TEST_CASE(char_instead_of_number)
			{
				BOOST_CHECK_THROW(
					auto shape = factory.CreateShape("RegularPolygon a 4 3 2 Black"),
					std::invalid_argument
				);
				BOOST_CHECK_THROW(
					auto shape = factory.CreateShape("RegularPolygon 5 b 3 2 Black"),
					std::invalid_argument
				);
				BOOST_CHECK_THROW(
					auto shape = factory.CreateShape("RegularPolygon 5 4 c 2 Black"),
					std::invalid_argument
				);
				BOOST_CHECK_THROW(
					auto shape = factory.CreateShape("RegularPolygon 5 4 3 d Black"),
					std::invalid_argument
				);
			}
			BOOST_AUTO_TEST_CASE(vertex_count_is_not_integer)
			{
				BOOST_CHECK_THROW(
					auto shape = factory.CreateShape("RegularPolygon 5.0 4 3 2 Black"),
					std::invalid_argument
				);
				BOOST_CHECK_THROW(
					auto shape = factory.CreateShape("RegularPolygon .3 4 3 2 Black"),
					std::invalid_argument
				);
			}
			BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()
	
	BOOST_AUTO_TEST_SUITE(when_construct_triangle)
		BOOST_AUTO_TEST_CASE(return_correct_figure)
		{
			STriangleParameters params;
			auto shape = factory.CreateShape("Triangle 1 2 3 4 5 6 Blue");
			auto triangle = dynamic_cast<CTriangle&> (*shape);
			params.vertex1 = SPoint{ 1, 2 };
			params.vertex2 = SPoint{ 3, 4 };
			params.vertex3 = SPoint{ 5, 6 };
			params.color = Color::Blue;
			CheckTriangle(triangle, params);
		}
		BOOST_AUTO_TEST_SUITE(throw_on)
			BOOST_AUTO_TEST_CASE(color_is_missed)
			{
				BOOST_CHECK_THROW(
					auto shape = factory.CreateShape("Triangle 1 2 3 4 5 6"),
					std::invalid_argument
				);
			}
			BOOST_AUTO_TEST_CASE(char_instead_of_number)
			{
				BOOST_CHECK_THROW(
					auto shape = factory.CreateShape("Triangle a 2 3 4 5 6 Blue"),
					std::invalid_argument
				);
				BOOST_CHECK_THROW(
					auto shape = factory.CreateShape("Triangle 1 b 3 4 5 6 Blue"),
					std::invalid_argument
				);
				BOOST_CHECK_THROW(
					auto shape = factory.CreateShape("Triangle 1 2 c 4 5 6 Blue"),
					std::invalid_argument
				);
				BOOST_CHECK_THROW(
					auto shape = factory.CreateShape("Triangle 1 2 3 d 5 6 Blue"),
					std::invalid_argument
				);
				BOOST_CHECK_THROW(
					auto shape = factory.CreateShape("Triangle 1 2 3 4 e 6 Blue"),
					std::invalid_argument
				);
				BOOST_CHECK_THROW(
					auto shape = factory.CreateShape("Triangle 1 2 3 4 5 f Blue"),
					std::invalid_argument
				);
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()


