#include <iostream>
#include <cassert>
#include "../macros.h"

#include <chrono>

#include "../../induction/ls/exponents_sequence.h"

namespace po_test
{
  void test_exponents_sequence(std::size_t npoints, std::size_t length, std::size_t count);

  void test_exponents_sequence()
  {
    test_exponents_sequence(  0,   0,  1);
    test_exponents_sequence( 10,   0,  1);
    test_exponents_sequence( 34,   0,  1);
    test_exponents_sequence(100,   0,  1);
    test_exponents_sequence(  0,  10,  1);
    test_exponents_sequence(  0,  34,  1);
    test_exponents_sequence(  0, 100,  1);

    test_exponents_sequence(  0,   1,  1);
    test_exponents_sequence( 10,   1, 10);
    test_exponents_sequence( 34,   1, 34);
    test_exponents_sequence(100,   1,100);

    /* (3, 2) --> 6
     * 200   begin
     * 110
     * 020
     * 101
     * 011
     * 002
     *       end
     */
    test_exponents_sequence(3, 2, 6);

    /* (5, 2) --> 15
     * 20000   begin
     * 11000
     * 02000
     * 10100
     * 01100
     * 00200
     * 10010
     * 01010
     * 00110
     * 00020
     * 10001
     * 01001
     * 00101
     * 00011
     * 00002
     *       end
     */
    test_exponents_sequence(5, 2, 15);
    test_exponents_sequence(4, 5, 8*7*6 / (3*2*1));
    test_exponents_sequence(5, 5, 9*8*7*6 / (4*3*2*1));
    test_exponents_sequence(5, 10, 14*13*12*11 / (4*3*2*1));
    test_exponents_sequence(5, 15, 19*18*17*16 / (4*3*2*1));
    test_exponents_sequence(10, 5, 14*13*12*11*10 / (5*4*3*2*1));
    // test_exponents_sequence(10, 10, 19zu*18*17*16*15*14*13*12*11/ (9*8*7*6*5*4*3*2*1));
    // test_exponents_sequence(10, 15, 24zu*23*22*21*20*19*18*17*16 / (9*8*7*6*5*4*3*2*1));
    // test_exponents_sequence(15, 5, 19*18*17*16*15 / (5*4*3*2*1));
    // test_exponents_sequence(15, 10, 24zu*23*22*21*20*19*18*17*16*15 / (10*9*8*7*6*5*4*3*2*1));
    // test_exponents_sequence(15, 15, 29zu*28*27*26*25*24*23*22*21*20*19*18*17*16 / (14zu*13*12*11*10*9*8*7*6*5*4*3*2*1));
  }

  void verify_is_begin(const po::exponents_sequence&);
  void verify_is_end(const po::exponents_sequence&);
  void verify_counts(const po::exponents_sequence&, std::size_t ac_count, std::size_t ex_count);
  std::size_t get_actual_count(po::exponents_sequence& ii);

  void test_exponents_sequence(std::size_t npoints, std::size_t length, std::size_t ex_count)
  {
    po::exponents_sequence ii(npoints, length);
    assert(ii.npoints() == npoints);

    verify_is_begin(ii);

    // TODO
    // assert(!(ii < ii));
    // assert(!(ii > ii));
    // assert(!(ii != ii));
    // assert(ii == ii);
    // assert(ii <= ii);
    // assert(ii >= ii);

    const std::size_t ac_count = get_actual_count(ii);

    verify_is_end(ii);

    // Verify that `next` has no effect on end state.
    ++ii;
    verify_is_end(ii);

    verify_counts(ii, ac_count, ex_count);

    PO_LINE;
  }

  std::size_t get_actual_count(po::exponents_sequence& ii)
  {
    using clock = std::chrono::high_resolution_clock;

    const clock::time_point start = clock::now();

    std::size_t ac_count = 0;
    while(!ii.end)
    {
      // PO_TRACE(ii);
      ++ac_count;
      ++ii;
    }

    const clock::time_point stop = clock::now();
    const clock::duration loop_time__ns = stop - start;

    if(loop_time__ns.count() >= 1000)
    {
      PO_TRACE(" npoints = " << ii.npoints() << ", length = " << ii.length() << " num multiindices = " << ii.count() << " : exec time: " << loop_time__ns.count() / 1000000. << " ms = " << loop_time__ns.count() / (double)ac_count << " ns / exponents_sequence");
    }

    return ac_count;
  }

  void verify_counts(const po::exponents_sequence& ii, std::size_t ac_count, std::size_t ex_count)
  {
    // Verify binomial count
    // const std::size_t bc_count = po::utils::C(npoints + length - 1, length);
    const std::size_t bc_count = ii.count();
    if(ac_count != bc_count)
    {
      PO_TRACE("ac_count = " << ac_count);
      PO_TRACE("bc_count = " << bc_count);
    }

    PO_ASSERT(ac_count == bc_count, ac_count);

    // Verify loop iteration count
    if(ac_count != ex_count)
    {
      PO_TRACE("ac_count = " << ac_count);
      PO_TRACE("ex_count = " << ex_count);
      PO_TRACE(ii);
    }

    PO_ASSERT(ac_count == ex_count, ac_count);
  }

  void verify_is_begin(const po::exponents_sequence& ii)
  {
    assert(!ii.end);

    // Verify `begin` state: ii == {length, 0, ..., 0};
    if(ii.npoints() == 0 || ii.length() == 0)
    {
      assert(ii.nnz() == 0);
    }
    else if(ii.npoints() == 0)
    {
      assert(ii.nnz() == 1);
    }
    else
    {
      assert(ii[0] == ii.length());
      assert(ii.nnz() == 1);
    }
  }

  void verify_is_end(const po::exponents_sequence& ii)
  {
    assert(ii.end);

    // Verify `end` state: ii == {0, ..., 0, length}
    if(ii.npoints() > 0 && ii.length() > 0)
    {
      assert(ii[ii.npoints() - 1] == ii.length());
      assert(ii.nnz() == 1);
      assert(ii.end);
    }
    else if(ii.npoints() == 0 && ii.length() > 0)
    {
      assert(ii.nnz() == 1);
      assert(ii.end);
    }
    else
    {
      assert(ii.nnz() == 0);
    }
  }

}