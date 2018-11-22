#include "stdafx.h"
#include "TestUtils.h"

void CheckFloats(const float f1, const float f2)
{
	BOOST_CHECK_CLOSE(f1, f2, PRECISION);
}

void CheckSPoints(const SPoint & point1, const SPoint & point2)
{
	BOOST_CHECK_CLOSE(point1.x, point2.x, PRECISION);
	BOOST_CHECK_CLOSE(point1.y, point2.y, PRECISION);
}