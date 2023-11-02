# Number of parallel jobs for compilation
export GNUMAKEFLAGS = -j16

# Project directory
PWD = $(shell pwd)

# Directories
SDK_LIBS_STATIC = $(patsubst %dynamic,%static,$(SDK_LIBS))

# Platform-dependent libraries
PLAT_DEPENDENT_LIB = -lmi_gfx -lmi_sys -lmi_common -ldl 
PLAT_DEPENDENT_LIB_EX = -lmi_disp -lmi_panel 

# MiniGUI libraries
MINIGUI_LIBS = -ljpeg -lz 

# Include directories
SDK_INCS = ./inc
UAPI_INCS = ./inc
INCLUDES = ./common

# Compiler flags
CFLAGS = -I./lv_node/common/libsqlite/include -I./lv_node/hardware/external/lv_node/hardware/external/mbedtls/include/mbedtls/config.hinclude/mbedtls
MODINC = -I./lv_node/common/external/mbedtls/include/mbedtls/ -I./lv_node/common/external/mbedtls/include/

# Linker flags
LDFLAGS = -L$(SDK_LIBS) -L$(SDK_LIBS_STATIC) -L$(PWD)/lib -L/usr/local/lib

# Standard libraries
STDLIBS = -ldl -lm -lz -lpthread -lmi_common -lmi_sys -lmi_wlan -lcjson -Wl,--hash-style=gnu 

# Final linker flags
LIBS = -Wl,-Bdynamic $(MINIGUI_LIBS) $(PLAT_DEPENDENT_LIB_EX) $(PLAT_DEPENDENT_LIB) -Wl,-Bdynamic $(STDLIBS)

# Compiler
CC := arm-linux-gnueabihf-gcc

# LVGL directory
LVGL_DIR_NAME ?= lvgl
LVGL_DIR ?= $(shell pwd)

# Additional compiler flags
CFLAGS += -rdynamic -funwind-tables -I. -I$(SDK_INCS) -I$(PWD)/inc -I$(UAPI_INCS) -I$(INCLUDES) -O3 -g0 -I$(LVGL_DIR)/ -Wall -Wshadow -Wundef -Wmaybe-uninitialized -Wmissing-prototypes -Wall -Wextra -Wno-unused-function -Wundef -Wno-error=strict-prototypes -Wpointer-arith -fno-strict-aliasing -Wno-error=cpp -Wuninitialized -Wmaybe-uninitialized -Wno-unused-parameter -Wno-missing-field-initializers -Wtype-limits -Wsizeof-pointer-memaccess -Wno-format-nonliteral -Wno-cast-qual -Wunreachable-code -Wno-switch-default -Wno-switch-enum -Wreturn-type -Wmultichar -Wformat-security -Wno-ignored-qualifiers -Wno-error=pedantic -Wno-sign-compare -Wno-error=missing-prototypes -Wdouble-promotion -Wclobbered -Wdeprecated -Wempty-body -Wtype-limits -Wstack-usage=1024 -Wno-unused-value -Wno-unused-parameter -Wno-missing-field-initializers -Wuninitialized -Wmaybe-uninitialized -Wall -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wtype-limits -Wsizeof-pointer-memaccess -Wno-format-nonliteral -Wpointer-arith -Wno-cast-qual -Wmissing-prototypes -Wunreachable-code -Wno-switch-default -Wswitch-enum -Wreturn-type -Wmultichar -Wformat-security -Wno-ignored-qualifiers -Wno-sign-compare

# Additional linker flags
LDFLAGS += $(LIBS)

# Target binary
BIN = demossd

# Main source file
MAINSRC = ./main.c

# Include LVGL build files
include $(LVGL_DIR)/lvgl/lvgl.mk
include $(LVGL_DIR)/lv_drivers/lv_drivers.mk
include $(LVGL_DIR)/lv_examples/lv_examples.mk
include $(LVGL_DIR)/lv_node/lv_node.mk

# Object file directory
OBJDIR = $(LVGL_DIR)/obj

# Object file extension
OBJEXT ?= .o

# Object files
AOBJS = $(patsubst %.S,$(OBJDIR)/%.o,$(ASRCS))
COBJS = $(patsubst %.c,$(OBJDIR)/%.o,$(CSRCS))
MAINOBJ = $(patsubst %.c,$(OBJDIR)/%.o,$(MAINSRC))

# Build rules
all: default

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(MODINC) $(CFLAGS) -c $< -o $@ -g
	@echo "CC $<"

default: $(AOBJS) $(COBJS) $(MAINOBJ)
	@$(CC) -o $(BIN) $(MAINOBJ) $(AOBJS) $(COBJS) $(LDFLAGS)
	@mkdir -p $(LVGL_DIR)/bin
	@mv $(BIN) $(LVGL_DIR)/bin/
	@echo "编译成功!!!"
	@echo "编译成功!!!"
	@echo "编译成功!!!"
	@echo "Compilation successful!!!"
	@echo "Binary file $(BIN) is generated in $(LVGL_DIR)/bin/ directory."

clean:
	rm -f $(BIN)
	rm -rf $(OBJDIR) ./bin/*
