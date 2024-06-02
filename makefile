#
#	filename:makefile
#
# 
#	history:
# 		2024/06/02:K.Yamada :create this file
#

# Variables Used by Implicit Rules
AR := ar rcvs
CC := gcc
CXX :=
RM := rm -rf
CFLAGS := -O1 -Iinclude -Itest -Iparts/schrocat/include
CPPFLAGS :=
LDFLAGS := -Llib
LDLIBS := -lschrocat

# Variables Used by My Rules
PROJECTNAME := Template
LIBRARYNAME := calculate
OUTDIR := ./build
BINDIR := ./bin
INCDIR := ./include
SRCDIR := ./src
TESTDIR := ./test

OBJDIR := $(OUTDIR)/obj
DEPDIR := $(OUTDIR)/dep
EXECUTEFILENAME := $(BINDIR)/$(PROJECTNAME).out
LIBRARYFILENAME := $(BINDIR)/lib$(LIBRARYNAME).a
SRCS := $(wildcard $(SRCDIR)/*.c)
TESTS := $(wildcard $(TESTDIR)/*.c)
SRCOBJS := $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))
TESTOBJS := $(addprefix $(OBJDIR)/, $(notdir $(TESTS:.c=.o)))
DEPS := $(addprefix $(DEPDIR)/, $(notdir $(SRCS:.c=.d))) + $(addprefix $(DEPDIR)/, $(notdir $(TESTS:.c=.d)))

DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

$(EXECUTEFILENAME) : $(SRCOBJS) $(TESTOBJS) | $(BINDIR)
	@$(CC) $^ $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -o $@

$(LIBRARYFILENAME) : $(SRCOBJS) | $(BINDIR)
	@echo "\e[33mGenerate static library($(LIBRARYFILENAME)) from $^\e[m"
	@$(AR) $(LIBRARYFILENAME) $(SRCOBJS)
	@echo ""

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(DEPDIR)/%.d | $(OBJDIR) $(DEPDIR)
	@$(CC) $(DEPFLAGS) $< $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -c -o $@

$(OBJDIR)/%.o : $(TESTDIR)/%.c $(DEPDIR)/%.d | $(OBJDIR) $(DEPDIR)
	@$(CC) $(DEPFLAGS) $< $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -c -o $@

include $(wildcard $(DEPS))

$(DEPS) :

$(BINDIR):
	@mkdir -p $@

$(OBJDIR):
	@mkdir -p $@

$(DEPDIR):
	@mkdir -p $@

.PHONY: all
all : clean $(EXECUTEFILENAME) execute

.PHONY: clean
clean :
	@echo "Remove \"$(OBJDIR) $(DEPDIR) $(EXECUTEFILENAME) $(LIBRARYFILENAME)\""
	@$(RM) $(OBJDIR) $(DEPDIR) $(EXECUTEFILENAME) $(LIBRARYFILENAME)
	@echo ""

.PHONY: execute
execute :
	$(EXECUTEFILENAME)
	@echo ""

.PHONY: debug
debug : CFLAGS += -D_DEBUG
debug : clean $(EXECUTEFILENAME)

.PHONY: lib
lib : $(LIBRARYFILENAME)

.PHONY: inspect
inspect :
	@nm $(LIBRARYFILENAME)
	@echo ""

.PHONY: help
help :
	@echo "option"
	@echo "  (default) : Compile"
	@echo "        all : Crean and Compile and Execute"
	@echo "    execute : Execute \"$(EXECUTEFILENAME)\""
	@echo "      clean : Crean (Remove \"$(OBJDIR) $(DEPDIR) $(EXECUTEFILENAME) $(LIBRARYFILENAME)\")"
	@echo "      debug : Compile debug code (define _DEBUG)"
	@echo "        lib : "
	@echo "    inspect : "
	@echo "       help : This"
	@echo ""
