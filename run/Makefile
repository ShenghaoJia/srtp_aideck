MODEL_PREFIX=model
AT_INPUT_WIDTH=324
AT_INPUT_HEIGHT=244
AT_INPUT_COLORS=1
# IMAGE=$(CURDIR)/samples/ripe.pgm

# io=host

include model_decl.mk

CLUSTER_STACK_SIZE=4028
CLUSTER_SLAVE_STACK_SIZE=1024
TOTAL_STACK_SIZE=$(shell expr $(CLUSTER_STACK_SIZE) \+ $(CLUSTER_SLAVE_STACK_SIZE) \* 7)
MODEL_L1_MEMORY=$(shell expr 60000 \- $(TOTAL_STACK_SIZE))
MODEL_L2_MEMORY=250000
MODEL_L3_MEMORY=8388608

$(info 123... $(MODEL_GEN_C))

APP_SRCS += $(MODEL_PREFIX).c $(MODEL_GEN_C) $(MODEL_COMMON_SRCS) $(CNN_LIB)

APP_CFLAGS += -g -O1 -mno-memcpy -fno-tree-loop-distribute-patterns
APP_CFLAGS += -I. -I$(MODEL_COMMON_INC) -I$(TILER_EMU_INC) -I$(TILER_INC) $(CNN_LIB_INCLUDE) -I$(MODEL_BUILD)
APP_CFLAGS += -DPERF -DAT_MODEL_PREFIX=$(MODEL_PREFIX) $(MODEL_SIZE_CFLAGS)
APP_CFLAGS += -DSTACK_SIZE=$(CLUSTER_STACK_SIZE) -DSLAVE_STACK_SIZE=$(CLUSTER_SLAVE_STACK_SIZE)
# APP_CFLAGS += -DAT_IMAGE=$(IMAGE)
APP_CFLAGS += -DUSE_HYPER

READFS_FILES=$(abspath $(MODEL_TENSORS))

clean::
	rm -rf $(CURDIR)/BUILD

include $(RULES_DIR)/pmsis_rules.mk
