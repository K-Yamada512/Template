.PHONY: clean run lib inspect test help

AR := ar rcvs
CC := gcc
CXX :=
RM := rm -rf
CFLAGS := -O1 -Iinclude -Iparts/schrocat/include
CPPFLAGS :=
LDFLAGS := -Llib
LDLIBS := -lm -lschrocat

PROJECTNAME := Template
BUILDPATH := build/
MAINFILENAME := src/source.c

LIBRARYNAME := calculate
SRCFILEPATH := src/
SRCS := calculate1.c\
		calculate2.c

SRCFILENAME := $(SRCS:%=$(SRCFILEPATH)%)
OBJFILEPATH := $(BUILDPATH)tmp/
OBJS := $(SRCS:%.c=%.o)
OBJFILENAME := $(OBJS:%=$(OBJFILEPATH)%)

$(BUILDPATH)$(PROJECTNAME).out : $(MAINFILENAME) $(OBJFILENAME)
	@mkdir -p $(BUILDPATH)
	$(CC) $(MAINFILENAME) $(OBJFILENAME) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -o $@

$(OBJFILENAME) : $(SRCFILENAME)
	@mkdir -p $(OBJFILEPATH)
	$(CC) $(@:$(OBJFILEPATH)%.o=$(SRCFILEPATH)%.c) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -c -o $@

run :
	./$(BUILDPATH)$(PROJECTNAME).out

clean :
	$(RM) $(BUILDPATH)
	@echo "Remove \"$(BUILDPATH)\""

lib : $(OBJFILENAME)
	@mkdir -p $(BUILDPATH)
	@echo "\e[33mGenerate static library(lib$(LIBRARYNAME).a) from $(OBJFILENAME)\e[m"
	$(AR) $(BUILDPATH)lib$(LIBRARYNAME).a $(OBJFILENAME)
	@echo ""

inspect :
	nm $(BUILDPATH)lib$(LIBRARYNAME).a
	@echo ""

test :
	@echo ""

help :
	@echo "option"
	@echo "  (default) : Compile"
	@echo "        run : Run (Execute $(PROJECTNAME).out)"
	@echo "      clean : Crean (Remove \"build\")"
	@echo "        lib : Generate static library"
	@echo "    inspect : Inspect the generated static library"
	@echo "       test : Debug makefile"
	@echo "       help : This"
