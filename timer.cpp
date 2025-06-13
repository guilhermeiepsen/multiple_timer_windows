#include "timer.hpp"
#include <iostream>
#include <cctype>
#include <thread>
#include <windows.h>
#include <mmsystem.h>

Timer::Timer() : m_totalSeconds(0), m_loopDuration(-1), m_bStart(false) {}

void Timer::setName(std::string name) {
    m_timerName = name;
}

void Timer::getBeepTime(unsigned int &minutes, unsigned int &seconds) {

    std::string time;
    size_t sizeOfSubstring, firstQuote, secondQuote;
    
    do {
        std::cout << "Digite o tempo que quer marcar na forma 1'10'' (minutos'segundos'')\n";
        std::cin >> time;
        firstQuote = time.find('\'');
        if(firstQuote != std::string::npos) {
            break;
        }
    } while(firstQuote == std::string::npos);
    
    
    if(time[firstQuote + 1] != '\'' ) { //acha minutos
        minutes = std::stoi(time.substr(0, firstQuote));
        this->m_totalSeconds += minutes*60;
        if(time[firstQuote + 1] == '\0') { //se nao tem mais, termina aqui
            seconds = 0;
            std::cout << "minutes: "<< minutes << " seconds: "<< seconds << " m_totalSeconds: " << this->m_totalSeconds << '\n';
            return;
        }
        //se nao terminar aqui, vai pro segundo if le embaixo
    } else { //senão, significa que eh segundos
        seconds = std::stoi(time.substr(0, firstQuote));
        this->m_totalSeconds += seconds;
        std::cout << "minutes: "<< minutes << " seconds: "<< seconds << " m_totalSeconds: " << this->m_totalSeconds << '\n';
        return;
    }
    //se ainda tiver, significa q eh segundos
    secondQuote = time.find('\'', firstQuote + 1);
    //std::cout << secondQuote << '\n';
    sizeOfSubstring = secondQuote - firstQuote - 1;
    std::cout << sizeOfSubstring << '\n';
    if(time[secondQuote + 1] == '\'') {
        seconds = std::stoi(time.substr(firstQuote + 1, sizeOfSubstring));
        this->m_totalSeconds += seconds;
        std::cout << "minutes: "<< minutes << " seconds: "<< seconds << " m_totalSeconds: " << this->m_totalSeconds << '\n';
    } else {
        std::cout << "Digitaçao errônea. Rode novamente\n";
    }

}
void Timer::setLoopDuration(int loopDuration) {

        m_loopDuration = loopDuration;

    std::cout << "m_loopDuration: " << m_loopDuration << '\n';
}

void Timer::printName() {
    std::cout << "m_timerName: " << m_timerName << '\n';
    std::cout << "m_totalSeconds: " << m_totalSeconds << '\n';
    //std::cout << "m_loopDuration: " << m_loopDuration << '\n';

}


void Timer::loadBeepFile(std::string fileName) {
    this->m_fileName = fileName;
    PlaySoundA(fileName.c_str(), NULL, SND_FILENAME | SND_ASYNC);
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    PlaySound(NULL, 0, 0);
}

void Timer::getInputToStart() {
    std::string input;
    do {
        std::cout << "Press ENTER to start timer: " << m_timerName;
        //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, input);
    } while(!input.empty());

    m_bStart = true;
    return;
}

void Timer::singleLoop(std::chrono::seconds totalSecondsChrono) {
    unsigned int secondsWentBy = 0;
    std::chrono::time_point<std::chrono::steady_clock> endInnerLoop;

    endInnerLoop = std::chrono::steady_clock::now() + totalSecondsChrono;

    while(std::chrono::steady_clock::now() <= endInnerLoop) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << ++secondsWentBy << ' ';
    }
    
    PlaySound(TEXT("beep.wav"), NULL, SND_FILENAME | SND_ASYNC); //se botar SYNC da ruim

}

void Timer::multipleLoop(std::chrono::seconds totalSecondsChrono, std::chrono::seconds loopDurationChrono) {
    unsigned int secondsWentBy = 0;
    std::chrono::time_point<std::chrono::steady_clock> endLoop;
    std::chrono::time_point<std::chrono::steady_clock> endInnerLoop;

    endLoop = std::chrono::steady_clock::now() + loopDurationChrono;
    
    while(std::chrono::steady_clock::now() < endLoop) {
        endInnerLoop = std::chrono::steady_clock::now() + totalSecondsChrono;
        while(std::chrono::steady_clock::now() <= endInnerLoop) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << ++secondsWentBy << ' ';
        }
        PlaySound(TEXT("beep.wav"), NULL, SND_FILENAME | SND_ASYNC); //se botar SYNC da merda
    }
}

void Timer::start(unsigned int minutes, unsigned int seconds) {

    m_totalSeconds = minutes*60 + seconds;

    std::chrono::seconds totalSecondsChrono = std::chrono::seconds(m_totalSeconds);
    std::chrono::seconds loopDurationChrono = std::chrono::seconds(m_loopDuration*60);

    getInputToStart();

    if(m_bStart) {

        if(m_loopDuration == -1) {
            singleLoop(totalSecondsChrono);
        } else {
            multipleLoop(totalSecondsChrono, loopDurationChrono);
        }
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));
    //END OF TIMER

}