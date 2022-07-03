#include <gmock/gmock.h>

#include <betree/build.h>

namespace betree {

namespace {

constexpr auto tick_success() -> Status {
  return Status::kSuccess;
}

constexpr auto tick_failure() -> Status {
  return Status::kFailure;
}

class TestNode {
 public:
  constexpr auto operator()() const {
    return Status::kSuccess;
  };
};

TEST(SimpleBuildTest, Should_Compile_And_ReturnSuccess) {
  constexpr auto runner = make_reactive_sequence(tick_success, TestNode());
  static_assert(runner() == Status::kSuccess);
  EXPECT_EQ(runner(), Status::kSuccess);
}

TEST(SimpleBuildTest, Should_Compile_And_ReturnFailure) {
  constexpr auto runner = make_reactive_sequence(tick_failure, TestNode());
  static_assert(runner() == Status::kFailure);
  EXPECT_EQ(runner(), Status::kFailure);
}

TEST(SimpleBuildTest, Should_Compile_And_ReturnRunning) {
  constexpr auto runner = make_reactive_sequence([]{ return Status::kRunning; }, TestNode());
  static_assert(runner() == Status::kRunning);
  EXPECT_EQ(runner(), Status::kRunning);
}

TEST(NestedBuildTest, Should_Compile_And_ReturnRunning) {
  constexpr auto runner = make_reactive_sequence(
    tick_success,
    tick_success,
    make_reactive_sequence(
      tick_success,
      []{ return Status::kRunning; }
    )
  );
  static_assert(runner() == Status::kRunning);
  EXPECT_EQ(runner(), Status::kRunning);
}

TEST(NestedBuildTest, Should_Compile_And_ReturnFailure) {
  constexpr auto runner = make_reactive_sequence(
    tick_success,
    tick_success,
    make_reactive_sequence(
      tick_failure,
      []{ return Status::kRunning; }
    )
  );
  static_assert(runner() == Status::kFailure);
  EXPECT_EQ(runner(), Status::kFailure);
}

}  // namespace

}  // namespace betree
