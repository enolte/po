#ifndef PO_EXPR_STATIC_ASSERT_TEST_SYMBOLS_H
#define PO_EXPR_STATIC_ASSERT_TEST_SYMBOLS_H

namespace static_asserts
{
  po::polynomial p{};
  po::expr_constant c;
  po::scalar_type s;

  const po::polynomial cp{};
  const po::expr_constant cc;
  const po::scalar_type cs{};

  using P = po::polynomial;
  using C = po::expr_constant;
  using S = po::scalar_type;

  using CC = const C;
  using CP = const P;
  using CS = const S;
}

#endif

