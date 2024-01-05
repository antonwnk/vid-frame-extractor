CXX=g++
RM=rm -f
MKDIR=mkdir -p
CPPFLAGS=-g -Wall -Wextra $(shell pkg-config --cflags opencv4)
CPPFLAGS+=-Icxxopts
LDLIBS=-g $(shell pkg-config --libs opencv4)

SRCS=main.cc
OBJS=$(subst .cc,.o,$(SRCS))

TARGET_DIR=target
TARGET=$(TARGET_DIR)/extractor

all: $(TARGET)

$(TARGET): $(TARGET_DIR) $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDLIBS)

$(TARGET_DIR):
	$(MKDIR) $(TARGET_DIR)

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) *~
