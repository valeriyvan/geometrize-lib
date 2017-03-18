#include "shapetypes.h"

namespace geometrize
{

namespace shapes
{

const std::array<ShapeTypes, static_cast<std::size_t>(ShapeTypes::SHAPE_COUNT)> allShapes =
{
    ShapeTypes::RECTANGLE,
    ShapeTypes::ROTATED_RECTANGLE,
    ShapeTypes::TRIANGLE,
    ShapeTypes::ELLIPSE,
    ShapeTypes::ROTATED_ELLIPSE,
    ShapeTypes::CIRCLE,
    ShapeTypes::LINE,
    ShapeTypes::SPLINE,
    ShapeTypes::POLYLINE
};

const std::vector<std::pair<ShapeTypes, std::string>> shapeTypeNames =
{
    { ShapeTypes::RECTANGLE, "rectangle" },
    { ShapeTypes::ROTATED_RECTANGLE, "rotated_rectangle" },
    { ShapeTypes::TRIANGLE, "triangle" },
    { ShapeTypes::ELLIPSE, "ellipse" },
    { ShapeTypes::ROTATED_ELLIPSE, "rotated_ellipse" },
    { ShapeTypes::CIRCLE, "circle" },
    { ShapeTypes::LINE, "line" },
    { ShapeTypes::SPLINE, "spline" },
    { ShapeTypes::POLYLINE, "polyline" }
};

}

}