#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include <string>

class Timer {
    public:
        Timer();

        void setName(std::string name);
        void getBeepTime(unsigned int &minutes, unsigned int &seconds);
        void setLoopDuration(int loopDuration);
        void loadBeepFile(std::string fileName);
        void start(unsigned int minutes, unsigned int seconds);
        void printName();

    private:
        void getInputToStart();
        void singleLoop(std::chrono::seconds totalSecondsChrono);
        void multipleLoop(std::chrono::seconds totalSecondsChrono, std::chrono::seconds loopDurationChrono);
        std::string m_fileName, m_timerName;
        unsigned int m_totalSeconds;
        int m_loopDuration; //pode ser -1 -> flag de apenas 1 loop
        bool m_bStart;
};

#endif