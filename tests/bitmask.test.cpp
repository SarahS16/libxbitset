#include <boost/ut.hpp>
#include <cstdint>
#include <libxbitset/bitset.hpp>

namespace xstd {
boost::ut::suite bitmask_test = [](){
    using namespace boost::ut;

    "bitrange::mask() width 1 (0)"_test = [](){
        constexpr auto test = bitrange::from<0,1>();
        expect(that % 3 == test.mask<int>());
    };

    "bitrange::mask() width 1 (1)"_test = [](){
        constexpr auto test = bitrange::from<1,2>();
        expect(that % 6 == test.mask<int>());
    };

    "bitrange::mask() width 1 (2)"_test = [](){
        constexpr auto test = bitrange::from<2,3>();
        expect(that % 12 == test.mask<int>());
    };

    "bitrange::mask() width 4 (0)"_test = [](){
        constexpr auto test = bitrange::from<0,3>();
        expect(that % 15 == test.mask<int>());
    };

    "bitrange::mask() width 4 (1)"_test = [](){
        constexpr auto test = bitrange::from<1,4>();
        expect(that % 30 == test.mask<int>());
    };

    "bitrange::mask() width 4 (2)"_test = [](){
        constexpr auto test = bitrange::from<2,5>();
        expect(that % 60 == test.mask<int>());
    };

    "bitrange::mask() width 16 (0)"_test = [](){
        constexpr auto test = bitrange::from<0,15>();
        expect(that % 65535 == test.mask<int>());
    };

    "bitrange::mask() width 16 (16)"_test = [](){
        constexpr auto test = bitrange::from<16,31>();
        expect(that % 4294901760 == test.mask<int>());
    };  
};
}