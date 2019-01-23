GPP = g++
ADDITIONAL_FLAGS = 
CFLAGS = $(ADDITIONAL_FLAGS) -std=c++14 -pedantic -Wall -Werror -lm

RUNNER = Simulator.run
ADDITIONAL_SOURCE = simulator.cpp HardwareSerial.cpp Stream.cpp Print.cpp
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