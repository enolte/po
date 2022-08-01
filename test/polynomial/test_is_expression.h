#include "../../ops/is_expression.h"


void test_is_expression()
{
  PO_LINE;
}



namespace po_test
{
  namespace is_expression_test
  {
    struct W
    {

    };

    struct X1
    {
      using expr1 = void;
    };

    struct X2
    {
      void* expr1;
    };

    struct X3
    {
      void* expr1;
      void* operator()();
    };

    struct X4
    {
      float expr;
      void operator()(float, char*, long);
    };

    struct X5
    {
      float expr1;
      void operator()(float, char*, long);
    };

    struct Y
    {
      float expr1, expr2;
      void operator()(float, float);
    };

    struct Y2
    {
      float expr1, expr2;
      void operator()(void);
    };

    struct Z
    {
      int expr1;
      void* expr2;
      template<typename... T>
      double operator()(T...);
    };

    struct Z2
    {
      int expr1;
      void* expr2;
      double operator()(...);
    };

    struct α
    {
      W expr2;
      Z expr1;

      template<typename... T>
      double operator()(T...);
    };

    static_assert(!po::is_expression<W>);
    static_assert(!po::is_expression<X1>);
    static_assert(po::is_expression<X2>);
    static_assert(po::is_expression<X3>);
    static_assert(!po::is_expression<X4>);
    static_assert(po::is_expression<X5>);
    static_assert(po::is_expression<Y>);
    static_assert(po::is_expression<Y2>);
    static_assert(po::is_expression<Z>);
    static_assert(po::is_expression<Z2>);
    static_assert(po::is_expression<α>);
  }
}

