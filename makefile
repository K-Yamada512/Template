#
#	filename:makefile
#
# 
#	history:
# 		2024/06/02:K.Yamada :create this file
# 		2024/12/11:K.Yamada :add build-other
# 		2024/12/23:K.Yamada :support icx compiler
#

# Variables Used by Implicit Rules
AR := ar rcvs
CC := gcc
CXX :=
RM := rm -rf
CFLAGS := -O1 -Iinclude -Itest -Iparts/create_log/include
CPPFLAGS :=
LDFLAGS := -Llib
LDLIBS := -lm -lclog

# Variables Used by My Rules
PROJECTNAME := Template
LIBRARYNAME := exercise
OUTDIR := ./build
BINDIR := ./bin
LIBDIR := ./lib
PARDIR := ./parts
INCDIR := ./include
SRCDIR := ./src
TESTDIR := ./test

OBJDIR := $(OUTDIR)/obj
DEPDIR := $(OUTDIR)/dep
MAKEFILESDIR := $(wildcard $(PARDIR)/*)
EXECUTEFILENAME := $(BINDIR)/$(PROJECTNAME).out
LIBRARYFILENAME := $(BINDIR)/lib$(LIBRARYNAME).a
SRCS := $(wildcard $(SRCDIR)/*.c)
TESTS := $(wildcard $(TESTDIR)/*.c)
SRCOBJS := $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))
TESTOBJS := $(addprefix $(OBJDIR)/, $(notdir $(TESTS:.c=.o)))
DEPS := $(addprefix $(DEPDIR)/, $(notdir $(SRCS:.c=.d))) + $(addprefix $(DEPDIR)/, $(notdir $(TESTS:.c=.d)))
LIBS := $(wildcard $(LIBDIR)/*.a)

DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

$(EXECUTEFILENAME) : $(SRCOBJS) $(TESTOBJS) | $(BINDIR)
	@$(CC) $^ $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -o $@

$(LIBRARYFILENAME) : $(SRCOBJS) | $(BINDIR)
	@echo "\e[33mGenerate static library($(LIBRARYFILENAME)) from $^\e[m"
	@$(AR) $(LIBRARYFILENAME) $(SRCOBJS)
	@echo ""

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(DEPDIR)/%.d | $(OBJDIR) $(DEPDIR)
	@$(CC) $(DEPFLAGS) $< $(CFLAGS) $(CPPFLAGS) -c -o $@

$(OBJDIR)/%.o : $(TESTDIR)/%.c $(DEPDIR)/%.d | $(OBJDIR) $(DEPDIR)
	@$(CC) $(DEPFLAGS) $< $(CFLAGS) $(CPPFLAGS) -c -o $@

include $(wildcard $(DEPS))

$(DEPS) :

$(BINDIR):
	@mkdir -p $@

$(OBJDIR):
	@mkdir -p $@

$(DEPDIR):
	@mkdir -p $@

$(LIBDIR):
	@mkdir -p $@

.PHONY: all
all : clean build-other $(EXECUTEFILENAME)

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

.PHONY: png
png :
	@gnuplot -e "load './script/gnuplot/plot_png.plt'"
	@echo ""

.PHONY: gif
gif :
	@gnuplot -e "load './script/gnuplot/plot_gif.plt'"
	@echo ""

.PHONY: build-other
build-other:
	@echo "Remove \"$(LIBS)\""
	@$(RM) $(LIBS)
	@for dir in $(MAKEFILESDIR); do \
		cd $$dir; \
		make lib; \
		cd ../..; \
	done
	@echo ""

.PHONY: help
help :
	@echo "option"
	@echo "    (default) : Compile"
	@echo "          all : Crean and Compile"
	@echo "      execute : Execute \"$(EXECUTEFILENAME)\""
	@echo "        clean : Crean (Remove \"$(OBJDIR) $(DEPDIR) $(EXECUTEFILENAME) $(LIBRARYFILENAME)\")"
	@echo "        debug : Compile debug code (define _DEBUG)"
	@echo "          lib : Generate static library"
	@echo "      inspect : Inspect the generated static library"
	@echo "  build-other : Crean and Compile Library"
	@echo "         help : This"
	@echo ""
