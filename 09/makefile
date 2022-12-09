TARGET			:= $(notdir $(CURDIR))
SRCDIR      :=
INCDIR      := ../../../aoc/2022
BUILDDIR    := obj
TARGETDIR   := bin
SRCEXT      := cpp
DEPEXT      := h
OBJEXT      := o

LIB 	:= 

LIBRARIES := 

INC		:= -I./$(INCDIR) \

CXX		:= g++
STD		:= c++11
CFLAGS	:= -Wall -Wextra -std=$(STD) -g


SOURCES     := $(shell find $(INCDIR) -maxdepth 1 -type f -name \*.$(SRCEXT))
SOURCES			+= $(shell find $(CURDIR) -type f -name \*.$(SRCEXT))

$(info $$SOURCES are [${SOURCES}])

#if the folder structure is like /src /obj then this would work as a supstituion
#OBJECTS     := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))

#replace the compelte path and prefix with a new one
OBJECTS = $(addprefix $(BUILDDIR)/, $(notdir $(patsubst %.cpp, %.o, $(SOURCES))))
$(info $$OBJECTS are [${OBJECTS}])
#OBJECTS 	:= $(SOURCES:%.$(SRCEXT) = $(BUILDDIR)/%.($OBJEXT))

all: $(TARGETDIR)/$(TARGET)

$(TARGETDIR)/$(TARGET): $(OBJECTS)
	$(CXX) $(CFLAGS) -o $@ $^ $(LIB) $(LIBRARIES)

#$(BUILDDIR)/%.$(OBJEXT): $(filter $(notdir $(patsubst %.o, %.cpp, $@)),$(SOURCES))
$(BUILDDIR)/%.$(OBJEXT): $(foreach S,$(SOURCES),$(if $(findstring $(notdir $(patsubst %.o, %.cpp, $@)),$S),$S))
	$(CXX) $(INC) $(CFLAGS) -c -MMD $(foreach S,$(SOURCES),$(if $(findstring $(notdir $(patsubst %.o, %.cpp, $@)),$S),$S)) -o $@


# If the first argument is "run"...
ifeq (run,$(firstword $(MAKECMDGOALS)))
  # use the rest as arguments for "run"
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  # ...and turn them into do-nothing targets
  $(eval $(RUN_ARGS):;@:)
endif

$(TARGET): # ...
    # ...

.PHONY: run
run : $(TARGET)
	@echo ./bin/$(TARGET) $(RUN_ARGS)

clean:

		rm -rf ./obj/*.d
		rm -rf ./obj/*.o
