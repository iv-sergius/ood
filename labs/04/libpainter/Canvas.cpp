#include "stdafx.h"

#include "CCanvas.h"
#include <boost/format.hpp>

namespace
{
	std::map <Color, std::string> colorString = {
		{ Color::Black, "#000000" },
		{ Color::Blue, "#0000ff" },
		{ Color::Green, "#00ff00" },
		{ Color::Pink, "#ff0080" },
		{ Color::Red, "#ff0000" },
		{ Color::Yellow, "#ffff00" },
	};
}

void CCanvas::Clear()
{
	m_str = "";
}

void CCanvas::SetColor(Color color)
{
	m_color = color;
}

void CCanvas::DrawLine(const SPoint & from, const SPoint & to)
{
	std::string lineStr = (boost::format("<path style=\"fill:none;stroke:%1%\" d=\"M %2%,%3% %4%,%5%\"/>\n")
		% colorString[m_color] % from.x % from.y % to.x % to.y).str();
	std::cout << lineStr;
	m_str.append(lineStr);
}

void CCanvas::DrawEllipse(const float left, const float top, const float width, const float height)
{
	std::string ellipseStr = (boost::format("<ellipse style = \"fill:none;stroke:%1%\" cx=\"%2%\" cy=\"%3%\" rx=\"%4%\" ry=\"%5%\"/>\n")
		% colorString[m_color] % left % top % width % height).str();
	std::cout << ellipseStr;
	m_str.append(ellipseStr);
}

void CCanvas::Show(std::ostream & outStream)
{
	outStream << m_str << std::endl;
}
