#include "timer.hpp"
#include <iostream>
#include <cctype>
#include <thread>
#include <windows.h>
#include <mmsystem.h>
#include <vector>
#include <cstdlib>

#pragma comment(lib, "winmm.lib")

int main(int argc, char** argv) {
    std::cout << "teste " << " " << argv[1] << " " << argv[2] << " " << argv[3] << " " << argv[4];
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    Timer timer1;

    char*** a;

    std::string timer1_name = argv[1];
    timer1.setName(timer1_name);
    int loopDuration = std::stoi(argv[4]);
    timer1.setLoopDuration(loopDuration);
    timer1.printName();
    timer1.loadBeepFile("beep.wav");
    timer1.start(std::stoi(argv[2]), std::stoi(argv[3]));


//    std::cin >> papa;

    return 0;


    //-how to create other parallel timers?
    //we're going to have a vector of timers. and for each timer we'll create an independent thread that'll run this timer.
    //-alright. but how are we going to manage the inteface? i mean the time count and input for each timer.
    //that's the main thing we need think of now. i'm certain there will be some way. just not sure exactly how at the moment.
    //so far i've thought of separating the time counting by a bunch of /n or spaces.
    //and the about the input: as soon as the timer is set, it desapears (maybe using system(cls) or smth like that)
    //-what about creating a window for each timer as soon as it gets set up? now i see a clear and plausible path in this solution
    //that might be the way for doing this. lets see
    
}