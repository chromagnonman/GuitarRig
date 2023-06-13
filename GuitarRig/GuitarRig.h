#pragma once

#include <string>
#include <unordered_map>
#include <optional>

#include "PedalBoard.h"

namespace AmpSetup {

    using map_pedal_boards = std::unordered_map<std::string, PedalBoard>;
    /**
     * @brief Creates guitar amp setup (rig). It allows multiple rigs and can switch between them.
    */
    class GuitarRig 
    {
      public:
        explicit GuitarRig(const std::string& name) noexcept;
        GuitarRig() noexcept;
        GuitarRig(GuitarRig&&) noexcept;
        GuitarRig& operator=(GuitarRig&&) noexcept;
        virtual ~GuitarRig();
          
        void create(const std::string& rig_name);
        void select(const std::string& rig_name);
        void remove(const std::string& rig_name);
        void activate();

        void addEffect(const Effects::Pedals& effect);
        void addEffect(std::shared_ptr<Effects::AudioEffect> effect);
        void removeEffect(const Effects::Pedals& effect);
        void removeEffect(std::shared_ptr<Effects::AudioEffect> effect);
        
        [[nodiscard]] bool feedbackDetected() const;
        [[nodiscard]] std::shared_ptr<Effects::AudioEffect> getEffects();
        const map_pedal_boards& allRigs() const;
        
      private:
        struct Impl;
        std::unique_ptr<Impl> m_Impl;
    };
}
