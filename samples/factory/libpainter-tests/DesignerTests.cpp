#include "stdafx.h"
#include "../libpainter/Designer.h"
#include "../libpainter/PictureDraft.h"
#include "../libpainter/IShapeFactory.h"

using namespace std;

struct MockShapeFactory : IShapeFactory
{
	vector<string> shapeDescriptions;
	// Inherited via IShapeFactory
	unique_ptr<CShape> CreateShape(const std::string & description) override
	{
		// «апротоколировали описание созданной фигуры
		shapeDescriptions.push_back(description);
		return make_unique<CShape>();
	}
};

struct Designer_
{
	MockShapeFactory factory;
	CDesigner designer = CDesigner(factory);
};

BOOST_FIXTURE_TEST_SUITE(Designer, Designer_)
	BOOST_AUTO_TEST_SUITE(when_creating_draft)
		BOOST_AUTO_TEST_CASE(returns_empty_draft_when_input_is_empty)
		{
			istringstream input;
			auto draft = designer.CreateDraft(input);
			BOOST_CHECK(draft.IsEmpty());
			BOOST_CHECK(input.eof());
		}
		BOOST_AUTO_TEST_CASE(passes_each_line_from_input_to_shape_factory)
		{
			vector<string> expectedShapeDescriptions = {
				"square", "circle", "triangle"
			};
			stringstream strm;
			boost::copy(expectedShapeDescriptions, ostream_iterator<string>(strm, "\n"));
			designer.CreateDraft(strm);
			BOOST_CHECK(factory.shapeDescriptions == expectedShapeDescriptions);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()