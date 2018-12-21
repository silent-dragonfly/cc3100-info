.PHONY: all clean

LIB_PATH := simple-link

APP_NAME := cc3100-info.exe
VPATH = src:$(LIB_PATH)/simple_link/source
SRCS := $(wildcard src/*.c) $(wildcard $(LIB_PATH)/simple_link/source/*.c)

CC := gcc

CPPFLAGS := -D GCC_BUILD -D _CONSOLE -DMINGW_ENV=1 \
 -I"/c/MinGW/include" \
 -I"$(LIB_PATH)/simple_link" \
 -I"$(LIB_PATH)/simple_link/include" \
 -I"$(LIB_PATH)/simple_link/source" \
 -I"$(LIB_PATH)/simple_link_studio"
CFLAGS := -O0 -w -Wall -Wextra -Werror

LDFLAGS := -L"$(LIB_PATH)/simple_link_studio"
LDLIBS := -lws2_32 -Wl,--start-group -l SimpleLinkStudio -l ftd2xx -Wl,--end-group


CLEAN_TARGETS ?= Release Debug
RELEASE ?= false
ifeq ($(RELEASE),true)
OUT_DIR = Release
CPPFLAGS += -D NDEBUG
else
OUT_DIR = Debug
CPPFLAGS += -D _DEBUG
CFLAGS += -g
endif

all: $(OUT_DIR) $(OUT_DIR)/$(APP_NAME)

$(OUT_DIR):
	mkdir -p $@

CLEAN_TARGETS += autodependencies.d
-include autodependencies.d
autodependencies.d: $(SRCS)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MM $^ | sed -e 's/\w*\.o/$(OUT_DIR)\/\0/' > $@

$(OUT_DIR)/$(APP_NAME): $(addprefix $(OUT_DIR)/, $(notdir $(SRCS:.c=.o)))
	$(CC) $(LDFLAGS) $^ $(LDLIBS) --output $@

$(OUT_DIR)/%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< --output $@

clean:
	rm -rf $(CLEAN_TARGETS)
