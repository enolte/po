#include "../../polynomial.h"

#include "compare.h"

#include <cassert>

void test_ctor_exprs()
{
  {
    po::polynomial{};
  }

  {
    po::polynomial{{}};
  }

  {
    po::polynomial{0, po::rank<0>{}};
  }

  {
    po::polynomial{-6.5, po::rank<0>{}};
  }

  {
    po::polynomial{0, po::rank<6>{}};
  }

  {
    po::polynomial(0, po::rank<6>{});
  }

  {
    po::polynomial p{7.5, po::rank<6>{}};
  }

  {
    po::polynomial p(7.5, po::rank<6>{});
  }

  {
    po::polynomial{po::rank<15>{}};
  }

  {
    po::polynomial(po::rank<15>{});
  }
/*
  {
    po::polynomial(7);           // <-- fails concept check, as expected
  }

  {
    po::polynomial(7.5);         // <-- fails concept check, as expected
  }

  {
    po::polynomial p{'a'};       // <-- fails concept check, as expected
  }

  {
    po::polynomial p('a');       // <-- fails concept check, as expected
  }
*/

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
/*
  {
    po::polynomial p{1.4, {2, 3, 2, 1}};   // Disabled for operator overload resolution
  }

  {
    po::polynomial p(1.4, {2, 3, 2, 1});   // Disabled for operator overload resolution
  }

  {
    po::polynomial({1.4, {2, 3, 2, 1}});   // Disabled for operator overload resolution
  }

  {
    po::polynomial p({1.4, {2, 3, 2, 1}}); // Disabled for operator overload resolution
  }

  {
    po::polynomial p({2.4, {3, 2, 3, 2}}, {-0.6, {1, 1, 1, 1}}); // Disabled for operator overload resolution
  }
*/
  {
    po::polynomial({{1.4, {2, 3, 2, 1}}});
  }

  {
    po::polynomial p({{1.4, {2, 3, 2, 1}}});
  }

  {
    po::polynomial(1.4, 2, 3, 2, 1);
  }

  {
    po::polynomial p(1.4, 2, 3, 2, 1);
  }

  {
    po::polynomial{1.4, 2, 3, 2, 1};
  }

  {
    po::polynomial p{1.4, 2, 3, 2, 1};
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
