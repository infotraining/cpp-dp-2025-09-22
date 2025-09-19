#include <iostream>

#include "src/ast.hpp"
#include "src/visitors.hpp"

using namespace std;

int main()
{
    using namespace AST::helpers;

    auto expr = add(integer(3), multiply(integer(2), integer(5)));

    ExprEvalVisitor evaluator;
    expr->accept(evaluator);

    // TODO - uncomment code
    
    // PrintingVisitor printer;
    // expr->accept(printer);

    // cout << printer.str() << " = " << evaluator.result() << std::endl;
}
