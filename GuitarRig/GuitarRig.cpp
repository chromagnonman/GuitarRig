#include <iostream>

#include "GuitarRig.h"
//#include "RtMidi.h"

namespace AmpSetup{

    struct GuitarRig::Impl 
    {
        void create(const std::string& rig_name);
        void select(const std::string& rig_name);
        void remove(const std::string& rig_name);
        void activate();

        void addEffect(const Effects::Pedals& effect);
        void addEffect(std::shared_ptr<Effects::AudioEffect> effect);
        void removeEffect(const Effects::Pedals& effect);
        void removeEffect(std::shared_ptr<Effects::AudioEffect> effect);

        bool feedbackDetected() const;
        std::shared_ptr<Effects::AudioEffect> getEffects();
        const map_pedal_boards& allRigs() const;

      private:
        std::unordered_map<std::string, PedalBoard> m_guitarRigs;
        std::unordered_map<std::string, PedalBoard>::iterator m_activeBoard;

        std::unordered_map<std::string, PedalBoard>::iterator findRig(const std::string& name);
    };

    void GuitarRig::Impl::create(const std::string& rig) 
    {
        auto [pedal_board, OK] = m_guitarRigs.emplace(std::make_pair(rig, PedalBoard{}));

        if (OK) 
        {
            m_activeBoard = pedal_board;
        }
    }

     void GuitarRig::Impl::remove(const std::string& rig)
     {
        if (auto it = findRig(rig); it != m_guitarRigs.end())
        {
            const auto active_rig = m_activeBoard->first;
            m_guitarRigs.erase(it);
            std::cout << rig << " was removed";

            if (!m_guitarRigs.empty() && active_rig == rig) 
            {
              m_activeBoard = m_guitarRigs.begin();
            }
        }
        else 
        {
            std::cout << rig << " not found.";
        }
    }

    void GuitarRig::Impl::select(const std::string& rig) 
    {
        if (m_activeBoard = findRig(rig); m_activeBoard == m_guitarRigs.end()) 
        {
            std::cerr << "Rig not found.";
            return;
        }
    }

    void GuitarRig::Impl::activate()
    {
        if (m_guitarRigs.empty()) 
        {
            std::cout << "\nNo guitar amps created.";
            return;
        }

        std::cout << '\n' << m_activeBoard->first << " amp activated.";

        // TODO: Listen for audio input using RtMidi
        /*auto midiIn = std::make_shared<RtMidiIn>();

        const auto input_ports = midiIn->getPortCount();
        std::cout << "\nNumber of ports available: " << input_ports;
        std::string portname;
        for (size_t port = 0; port < input_ports; port++) 
        {
            try {
              portname = midiIn->getPortName(port);
            }catch(RtMidiError& error) {
              error.printMessage();
            }
        }*/

        // Process effects when input is detected
        float audio_input = 4.2;
        auto all_effects = m_activeBoard->second.getEffects();
        auto effects = all_effects.get();

        if (!m_activeBoard->second.feedbackDetected()) 
        {
            while (effects) 
            {
                effects->process(&audio_input, 2);
                effects = effects->nextEffect().get();
            }
        }
        else 
        {
            std::cerr << "\nFeedback loop detected in rig: " << m_activeBoard->first; 
        }
    }

    const map_pedal_boards& GuitarRig::Impl::allRigs() const 
    {
        if (m_guitarRigs.empty()) 
        {
            std::cout << "\nNo guitar amps created.";
        }

        return m_guitarRigs;
    }

    void GuitarRig::Impl::addEffect(const Effects::Pedals& effect) 
    {
        if (!m_guitarRigs.empty())
        {
            m_activeBoard->second.addEffect(effect);
        }
    }

    void GuitarRig::Impl::addEffect(std::shared_ptr<Effects::AudioEffect> effect)
    {
        if (!m_guitarRigs.empty())
        {
            m_activeBoard->second.addEffect(effect);
        }
    }

    void GuitarRig::Impl::removeEffect(const Effects::Pedals& effect) 
    {
        if (!m_guitarRigs.empty()) 
        {
            m_activeBoard->second.removeEffect(effect);
        }
    }

    void GuitarRig::Impl::removeEffect(std::shared_ptr<Effects::AudioEffect> effect) 
    {
        if (!m_guitarRigs.empty()) 
        {
            m_activeBoard->second.removeEffect(effect);
        }
    }

    bool GuitarRig::Impl::feedbackDetected() const 
    {
        bool result{false};

        if (!m_guitarRigs.empty()) 
        {
            result = m_activeBoard->second.feedbackDetected();
        }

        return result;
    }

    std::shared_ptr<Effects::AudioEffect> GuitarRig::Impl::getEffects() 
    {
        return m_activeBoard->second.getEffects();
    }

    std::unordered_map<std::string, PedalBoard>::iterator GuitarRig::Impl::findRig(const std::string& name) 
    {
        return m_guitarRigs.find(name);
    }


    // Constructors
    GuitarRig::GuitarRig(const std::string& name) noexcept : m_Impl{std::make_unique<Impl>()} 
    {
        m_Impl->create(name);
    }

    GuitarRig::GuitarRig() noexcept : m_Impl{std::make_unique<Impl>()} 
    {
    }

    GuitarRig::GuitarRig(GuitarRig&& rig) noexcept
    {
        m_Impl = std::move(rig.m_Impl);
    }

    GuitarRig& GuitarRig::operator=(GuitarRig&& rig) noexcept 
    {
        m_Impl = std::move(rig.m_Impl);
        return *this;
    }

    GuitarRig::~GuitarRig() = default;



    void GuitarRig::create(const std::string& rig) 
    { 
        m_Impl->create(rig);
    }

    void GuitarRig::remove(const std::string& rig) 
    { 
        m_Impl->remove(rig);
    }

    void GuitarRig::select(const std::string& rig) 
    { 
       m_Impl->select(rig);
    }

    void GuitarRig::activate() 
    { 
        m_Impl->activate();
    }

    const map_pedal_boards& GuitarRig::allRigs() const 
    {
        return m_Impl->allRigs();
    }

    void GuitarRig::addEffect(const Effects::Pedals& effect) 
    { 
       m_Impl->addEffect(effect);
    } 

    void GuitarRig::addEffect(std::shared_ptr<Effects::AudioEffect> effect) 
    {
       m_Impl->addEffect(effect);
    }

    void GuitarRig::removeEffect(const Effects::Pedals& effect) 
    {
       m_Impl->removeEffect(effect);
    }

    void GuitarRig::removeEffect(std::shared_ptr<Effects::AudioEffect> effect) 
    {
       m_Impl->removeEffect(std::move(effect));
    }

    bool GuitarRig::feedbackDetected() const 
    {
       return m_Impl->feedbackDetected();
    }

    std::shared_ptr<Effects::AudioEffect> GuitarRig::getEffects() 
    {
       return m_Impl->getEffects();
    }
} // namespace AmpSetup
