LIB_INSTALL=/usr/lib
INCLUDE_INSTALL=/usr/include

# destination for object files
OBJDIR = build/obj

# c compiler
CC ?= clang
# flags for c compiler
CFLAGS := $(CFLAGS) -Wall -Wextra -pedantic -std=c99 #-Os

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

all: clean nxdraw_shared nxdraw_static

nxdraw_static: $(OBJS)
	mkdir -p ./build/static/nxdraw
	ar rcs ./build/static/nxdraw/libnxdraw.a $(OBJS)

nxdraw_shared: $(OBJS)
	mkdir -p ./build/dynamic/nxdraw
	$(CC) -Wl,--version-script=nxdraw.version -shared $(CIFLAGS) $(CLFLAGS)  $(CFLAGS) -o ./build/dynamic/nxdraw/libnxdraw.so $(OBJS)

install:
	mkdir -p ${INCLUDE_INSTALL}/nxdraw
	mkdir -p ${INCLUDE_INSTALL}/nxdraw/fonts
	cp ./include/nxdraw/nxdraw.h ${INCLUDE_INSTALL}/nxdraw/
	cp ./include/nxdraw/event.h ${INCLUDE_INSTALL}/nxdraw/
	cp ./include/nxdraw/fonts/testfont.h ${INCLUDE_INSTALL}/nxdraw/fonts

	mkdir -p ${LIB_INSTALL}/nxdraw
	cp ./build/dynamic/nxdraw/libnxdraw.so ${LIB_INSTALL}/


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
