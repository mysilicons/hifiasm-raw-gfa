# SPDX-License-Identifier: MIT
# Copyright (c) 2024 hifiasm-raw-gfa authors
# Adapted from hifiasm (MIT-licensed). Original authors: Haoyu Cheng, Heng Li, et al.
# See LICENSE in the project root for the full license text.

CXX=		g++
CC=			gcc
CXXFLAGS=	-g -O3 -msse4.2 -mpopcnt -fomit-frame-pointer -Wall
CFLAGS=		$(CXXFLAGS)
CPPFLAGS=
INCLUDES=
OBJS=		main.o CommandLines.o Process_Read.o Assembly.o Hash_Table.o \
			POA.o Correct.o Levenshtein_distance.o Overlaps.o kthread.o \
			htab.o sketch.o anchor.o sys.o rcut.o ecovlp.o \
			kalloc.o gfa_ut.o stubs.o ksw2_extz2_sse.o

EXE=		hifiasm-raw
LIBS=		-lz -lpthread -lm

ifneq ($(asan),)
	CXXFLAGS+=-fsanitize=address
	LIBS+=-fsanitize=address
endif

.SUFFIXES:.cpp .c .o
.PHONY:all clean

.cpp.o:
		$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $(INCLUDES) $< -o $@

.c.o:
		$(CC) -c $(CFLAGS) $(CPPFLAGS) $(INCLUDES) $< -o $@

all:$(EXE)

$(EXE):$(OBJS)
		$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LIBS)

clean:
		rm -fr *.o $(EXE)
