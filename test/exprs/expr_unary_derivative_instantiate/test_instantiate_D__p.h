#include "../../../ostream/valarray_ostream.h"
#include "../../../polynomial.h"
#include "../../errors.h"
#include <cassert>

void test_instantiate_D__p()
{
  // lvalue polynomial, place within rank, zero constant term
  {
    po::polynomial p{{0, {0, 0}}};
    po::polynomial r = po::instantiate(po::D(p, 1), po::rank<2>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {0, {0, 0}}
      }),
      r);

    PO_ASSERT(r.rank() == 2, r.rank());
    PO_ASSERT(compare::equal(r.degrees(), {0, 0}), r.degrees());
    PO_ASSERT(r.degree() == 0, r.degree());
  }

  // lvalue polynomial, place within rank, non-zero constant term
  {
    po::polynomial p{{-31.2, {0, 0}}};
    po::polynomial r = po::instantiate(po::D(p, 1), po::rank<2>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {0, {0, 0}}
      }),
      r);

    PO_ASSERT(r.rank() == 2, r.rank());
    PO_ASSERT(compare::equal(r.degrees(), {0, 0}), r.degrees());
    PO_ASSERT(r.degree() == 0, r.degree());
  }

  // lvalue polynomial, place within rank, zero non-constant term
  {
    po::polynomial p{{0, {1, 7}}};
    po::polynomial r = po::instantiate(po::D(p, 1), po::rank<2>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {0, {1, 6}}
      }),
      r);

    PO_ASSERT(r.rank() == 2, r.rank());
    PO_ASSERT(compare::equal(r.degrees(), {1, 6}), r.degrees());
    PO_ASSERT(r.degree() == 7, r.degree());
  }


  // lvalue polynomial, place within rank, with zero coefficient
  {
    po::polynomial p{{0, {5, 1}}};
    po::polynomial r = po::instantiate(po::D(p, 1), po::rank<2>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {0, {5, 0}}
      }),
      r);

    PO_ASSERT(r.rank() == 2, r.rank());
    PO_ASSERT(compare::equal(r.degrees(), {5, 0}), r.degrees());
    PO_ASSERT(r.degree() == 5, r.degree());
  }

  // lvalue polynomial, place within rank
  {
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}};
    po::polynomial r = po::instantiate(po::D(p, 1), po::rank<2>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {2, {5, 0}}, {6, {2, 1}}
      }),
      r);

    PO_ASSERT(r.rank() == 2, r.rank());
    PO_ASSERT(compare::equal(r.degrees(), {5, 1}), r.degrees());
    PO_ASSERT(r.degree() == 5, r.degree());
  }

  // lvalue polynomial, place within rank, without zero term
  {
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}};
    po::polynomial r = po::instantiate(po::D(p, 0), po::rank<2>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {10, {4, 1}}, {6, {1, 2}}
      }),
      r);

    PO_ASSERT(r.rank() == 2, r.rank());
    PO_ASSERT(compare::equal(r.degrees(), {4, 2}), r.degrees());
    PO_ASSERT(r.degree() == 5, r.degree());
  }

  // lvalue polynomial, place within rank, with zero term
  {
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}, {0, {0, 0}}};
    po::polynomial r = po::instantiate(po::D(p, 0), po::rank<2>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {10, {4, 1}}, {6, {1, 2}}, {0, {0, 0}}
      }),
      r);

    PO_ASSERT(r.rank() == 2, r.rank());
    PO_ASSERT(compare::equal(r.degrees(), {4, 2}), r.degrees());
    PO_ASSERT(r.degree() == 5, r.degree());
  }

  // lvalue polynomial, place within rank
  {
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}, {7, {0, 0}}};
    po::polynomial r = po::instantiate(po::D(p, 0), po::rank<2>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {10, {4, 1}}, {6, {1, 2}}, {0, {0, 0}}
      }),
      r);

    PO_ASSERT(r.rank() == 2, r.rank());
    PO_ASSERT(compare::equal(r.degrees(), {4, 2}), r.degrees());
    PO_ASSERT(r.degree() == 5, r.degree());
  }

  // lvalue polynomial, place not in rank
  {
    po::polynomial p{{2, {5, 1}}, {3, {2, 2}}};
    po::polynomial r = po::instantiate(po::D(p, 5), po::rank<2>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {0, {0, 0}}
      }),
      r);

    PO_ASSERT(r.rank() == 2, r.rank());
    PO_ASSERT(compare::equal(r.degrees(), {0, 0}), r.degrees());
    PO_ASSERT(r.degree() == 0, r.degree());
  }

  // rvalue polynomial, place not in rank
  {

    po::polynomial r = po::instantiate(po::D(po::polynomial{{2, {5, 1}}, {3, {2, 2}}}, 5), po::rank<2>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {0, {0, 0}}
      }),
      r);

    PO_ASSERT(r.rank() == 2, r.rank());
    PO_ASSERT(compare::equal(r.degrees(), {0, 0}), r.degrees());
    PO_ASSERT(r.degree() == 0, r.degree());
  }

  // rvalue polynomial, place within rank
  {

    po::polynomial r = po::instantiate(po::D(po::polynomial{{2, {5, 1, 4}}, {3, {2, 2, 0}}}, 1), po::rank<2>{});

    PO_ASSERT(compare::unordered_equal_terms(
      r,
      {
        {2, {5, 0, 4}},
        {6, {2, 1, 0}}
      }),
      r);

    PO_ASSERT(r.rank() == 3, r.rank());
    PO_ASSERT(compare::equal(r.degrees(), {5, 1, 4}), r.degrees());
    PO_ASSERT(r.degree() == 9, r.degree());
  }

  PO_LINE;
}
