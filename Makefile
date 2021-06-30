CC	:= clang
CXX	:= /usr/bin/clang++

CCV := $(shell $(CC) -dumpversion)

PREFIX       := /usr/bin
HOSTCC       := $(PREFIX)/clang
OS           := $(shell uname -s)
HOSTARCH     ?= $(shell $(HOSTCC) -dumpmachine | cut -f1 -d- | sed -e s,i[3456789]86,ia32, -e 's,armv[67].*,arm,' )
ARCH         ?= $(shell $(HOSTCC) -dumpmachine | cut -f1 -d- | sed -e s,i[3456789]86,ia32, -e 's,armv[67].*,arm,' )

ASMFLAGS := -O3 \
			-Wall -Wextra \
			-m64 -c -g

CFLAGS := \
		-c \
		-g \
		-Wall \
		-Wextra \
		-std=c11 \
		-O3 \
		-fno-stack-protector \
		-fno-exceptions \
		-ffreestanding \
		-nostdlib \
		-Wall -Wextra \
		-I ./include

CXXFLAGS := \
		-c \
		-g \
		-Wall \
		-Wextra \
		-std=c++20 \
		-O3 \
		-fno-stack-protector \
		-fno-exceptions \
		-ffreestanding \
		-nostdlib \
		-Wall -Wextra \
		-I ./include

SRC_DIR		:= ./code
BUILD_DIR 	:= build

CFILES 		:= $(shell find $(SRC_DIR)/ -type f -name '*.c')
CXXFILES 	:= $(shell find $(SRC_DIR)/ -type f -name '*.cpp')
ASMFILES 	:= $(shell find $(SRC_DIR)/ -name '*.s')
OBJS    	:= $(addprefix $(BUILD_DIR)/, $(CFILES:.c=.o))
OBJS    	+= $(addprefix $(BUILD_DIR)/, $(CXXFILES:.cpp=.o))
OBJS  		+= $(addprefix $(BUILD_DIR)/, $(patsubst ./%.s, ./%.s.o,$(ASMFILES)))
DIRS 		:= $(wildcard ./*)

T_C_OBJECT_FILES += $(addprefix $(BUILD_DIR)/, $(patsubst %.c, %.o, $(notdir $(wildcard tests/*.c))))
T_CPP_OBJECT_FILES += $(addprefix $(BUILD_DIR)/, $(patsubst %.cpp, %.o, $(notdir $(wildcard tests/*.cpp))))

$(BUILD_DIR)/libcerberus.a: setup $(OBJS)
	ar rcs $@ $(OBJS)

all: $(BUILD_DIR)/libcerberus.a test

test: $(T_C_OBJECT_FILES) $(T_CPP_OBJECT_FILES)
	$(CXX) $^ $(BUILD_DIR)/libcerberus.a -o build/CerberusBuilder

setup:
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BUILD_DIR)/$(SRC_DIR)/$(ARCH)/%.s.o: $(SRC_DIR)/$(ARCH)/%.s
	@mkdir -p $(@D)
	$(CC) $(ASMFLAGS) $< -o $@

$(BUILD_DIR)/$(SRC_DIR)/$(ARCH)/sseavx/%.o: $(SRC_DIR)/$(ARCH)/sseavx/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(SRC_DIR)/$(ARCH)/sseavx/%_sse.o: $(SRC_DIR)/$(ARCH)/sseavx/%_sse.cpp
	@mkdir -p $(@D)
	$(CXX) -mavx -mavx2 $(CXXFLAGS) $< -o $@


$(BUILD_DIR)/$(SRC_DIR)/$(ARCH)/sseavx/%_avx.o: $(SRC_DIR)/$(ARCH)/sseavx/%_avx.cpp
	@mkdir -p $(@D)
	$(CXX) -mavx -mavx2 $(CXXFLAGS) $< -o $@


$(BUILD_DIR)/%.o: tests/%.cpp
	$(CXX) -c -g -Wall -Wextra -O0 -std=c++20 -I ./include $< -o $@

$(BUILD_DIR)/%.o: tests/%.c
	$(CC) -c -g -Wall -Wextra -O0 -std=c11 -I ./include $< -o $@
