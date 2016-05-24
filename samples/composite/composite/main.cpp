#include <cstdint>
#include <boost/optional.hpp>
#include <memory>
#include <limits>
#include <functional>

template <typename T>
struct Rect
{
	T left;
	T top;
	T width;
	T height;
};

typedef Rect<double> RectD;
typedef uint32_t RGBAColor;

using boost::optional;

class ICanvas
{
public:
	virtual void SetLineStyle(double width, RGBAColor color) = 0;
	virtual void BeginFill(RGBAColor color) = 0;
	virtual void EndFill() = 0;
	virtual void MoveTo(double x, double y) = 0;
	virtual void LineTo(double x, double y) = 0;
	virtual void DrawEllipse(double left, double top, double width, double height) = 0;
	
	virtual ~ICanvas() = 0;
};

class IDrawable
{
public:
	virtual void Draw(const ICanvas & canvas) = 0;

	virtual ~IDrawable() = default;
};

class IOutlineStyle
{
public:
	virtual optional<bool> IsEnabled()const = 0;
	virtual void Enable(bool enable) = 0;

	virtual optional<RGBAColor> GetColor()const = 0;
	virtual void SetColor(RGBAColor color) = 0;

	virtual optional<double> GetWidth()const = 0;
	virtual void SetWidth(double width) = 0;

	virtual ~IOutlineStyle() = default;
};

class IFillStyle
{
public:
	virtual optional<bool> IsEnabled()const = 0;
	virtual void Enable(bool enable) = 0;

	virtual optional<RGBAColor> GetColor()const = 0;
	virtual void SetColor(RGBAColor color) = 0;

	virtual ~IFillStyle() = default;
};

class IGroupShape;

class IShape : public IDrawable
{
public:
	virtual RectD GetFrame() = 0;
	virtual void SetFrame(const RectD & rect) = 0;

	virtual IOutlineStyle & GetOutline() = 0;
	virtual const IOutlineStyle & GetOutline()const = 0;
	
	virtual IFillStyle & GetFill() = 0;
	virtual const IFillStyle & GetFill()const = 0;

	virtual std::shared_ptr<IGroupShape> GetGroup() = 0;
	virtual std::shared_ptr<const IGroupShape> GetGroup() const = 0;

	virtual ~IShape() = default;
};

class IShapeOwner
{
public:
	virtual size_t GetShapesCount() = 0;
	virtual void InsertShape(const std::shared_ptr<IShape> & shape, size_t position = std::numeric_limits<size_t>::max()) = 0;
	virtual std::shared_ptr<IShape> GetShapeAtIndex(size_t index) = 0;
	virtual void RemoveShapeAtIndex(size_t index) = 0;

	virtual ~IShapeOwner() = default;
};

class IGroupShape : public IShape, public IShapeOwner
{
public:
	virtual void Ungroup() = 0;
	virtual ~IGroupShape() = default;
};

typedef std::function<void(ICanvas & canvas, const IShape & shape)> DrawingStrategy;

class CSimpleShape : public IShape
{
public:
	CSimpleShape(const DrawingStrategy & drawingStrategy)
	{
		(void)&drawingStrategy;
	}
};

class CGroupShape : public IGroupShape
{

};

class ISlide : public IShapeOwner
{
public:
	virtual double GetWidth()const = 0;
	virtual double GetHeight()const = 0;

	virtual ~ISlide() = default;
};

class CSlide : public ISlide
{
public:

};


int main()
{

}
