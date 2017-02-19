SOURCES := *.cpp
# Objs are all the sources, with .cpp replaced by .o
OBJS := $(SOURCES:.cpp=.o)

# INCLUDES=""
CFLAGS="-I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks -framework SDL2 -std=c++11"

all: maze

# Compile the binary 't' by calling the compiler with cflags, lflags, and any libs (if defined) and the list of objects.
maze: $(OBJS) $(CC) $(CFLAGS) -o maze $(OBJS) $(LFLAGS) $(LIBS)

# Get a .o from a .cpp by calling compiler with cflags and includes (if defined)
.cpp.o: $(CC) $(CFLAGS) $(INCLUDES) -c $<