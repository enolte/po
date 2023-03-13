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

    struct Y
    {
      using expr1 = double;
      using expr2 = float;
    };

    struct Z
    {
      struct {} expr1;
      struct {} expr2;
    };

    struct Z2
    {
      void* expr1;
      float expr2;
    };

    struct Z3
    {
      void* expr1;
      float expr2;

      void operator()(...);
    };

    struct Z4
    {
      void* t1;
      float t2;

      void operator()(...);
    };

    struct α
    {
      Y expr2;
      Z expr1;

      template<typename... T>
      double operator()(T...);
    };

    static_assert(!po::is_binary_expression<X>);
    static_assert(!po::is_binary_expression<Y>);
    static_assert(po::is_binary_expression<Z>);
    static_assert(po::is_binary_expression<Z2>);
    static_assert(po::is_binary_expression<Z3>);
    static_assert(!po::is_binary_expression<Z4>);
    // static_assert(po::is_binary_expression<α>);
  }
}

