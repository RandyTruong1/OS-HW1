CXX = g++
CXXFLAGS = -pthread -lrt -std=c++17

all: producer consumer

producer: producer.cpp
	$(CXX) $(CXXFLAGS) producer.cpp -o producer

consumer: consumer.cpp
	$(CXX) $(CXXFLAGS) consumer.cpp -o consumer

clean:
	rm -f producer consumer