APP_NAME := MTD12-X
MAJOR := 0
MINOR := 1

TOOLCHAIN := arm-none-eabi
CC := $(TOOLCHAIN)-gcc

# CMSIS
CMSIS_PATH   := ./../../CMSIS_6/CMSIS
STARTUP_PATH := ./../../SAMC21_DFP/3.8.119/samc21/gcc/gcc
LD_PATH      := ./../../SAMC21_DFP/3.8.119/samc21/gcc/gcc
DFP_PATH     := ./../../SAMC21_DFP/3.8.119/samc21

# ARM_MATH support
CMSIS_DSP_PATH := ./../../CMSIS-DSP

# apps source folder
SRC_PATH := ./src
INC_PATH := ./inc
OBJ_PATH := ./obj
LIB_PATH := ./../../libs

# ARM CORTEX-M0+ CMSIS startup file
startup_src += $(wildcard $(STARTUP_PATH)/startup_samc21g15a.c)
#startup_src += $(wildcard $(STARTUP_PATH)/startup_samc21j18a.c)
startup_obj += $(patsubst $(STARTUP_PATH)/%.c, $(OBJ_PATH)/cmsis/%.o, $(startup_src))

# ARM DSP, Math support
arm_dsp_src += $(shell find $(CMSIS_DSP_PATH)/Source -name *.c)
arm_dsp_obj += $(patsubst $(CMSIS_DSP_PATH)/%.c, $(OBJ_PATH)/cmsis-dsp/%.o, $(arm_dsp_src))

# FreeRTOS support
# freertos_src +=
# freertos_obj +=

# apps libs foldes @ ./libs/[LIB_NAME]
libs += modbus
libs += nvm
LIB_INC := $(foreach lib, $(libs), -I$(LIB_PATH)/$(lib))

# apps libs
libs_src += $(foreach \
	lib_name, \
	$(libs), \
	$(shell find $(LIB_PATH)/$(lib_name) -name *.c) \
)
libs_obj += $(patsubst $(LIB_PATH)/%.c, $(OBJ_PATH)/libs/%.o, $(libs_src))

# apps src
headers += $(shell find $(INC_PATH) -name *.h)
headers += $(shell find $(SRC_PATH) -name *.h)
src := $(shell find $(SRC_PATH) -name *.c)
obj += $(patsubst $(SRC_PATH)/%.c, $(OBJ_PATH)/%.o, $(src))
APP_INC := $(foreach \
	inc,\
	$(sort $(dir $(src)) $(dir $(headers))),\
	-I$(inc)\
)

#linker_script := $(LD_PATH)/samc21j18a_flash.ld
linker_script := $(LD_PATH)/samc21g15a_flash.ld
specs := --specs=nosys.specs
mcu := -mcpu=cortex-m0plus -mfloat-abi=soft -mthumb -std=gnu2x
debug := -g -gdwarf-4 -O0

CFLAGS += $(mcu) $(specs)

#CFLAGS += -DDONT_USE_CMSIS_INIT -D__SAMC21J18A__ -DUSE_HARMONY_V3 -D_NVM_SAMC21_ -DARM_MATH_CM0PLUS
CFLAGS += -DDONT_USE_CMSIS_INIT -D__SAMC21G15A__ -DUSE_HARMONY_V3 -D_NVM_SAMC21_ -DARM_MATH_CM0PLUS
# CMSIS INSTANCE include
CFLAGS += \
	-I$(CMSIS_PATH)/Core/Include \
	-I$(CMSIS_DSP_PATH)/Include \
	-I$(CMSIS_DSP_PATH)/PrivateInclude \
	-I$(DFP_PATH)/include \
	-I$(DFP_PATH)/include/component \
	-I$(DFP_PATH)/include/instance \

# LIBS include
CFLAGS += $(LIB_INC)

# apps include 
CFLAGS += $(APP_INC)

CFLAGS += -Wall -Werror=implicit-function-declaration 
CFLAGS += $(debug)
CFLAGS += -c -o

LDFLAGS += $(mcu) $(specs)
#LDFLAGS += -DDONT_USE_CMSIS_INIT -D__SAMC21J18A__
LDFLAGS += -DDONT_USE_CMSIS_INIT -D__SAMC21G15A__ -DARM_MATH_CM0PLUS
LDFLAGS += -lc -lm -lg -lgcc -lrdimon -lnosys
LDFLAGS += -Wl,--gc-sections -Wl,--print-memory-usage -Wl,--no-warn-rwx-segments -Wl,--cref
#LDFLAGS += -Wl,--print-gc-sections # printf all object files
LDFLAGS += -Wl,--defsym,__stack_size=0x0400 -Wl,-Map=./$(APP_NAME).map
LDFLAGS += $(debug)

# LINKER DESCIPRTOR
LDFLAGS += -T$(linker_script)

.PHONY : all

# build object files
objs += $(startup_obj)
objs += $(obj)
objs += $(libs_obj)
#objs += $(arm_dsp_obj)
all: dump_info check_obj_path $(APP_NAME).elf $(APP_NAME).hex
	@echo done!

clean:
	rm ./obj/* -rf
	rm ./$(APP_NAME).elf
	rm ./$(APP_NAME).hex
	rm ./$(APP_NAME).map

dump_info:
	@echo "----------------------------------------"
	@echo "---- ARM CortexM0+ SDK by Ryan Lin  ----"
	@echo "----------------------------------------"

path := $(dir $(objs))
check_obj_path:
	@mkdir -p $(path)

# ELF
$(APP_NAME).elf : $(objs)
	@$(CC) $(objs) $(LDFLAGS) -o ./$@

# HEX
$(APP_NAME).hex : $(APP_NAME).elf
	$(TOOLCHAIN)-objcopy $< -Oihex $@

# CMSIS STARTUP .o RULES
$(OBJ_PATH)/cmsis/%.o : $(STARTUP_PATH)/%.c
	@echo $(CC) $<
	@$(CC) $< $(CFLAGS) $@

# CMSIS-DSP .o RULES
$(OBJ_PATH)/cmsis-dsp/%.o : $(CMSIS_DSP_PATH)/%.c
	@echo $(CC) $<
	@$(CC) $< $(CFLAGS) $@

# LIBS .o RULES
$(OBJ_PATH)/libs/%.o : $(LIB_PATH)/%.c
	@echo $(CC) $<
	@$(CC) $< $(CFLAGS) $@	

# FreeRTOS .o RULES
#
#

# USER APPS .o RULES
$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	@echo $(CC) $<
	@$(CC) $< $(CFLAGS) $@
