#include "stdafx.h"
#include "../libpainter/Designer.h"
#include "../libpainter/PictureDraft.h"

using namespace std;

struct Designer_
{
	CDesigner designer;
};

BOOST_FIXTURE_TEST_SUITE(Designer, Designer_)
	BOOST_AUTO_TEST_SUITE(when_creating_draft)
		BOOST_AUTO_TEST_CASE(returns_empty_draft_when_input_is_empty)
		{
			istringstream input;
			auto draft = designer.CreateDraft(input);
			BOOST_CHECK(draft.IsEmpty());
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()