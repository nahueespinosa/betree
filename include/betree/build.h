#pragma once

#include <betree/concepts.h>

namespace betree {

consteval auto make_reactive_sequence(NodeLike auto ... args) {
  constexpr auto do_continue = [](Status result, Status& last) {
    last = result;
    return result == Status::kSuccess;
  };

  return [args..., do_continue]() {
    Status last = Status::kSuccess;
    (... && do_continue(args(), last));  // short-circuit evaluation
    return last;
  };
}

}  // namespace betree
