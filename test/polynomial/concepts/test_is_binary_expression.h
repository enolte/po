#include "../../../ops/is_binary_expression.h"


void test_is_binary_expression()
{
  PO_LINE;
}

namespace po_test
{
  namespace is_binary_expression_test
  {
    struct X
    {

    };

    static_assert(!po::is_binary_expression<X>);

    struct Y
    {
      using expr1 = double;
      using expr2 = float;
    };

    static_assert(!po::is_binary_expression<Y>);

    struct Z1
    {
      struct expr1 {};
      struct expr2 {};
    };

    static_assert(!po::is_binary_expression<Z1>);

    struct Z3
    {
      void* expr1;
      float t2;
    };

    static_assert(!po::is_binary_expression<Z3>);

    struct Z
    {
      struct {} expr1;
      struct {} expr2;
    };

    static_assert(po::is_binary_expression<Z>);

    struct Z2
    {
      void* expr1;
      float expr2;
    };

    static_assert(po::is_binary_expression<Z2>);

    struct α
    {
      Y expr2;
      Z expr1;
    };

    static_assert(po::is_binary_expression<α>);
  }
}

