#pragma once

#include <concepts>

namespace betree {

enum class Status {
  kSuccess,
  kFailure,
  kRunning,
};

template <typename T>
concept Tickable = requires(T t) {
  { t() } -> std::convertible_to<Status>;
};

template <typename T>
concept NodeLike = Tickable<T> && std::copy_constructible<T>;

}  // namespace betree
