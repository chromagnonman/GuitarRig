#include <iostream>
//#include <csignal>

#include "GuitarRig.h"

//volatile std::sig_atomic_t signal_status;
//
//void signal_handler(int signal) 
//{
//    signal_status = signal;
//}

static void showMenu() 
{
    std::cout << "\t\t\t\n\nNative Instruments: Guitar Rig";
    std::cout << "\n1. Create";
    std::cout << "\n2. Remove";
    std::cout << "\n3. Activate";
    std::cout << "\n4. Select";
    std::cout << "\n5. List all guitar amp setup";
    std::cout << "\n9. Quit\n";
}

int main() 
{
    // TODO: Improve UI

    showMenu();

    //std::signal(SIGINT, signal_handler);

    AmpSetup::GuitarRig guitar_rig;

    std::string input;
    auto command = 0;

    do
    {
      std::string name;
      std::string pedal;
      auto pedal_type = 0;

      std::cin >> input;
      command = std::stoi(input);

      switch (command) {
        case 1:  // Create guitar amp setup
            std::cout << "\nEnter name of guitar setup (e.g. Metal, Punk, Grunge, Rock, etc.): ";
            std::cin >> name;
            guitar_rig.create(name);

            std::cout << "\nAdd effects: (0 - Overdrive, 1 - Distortion, 2 - Reverb. 9 - Done): ";
                do {
                std::cin >> pedal;
                pedal_type = std::stoi(pedal);
                switch (pedal_type) {
                case 0:
                    guitar_rig.addEffect(Effects::Pedals::OVERDRIVE);
                    std::cout << "\nOverdrive added\n";
                    break;
                case 1:
                    guitar_rig.addEffect(Effects::Pedals::DISTORTION);
                    std::cout << "\nDistortion added\n";
                    break;
                case 2:
                    guitar_rig.addEffect(Effects::Pedals::REVERB);
                    std::cout << "\nReverb added\n";
                    break;
                    }
                } while(pedal_type != 9);
                showMenu();
                break;

        case 2: // Remove guitar amp setup
            std::cout << "\nEnter name of guitar setup to be removed: ";
            std::cin >> name;
            guitar_rig.remove(name);
            showMenu();
            break;

        case 3: // Activate guitar amp setup
            guitar_rig.activate();
            showMenu();
            break;

        case 4:
            std::cout << "\nEnter name of guitar setup: ";
            std::cin >> name;
            guitar_rig.select(name);
            showMenu();
            break;

        case 5:
            std::cout << "\nListing all guitar amps created.";
            const auto& rigs = guitar_rig.allRigs();
            if (!rigs.empty())
            {
                for (const auto& [name, _] : rigs) 
                {
                    std::cout << "\n" << name;
                }
            }
            showMenu();
            break;
          }
    }while (command != 9);
    

    // For testing feedback loop
    AmpSetup::GuitarRig rig;

    rig.create("Metal");

    rig.addEffect(Effects::Pedals::OVERDRIVE);
    rig.addEffect(Effects::Pedals::DISTORTION);
    rig.addEffect(Effects::Pedals::REVERB);
    rig.activate();

    // This causes feedback loop
    auto effects = rig.getEffects();
    rig.addEffect(effects);
    rig.activate();

    return 0;
}