CC := g++
CFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -Weffc++ -g -O2
LDFLAGS := -L${SFML_ROOT}/lib -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio
OBJFILES = $(patsubst %.cc,%.o,$(wildcard *.cc))
HEADERFILES = $(wildcard *.h) $(wildcard.hpp)
OUTPUTFILENAME = asteroids

.PHONY: asteroids clean

asteroids: $(OBJFILES) $(HEADERSFILES)
	$(CC) $^ $(LDFLAGS) -o $(OUTPUTFILENAME)

%.o: %.cc
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	-@rm -rfv $(OBJFILES)
	-@rm -v $(OUTPUTFILENAME)
