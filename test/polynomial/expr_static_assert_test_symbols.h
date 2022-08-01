#ifndef PO_EXPR_STATIC_ASSERT_TEST_SYMBOLS_H
#define PO_EXPR_STATIC_ASSERT_TEST_SYMBOLS_H

namespace static_asserts
{
  po::polynomial p{};
  po::expr_constant c{};
  const po::expr_constant cc{};
  const po::polynomial cp{};

  // For brevity below
  using P = po::polynomial;
  using C = po::expr_constant;

  using CC = const C;
  using CP = const P;
}

#endif

