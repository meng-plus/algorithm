# ./demo/Makefile

CC = gcc
CFLAGS = -Wall -Wextra -O2 -g -fPIC -Wunused-parameter
INCLUDES = -I../src/
LIBS = -lcheck -lm -lpthread -lrt -lsubunit

# 目标文件路径
BUILD_DIR = ./build
SRCDIR = ../src/algorithms
OBJDIR = $(BUILD_DIR)/obj
TESTDIR =  ./
# 确保目标文件夹存在
$(shell mkdir -p $(OBJDIR))

# 源文件
SRCS = $(wildcard $(SRCDIR)/*.c)

# 测试文件
SRC_TEST = $(wildcard *.c)
# 目标文件
TARGET = $(patsubst %.c, $(BUILD_DIR)/%.out, $(SRC_TEST))
# 生成的可执行文件
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

all: $(TARGET)
	echo $(TARGET)

# 链接 demo_app 可执行文件
$(BUILD_DIR)/%.out: $(OBJS) $(BUILD_DIR)/%.o
	$(CC) $^ $(LDFLAGS) $(LIBS)  $(INCLUDES)  -o $@

# 编译目标文件
$(BUILD_DIR)/%.o: $(TESTDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# 编译目标文件
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(OBJDIR)/*.o

test: $(BUILD_DIR)/test_algorithms.out
	$<

.PHONY: clean all test

# end of Makefile
