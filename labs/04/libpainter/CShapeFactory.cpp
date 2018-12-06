#include "stdafx.h"

#include "CShapeFactory.h"

#include "Shape.h"
#include "Ellipse.h"
#include "Rectangle.h"
#include "RegularPolygon.h"
#include "Triangle.h"

namespace
{
	static std::map <std::string, Color> colorsMap = {
		{ "black", Color::Black },
		{ "blue", Color::Blue },
		{ "green", Color::Green },
		{ "pink", Color::Pink },
		{ "red", Color::Red },
		{ "yellow", Color::Yellow },
	};

	Color GetColor(std::istringstream & desciptionStream)
	{
		std::string colorStr;
		if (desciptionStream >> colorStr)
		{
			boost::algorithm::to_lower(colorStr);
			auto iter = colorsMap.find(colorStr);
			if (iter == colorsMap.end())
			{
				throw std::invalid_argument("Incorrect Color");
			}
			else
			{
				return iter->second;
			}
		}
		else
		{
			throw std::invalid_argument("Expected Color");
		}
	}

	std::unique_ptr<CShape> CreateEllipse(std::istringstream & desciptionStream)
	{
		float centerX, centerY, horizontalRadius, verticalRadius;
		if (!(desciptionStream >> centerX) || !(desciptionStream >> centerY) ||
			!(desciptionStream >> horizontalRadius) || !(desciptionStream >> verticalRadius))
		{
			throw std::invalid_argument("Expected a number");
		}
		auto color = GetColor(desciptionStream);
		return std::make_unique<CEllipse>(SPoint{ centerX, centerY }, horizontalRadius, verticalRadius, color);
	}

	std::unique_ptr<CShape> CreateRectangle(std::istringstream & desciptionStream)
	{
		float leftTopX, leftTopY, rightBottomX, rightBottomY;
		if (!(desciptionStream >> leftTopX) || !(desciptionStream >> leftTopY) ||
			!(desciptionStream >> rightBottomX) || !(desciptionStream >> rightBottomY))
		{
			throw std::invalid_argument("Expected a number");
		}
		auto color = GetColor(desciptionStream);
		return std::make_unique<CRectangle>(SPoint{ leftTopX, leftTopY }, SPoint{ rightBottomX, rightBottomY }, color);
	}

	std::unique_ptr<CShape> CreateRegularPolygon(std::istringstream & desciptionStream)
	{
		float centerX, centerY, radius;
		uint32_t verterxCount;
		if (!(desciptionStream >> verterxCount) || !(desciptionStream >> centerX) ||
			!(desciptionStream >> centerY) || !(desciptionStream >> radius))
		{
			throw std::invalid_argument("Expected a number");
		}
		auto color = GetColor(desciptionStream);
		return std::make_unique<CRegularPolygon>(verterxCount, SPoint{ centerX, centerY }, radius, color);
	}

	std::unique_ptr<CShape> CreateTriangle(std::istringstream & desciptionStream)
	{
		float vertex1X, vertex1Y, vertex2X, vertex2Y, vertex3X, vertex3Y;
		if (!(desciptionStream >> vertex1X) || !(desciptionStream >> vertex1Y) ||
			!(desciptionStream >> vertex2X) || !(desciptionStream >> vertex2Y) ||
			!(desciptionStream >> vertex3X) || !(desciptionStream >> vertex3Y))
		{
			throw std::invalid_argument("Expected a number");
		}
		auto color = GetColor(desciptionStream);
		return std::make_unique<CTriangle>(SPoint{ vertex1X, vertex1Y }, SPoint{ vertex2X, vertex2Y }, SPoint{ vertex3X, vertex3Y }, color);
	}

	using ShapeCreator = std::function < std::unique_ptr<CShape>(std::istringstream &) > ;

	ShapeCreator tmp = CreateTriangle;

	static std::map <std::string, ShapeCreator> creatorsMap = {
		{ "ellipse", CreateEllipse },
		{ "rectangle", CreateRectangle },
		{ "regularpolygon", CreateRegularPolygon },
		{ "triangle", CreateTriangle },
	};
}

std::unique_ptr<CShape> CShapeFactory::CreateShape(const std::string & description)
{
	auto descriptionStream = std::istringstream(description);
	std::string shapeName;
	if (!(descriptionStream >> shapeName))
	{
		throw std::invalid_argument("Shape decription must start with name of shape");
	}
	boost::algorithm::to_lower(shapeName);
	auto iter = creatorsMap.find(shapeName);
	if (iter != creatorsMap.end())
	{
		return iter->second(descriptionStream);
	}
	else
	{
		throw std::invalid_argument("Unknown name of shape");
	}
}
