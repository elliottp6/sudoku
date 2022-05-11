# parameters for "make" (must come first in file!)
MAKEFLAGS+=j$(shell nproc)

# output folders
DEBUG_FOLDER = bin/debug
RELEASE_FOLDER = bin/release

# exectuable
EXE = main
DEBUG_EXE = $(DEBUG_FOLDER)/$(EXE)
RELEASE_EXE = $(RELEASE_FOLDER)/$(EXE)

# objects
SOURCES = $(shell find . -name "*.cc" ! -wholename "*/dead/*") # all *.cc files, except those in the "dead" folder
OBJECTS = $(SOURCES:%.cc=%.o)
DEBUG_OBJECTS = $(addprefix $(DEBUG_FOLDER)/, $(OBJECTS))
RELEASE_OBJECTS = $(addprefix $(RELEASE_FOLDER)/, $(OBJECTS))

# compilation flags
LIBS = -std=c++17 -pthread -lSDL2 -lSDL2main -lX11 -lgtest
DEBUG_FLAGS = -Wall -Wextra -g -DDEBUG #Werror
RELEASE_FLAGS = -Wall -Wextra -Ofast -flto -fopenmp -DNDEBUG

# top-level targets
debug: $(DEBUG_EXE)
release: $(RELEASE_EXE)

# link
$(DEBUG_EXE): $(DEBUG_OBJECTS)
	g++ -o $@ $^ $(DEBUG_FLAGS) $(LIBS)
$(RELEASE_EXE): $(RELEASE_OBJECTS)
	g++ -o $@ $^ $(RELEASE_FLAGS) $(LIBS)

# compile
$(DEBUG_FOLDER)/%.o: %.cc
	mkdir -p $(dir $@) && g++ -o $@ $^ -c $(DEBUG_FLAGS)
$(RELEASE_FOLDER)/%.o: %.cc
	mkdir -p $(dir $@) && g++ -o $@ $^ -c $(RELEASE_FLAGS)

# clean
clean:
	rm -f $(DEBUG_EXE) $(RELEASE_EXE) $(DEBUG_OBJECTS) $(RELEASE_OBJECTS)

# note: ideas from these links
# https://stackoverflow.com/questions/1079832/how-can-i-configure-my-makefile-for-debug-and-release-builds
# https://stackoverflow.com/questions/13513905/how-to-set-up-googletest-as-a-shared-library-on-linux

