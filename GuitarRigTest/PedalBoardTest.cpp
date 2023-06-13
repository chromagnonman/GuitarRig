#include "pch.h"
#include "PedalBoard.h"


TEST(PedalBoardTest, AddEffects) {
  AmpSetup::PedalBoard pedal_board;

  pedal_board.addEffect(Effects::Pedals::DISTORTION);
  const auto effect = pedal_board.getEffects();
  ASSERT_NE(nullptr, effect);
}

TEST(PedalBoardTest, FeedbackLoop) {
  AmpSetup::PedalBoard pedal_board;

  pedal_board.addEffect(Effects::Pedals::DISTORTION);
  const auto effect = pedal_board.getEffects();
  ASSERT_NE(nullptr, effect);

  pedal_board.addEffect(effect);
  ASSERT_TRUE(pedal_board.feedbackDetected());
}
