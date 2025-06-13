#include "timer.hpp"
#include <iostream>
#include <csignal>
#include <thread>
#include <windows.h>



void signalHandler(int signal) {
    std::cout << "\nSignal " << signal << " received. Exiting...\n";
    exit(0);
}

// Thread function using Windows Console API to detect ESC key press asynchronously
void listenToStop() {
        while (true) {
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) { //GetAsyncKeyState() from windows.h
            std::cout << "\nESC pressed. Sending SIGINT...\n";
            std::raise(SIGINT);
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
}



int main() {
    
    char setNewTimer = 'N';
    unsigned int count = 0;

    std::signal(SIGINT, signalHandler);
    
    std::thread keyThread(listenToStop);

    std::cout << "Running. Press ESC to stop...\n";


    do {

        Timer timer;
        unsigned int minutes = 0, seconds = 0;
        std::string title;
        std::string command;
        std::string sLoopDuration = "-1";
        
        if(count > 0) {
            std::cin.ignore(100 , '\n');
        }
        
        std::cout << "Type the timer's title: ";

        std::getline(std::cin, title);
    
        timer.getBeepTime(minutes, seconds);
    
        std::cout << "Do you wish the timer to keep looping? (Y/N): ";
        char loopOrNot;
        std::cin >> loopOrNot;
        if(toupper(loopOrNot) == 'Y') {
            std::cout << "\nType loop duration: ";
            std::cin >> sLoopDuration;
        }
    
        command = "cmd /c start \"" + title + "\" cmd /k timerInstance.exe " + title + " " + std::to_string(minutes) + " " + std::to_string(seconds) + " " + sLoopDuration;
    
        std::cout << command << std::endl;
        std::system(command.c_str());

        std::cout << "Do you wish to set a new timer? (Y/N) ";
        std::cin >> setNewTimer;
        count++;

    } while(toupper(setNewTimer) == 'Y');


    keyThread.join(); // If you want to wait for it, or detach if not.
    return 0;
}