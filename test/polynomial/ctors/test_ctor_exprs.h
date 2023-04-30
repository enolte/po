#include "../../../polynomial.h"
#include "../../compare.h"
#include <cassert>

void test_ctor_exprs()
{
  {
    const auto cc_before = po::polynomial::construction_count();
    po::polynomial{};
    const auto cc_after = po::polynomial::construction_count();
    assert(cc_after == cc_before + 1);
  }

  {
    po::polynomial{{}};
  }

  {
    po::polynomial(po::polynomial::make_constant(po::rank<0>{}, 0));
  }

  {
    po::polynomial{po::polynomial::make_constant(po::rank<0>{}, -6.5)};
  }

  {
    po::polynomial p{po::polynomial::make_constant(po::rank<6>{}, 7.5)};
  }

  {
    po::polynomial p(po::polynomial::make_constant(po::rank<6>{}, 7.5));
  }

  {
    po::polynomial{po::polynomial::make_zero(po::rank<15>{})};
  }

  {
    po::polynomial(po::polynomial::make_zero(po::rank<15>{}));
  }

/*
  static_assert(std::same_as<decltype('þ'), int>);
  {
    po::polynomial p('þ');       // <-- Ok, multi-byte char encoded as int, which is an acceptable scalar type.
                                 //     This may induce a compiler disagnostic, though.
  }

  {
    po::polynomial p(int('þ'));  // <-- Idem. This may also induce a compiler disagnostic, though.
  }

  {
    po::polynomial p{'þ'};       // <-- Idem. This may also induce a compiler disagnostic, though.
  }

  {
    po::polynomial p{int('þ')};  // <-- Idem. This may also induce a compiler disagnostic, though.
  }
*/
  {
    po::polynomial{{1.4, {2, 3, 2, 1}}};
  }

  {
    po::polynomial p{{1.4, {2, 3, 2, 1}}};
  }

  {
    po::polynomial p = {{1.4, {2, 3, 2, 1}}};
  }

  {
    po::polynomial({{1.4, {2, 3, 2, 1}}});
  }

  {
    po::polynomial p({{1.4, {2, 3, 2, 1}}});
  }

  {
    po::polynomial p({{2.4, {3, 2, 3, 2}}, {-0.6, {1, 1, 1, 1}}});
  }

  {
    po::polynomial p{{2.4, {3, 2, 3, 2}}, {-0.6, {1, 1, 1, 1}}};
  }

  {
    po::polynomial p{{2.4, {3, 2, 3, 2}}, {-0.6, {1, 1, 1, 1}}};
    po::polynomial copied{p};

    assert(p.nterms() == 2);
    assert(copied.nterms() == 2);
  }

  {
    po::polynomial p{{2.4, {3, 2, 3, 2}}, {-0.6, {1, 1, 1, 1}}};
    po::polynomial moved{std::move(p)};

    assert(p.nterms() == 0);
    assert(moved.nterms() == 2);
  }

  PO_LINE;
}
