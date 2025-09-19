#include "point.hpp"

static constexpr const char opening_bracket = '[';
static constexpr const char closing_bracket = ']';
static constexpr const char comma = ',';

std::ostream& operator<<(std::ostream& out, const Drawing::Point& pt)
{
    out << opening_bracket << pt.x << comma << pt.y << closing_bracket;
    return out;
}

std::istream& operator>>(std::istream& in, Drawing::Point& pt)
{
    char start, separator, end;
    int x, y;

    if (in >> start && start != opening_bracket)
    {
        in.unget();
        in.clear(std::ios_base::failbit);
        return in;
    }

    in >> x >> separator >> y >> end;

    if (!in || (separator != comma) || (end != closing_bracket))
        throw std::runtime_error("Stream reading error");

    pt.x = x;
    pt.y = y;

    return in;
}
