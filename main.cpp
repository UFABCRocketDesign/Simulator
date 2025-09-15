#ifndef ARDUINO

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdint>
#include <filesystem>

#include "src/simulator.h"
#include "src/HardwareSerial.h"

#include "Target/Target.ino"

std::fstream pinsOutput ("pinsOutputLog.log", std::fstream::out);
std::fstream pinsInput  ("pinsInputLog.log", std::fstream::out);
std::fstream pinsMode   ("pinsModeLog.log", std::fstream::out);

int main(int argc, char *argv[])
{

	if(!std::filesystem::exists(simulator::fifo_path)) if (mkfifo(simulator::fifo_path, simulator::fifo_mode) == -1) {
		std::cerr << "mkfifo fail" << std::endl;
	}

	std::cerr << "\x1b[2J";

	simulator::arduinoThread = std::thread(simulator::arduinoMain);
	simulator::serialThread = std::thread(simulator::handleSerial0);
	simulator::diagramThread = std::thread(simulator::showDiagram);

	if(simulator::arduinoThread.joinable()) simulator::arduinoThread.join();
	if(simulator::diagramThread.joinable()) simulator::diagramThread.join();
	if(simulator::serialThread.joinable()) simulator::serialThread.join();

	std::remove(simulator::fifo_path);

	std::cerr << "\x1b[2J";
	std::cerr << "\x1b[0;0f";
	std::cerr << "Press \x1b[1mEnter\x1b[m no finish" << std::endl;

	return 0;
}

#endif