default:
	g++ timerLauncher.cpp timer.cpp -o timerLauncher -lwinmm
	g++ timerInstance.cpp timer.cpp -o timerInstance -lwinmm