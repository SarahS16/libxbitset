#include <boost/ut.hpp>
#include <cstdint>
#include <libxbitset/bitset.hpp>

namespace xstd {
boost::ut::suite bitset_test = []() {
  using namespace boost::ut;

  "bitset::set() set no change (0)"_test = []() {
    xstd::bitset test_set(0);
    expect(that % 0x0000'0000 == test_set.set(0UL, false));
  };

  "bitset::set() increment position (0)"_test = []() {
    xstd::bitset test_set(0);
    expect(that % 0x0000'0001 == test_set.set(0UL));
    expect(that % 0x0000'0003 == test_set.set(1UL));
    expect(that % 0x0000'0007 == test_set.set(2UL));
  };

  "bitset::set() increment value (0)"_test = []() {
    xstd::bitset test_set(0);
    expect(that % 0x0000'0000 == test_set.set(0UL, false));
    expect(that % 0x0000'0001 == test_set.set(0UL, true));
  };

  "bitset::set() set no change (1)"_test = []() {
    xstd::bitset test_set(1);
    expect(that % 0x0000'0001 == test_set.set(0UL));
  };

  "bitset::set() increment position (1)"_test = []() {
    xstd::bitset test_set(1);
    expect(that % 0x0000'0001 == test_set.set(0UL));
    expect(that % 0x0000'0003 == test_set.set(1UL));
    expect(that % 0x0000'0007 == test_set.set(2UL));
  };

  "bitset::set() increment value (1)"_test = []() {
    xstd::bitset test_set(1);
    expect(that % 0x0000'0000 == test_set.set(0UL, false));
    expect(that % 0x0000'0001 == test_set.set(0UL));
  };

  "bitset::set() set no change (2)"_test = []() {
    xstd::bitset test_set(2);
    expect(that % 0x0000'0002 == test_set.set(0UL, false));
  };

  "bitset::set() increment position (2)"_test = []() {
    xstd::bitset test_set(2);
    expect(that % 0x0000'0003 == test_set.set(0UL));
    expect(that % 0x0000'0003 == test_set.set(1UL));
    expect(that % 0x0000'0007 == test_set.set(2UL));
  };

  "bitset::set() increment val (2)"_test = []() {
    xstd::bitset test_set(2);
    expect(that % 0x0000'0002 == test_set.set(0UL, false));
    expect(that % 0x0000'0003 == test_set.set(0UL));
  };

  "bitset::set() set no change (10)"_test = []() {
    xstd::bitset test_set(0xA);
    expect(that % 0x0000'000A == test_set.set(0UL, false));
  };

  "bitset::set() increment position (10)"_test = []() {
    xstd::bitset test_set(0xA);
    expect(that % 0x0000'000B == test_set.set(0UL));
    expect(that % 0x0000'000B == test_set.set(1UL));
    expect(that % 0x0000'000F == test_set.set(2UL));
  };

  "bitset::set() increment val (10)"_test = []() {
    xstd::bitset test_set(0xA);
    expect(that % 0x0000'000A == test_set.set(0UL, false));
    expect(that % 0x0000'000B == test_set.set(0UL));
  };

  "bitset::set() set no change upper half (0x1'FFFF)"_test = []() {
    xstd::bitset test_set(0x1'FFFF);
    expect(that % 0x0001'FFFF == test_set.set(16UL));
  };

  "bitset::set() increment position upper half (0x1'FFFF)"_test = []() {
    xstd::bitset test_set(0x1'FFFF);
    expect(that % 0x0001'FFFF == test_set.set(16UL));
    expect(that % 0x0003'FFFF == test_set.set(17UL));
    expect(that % 0x0007'FFFF == test_set.set(18UL));
  };

  "bitset::set() increment val upper half (0x1'FFFF)"_test = []() {
    xstd::bitset test_set(0x1'FFFF);
    expect(that % 0x0000'FFFF == test_set.set(16UL, false));
    expect(that % 0x0001'FFFF == test_set.set(16UL));
  };

  "bitset::set() set out of range"_test = []() {
    // xstd::bitset test_set(0);
    // expect(throws<std::out_of_range>([&test_set]() { test_set.set(32); }));
  };
};
}