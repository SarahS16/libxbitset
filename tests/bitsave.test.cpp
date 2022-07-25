#include <boost/ut.hpp>
#include <cstdint>
#include <libxbitset/bitset.hpp>

namespace xstd {
boost::ut::suite bitsave_test = [](){
    using namespace boost::ut;

    "bitmanip::save() (1)"_test = [](){
        volatile uint32_t val{0};
        xstd::bitmanip test(val);
        expect(that % 0x0000'0000 == val);
        test.set(0);
        expect(that % 0x0000'0000 == val);
        test.save();
        expect(that % 0x0000'0001 == val);
        test.set(1);
        expect(that % 0x0000'0001 == val);
        expect(that % 0x0000'0003 == test);
        test.save();
        expect(that % 0x0000'0003 == val);
        expect(that % 0x0000'0003 == test);
    };

    "bitmanip::save() (2)"_test = [](){
        volatile uint32_t val{10};
        xstd::bitmanip test(val);
        expect(that % 0x0000'000A == val);
        test.set(0);
        expect(that % 0x0000'000A == val);
        test.save();
        expect(that % 0x0000'000B == val);
        test.set(2);
        expect(that % 0x0000'000B == val);
        expect(that % 0x0000'000F == test);
        test.save();
        expect(that % 0x0000'000F == val);
        expect(that % 0x0000'000F == test);
    };
};
}