#ifndef CIRCLEREADERWRITER_H
#define CIRCLEREADERWRITER_H

#include "../circle.hpp"
#include "shape_reader_writer.hpp"

namespace Drawing
{
    namespace IO
    {
        class CircleReaderWriter : public ShapeReaderWriter
        {
        public:
            void read(Shape& shp, std::istream& in) override
            {
                Drawing::Circle& circle = static_cast<Drawing::Circle&>(shp);

                Point pt;
                int r;

                in >> pt >> r;

                circle.set_coord(pt);
                circle.set_radius(r);
            }

            void write(const Shape& shp, std::ostream& out) override
            {
                const Circle& circle = static_cast<const Circle&>(shp);

                out << Circle::id << " " << circle.coord() << " " << circle.radius() << std::endl;
            }
        };
    } // namespace IO
} // namespace Drawing

#endif // CIRCLEREADERWRITER_H
