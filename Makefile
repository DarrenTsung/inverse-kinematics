# CONFIGURATION
PROJECT := inverse-k	
TESTBUILD := itester

CC := g++
CCFLAGS := -Ilib -Wall -O3
ifeq ($(shell sw_vers 2>/dev/null | grep Mac | awk '{ print $$2}'),Mac)
	# CFLAGS = -g -DGL_GLEXT_PROTOTYPES -I./include/ -I/usr/X11/include -DOSX
	LDFLAGS = -framework GLUT -framework OpenGL \
    	-L"/System/Library/Frameworks/OpenGL.framework/Libraries" \
    	-lGL -lGLU -lm -lstdc++
else
	# CFLAGS = -g -DGL_GLEXT_PROTOTYPES -Iglut-3.7.6-bin
	LDFLAGS = -lglu32 -lglut32 -lopengl32
endif

SRCFOLDER := src
OBJFOLDER := obj

# processing stuff
SRC := $(wildcard $(SRCFOLDER)/*.cpp)
OBJ := $(addprefix $(OBJFOLDER)/, $(notdir $(SRC:.cpp=.o)))

ifeq ($(OS), Windows_NT)
	RM = del /F
	DELETEOBJS = $(OBJFOLDER)\*.o $(PROJECT).exe
else
	RM = rm -f
	DELETEOBJS = $(OBJFOLDER)/*.o $(PROJECT)
endif

.PHONY: all clean build
all: $(PROJECT)

clean:
	$(RM) $(DELETEOBJS)
	
build: clean all





# compile targets
$(PROJECT): $(OBJ)
	$(CC) $(CCFLAGS) -o $@ $^ $(LDFLAGS)
$(OBJFOLDER)/%.o: $(SRCFOLDER)/%.cpp
	$(CC) $(CCFLAGS) -o $@ -c $< 
