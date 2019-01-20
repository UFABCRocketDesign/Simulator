GPP = g++
ADDITIONAL_FLAGS = 
CFLAGS = $(ADDITIONAL_FLAGS) -std=c++11 -pedantic -Wall -Werror -lm

RUNNER = Simulator.run
ADDITIONAL_SOURCE = simulator.cpp
SOURCE = main.cpp $(ADDITIONAL_SOURCE)

.PHONY: compile
compile: $(SOURCE)
	@$(GPP) $^ -o $(RUNNER) $(CFLAGS)

.PHONY: run
run: compile $(RUNNER)
	@./Simulator.run