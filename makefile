GPP = g++
ADDITIONAL_FLAGS = -I./src/
CFLAGS = $(ADDITIONAL_FLAGS) -std=c++14 -pedantic -Wall -Werror -lm -lpthread

RUNNER = Simulator.run
ADDITIONAL_SOURCE = src/simulator.cpp src/HardwareSerial.cpp src/Stream.cpp src/Print.cpp
SOURCE = main.cpp

.PHONY: compile
compile: $(SOURCE) $(ADDITIONAL_SOURCE)
	@$(GPP) $^ -o $(RUNNER) $(CFLAGS)

.PHONY: run_log
run_log: compile $(RUNNER)
	@./Simulator.run 1> output.log

.PHONY: run
run: compile $(RUNNER)
	@./Simulator.run

.PHONY: clear
clear:
	rm -rf *.run *.log