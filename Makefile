# Makefile for lemos

# output
OUT=build
KERNEL=kernel.bin

CSRCS := $(wildcard *.c)
ASRCS := $(wildcard *.S)
COBJS := $(patsubst %.c,${OUT}/%.o,$(CSRCS))
AOBJS := $(patsubst %.S,${OUT}/%.o,$(ASRCS))

# header files
DEPS := $(wildcard *.h)

ifndef NSMP
NSMP = 1
endif

# qemu
QEMU=qemu-system-riscv64
QFLAGS= -nographic -smp ${NSMP} -machine virt -bios none

# gcc
CFLAGS+= -nostdlib -fno-builtin -Wall -fPIC
CFLAGS+= -march=rv64g -mabi=lp64

GCCPRIFIX=riscv64-unknown-elf-
CC=${GCCPRIFIX}gcc

# ld
LDFLAGS=-T kernel.ld

# shell
MKDIR=mkdir -p
RM = rm -rf

.DEFAULT_GOAL := all

all: ${OUT} ${OUT}/${KERNEL}

# generate out directory
${OUT}:
	@${MKDIR} $@

${OUT}/${KERNEL}: ${AOBJS} ${COBJS}
	${CC} ${CFLAGS} ${LDFLAGS} $^ -o $@

# generate OBJS with dependency on headers
${OUT}/%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

${OUT}/%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	@${RM} ${OUT}

run: all
	@${QEMU} -M ? | grep virt >/dev/null || exit
	@echo "Press Ctrl-A and then X to exit QEMU"
	@echo "------------------------------------"
	@${QEMU} ${QFLAGS} -kernel ${OUT}/${KERNEL}

# phony target to display build info
.PHONY: info
info:
	@echo "C source files: $(CSRCS)"
	@echo "Assembly source files: $(ASRCS)"
	@echo "Header files: $(DEPS)"
	@echo "Output directory: $(OUT)"

