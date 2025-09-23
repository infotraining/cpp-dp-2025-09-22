#include "shape_group.hpp"
#include "shape_factories.hpp"
#include <algorithm>

using namespace std;
using namespace Drawing;

namespace 
{
    bool is_registered = 
        SingletonShapeFactory::instance().register_creator(ShapeGroup::id, []{
            return make_unique<ShapeGroup>();
        });       
}
