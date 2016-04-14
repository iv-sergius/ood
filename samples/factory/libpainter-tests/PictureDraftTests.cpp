#include "stdafx.h"
#include "../libpainter/PictureDraft.h"
#include "../libpainter/Shape.h"

using namespace std;
struct Picture_draft_
{
	CPictureDraft draft;
};

BOOST_FIXTURE_TEST_SUITE(Picture_draft, Picture_draft_)
	BOOST_AUTO_TEST_SUITE(by_default)
		BOOST_AUTO_TEST_CASE(is_empty)
		{
			BOOST_CHECK(draft.IsEmpty());
		}
		BOOST_AUTO_TEST_CASE(has_equal_begin_and_end_iterators)
		{
			BOOST_CHECK(draft.begin() == draft.end());
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct after_adding_a_shape_ : Picture_draft_
	{
		after_adding_a_shape_()
		{
			draft.AddShape(make_unique<CShape>());
		}
	};
	BOOST_FIXTURE_TEST_SUITE(after_adding_a_shape, after_adding_a_shape_)
		BOOST_AUTO_TEST_CASE(becomes_not_empty)
		{
			BOOST_CHECK(!draft.IsEmpty());
		}
		BOOST_AUTO_TEST_CASE(has_different_begin_and_end_iterators)
		{
			BOOST_CHECK(draft.begin() != draft.end());
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()