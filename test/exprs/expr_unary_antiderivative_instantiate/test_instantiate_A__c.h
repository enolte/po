#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_instantiate_A__c()
{
  // po::expr_constant
  {
    const auto x = po::antiderivative(po::expr_constant{6.7}, 5);

    static_assert((std::same_as<decltype(x), const po::expr_antiderivative<po::expr_constant>>));
    static_assert((std::same_as<decltype(x.expr1), const po::expr_constant>));
    static_assert((std::same_as<decltype(x.expr1.expr1), const po::scalar_type>));

    assert(x.place == 5);
    assert(x.expr1.expr1 == 6.7);

    po::polynomial p = po::instantiate(x);

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {6.7, {0, 0, 0, 0, 0, 1}},
      }),
      p);

    assert(p.rank() == 6);
    assert(compare::equal(p.degrees(), {0, 0, 0, 0, 0, 1}));
    assert(p.degree() == 1);

    assert(p.constant() == 0.);
    assert(p.coefficient(0, 0, 0, 0, 0, 1) == 6.7);

    PO_LINE;
  }

  // scalar field member rvalue
  {
    const auto x = po::antiderivative(7.2, 0);

    static_assert((std::same_as<decltype(x), const po::expr_antiderivative<po::expr_constant>>));
    static_assert((std::same_as<decltype(x.expr1), const po::expr_constant>));
    static_assert((std::same_as<decltype(x.expr1.expr1), const po::scalar_type>));

    assert(x.expr1.expr1 == 7.2);
    assert(x.expr1 == po::expr_constant{7.2});
    assert(x.place == 0);

    po::polynomial p = instantiate(x);

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {7.2, {1}},
      }),
      p);

    assert(p.rank() == 1);
    assert(compare::equal(p.degrees(), {1}));
    assert(p.degree() == 1);

    assert(p.constant() == 0.);
    assert(p.coefficient(1) == 7.2);

    PO_LINE;
  }


  // non-field member rvalue
  {
    const auto x = po::antiderivative(7.2f, 0);

    static_assert((std::same_as<decltype(x), const po::expr_antiderivative<po::expr_constant>>));
    static_assert((std::same_as<decltype(x.expr1), const po::expr_constant>));
    static_assert((std::same_as<decltype(x.expr1.expr1), const po::scalar_type>));

    assert(x.expr1.expr1 == po::scalar_type(7.2f));
    assert(x.place == 0);

    po::polynomial p = instantiate(x);

    PO_ASSERT(compare::unordered_equal_terms(
      p,
      {
        {po::scalar_type(7.2f), {1}},
      }),
      p);

    assert(p.rank() == 1);
    assert(compare::equal(p.degrees(), {1}));
    assert(p.degree() == 1);

    assert(p.constant() == 0.);
    assert(p.coefficient(1) == po::scalar_type(7.2f));

    PO_LINE;
  }

}
