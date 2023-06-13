#include "pch.h"
#include "GuitarRig.h"

TEST(GuitarRigTest, GuitarRigCreation) {
  AmpSetup::GuitarRig guitar_rig;

  guitar_rig.create("Heavyh Metal");
  guitar_rig.addEffect(Effects::Pedals::OVERDRIVE);
  guitar_rig.addEffect(Effects::Pedals::DISTORTION);
  guitar_rig.activate();

  auto effects = guitar_rig.getEffects();
  ASSERT_NE(nullptr, effects);
  guitar_rig.addEffect(effects);
  EXPECT_TRUE(guitar_rig.feedbackDetected());
}

TEST(GuitarRigTest, VerifyPedalsInEachRig) {
  AmpSetup::GuitarRig guitar_rig;

  guitar_rig.create("Heavy Metal");
  guitar_rig.addEffect(Effects::Pedals::OVERDRIVE);
  guitar_rig.addEffect(Effects::Pedals::DISTORTION);
  guitar_rig.activate();

  auto effects = guitar_rig.getEffects();
  ASSERT_NE(nullptr, effects);

  auto number_of_pedals = 0;
  auto effect = effects.get();
  
  while (effect) {
    number_of_pedals++;
    effect = effect->nextEffect().get();
  }
  
  // Verify there are two pedals in this guitar rig
  EXPECT_EQ(number_of_pedals, 2);
  
  guitar_rig.create("Punk Rock");
  guitar_rig.addEffect(Effects::Pedals::OVERDRIVE);
  effects = guitar_rig.getEffects();
  ASSERT_NE(nullptr, effects);
  
  number_of_pedals = 0;
  effect = effects.get();
  while (effect) {
  	  number_of_pedals++;
      effect = effect->nextEffect().get();
  }

  // We expect only one pedal for this setup
  EXPECT_EQ(number_of_pedals, 1);
}

TEST(GuitarRigTest, VerifyAllRigsAreCreated)
{ 
    AmpSetup::GuitarRig guitar_rig;

    guitar_rig.create("Metal");
    guitar_rig.create("Punk Rock");
    guitar_rig.create("Grunge");

    EXPECT_EQ(guitar_rig.allRigs().size(), 3);
}
