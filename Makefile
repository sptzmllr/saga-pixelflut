###########################################################
#                                                         #
#                    SAGA Tool Library                    #
#                       pixelflut                         #
#                                                         #
#                        Makefile                         #
#                                                         #
#           Copyright (C) 2021 Justus Spitzmüller         #
#                                                         #
###########################################################

LIB_NAME           = saga_pixelflut.so

SAGA_ROOT          = /usr
WX_ROOT			   = /usr/include/wx-3.1

CXX_INCS           = -I"$(SAGA_ROOT)/include/saga/saga_core"
CXX_DEFS           = -D_SAGA_LINUX -D_TYPEDEF_BYTE -D_TYPEDEF_WORD -D_SAGA_UNICODE
CXX_FLGS           = -fPIC -DPIC -fopenmp

ifdef DEBUG
CXX_DEFS += -D_DEBUG 
CXX_FLGS += -ggdb -O0 -Wall -std=c++20
else
CXX_DEFS += -DNDEBUG
CXX_FLGS += -O2 -Wall -std=c++20
endif

CXXFLAGS           = $(CXX_INCS) $(CXX_DEFS) $(CXX_FLGS)
LNKFLAGS           = -fPIC -DPIC -shared
LNKLIBS            = -L"$(SAGA_ROOT)/lib" -lgomp -lsaga_api

CPP                = g++
LD                 = g++

SRC                = TLB_Interface.cpp\
					 saga_pixelflut.cpp
OBJ                = $(SRC:cpp=o)

DEPEND             = depend.mk

#DOXYGEN_OUTPUT_DIR = api

###########################################################

.PHONY: all all-before all-after clean clean-custom docs

all: all-before $(LIB_NAME) all-after

clean: clean-custom
	rm -f $(OBJ) $(LIB_NAME)

$(LIB_NAME): $(OBJ)
	$(LD) $(LNKFLAGS) $(OBJ) $(LNKLIBS) -o $(LIB_NAME)

include $(DEPEND)

###########################################################

.cpp.o:
	$(CPP) -c $< -o $@ $(CXXFLAGS)

###########################################################

$(DEPEND): $(SRC)
	$(CPP) -MM $(SRC) > $(DEPEND)
