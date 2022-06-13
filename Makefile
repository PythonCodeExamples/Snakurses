CXX = gcc
CXXFLAGS = -Wall -Wextra -I src

SRCPATH = src
SRCMODULES = main.c \
	 deque.c \
	 button.c button_callbacks.c button_list.c \
	 panel.c \
	 snake.c apple.c \
	 menu.c game_cycle.c

OBJMODULES=$(SRCMODULES:.c=.o)

build: $(OBJMODULES)
	$(CXX) $(CXXFLAGS) $^ -o Snake -lncurses
	make clear

%.o: $(SRCPATH)/%.c
	$(CXX) $(CXXFLAGS) -c $^

clear:
	rm *.o
