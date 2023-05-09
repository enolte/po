#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_evaluate_mult_rank3_rank5_expr_correct_extended_rank();
void test_evaluate_mult_rank3_rank5_correct_extended_rank();
void test_evaluate_mult_rank3_rank5_wrong_extended_rank();

void test_evaluate_mult()
{
  test_evaluate_mult_rank3_rank5_correct_extended_rank();
  test_evaluate_mult_rank3_rank5_wrong_extended_rank();
}

void test_evaluate_mult_rank3_rank5_expr_correct_extended_rank()
{
  po::polynomial p = po::make_constant(2.3, 3);
  po::polynomial q = po::make_constant(2.3, 5);

  assert(p.rank() == 3 && q.rank() == 5);

  {
    auto x = p*(q - 9);
    const po::scalar_type y = x(3, 5.5, 0, -3, 6);
    assert(y != y);
  }

  PO_LINE;
}




void test_evaluate_mult_rank3_rank5_correct_extended_rank()
{
  po::polynomial p = po::make_constant(2.3, 3);
  po::polynomial q = po::make_constant(2.3, 5);

  assert(p.rank() == 3 && q.rank() == 5);

  {
    auto x = p*q;
    const po::scalar_type y = x(3, 5.5, 0, -3, 6);
    assert(y != y);
  }

  {
    static_assert(po::is_extend<decltype(extend(p, 5, 2, 3, 4))>);

    const double yx = extend(p, 5, 2, 3, 4)(0, 0, 0, 0, 0);
    auto x = q * extend(p, 5, 2, 3, 4);
    const po::scalar_type y = x(3, 5.5, 0, -3, 6);
    assert(y == y);
    assert(std::fabs(y - 5.29) <= 0x1p-50);
  }

  PO_LINE;
}

void test_evaluate_mult_rank3_rank5_wrong_extended_rank()
{
  po::polynomial p = po::make_constant(-1.1, 3);
  po::polynomial q = po::make_constant(-1.1, 5);

  assert(p.rank() == 3 && q.rank() == 5);

  {
    auto x = q * extend(p, 6, 2, 3, 4);
    const po::scalar_type y = x(3, 5.5, 0, -3, 6);
    assert(y != y);
  }

  PO_LINE;
}