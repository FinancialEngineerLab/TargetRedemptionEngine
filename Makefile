.SUFFIXES :
.SUFFIXES : .o .c

CC = gcc

SELF = basic.mk
MAKEFILE = Makefile
DIRS = $(shell find . -mindepth 1 -maxdepth 1 -type d | grep -v "\/\.")
SELFS = $(addsuffix /$(SELF), $(DIRS))
MAKEFILES = $(addsuffix /$(MAKEFILE), $(DIRS))

SDE_WA_SELFS = $(shell find . -name '$(SELF)')
SDE_WA_MAKEFILES = $(shell find . -name '$(MAKEFILE)')
SDE_WA_SRC = $(shell find . -name '*.c')
SDE_WA_OBJS =  $(SDE_WA_SRC:.c=.o)
SDE_WA = sde_wa
TARGET_SDE_WA = lib$(SDE_WA).a
TARGETS = $(TARGET_SDE_WA) 


$(TARGET_SDE_WA): create-objs
	rm -f $@
	ar cvr $@ $(SDE_WA_OBJS)

Makefiles: $(SELFS)
	for dir in $(DIRS) ; do	\
	 cd $$dir	;\
	 make -f $(SELF) $(MAKEFILE)	;\
	 cd ..	;\
	done

create-objs: $(SDE_WA_SELFS)
	for dir in $(DIRS); do	\
		cd $$dir	;\
		make	;\
		cd ..	;\
	done


.PHONY: all
all: clean $(TARGETS)

.PHONY: clean
clean :
	rm -f $(SDE_WA_OBJS) $(TARGETS)

