CC=g++

CFLAGS=-D _DEBUG -ggdb3 -std=c++2a -O0 -Wall -Wextra -Weffc++\
-Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations\
-Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported\
-Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral\
-Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op\
-Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith\
-Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo\
-Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn\
-Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default\
-Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast\
-Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers\
-Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new\
-fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging\
-fno-omit-frame-pointer -fPIE -fsanitize=address,alignment,bool,${strip \
}bounds,enum,float-cast-overflow,float-divide-by-zero,${strip \
}integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,${strip \
}returns-nonnull-attribute,shift,signed-integer-overflow,undefined,${strip \
}unreachable,vla-bound,vptr\
-pie -Wlarger-than=8192 -Wstack-usage=8192

BUILDTYPE?=Debug
TEST_CASE?=

ifeq ($(BUILDTYPE), Release)
	CFLAGS=-std=c++2a -O3 -Wall
endif

PROJECT	:= sort_practice
SRCDIR	:= src
OBJDIR 	:= obj
BINDIR	:= bin

SRCS	:= cpp
OBJS	:= o


INCFLAGS:= -I$(SRCDIR)

SOURCES := $(shell find $(SRCDIR) -type f -name "*.$(SRCS)")
OBJECTS	:= $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES:.$(SRCS)=.$(OBJS)))

all: $(BINDIR)/$(PROJECT)

remake: cleaner all

.FORCE:

$(OBJDIR)/tester/tester.o: $(SRCDIR)/tester/tester.cpp .FORCE
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCFLAGS) -DTEST_CASE="test_cases/$(TEST_CASE).h" -DTEST_CASE_NAME=$(TEST_CASE) -c $< -o $@

$(OBJDIR)/%.$(OBJS): $(SRCDIR)/%.$(SRCS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

$(BINDIR)/$(PROJECT): $(OBJECTS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $^ -o $(BINDIR)/$(PROJECT)

clean:
	@rm -rf $(OBJDIR)

cleaner: clean
	@rm -rf $(BINDIR)

run: $(BINDIR)/$(PROJECT)
	$(BINDIR)/$(PROJECT) $(ARGS)

.PHONY: all remake clean cleaner .FORCE

