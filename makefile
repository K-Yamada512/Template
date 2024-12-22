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
CC := $(or $(ICX_CC), gcc)
CXX :=
RM := rm -rf
CFLAGS := -O1 -Iinclude -Itest -Iparts/create_log/include
CPPFLAGS :=
LDFLAGS := -Llib
LDLIBS := -lm -lclog

# Project-specific Variables
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
PARTSFILENAME := ../../lib/lib$(LIBRARYNAME).a
SRCS := $(wildcard $(SRCDIR)/*.c)
TESTS := $(wildcard $(TESTDIR)/*.c)
SRCOBJS := $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))
TESTOBJS := $(addprefix $(OBJDIR)/, $(notdir $(TESTS:.c=.o)))
DEPS := $(addprefix $(DEPDIR)/, $(notdir $(SRCS:.c=.d))) $(addprefix $(DEPDIR)/, $(notdir $(TESTS:.c=.d)))
LIBS := $(wildcard $(LIBDIR)/*.a)

DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

# Targets
.PHONY: all clean execute debug lib lib-parts inspect inspect-parts png gif build-other help

# Build executable
$(EXECUTEFILENAME) : $(SRCOBJS) $(TESTOBJS) | $(BINDIR)
	@echo "\r\n\e[33;44mBuilding $(EXECUTEFILENAME) ...\e[0m"
	$(CC) $^ $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -o $@
	@echo "\e[33mExecutable $(EXECUTEFILENAME) created.\e[0m"

# Create static library
$(LIBRARYFILENAME) : $(SRCOBJS) | $(BINDIR)
	@echo "\r\n\e[33mGenerating static library ($@) from $^\e[0m"
	$(AR) $@ $^

# Create parts static library
$(PARTSFILENAME) : $(SRCOBJS) | $(BINDIR)
	@echo "\r\n\e[33mGenerating parts static library ($@) from $^\e[0m"
	$(AR) $@ $^

# Compilation rule for source files
$(OBJDIR)/%.o : $(SRCDIR)/%.c $(DEPDIR)/%.d | $(OBJDIR) $(DEPDIR)
	$(CC) $(DEPFLAGS) $< $(CFLAGS) $(CPPFLAGS) -c -o $@

# Compilation rule for test files
$(OBJDIR)/%.o : $(TESTDIR)/%.c $(DEPDIR)/%.d | $(OBJDIR) $(DEPDIR)
	$(CC) $(DEPFLAGS) $< $(CFLAGS) $(CPPFLAGS) -c -o $@

# Include dependency files
-include $(wildcard $(DEPS))

$(DEPS) :

# Create necessary directories
$(BINDIR) $(OBJDIR) $(DEPDIR) $(LIBDIR):
	@mkdir -p $@

# Clean build artifacts
clean :
	@echo "Remove \"$(OBJDIR) $(DEPDIR) $(EXECUTEFILENAME) $(LIBRARYFILENAME)\""
	@$(RM) $(OBJDIR) $(DEPDIR) $(EXECUTEFILENAME) $(LIBRARYFILENAME)
	@echo ""

# Execute the program
execute :
	$(EXECUTEFILENAME)
	@echo ""

# Debug build
debug : CFLAGS += -D_DEBUG
debug : clean $(EXECUTEFILENAME)

# Library targets for main or sub-make
lib : clean $(LIBRARYFILENAME)
ifeq ($(MAKEFILE_LIST),$(firstword $(MAKEFILE_LIST)))
else
lib-parts : clean $(PARTSFILENAME)
endif

# Inspect generated library
inspect :
	nm $(LIBRARYFILENAME)
ifeq ($(MAKEFILE_LIST),$(firstword $(MAKEFILE_LIST)))
else
inspect-parts :
	nm $(PARTSFILENAME)
endif

# Generate PNG plot
png :
	gnuplot -e "load './script/gnuplot/plot_png.plt'"

# Generate GIF plot
gif :
	gnuplot -e "load './script/gnuplot/plot_gif.plt'"

# Build other libraries from subdirectories
build-other:
	@echo "\e[33;44mBuilding other libraries\e[0m"
	@echo "Remove \"$(LIBS)\""
	$(RM) $(LIBS)
	@for dir in $(MAKEFILESDIR); do \
		echo "\r\n\e[33mEntering directory $$dir\e[0m"; \
		(cd $$dir && make lib-parts) || { \
			echo "\e[31mFailed to build library in $$dir\e[0m"; \
			exit 1; \
		}; \
		echo "\e[33mSuccessfully built library in $$dir\e[0m"; \
	done
	@echo ""

all : clean build-other $(EXECUTEFILENAME)

# Help message
help:
	@echo "Makefile options:"
	@echo "  all         : Clean and compile everything"
	@echo "  clean       : Remove build artifacts"
	@echo "  execute     : Run the program"
	@echo "  debug       : Build with debug flags"
	@echo "  lib         : Generate static library"
	@echo "  inspect     : Inspect generated library"
	@echo "  build-other : Build additional libraries"
	@echo "  png         : Generate PNG plots"
	@echo "  gif         : Generate GIF plots"
	@echo "  help        : Show this help message"
