#include "../../../polynomial.h"
#include "../../compare.h"
#include <cassert>

void test_ctor_exprs()
{
  {
    const std::uint64_t count_before = po::polynomial::construction_count();

    po::polynomial p;

    const std::uint64_t count_after = po::polynomial::construction_count();
    const std::uint64_t count_diff = count_after - count_before;

    PO_ASSERT(count_diff == 1, count_diff);

    assert(p.rank() == 0);
    assert(p.degree() == 0);
    assert(compare::equal(p.degrees(), {}));
    assert(compare::unordered_equal_terms(p, {}));

    PO_LINE;
  }

  {
    po::polynomial p{};

    assert(p.rank() == 0);
    assert(p.degree() == 0);
    assert(p.nterms() == 0);
    assert(compare::equal(p.degrees(), {}));
    assert(compare::unordered_equal_terms(p, {}));

    PO_LINE;
  }

  {
    po::polynomial p{{}};

    assert(p.rank() == 0);
    assert(p.degree() == 0);
    assert(p.nterms() == 1);
    assert(compare::equal(p.degrees(), {}));
    assert(compare::unordered_equal_terms(p, {{0, {}}}));

    PO_LINE;
  }

  {
    auto p = po::polynomial{{}};

    assert(p.rank() == 0);
    assert(p.degree() == 0);
    assert(p.nterms() == 1);
    assert(compare::equal(p.degrees(), {}));
    assert(compare::unordered_equal_terms(p, {{0, {}}}));

    PO_LINE;
  }

  {
    auto p = po::zero(5);
    assert(p.rank() == 5);
    assert(p.degree() == 0);
    assert(compare::equal(p.degrees(), {0, 0, 0, 0, 0}));
    assert(compare::unordered_equal_terms(p, {}));

    PO_LINE;
  }

  {
    auto p = po::make_constant(2.5, 5);
    assert(p.rank() == 5);
    assert(p.degree() == 0);
    assert(compare::equal(p.degrees(), {0, 0, 0, 0, 0}));
    assert(compare::unordered_equal_terms(
      p,
      {
        {2.5, {0, 0, 0, 0, 0}}
      }));

    PO_LINE;
  }

  {
    auto p = po::polynomial::make_constant(5, 2.5);
    assert(p.rank() == 5);
    assert(p.degree() == 0);
    assert(compare::equal(p.degrees(), {0, 0, 0, 0, 0}));
    assert(compare::unordered_equal_terms(
      p,
      {
        {2.5, {0, 0, 0, 0, 0}}
      }));

    PO_LINE;
  }

  {
    auto p = po::polynomial::make_constant(po::rank<0>{}, 2.5);
    assert(p.rank() == 0);
    assert(p.degree() == 0);
    assert(compare::equal(p.degrees(), {}));
    assert(compare::unordered_equal_terms(
      p,
      {
        {2.5, {}}
      }));

    PO_LINE;
  }

  {
    auto p = po::polynomial::make_constant(po::rank<5>{}, 2.5);
    assert(p.rank() == 5);
    assert(p.degree() == 0);
    assert(compare::equal(p.degrees(), {0, 0, 0, 0, 0}));
    assert(compare::unordered_equal_terms(
      p,
      {
        {2.5, {0, 0, 0, 0, 0}}
      }));

    PO_LINE;
  }

  {
    po::polynomial(po::polynomial::make_constant(po::rank<0>{}, 0));

    PO_LINE;
  }

  {
    po::polynomial{po::polynomial::make_constant(po::rank<0>{}, -6.5)};

    PO_LINE;
  }

  {
    po::polynomial p{po::polynomial::make_constant(po::rank<6>{}, 7.5)};

    PO_LINE;
  }

  {
    po::polynomial p(po::polynomial::make_constant(po::rank<6>{}, 7.5));

    PO_LINE;
  }

  {
    po::polynomial{po::polynomial::make_zero(po::rank<15>{})};

    PO_LINE;
  }

  {
    po::polynomial(po::polynomial::make_zero(po::rank<15>{}));

    PO_LINE;
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

    PO_LINE;
  }

  {
    po::polynomial p{{1.4, {2, 3, 2, 1}}};

    PO_LINE;
  }

  {
    po::polynomial p = {{1.4, {2, 3, 2, 1}}};

    PO_LINE;
  }

  {
    po::polynomial({{1.4, {2, 3, 2, 1}}});

    PO_LINE;
  }

  {
    po::polynomial p({{1.4, {2, 3, 2, 1}}});

    PO_LINE;
  }

  {
    po::polynomial p({{2.4, {3, 2, 3, 2}}, {-0.6, {1, 1, 1, 1}}});

    PO_LINE;
  }

  {
    po::polynomial p{{2.4, {3, 2, 3, 2}}, {-0.6, {1, 1, 1, 1}}};

    PO_LINE;
  }

  {
    po::polynomial p{{2.4, {3, 2, 3, 2}}, {-0.6, {1, 1, 1, 1}}};
    po::polynomial copied{p};

    assert(p.nterms() == 2);
    assert(copied.nterms() == 2);

    PO_LINE;
  }

  {
    po::polynomial p{{2.4, {3, 2, 3, 2}}, {-0.6, {1, 1, 1, 1}}};
    po::polynomial moved{std::move(p)};

    assert(p.nterms() == 0);
    assert(moved.nterms() == 2);

    PO_LINE;
  }
}
