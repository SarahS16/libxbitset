#pragma once

#include <bitset>
#include <concepts>
#include <cstdint>
#include <limits>
#include <type_traits>

namespace xstd {

struct bitrange
{
  uint32_t position;
  uint32_t width;

  template<size_t BitPosition1, size_t BitPosition2>
  static consteval bitrange from()
  {
    constexpr uint32_t plus_one = 1;
    if constexpr (BitPosition1 < BitPosition2) {
      return bitrange{ .position = BitPosition1,
                       .width = plus_one + (BitPosition2 - BitPosition1) };
    } else {
      return bitrange{ .position = BitPosition2,
                       .width = plus_one + (BitPosition1 - BitPosition2) };
    }
  }
  template<size_t BitPosition>
  static constexpr bitrange from()
  {
    return bitrange{ .position = BitPosition, .width = 1 };
  }

  template<typename T>
  constexpr auto origin_mask() const
  {
    // Need to use an unsigned version of the type T for the mask to make sure
    // that the shift right doesn't result in a sign extended shift.
    using UnsignedT = typename std::make_unsigned<T>::type;

    // At compile time, generate variable containing all 1s with the size of the
    // target parameter.
    constexpr UnsignedT kFieldOfOnes = std::numeric_limits<UnsignedT>::max();

    // At compile time calculate the number of bits in the target parameter.
    constexpr size_t kTargetWidth = sizeof(T) * 8;

    // Create mask by shifting the set of 1s down so that the number of 1s from
    // bit position 0 is equal to the width parameter.
    UnsignedT bitmask_at_origin =
      static_cast<UnsignedT>(kFieldOfOnes >> (kTargetWidth - width));

    return bitmask_at_origin;
  }

  template<typename T>
  constexpr auto mask() const
  {
    // Need to use an unsigned version of the type T for the mask to make sure
    // that the shift right doesn't result in a sign extended shift.
    using UnsignedT = decltype(origin_mask<T>());

    return static_cast<UnsignedT>(origin_mask<T>() << position);
  }

  template<typename T>
  constexpr auto inverted_mask() const
  {
    return ~mask<T>();
  }

  constexpr bool operator==(const bitrange& other)
  {
    return other.position == position && other.width == width;
  }
};

template<typename T>
class bitset : public std::bitset<sizeof(T) * 8>
{
public:
  static constexpr size_t bit_width = sizeof(T) * 8;
  bitset(T p_initial_value)
    : std::bitset<bit_width>(
        static_cast<std::make_unsigned_t<T>>(p_initial_value))
  {
  }

  auto& set(std::unsigned_integral auto p_pos, bool p_value = true)
  {
    static_cast<std::bitset<bit_width>*>(this)->set(static_cast<size_t>(p_pos),
                                                    p_value);
    return *this;
  }

  auto& set(xstd::bitrange p_range)
  {
    this->set(p_range.position);
    return *this;
  }

  auto& reset(std::unsigned_integral auto p_pos)
  {
    static_cast<std::bitset<bit_width>*>(this)->reset(
      static_cast<size_t>(p_pos));
    return *this;
  }

  auto& reset(xstd::bitrange p_range)
  {
    this->reset(p_range.position);
    return *this;
  }

  auto& flip(std::unsigned_integral auto p_pos)
  {
    static_cast<std::bitset<bit_width>*>(this)->flip(
      static_cast<size_t>(p_pos));
    return *this;
  }

  auto& flip(xstd::bitrange p_range)
  {
    this->flip(p_range.position);
    return *this;
  }

  auto test(std::unsigned_integral auto p_pos) const
  {
    return static_cast<const std::bitset<bit_width>*>(this)->test(
      static_cast<size_t>(p_pos));
  }

  auto test(xstd::bitrange p_range) const
  {
    return this->test(p_range.position);
  }

  template<bitrange field>
  constexpr auto& insert(std::unsigned_integral auto p_value)
  {
    using NonVT = std::remove_volatile_t<T>;
    auto kBitmask = field.mask<std::remove_volatile_t<T>>();
    auto kInvertedBitmask = field.inverted_mask<std::remove_volatile_t<T>>();

    // Clear width's number of bits in the target value at the bit position
    // specified.
    *this &= kInvertedBitmask;

    // AND value with mask to remove any bits beyond the specified width.
    // Shift masked value into bit position and OR with target value.
    auto shifted_field = static_cast<NonVT>(p_value) << field.position;
    auto value = shifted_field & static_cast<NonVT>(kBitmask);

    *this |= static_cast<std::make_unsigned_t<NonVT>>(value);

    return *this;
  }

  template<bitrange mask>
  [[nodiscard]] constexpr auto extract() const
  {
    const auto shifted = this->to_ullong() >> mask.position;
    const auto masked = shifted & mask.origin_mask<T>();
    const auto final_result = static_cast<T>(masked);
    // Create mask by shifting the set of 1s down so that the number of 1s
    // from bit position 0 is equal to the width parameter.
    return xstd::bitset<T>(final_result);
  }

  template<std::integral U>
  [[nodiscard]] constexpr auto to()
  {
    return static_cast<U>(this->to_ullong());
  }
};

template<typename T>
class bitmanip : public xstd::bitset<std::remove_volatile_t<T>>
{
public:
  bitmanip(T& p_register_reference)
    : xstd::bitset<std::remove_volatile_t<T>>(p_register_reference)
    , register_reference_(p_register_reference)
  {
  }

  auto& save()
  {
    if constexpr (!std::is_const_v<T>) {
      register_reference_ = static_cast<T>(this->to_ullong());
    }
    return *this;
  }

  auto& update()
  {
    *static_cast<xstd::bitset<std::remove_volatile_t<T>>*>(this) =
      register_reference_;
    return *this;
  }

  ~bitmanip()
  {
    save();
  }

private:
  T& register_reference_;
};
}  // namespace xstd
