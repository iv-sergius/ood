#include "stdafx.h"
#include "TestUtils.h"
#include "../libpainter/CShapeFactory.h"
#include "../libpainter/Shape.h"
#include "../libpainter/Ellipse.h"
#include "../libpainter/Rectangle.h"
#include "../libpainter/RegularPolygon.h"
#include "../libpainter/Triangle.h"

struct SParameters
{
	SPoint center;
	float horizontalRadius;
	float verticalRadius;
	SPoint leftTop;
	SPoint rightBottom;
	uint32_t vertexCount;
	float radius;
	SPoint vertex1;
	SPoint vertex2;
	SPoint vertex3;
	Color color;
};

void CheckShape(const std::unique_ptr<CShape> shapePtr, const SParameters & params)
{
	BOOST_CHECK_EQUAL(shapePtr->GetColor(), params.color);
}

void CheckShape(const std::unique_ptr<CEllipse> ellipsePtr, const SParameters & params)
{
	CheckSPoints(ellipsePtr->GetCenter(), params.center);
	CheckFloats(ellipsePtr->GetHorizontalRadius(), params.horizontalRadius);
	CheckFloats(ellipsePtr->GetVerticalRadius(), params.verticalRadius);
	BOOST_CHECK_EQUAL(ellipsePtr->GetColor(), params.color);
}

void CheckShape(const std::unique_ptr<CRectangle> rectanglePtr, const SParameters & params)
{
	CheckSPoints(rectanglePtr->GetLeftTop(), params.leftTop);
	CheckSPoints(rectanglePtr->GetRightBottom(), params.rightBottom);
	BOOST_CHECK_EQUAL(rectanglePtr->GetColor(), params.color);
}

void CheckShape(const std::unique_ptr<CRegularPolygon> regPolygonPtr, const SParameters & params)
{
	CheckSPoints(regPolygonPtr->GetCenter(), params.center);
	CheckFloats(regPolygonPtr->GetRadius(), params.radius);
	BOOST_CHECK_EQUAL(regPolygonPtr->GetVertexCount(), params.vertexCount);
	BOOST_CHECK_EQUAL(regPolygonPtr->GetColor(), params.color);
}

void CheckShape(const std::unique_ptr<CTriangle> trianglePtr, const SParameters & params)
{
	CheckSPoints(trianglePtr->GetVertex1(), params.vertex1);
	CheckSPoints(trianglePtr->GetVertex2(), params.vertex2);
	CheckSPoints(trianglePtr->GetVertex3(), params.vertex3);
	BOOST_CHECK_EQUAL(trianglePtr->GetColor(), params.color);
}

struct Shape_factory_
{
	CShapeFactory factory;
};

BOOST_FIXTURE_TEST_SUITE(Shape_factory, Shape_factory_)
	
	BOOST_AUTO_TEST_SUITE(when_construct_ellipse)
		BOOST_AUTO_TEST_CASE(get_right_parameters)
		{
			SParameters params;
			auto shape = factory.CreateShape("Ellipse 1 2  5 4  Red");
			params.center = SPoint{ 1, 2 };
			params.horizontalRadius = 5;
			params.verticalRadius = 3;
			params.color = Color::Red;
			CheckShape(std::move(shape), params);
			
			shape = factory.CreateShape("Ellipse    -3.14  2.5 \n  54.001\t\t.4  Black");
			params.center = SPoint{ -3.14f, 2.5f };
			params.horizontalRadius = 54.001f;
			params.verticalRadius = .4f;
			params.color = Color::Black;
			CheckShape(std::move(shape), params);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(when_construct_rectange)
		BOOST_AUTO_TEST_CASE(get_right_parameters)
		{
			SParameters params;
			auto shape = factory.CreateShape("Rectangle 1 2 3 4 Blue");
			params.leftTop = SPoint{ 1, 2 };
			params.rightBottom = SPoint{ 3, 4 };
			params.color = Color::Blue;
			CheckShape(std::move(shape), params);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(when_construct_regular_polygon)
		BOOST_AUTO_TEST_CASE(get_right_parameters)
		{
			SParameters params;
			auto shape = factory.CreateShape("RegularPolygon 5 4 3 2 Black");
			params.vertexCount = 5;
			params.center = SPoint{ 4, 3 };
			params.radius = 2;
			params.color = Color::Black;
			CheckShape(std::move(shape), params);
		}
	BOOST_AUTO_TEST_SUITE_END()
	
	BOOST_AUTO_TEST_SUITE(when_construct_triangle)
		BOOST_AUTO_TEST_CASE(get_right_parameters)
		{
			SParameters params;
			auto shape = factory.CreateShape("Triangle 1 2 3 4 5 6 Blue");
			params.vertex1 = SPoint{ 1, 2 };
			params.vertex2 = SPoint{ 3, 4 };
			params.vertex3 = SPoint{ 5, 6 };
			params.color = Color::Blue;
			CheckShape(std::move(shape), params);
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()


