TARGET			:= $(notdir $(CURDIR))
SRCDIR      :=
INCDIR      := ../../../aoc/2022
BUILDDIR    := obj
TARGETDIR   := bin
CPPUTEST_HOME	:= /home/rb/projects/tdd/cpputest
SRCEXT      := cpp
DEPEXT      := h
OBJEXT      := o

LIB 	:= -L$(CPPUTEST_HOME)/cpputest_build/lib

LIBRARIES := -lCppUTest -lCppUTestExt

INC		:= -I./$(INCDIR) \
		   -I$(CPPUTEST_HOME)/include

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


run:
		./bin/$(TARGET)

clean:

		rm -rf ./obj/*.d
		rm -rf ./obj/*.o
