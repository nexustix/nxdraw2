# destination for object files
OBJDIR = build/obj

# c compiler
CC ?= clang
# flags for c compiler
CFLAGS := $(CFLAGS)  -g -Wall -Wextra -pedantic #-Os

# get list of .c files
C_SOURCES = $(shell find ./src/nxdraw -name "*.c")

# list of include directories
C_INCLUDES=$\
	include/\
	trd/include/\

# list of things to link
C_LINKS=$\
	glfw\
	GL\

# generate include flags
CIFLAGS= $(addprefix -I, $(C_INCLUDES))

# generate link flags
CLFLAGS= $(addprefix -l, $(C_LINKS))

# set search paths for .c source files
vpath %.c $(addsuffix :,$(sort $(dir $(C_SOURCES))))

# generate list of object files created from .c files
OBJS := $(addprefix $(OBJDIR)/,$(notdir $(C_SOURCES)))
OBJS := $(OBJS:.c=.o)

# create all .o files
# all: $(OBJDIR) $(OBJS)

#run: kellerspiel
#	./kellerspiel

#debug: kellerspiel
#	nemiver ./kellerspiel

syslib_path="./lib/"
sysinclude_path="./lib/"

all: nxdraw_shared nxdraw_static

nxdraw_static: $(OBJS)
	ar rcs libnxdraw.a $(OBJS)

nxdraw_shared: $(OBJS)
	$(CC) -shared $(CIFLAGS) $(CLFLAGS) $(CFLAGS) -o libnxdraw.so $(OBJS)

install:


# rule that can turn any .c file into an .o file in object directory
$(OBJDIR)/%.o : %.c
	@echo "CC [$@] ${<}"
	@$(CC) $(CIFLAGS) $(CLFLAGS) $(CFLAGS) -o $@ -c $<

# all .o files need the object directory
$(OBJS): | $(OBJDIR)

# if object directory is needed, create it
$(OBJDIR):
	mkdir -p $(OBJDIR)


clean:
	rm -f -r ./build
	rm -f ./libnxdraw.so
	rm -f ./libnxdraw.a

.PHONY: all run debug kellerspiel clean
