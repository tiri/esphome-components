#pragma once

#include <array>

namespace esphome {
namespace tecson {

template<typename ValueT, std::size_t Size> class circular_buffer {
  std::array<ValueT, Size> data;
  int current;

 public:
  circular_buffer() : data{}, current{0} {}

  void push(ValueT v) {
    data[current] = v;
    if (++current >= Size)
      current = 0;
  }

  std::array<ValueT, Size> read_all() const {
    std::array<ValueT, Size> copy{};
    for (std::size_t i = 0; i < Size; ++i)
      copy[i] = data[(current + i) % Size];

    return copy;
  }

  void flush() {
    for (auto &v : data) {
      v = 0;
    }
    current = 0;
  }
};

}  // namespace tecson
}  // namespace esphome
