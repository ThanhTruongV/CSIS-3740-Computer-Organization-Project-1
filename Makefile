CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude
SRC = src/main.cpp src/converters.cpp src/alu.cpp src/utils.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = alu_sim

TESTS = tests/test_converters tests/test_alu

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

tests: $(TESTS)

tests/test_converters: tests/test_converters.cpp src/converters.cpp include/converters.hpp
	$(CXX) $(CXXFLAGS) -o $@ tests/test_converters.cpp src/converters.cpp src/utils.cpp

tests/test_alu: tests/test_alu.cpp src/alu.cpp src/converters.cpp src/utils.cpp include/alu.hpp include/converters.hpp include/utils.hpp
	$(CXX) $(CXXFLAGS) -o $@ tests/test_alu.cpp src/alu.cpp src/converters.cpp src/utils.cpp

run_tests: tests
	@echo "==== Running converter tests ===="
	./tests/test_converters
	@echo "==== Running ALU tests ===="
	./tests/test_alu

clean:
	rm -f $(OBJ) $(TARGET) tests/test_converters tests/test_alu

.PHONY: all tests run_tests clean
