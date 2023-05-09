#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_add_eq_nullary_expr_level_0()
{
  {
    po::polynomial p = po::polynomial::make_zero(po::rank<5>{});

    assert(p.nterms() == 0);
    assert(p.constant() == 0);
    assert(p.coefficient(0, 0, 0, 0, 0) == 0.);

    p += po::expr_constant{8.};

    PO_ASSERT(p.nterms() == 1, p);
    assert(p.constant() == 8.);
    PO_ASSERT(p.coefficient(0, 0, 0, 0, 0) == 8., p);
    PO_LINE;
  }

  {
    po::polynomial p{{-7.1, {4, 1, 2, 2, 5}}, {4.9, {5, 0, 0, 0, 5}}};

    assert(p.nterms() == 2);
    assert(p.constant() == 0);
    assert(p.coefficient(0, 0, 0, 0, 0) == 0.);

    p += po::expr_constant{8.f};

    PO_ASSERT(p.nterms() == 3, p);
    assert(p.constant() == 8.);
    PO_ASSERT(p.coefficient(0, 0, 0, 0, 0) == 8., p);
    PO_LINE;
  }

}


