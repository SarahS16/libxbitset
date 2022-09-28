#include <boost/ut.hpp>
#include <cstdint>
#include <libxbitset/bitset.hpp>

namespace xstd {
boost::ut::suite classbitset_test = []() {
  using namespace boost::ut;

  "class bitset (0)"_test = []() {
    xstd::bitset test(0);
    constexpr xstd::bitrange bitr_obj{ 0, 16 };
    expect(that % 0x0000'0001 == test.set(0));
    expect(that % 0x0000'0000 == test.reset(0));
    expect(that % false == test.test(0));
    expect(that % 0x0000'0001 == test.flip(0));
    expect(that % true == test.test(0));
    expect(that % 0x0000'ABCD == test.insert<bitr_obj>(0xABCD));
    expect(that % 0xABCD == test.extract<bitr_obj>());
  };

  "class bitset (1)"_test = []() {
    xstd::bitset test(1);
    constexpr xstd::bitrange bitr_obj{ 0, 16 };
    expect(that % 0x0000'0003 == test.set(1));
    expect(that % 0x0000'0001 == test.reset(1));
    expect(that % false == test.test(1));
    expect(that % 0x0000'0003 == test.flip(1));
    expect(that % true == test.test(1));
    expect(that % 0x0000'ABCD == test.insert<bitr_obj>(0xABCD));
    expect(that % 0xABCD == test.extract<bitr_obj>());
  };

  "class bitset (2)"_test = []() {
    xstd::bitset test(2);
    constexpr xstd::bitrange bitr_obj{ 0, 16 };
    expect(that % 0x0000'0006 == test.set(2));
    expect(that % 0x0000'0002 == test.reset(2));
    expect(that % false == test.test(2));
    expect(that % 0x0000'0006 == test.flip(2));
    expect(that % true == test.test(2));
    expect(that % 0x0000'ABCD == test.insert<bitr_obj>(0xABCD));
    expect(that % 0xABCD == test.extract<bitr_obj>());
  };

  "class bitset upper half (16)"_test = []() {
    xstd::bitset test(0x0000'FFFF);
    constexpr xstd::bitrange bitr_obj{ 16, 16 };
    expect(that % 0x0001'FFFF == test.set(16));
    expect(that % 0x0000'FFFF == test.reset(16));
    expect(that % false == test.test(16));
    expect(that % 0x0001'FFFF == test.flip(16));
    expect(that % true == test.test(16));
    expect(that % 0xABCD'FFFF == test.insert<bitr_obj>(0xABCD));
    expect(that % 0xABCD == test.extract<bitr_obj>());
  };

  "class bitset upper half (17)"_test = []() {
    xstd::bitset test(0x0001'FFFF);
    constexpr xstd::bitrange bitr_obj{ 16, 16 };
    expect(that % 0x0003'FFFF == test.set(17));
    expect(that % 0x0001'FFFF == test.reset(17));
    expect(that % false == test.test(17));
    expect(that % 0x0003'FFFF == test.flip(17));
    expect(that % true == test.test(17));
    expect(that % 0xABCD'FFFF == test.insert<bitr_obj>(0xABCD));
    expect(that % 0xABCD == test.extract<bitr_obj>());
  };

  "class bitset::to<>"_test = []() {
    xstd::bitset test(0x0001'FFAA);
    expect(that % 0x0001'FFAA == test.to<std::uint32_t>());
    expect(that % 0xFFAA == test.to<std::uint16_t>());
    expect(that % 0xAA == test.to<std::uint8_t>());
  };

  "class bitset out of bounds"_test = []() {
    // xstd::bitset test(0xFFFF'FFFF);
    // constexpr xstd::bitrange bitr_obj{24,39};
    // expect(throws<std::out_of_range>([&test](){test.set(32);}));
    // expect(throws<std::out_of_range>([&test](){test.reset(32);}));
    // expect(throws<std::out_of_range>([&test](){test.flip(32);}));
    // expect(throws<std::out_of_range>([&test](){test.test(32);}));
    // expect(that % 0xCDFF'FFFF == test.insert<bitr_obj>(0xABCD));
    // expect(that % 0x00CD == test.extract<bitr_obj>());
  };
};
}