17.PHONY: all build clean run

LDFLAGS += -lpistache -lcrypto -lssl -lpthread -std=c++17

all: build run

build: smartLamp

clean:
	-rm smartLamp

run:
	./smartLamp

smartLamp: smartLamp.cpp
	$(CXX) $< -o $@ $(CXXFLAGS) $(LDFLAGS)
