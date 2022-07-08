#include "../../ops/is_expression.h"

void test_is_unary_expression()
{
  PO_LINE;
}

namespace po_test
{
  namespace is_unary_expression_test
  {
    struct W
    {

    };

    struct W2
    {
      using E1 = void;
    };

    struct W3
    {
      void* expr1;
    };

    struct W4
    {
      void* expr1;
      void operator()(...);
    };

    template<typename T>
    struct V
    {
      T t;
      void operator()(...);
    };

    template<typename T>
    struct V2
    {
      T t;
      void operator()(...);
    };

    template<typename T>
    struct U
    {
      T expr1;
      void operator()(...);
    };

    template<typename T>
    struct U2
    {
      T expr1;
      void operator()(...);
    };

    static_assert(!po::is_unary_expression<W>);
    static_assert(!po::is_unary_expression<W2>);
    static_assert(!po::is_unary_expression<W3>);
    static_assert(po::is_unary_expression<W4>);
    static_assert(!po::is_unary_expression<V<int>>);
    static_assert(!po::is_unary_expression<V2<int>>);
    static_assert(!po::is_unary_expression<V<V<int>>>);
    static_assert(!po::is_unary_expression<V<V2<int>>>);
    static_assert(!po::is_unary_expression<V2<V<int>>>);

    static_assert(po::is_unary_expression<U<int>>);

    static_assert(po::is_unary_expression<U<U<int>>>);
    static_assert(po::is_unary_expression<U<U2<int>>>);
    static_assert(po::is_unary_expression<U2<U<int>>>);

    static_assert(po::is_unary_expression<U2<U<U<int>>>>);
    static_assert(po::is_unary_expression<U<U2<U<int>>>>);
    static_assert(po::is_unary_expression<U<U<U2<int>>>>);
    static_assert(po::is_unary_expression<U2<U2<U<int>>>>);
    static_assert(po::is_unary_expression<U2<U<U2<int>>>>);
    static_assert(po::is_unary_expression<U<U2<U2<int>>>>);
  }
}

