#include "stdafx.h"
#include "TestUtils.h"
#include "../libpainter/CShapeFactory.h"
#include "../libpainter/Shape.h"
#include "../libpainter/Ellipse.h"
#include "../libpainter/Rectangle.h"
#include "../libpainter/RegularPolygon.h"
#include "../libpainter/Triangle.h"

struct Shape_factory_
{
	CShapeFactory factory;
};

BOOST_FIXTURE_TEST_SUITE(Shape_factory, Shape_factory_)



BOOST_AUTO_TEST_SUITE_END()


