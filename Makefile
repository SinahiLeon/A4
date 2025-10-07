CXX := g++
CXXFLAGS := -Wall -std=gnu++17
# CXXFLAGS += -fsanitize=address,undefined -g

TARGET := TrieTest
OBJS := Trie.o TrieTest.o

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

Trie.o: Trie.cpp Trie.h
	$(CXX) $(CXXFLAGS) -c Trie.cpp

TrieTest.o: TrieTest.cpp Trie.h
	$(CXX) $(CXXFLAGS) -c TrieTest.cpp

clean:
	rm -f ./$(TARGET) *.o

# Usage: make test WORDS=words.txt QUERIES=queries.txt
test:
	./$(TARGET) $(WORDS) $(QUERIES)
