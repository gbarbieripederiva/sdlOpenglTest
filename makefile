SOURCES = $(wildcard src/*.cpp)
INCLUDE = ./include
CPRE_FLAGS = -I $(INCLUDE)
CPOS_FLAGS = $$(sdl2-config --cflags --libs) -lGL -lGLEW

all:$(SOURCES)
	g++ $(CPRE_FLAGS) $(SOURCES) -o main  $(CPOS_FLAGS)

debug:$(SOURCES)
	g++ -g $(CPRE_FLAGS) $(SOURCES) -o main  $(CPOS_FLAGS)

.PHONY:clean
clean:
	rm main