CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

SRC_SERVER = src/server/Server.cpp src/Packet.cpp src/Main.cpp
SRC_CLIENT = src/client/Client.cpp src/Packet.cpp src/Main.cpp

server: $(SRC_SERVER)
	$(CXX) $(CXXFLAGS) -o server $(SRC_SERVER)

client: $(SRC_CLIENT)
	$(CXX) $(CXXFLAGS) -o client $(SRC_CLIENT)

clean:
	rm -f server client
