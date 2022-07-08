#include "../../polynomial.h"

#include <cassert>

void test_instantiate_unary_minus_p()
{
  {
    po::polynomial p{
      { 6  , {0, 5,  3, 7, 7}},
      {-2.4, {3, 0,  1, 3, 1}},
      { 4.4, {5, 5,  6, 3, 5}},
      { 5.1, {3, 0, 10, 5, 1}}};

    po::polynomial r = po::instantiate(-p, po::rank<3>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {-6  , {0, 5,  3, 7, 7}},
        { 2.4, {3, 0,  1, 3, 1}},
        {-4.4, {5, 5,  6, 3, 5}},
        {-5.1, {3, 0, 10, 5, 1}}
      }),
      r);
  }

  {
    po::polynomial p{
      { 6  , {0, 5,  3, 7, 7}},
      {-2.4, {3, 0,  1, 3, 1}},
      { 4.4, {5, 5,  6, 3, 5}},
      { 5.1, {3, 0, 10, 5, 1}}};

    po::polynomial r = po::instantiate(- -p, po::rank<3>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        { 6  , {0, 5,  3, 7, 7}},
        {-2.4, {3, 0,  1, 3, 1}},
        { 4.4, {5, 5,  6, 3, 5}},
        { 5.1, {3, 0, 10, 5, 1}}
      }),
      r);
  }

  {
    po::polynomial p{
      { 6  , {0, 5,  3, 7, 7}},
      {-2.4, {3, 0,  1, 3, 1}},
      { 4.4, {5, 5,  6, 3, 5}},
      { 5.1, {3, 0, 10, 5, 1}}};

    po::polynomial r = po::instantiate(- - - - -p, po::rank<3>{});

    PO_ASSERT(unordered_equal(
      r.terms,
      {
        {-6  , {0, 5,  3, 7, 7}},
        { 2.4, {3, 0,  1, 3, 1}},
        {-4.4, {5, 5,  6, 3, 5}},
        {-5.1, {3, 0, 10, 5, 1}}
      }),
      r);
  }

  PO_LINE;
}