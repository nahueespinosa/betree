#include <gmock/gmock.h>

#include <betree/build.h>

namespace betree {

namespace {

class MockClass {
 public:
  MOCK_METHOD(Status, CallOp, (int), (const));
};

class SequenceTest : public ::testing::Test {
 protected:
  // Static mock object required because our behavior tree must be built with entities defined at compile time.
  // Lambda expressions in tests will have access to this without capturing.
  // We can't build the tree with mock objects because they are not copy constructible.
  static std::unique_ptr<MockClass> mock;

  void SetUp() override {
    mock = std::make_unique<MockClass>();
  }

  void TearDown() override {
    mock.reset();
  }
};

std::unique_ptr<MockClass> SequenceTest::mock;

TEST_F(SequenceTest, Should_ReturnSuccess_And_RunInOrder) {
  constexpr auto runner = make_reactive_sequence(
    []{ return mock->CallOp(1); },
    []{ return mock->CallOp(2); },
    []{ return mock->CallOp(3); }
  );
  
  {
    using ::testing::Return;
    ::testing::InSequence s;
    EXPECT_CALL(*mock, CallOp(1)).WillOnce(Return(Status::kSuccess));
    EXPECT_CALL(*mock, CallOp(2)).WillOnce(Return(Status::kSuccess));
    EXPECT_CALL(*mock, CallOp(3)).WillOnce(Return(Status::kSuccess));
  }

  ASSERT_EQ(runner(), Status::kSuccess);  
}

TEST_F(SequenceTest, Should_ReturnFailure_When_AnyChildReturnsFailure) {
  constexpr auto runner = make_reactive_sequence(
    []{ return mock->CallOp(1); },
    []{ return mock->CallOp(2); },
    []{ return mock->CallOp(3); }
  );

  {
    using ::testing::Return;
    ::testing::InSequence s;
    EXPECT_CALL(*mock, CallOp(1)).WillOnce(Return(Status::kSuccess));
    EXPECT_CALL(*mock, CallOp(2)).WillOnce(Return(Status::kFailure));
  }

  ASSERT_EQ(runner(), Status::kFailure);
}

TEST_F(SequenceTest, Should_ReturnRunning_When_AnyChildReturnsRunning) {
  constexpr auto runner = make_reactive_sequence(
    []{ return mock->CallOp(1); },
    []{ return mock->CallOp(2); },
    []{ return mock->CallOp(3); }
  );

  {
    using ::testing::Return;
    ::testing::InSequence s;
    EXPECT_CALL(*mock, CallOp(1)).WillOnce(Return(Status::kSuccess));
    EXPECT_CALL(*mock, CallOp(2)).WillOnce(Return(Status::kRunning));
  }

  ASSERT_EQ(runner(), Status::kRunning);
}

}  // namespace

}  // namespace betree
