#include "../../../polynomial.h"
#include "../../macros.h"
#include "../../compare.h"
#include <cassert>

void test_assign_expr_level_6()
{
  {
    po::polynomial q{{4.2, {4, 0, 7, 6, 5}}, { 5.5, {3, 1, 1, 0, 0}}};
    po::polynomial r{{1.2, {2, 2, 2, 2, 0}}, {13  , {3, 1, 1, 0, 0}}};

    po::polynomial p(1.4, po::rank<2>{});

    p = 2*(r-3)*r*r - 3.2*q;

    PO_ASSERT(compare::unordered_near_rel_terms(
      p,
      {
        {    3.456, {6, 6, 6, 6, 0}},
        {  112.32 , {7, 5, 5, 4, 0}},
        { 1216.8  , {8, 4, 4, 2, 0}},
        { 4394    , {9, 3, 3, 0, 0}},
        {   -8.64 , {4, 4, 4, 4, 0}},
        { -187.2  , {5, 3, 3, 2, 0}},
        {-1014    , {6, 2, 2, 0, 0}},
        {  -13.44 , {4, 0, 7, 6, 5}},
        {  -17.6  , {3, 1, 1, 0, 0}}
      }),
      p);

    PO_ASSERT(p.rank() == 5, p.rank());
    PO_ASSERT(p.degree() == 24, p.degree());
    PO_ASSERT(compare::equal(p.degrees(), {9, 6, 7, 6, 5}), p.degrees());


    po::polynomial p2(2*(r-3)*r*r - 3.2*q);

    PO_ASSERT(compare::unordered_equal_terms(p, p2.terms), p2);
    PO_ASSERT(p.rank() == p2.rank(), p2.rank());
    PO_ASSERT(p.degree() == p2.degree(), p2.degree());
    PO_ASSERT(compare::equal(p.degrees(), p2.degrees()), p2.degrees());
  }

  PO_LINE;
}
