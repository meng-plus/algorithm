# ./demo/Makefile

CC = gcc
CFLAGS = -Wall -Wextra -O2 -g -fPIC
INCLUDES = -I../src/algorithms
LIBS = -lcheck -lm -lpthread -lrt -lsubunit

# 目标文件路径
BUILD_DIR = ./build
SRCDIR = ../src/algorithms
OBJDIR = $(BUILD_DIR)/obj

# 确保目标文件夹存在
$(shell mkdir -p $(OBJDIR))

# 源文件
SRCS = $(wildcard $(SRCDIR)/*.c) $(wildcard *.c)

# 目标文件
TARGET = $(BUILD_DIR)/test_cubic_fit.out
# 生成的可执行文件
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

all: $(TARGET)

# 链接 demo_app 可执行文件
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS) $(LIBS)  $(INCLUDES)

# 编译目标文件
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/%.o: ../%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(OBJDIR)/*.o

test: $(TARGET)
	$(TARGET)

.PHONY: clean all test

# end of Makefile
