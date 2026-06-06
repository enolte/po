#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>


template<typename ostream, std::size_t n>
ostream& operator<<(ostream& o, const std::array<po::rank_type, n>& a)
{
  if(a.size() > 0)
  {
    for(auto i = std::cbegin(a); i != std::prev(std::cend(a)); ++i)
      o << *i << ", ";
    o << a.back();
  }
  return o;
}

void test_expr_nullary_extend_p()
{
  // degree 0: rank 3 -- rank 5, test 0
  {
    // p(x, y, z) = 2.3
    po::polynomial p = po::make_constant(2.3, 3);
    auto y1 = p(0, 0, 0, 0, 0);
    assert(y1 != y1);

    // px(v, w, x, y, z) := p(x, y, v)
    // px(x, y, z, a, b) := p(z, a, x)
    auto px = extend(p, 5, 2, 3, 0);
    static_assert(std::same_as<decltype(px), po::expr_extend<po::polynomial&, std::array<po::rank_type, 3>>>);
    assert(px.rank == 5);
    assert(compare::equal(px.places, {2, 3, 0}));

    auto y2 = px(0, 0, 0, 0, 0);
    assert(y2 == y2);
    assert(y2 == 2.3);

    auto y3 = px(2, 1, 0.6, 4, -14.87);
    assert(y3 == y3);
    assert(y3 == 2.3);
  }

  // degree 0: rank 0 --> rank 3, test 1
  {
    po::polynomial p = po::make_constant(3, 0);
    auto x = po::extend(p, 3);

    assert(compare::equal(x.places, {}));
    assert(x.rank == 3);

    po::scalar_type y = x(0, 1, 2);
    PO_ASSERT(y == p(), y);
    PO_ASSERT(y == 3, y);

    PO_LINE;
  }

  // rank 1 --> rank 3, test 1
  {
    po::polynomial p{{3, {   0   }}};
    auto x = po::extend(p, 3, 1);

    assert(compare::equal(x.places, {1}));
    assert(x.rank == 3);

    po::scalar_type y = x(1, 2, 3);
    PO_ASSERT(y == 3, y);

    y = x(2, 1, 3);
    PO_ASSERT(y == 3, y);

    PO_LINE;
  }

  // rank 1 --> rank 3, test 2
  {
    const po::polynomial p{{3, {   0   }}};
    auto x = po::extend(p, 3, 2);

    assert(compare::equal(x.places, {2}));
    assert(x.rank == 3);

    po::scalar_type y = x(1, 2, 3);

    PO_ASSERT(y == 3, y);

    PO_LINE;
  }

  // rank 1 --> rank 3, test 3
  {
    po::polynomial p{{3, {   0   }}};
    auto x = po::extend(p, 3, 1);

    assert(compare::equal(x.places, {1}));
    assert(x.rank == 3);

    po::scalar_type y = x(0, 7, 0);

    assert(y == y);
    PO_ASSERT(y == p(7), y);

    PO_LINE;
  }

  // rank 1 --> rank 3, test 4
  {
    po::polynomial p{{3, {   4   }}};

    // Define x(u, v, w) := p(v)
    auto x = po::extend(p, 3, 1);
    // static_assert(std::same_as<decltype(x), po::expr_extend<po::polynomial&, po::places<1>>);

    assert(compare::equal(x.places, {1}));
    assert(x.rank == 3);

    double y = x(7, 0, 0);
    assert(y == 0.);
    PO_ASSERT(y == p(0), y);

    y = x(0, 7, 0);
    PO_ASSERT(y == p(7), y);
    PO_ASSERT(y == 3*2401, y);

    y = x(0, 0, 7);
    assert(y == 0.);
    PO_ASSERT(y == p(0), y);

    PO_LINE;
  }

  // rank 1 --> rank 3, test 5, place OOB
  {
    po::polynomial p{{3, {   0   }}};

    auto x = po::extend(p, 3, 3);

    assert(compare::equal(x.places, {3}));

    assert(x.rank == 3);
    po::scalar_type y = x(1, 2, 3);
    PO_ASSERT(y != y, y);

    PO_LINE;
  }

  // rank 1 --> rank 3, test 6, place OOB
  {
    po::polynomial p{{3, {   0   }}};

    auto x = po::extend(p, 3, 77);

    assert(compare::equal(x.places, {77}));

    assert(x.rank == 3);
    po::scalar_type y = x(1, 2, 3);
    PO_ASSERT(y != y, y);

    PO_LINE;
  }

  // rank 2 --> rank 3, test 1
  {
    po::polynomial p{{3, {1, 4}}};

    // (x, y) --> (α, x, y)
    auto x = po::extend(p, 3, 1, 2);

    assert(compare::equal(x.places, {1, 2}));
    assert(x.rank == 3);

    po::scalar_type y = x(2, 7, 3);
    assert(y == y);
    PO_ASSERT(y == p(7, 3), y);

    PO_LINE;
  }

  // rank 2 --> rank 3, test 2
  {
    po::polynomial p{{3, {1, 4}}};

    // (x, y) --> (x, α, y)
    auto x = po::extend(p, 3, 0, 2);

    assert(compare::equal(x.places, {0, 2}));
    assert(x.rank == 3);

    po::scalar_type y = x(2, 7, 3);
    assert(y == y);
    PO_ASSERT(y == p(2, 3), y);

    PO_LINE;
  }

  // rank 2 --> rank 3, test 3
  {
    po::polynomial p{{3, {1, 4}}};

    // (x, y) --> (x, y, α)
    auto x = po::extend(p, 3, 0, 1);

    assert(compare::equal(x.places, {0, 1}));
    assert(x.rank == 3);

    po::scalar_type y = x(2, 7, 3);
    assert(y == y);
    PO_ASSERT(y == p(2, 7), y);

    y = x(2, 7, 5.887);
    assert(y == y);
    PO_ASSERT(y == p(2, 7), y);

    y = x(2, -3.2, 44.0548);
    assert(y == y);
    PO_ASSERT(y == p(2, -3.2), y);

    PO_LINE;
  }

  // rank 2 --> rank 3, test 4, too few place values
  {
    po::polynomial p{{3, {1, 4}}};

    // (x, y) --> ?
    auto x = po::extend(p, 3, 0);

    assert(compare::equal(x.places, {0}));
    assert(x.rank == 3);

    po::scalar_type y = x(2, 7, 3);
    assert(y != y);

    PO_LINE;
  }

  // rank 2 --> rank 3, test 5, too many place values
  {
    po::polynomial p{{3, {1, 4}}};

    // (x, y) --> ?
    auto x = po::extend(p, 3, 0, 1, 2);

    assert(compare::equal(x.places, {0, 1, 2}));
    assert(x.rank == 3);

    po::scalar_type y = x(2, 7, 3);
    assert(y != y);

    PO_LINE;
  }

  // rank 2 --> rank 4, test 1
  {
    po::polynomial p{{3.2, {3, 2}}, {2.2, {2, 2}}};

    auto x = extend(p, 4, 1, 2);
    assert(x.rank == 4);

    assert(x(6, 7, 3, 3) == p(7, 3));
    assert(x(5, 7, 3, 3) == p(7, 3));
    assert(x(4, 7, 3, 3) == p(7, 3));
    assert(x(3, 7, 3, 3) == p(7, 3));
    assert(x(2, 7, 3, 3) == p(7, 3));
    assert(x(2, 7, 3, 2) == p(7, 3));
    assert(x(2, 7, 3, 1) == p(7, 3));
    assert(x(2, 7, 3, 0) == p(7, 3));
    assert(x(2, 7, 3,-1) == p(7, 3));

    PO_LINE;
  }

  // rank 2 --> rank 3, loop test 1
  {
    po::polynomial p{{7.4, {0, 0}}};

    const po::rank_type rank = 3;

    //           0, 1       0, 1, 2
    // -----------------------------
    // (0, 1) : (x, y) --> (x, y, α)
    // (0, 2) : (x, y) --> (x, α, y)
    // (1, 2) : (x, y) --> (α, x, y)
    for(po::rank_type n0 = 0; n0 < rank; ++n0)
      for(po::rank_type n1 = n0 + 1; n1 < rank; ++n1)
      {
        auto x = po::extend(p, rank, n0, n1);
        PO_ASSERT(compare::equal(x.places, {n0, n1}), x.places);
        assert(x.rank == 3);

        po::scalar_type y = x(2, 7, 3);
        assert(y == y);
        PO_ASSERT(y == 7.4, y);
      }
    PO_LINE;
  }

  // rank 3 --> rank 5, loop test 1
  {
    po::polynomial p{{7.4, {0, 0, 0}}};

    const po::rank_type rank = 5;

    //              0, 1, 2       0, 1, 2, 3, 4
    // -----------------------------------------
    // (0, 1, 2) : (x, y, z) --> (x, y, z, α, ß)
    // (0, 1, 3) : (x, y, z) --> (x, y, α, z, ß)
    // (0, 1, 4) : (x, y, z) --> (x, y, α, ß, z)
    // (0, 2, 3) : (x, y, z) --> (x, α, y, z, ß)
    // (0, 2, 4) : (x, y, z) --> (x, α, y, ß, z)
    // (0, 3, 4) : (x, y, z) --> (x, α, ß, y, z)
    // (1, 2, 3) : (x, y, z) --> (α, x, y, z, ß)
    // (1, 2, 4) : (x, y, z) --> (α, x, y, ß, z)
    // (1, 3, 4) : (x, y, z) --> (α, x, ß, y, z)
    // (2, 3, 4) : (x, y, z) --> (α, ß, x, y, z)
    for(po::rank_type n0 = 0; n0 < rank; ++n0)
      for(po::rank_type n1 = n0 + 1; n1 < rank; ++n1)
        for(po::rank_type n2 = n1 + 1; n2 < rank; ++n2)
        {
          auto x = po::extend(p, rank, n0, n1, n2);
          PO_ASSERT(compare::equal(x.places, {n0, n1, n2}), x.places);
          assert(x.rank == 5);

          po::scalar_type y = x(2, 7, 3, -4, 4);
          assert(y == y);
          PO_ASSERT(y == 7.4, y);
        }
    PO_LINE;
  }

  // rank 4 --> rank 7, test 1
  {
    po::polynomial p{{7.4, {0, 0, 0, 1}}};

    auto x = po::extend(p, po::rank<7>{}, 1, 3, 5, 6);

    assert(compare::equal(x.places, {1, 3, 5, 6}));
    assert(x.rank == 7);

    po::scalar_type y = x(2, 7, 3, 4, -5.4, -.2, 2.4);
    assert(y == p(7, 4, -0.2, 2.4));
    assert(y == 7.4*2.4);

    PO_LINE;
  }
  // TODO
#if 0
  // rank 4 --> rank 7, test 1.5
  {
    po::polynomial p{{7.4, {0, 0, 0, 1}}};

    auto x = po::extend(p, po::rank<7>{}, {1, 3, 5, 6});

    assert(compare::equal(x.places, {1, 3, 5, 6}));
    assert(x.rank == 7);

    po::scalar_type y = x(2, 7, 3, 4, -5.4, -.2, 2.4);
    assert(y == p(7, 4, -0.2, 2.4));
    assert(y == 7.4*2.4);

    PO_LINE;
  }
#endif
  // rank 4 --> rank 7, test 2, too few args
  {
    po::polynomial p{{7.4, {0, 0, 0, 1}}};

    auto x = po::extend(p, 7, 1, 3, 5, 6);

    assert(compare::equal(x.places, {1, 3, 5, 6}));
    assert(x.rank == 7);

    po::scalar_type y = x(2, 7, 3, 4, -5.4, -.2);
    assert(y != y);

    PO_LINE;
  }

  // rank 4 --> rank 7, test 3, too many args
  {
    po::polynomial p{{7.4, {0, 0, 0, 1}}};

    auto x = po::extend(p, po::rank<7>{}, 1, 3, 5, 6);

    assert(compare::equal(x.places, {1, 3, 5, 6}));
    assert(x.rank == 7);

    po::scalar_type y = x(2, 7, 3, 4, -5.4, -.2, 2.4, 0.7);
    assert(y != y);

    PO_LINE;
  }

  // rank 6 --> rank 9, test 1
  {
    po::polynomial p{{3, {1, 2, 3, 1, 2, 3}}};
    auto x = po::extend(p, 9, 1, 2, 3, 6, 7, 8);
    assert(compare::equal(x.places, {1, 2, 3, 6, 7, 8}));
    assert(x.rank == 9);

    //     p(     x, y, z,           u, v, w)
    assert(x(0  , 1, 1, 1, 0  , 0  , 1, 1, 1) == 3);
    assert(x(0  , 1, 1, 1, 0  , 0.1, 1, 1, 1) == 3);
    assert(x(0  , 1, 1, 1, 0.1, 0  , 1, 1, 1) == 3);
    assert(x(0.1, 1, 1, 1, 0  , 0  , 1, 1, 1) == 3);

    assert(x(0  , 2, 1, 1, 0  , 0  , 1, 1, 1) == 6);
    assert(x(0  , 2, 1, 1, 0  , 0.1, 1, 1, 1) == 6);
    assert(x(0  , 2, 1, 1, 0.1, 0  , 1, 1, 1) == 6);
    assert(x(0.1, 2, 1, 1, 0  , 0  , 1, 1, 1) == 6);

    assert(x(0  , 1, 0.4, 1, 0  , 0  , 1, 1, 1) == 3 * 0.4 * 0.4);
    assert(x(0  , 1, 0.4, 1, 0  , 0.1, 1, 1, 1) == 3 * 0.4 * 0.4);
    assert(x(0  , 1, 0.4, 1, 0.1, 0  , 1, 1, 1) == 3 * 0.4 * 0.4);
    assert(x(0.1, 1, 0.4, 1, 0  , 0  , 1, 1, 1) == 3 * 0.4 * 0.4);

    assert(x(0  , 2, 0.4, 1, 0  , 0  , 1, 0.4, 1) == 3 * 2 * 0.4 * 0.4 * 0.4 * 0.4);
    assert(x(0  , 2, 0.4, 1, 0  , 0.1, 1, 0.4, 1) == 3 * 2 * 0.4 * 0.4 * 0.4 * 0.4);
    assert(x(0  , 2, 0.4, 1, 0.1, 0  , 1, 0.4, 1) == 3 * 2 * 0.4 * 0.4 * 0.4 * 0.4);
    assert(x(0.1, 2, 0.4, 1, 0  , 0  , 1, 0.4, 1) == 3 * 2 * 0.4 * 0.4 * 0.4 * 0.4);

    PO_LINE;
  }
}
