#include "PedalBoard.h"
#include "Overdrive.h"
#include "Reverb.h"
#include "Distortion.h"

#include <iostream>

namespace AmpSetup {

    struct PedalBoard::Impl 
    {
        void addEffect(const Effects::Pedals& effect);
        void addEffect(std::shared_ptr<Effects::AudioEffect> effect);
        void removeEffect(const Effects::Pedals& effect);
        void removeEffect(const std::shared_ptr<Effects::AudioEffect>& effect);
        bool feedbackDetected() const;
        std::shared_ptr<Effects::AudioEffect> getEffects();

      private:
        std::shared_ptr<Effects::AudioEffect> m_effects {nullptr};
    };

    void PedalBoard::Impl::addEffect(const Effects::Pedals& effect) 
    {
        switch (effect) {

          case Effects::Pedals::OVERDRIVE:
            if (!m_effects) 
            {
                m_effects = std::make_shared<Effects::Overdrive>();
            } 
            else 
            {
                auto new_effect = std::make_shared<Effects::Overdrive>();
                auto pedals = m_effects.get();

                while (pedals->nextEffect()) 
                {
                    pedals = pedals->nextEffect().get();
                }

                pedals->nextEffect() = std::move(new_effect);
            }

            break;

          case Effects::Pedals::DISTORTION:
            if (!m_effects) 
            {
                m_effects = std::make_shared<Effects::Distortion>();
            } 
            else 
            {
                auto new_effect = std::make_shared<Effects::Distortion>();
                auto pedals = m_effects.get();

                while (pedals->nextEffect()) 
                {
                    pedals = pedals->nextEffect().get();
                }

                pedals->nextEffect() = std::move(new_effect);
            }

            break;

          case Effects::Pedals::REVERB:
            if (!m_effects) 
            {
                m_effects = std::make_shared<Effects::Reverb>();
            } 
            else 
            {
                auto new_effect = std::make_shared<Effects::Reverb>();
                auto pedals = m_effects.get();

                while (pedals->nextEffect()) 
                {
                    pedals = pedals->nextEffect().get();
                }

                pedals->nextEffect() = std::move(new_effect);
            }

            break;

            // TODO: Support other effects pedals
            case Effects::Pedals::CHORUS:
            case Effects::Pedals::DELAY:
            case Effects::Pedals::FILTER:
            case Effects::Pedals::FUZZY:
            case Effects::Pedals::WAH:
            break;
        }
    }

    void PedalBoard::Impl::addEffect(std::shared_ptr<Effects::AudioEffect> effect) 
    {
        auto pedals = m_effects.get();

        while (pedals->nextEffect()) 
        {
            pedals = pedals->nextEffect().get();
        }

        pedals->nextEffect() = std::move(effect);
    }

    void PedalBoard::Impl::removeEffect(const Effects::Pedals& effect) 
    {
        // TODO:
    }

    void PedalBoard::Impl::removeEffect(const std::shared_ptr<Effects::AudioEffect>& effect) 
    {
        // TODO:
    }

    bool PedalBoard::Impl::feedbackDetected() const 
    {
        auto pedal1 = m_effects.get();
        auto pedal2 = m_effects->nextEffect().get();

        while (pedal2 && pedal2->nextEffect()) 
        {
            if (pedal2 == pedal1) 
            {
                return true;
            }
            pedal1 = pedal1->nextEffect().get();
            pedal2 = pedal2->nextEffect()->nextEffect().get();
        }
        return false;
    }

    std::shared_ptr<Effects::AudioEffect> PedalBoard::Impl::getEffects() 
    {
        return m_effects;
    }



    // Constructors
    PedalBoard::PedalBoard() noexcept : m_pImpl { std::make_unique<Impl>() } 
    {
    }

    PedalBoard::PedalBoard(PedalBoard&& pedal) noexcept
    {
        m_pImpl = std::move(pedal.m_pImpl);
    }

    PedalBoard& PedalBoard::operator=(PedalBoard&& pedal) noexcept
    {
        m_pImpl = std::move(pedal.m_pImpl);
        return *this;
    }
    
    PedalBoard::~PedalBoard() = default;



    void PedalBoard::addEffect(const Effects::Pedals& effect) 
    {
        m_pImpl->addEffect(effect);
    }

    void PedalBoard::addEffect(std::shared_ptr<Effects::AudioEffect> effect) 
    {
        m_pImpl->addEffect(effect);
    }

    void PedalBoard::removeEffect(const Effects::Pedals& effect) 
    {
        m_pImpl->removeEffect(effect);
    }

    void PedalBoard::removeEffect(const std::shared_ptr<Effects::AudioEffect>& effect) 
    {
        m_pImpl->removeEffect(effect);
    }

    bool PedalBoard::feedbackDetected() const 
    {
        return m_pImpl->feedbackDetected();
    }

    std::shared_ptr<Effects::AudioEffect> PedalBoard::getEffects() 
    {
        return m_pImpl->getEffects();
    }
 }
