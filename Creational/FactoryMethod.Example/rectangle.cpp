#include "rectangle.hpp"
#include "shape_factories.hpp"

using namespace Drawing;

static bool is_registered = 
    SingletonShapeFactory::instance()
        .register_creator(Rectangle::id, [] { return std::make_unique<Rectangle>(); });

Drawing::Rectangle::Rectangle(int x, int y, int w, int h)
    : ShapeBase{x, y}
    , width_{w}
    , height_{h}
{
}

void Drawing::Rectangle::draw() const
{
    std::cout << "Drawing rectangle at " << coord() << " with width: " << width_
              << " and height: " << height_ << std::endl;
}
