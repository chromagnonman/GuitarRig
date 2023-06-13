#pragma once

#include <memory>
#include <string>

#include "AudioEffect.h"

namespace AmpSetup {
    /**
     * @brief Class that manages the chained effects pedals
    */
    class PedalBoard 
    {
        public:
          PedalBoard() noexcept;
          PedalBoard (PedalBoard&&) noexcept;
          PedalBoard& operator=(PedalBoard&&) noexcept;
          virtual ~PedalBoard();

          void addEffect(const Effects::Pedals& effect);
          void addEffect(std::shared_ptr<Effects::AudioEffect> effect);
          void removeEffect(const Effects::Pedals& effect);
          void removeEffect(const std::shared_ptr<Effects::AudioEffect>& effect);
          
          [[nodiscard]] bool feedbackDetected() const;
          [[nodiscard]] std::shared_ptr<Effects::AudioEffect> getEffects();

        private:
          struct Impl;
          std::unique_ptr<Impl> m_pImpl;
    };
}
