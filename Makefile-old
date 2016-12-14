BIN_DIR = bin
BUILD_DIR = build
DEPS_DIR = $(BUILD_DIR)/dep
INCLUDE_DIR = include
SRC_DIR = src
TEST_DIR = test
DOC_DIR = doc
CLI_ELF = funcopt_cli
TEST_ELF = funcopt_unittest
GTEST_DIR = gtest

CPPFLAGS += -isystem $(GTEST_DIR)/include -I $(INCLUDE_DIR)	# preprocessor
CXXFLAGS += -g -Wall -Wextra -pthread -std=c++14		# compiler
# LDFLAGS += -lm

SRC_EXT = cc
# SOURCES = $(shell find $(SRC_DIR) -type f -name *.$(SRC_EXT))
SOURCES = $(wildcard $(SRC_DIR)/*.$(SRC_EXT))
OBJECTS = $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(SOURCES:.$(SRC_EXT)=.o))
TEST_OBJECTS = $(subst $(CLI_ELF),$(TEST_ELF),$(OBJECTS)) $(BUILD_DIR)/gtest_main.a
GTEST_BINS = $(addprefix $(BUILD_DIR)/,gtest_main.a gtest_main.o gtest-all.o)
DEPS = $(patsubst $(SRC_DIR)/%,$(DEPS_DIR)/%,$(SOURCES:.$(SRC_EXT)=.d))
DEPS += $(DEPS_DIR)/$(TEST_ELF).d

# .PHONY: all
# all: $(BIN_DIR)/$(CLI_ELF)

$(BIN_DIR)/$(CLI_ELF): $(OBJECTS)
	@echo " Linking $(CLI_ELF)..."
	$(LINK.cc) $^ -o $@

-include $(DEPS)

$(DEPS_DIR)/%.d: $(SRC_DIR)/%.$(SRC_EXT) 
	@mkdir -p $(DEPS_DIR)
	@echo " Composing dependencies for $<..."
	@$(CPP) $(CPPFLAGS) $< -MM -MT $(subst /dep,,$(@:.d=.o)) > $@

# Pattern rules with multiple targets are explicitly required to build all of
# their targets in a single invocation of command.
$(DEPS_DIR)/%.d: $(TEST_DIR)/%.$(SRC_EXT)
	@mkdir -p $(DEPS_DIR)
	@echo " Composing dependencies for $<..."
	@$(CPP) $(CPPFLAGS) $< -MM -MT $(subst /dep,,$(@:.d=.o)) > $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.$(SRC_EXT)
	@mkdir -p $(BUILD_DIR)
	@echo " Compiling $<..."
	$(COMPILE.cc) -o $@ $<

# --- Google Tests ---# {{{
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
		$(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

$(BUILD_DIR)/gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
	    $(GTEST_DIR)/src/gtest-all.cc -o $(BUILD_DIR)/gtest-all.o

$(BUILD_DIR)/gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
	    $(GTEST_DIR)/src/gtest_main.cc -o $(BUILD_DIR)/gtest_main.o

$(BUILD_DIR)/gtest.a : $(BUILD_DIR)/gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

$(BUILD_DIR)/gtest_main.a : $(BUILD_DIR)/gtest-all.o $(BUILD_DIR)/gtest_main.o
	$(AR) $(ARFLAGS) $@ $^
# ------# }}}

tests: $(BIN_DIR)/$(TEST_ELF)

$(BIN_DIR)/$(TEST_ELF): $(TEST_OBJECTS)
	@echo " Linking unit tests..."
	$(LINK.cc) $^ -o $@

$(BUILD_DIR)/$(TEST_ELF).o: $(TEST_DIR)/$(TEST_ELF).$(SRC_EXT)
	@echo " Compiling unit tests..."
	$(COMPILE.cc) -o $@ $<

.PHONY: clean
clean: cleandep
	@echo " Cleaning..."
	$(RM) $(OBJECTS) $(TEST_OBJECTS) $(GTEST_BINS) $(BIN_DIR)/$(CLI_ELF) $(BIN_DIR)/$(TEST_ELF)
	$(RM) -r $(DOC_DIR)/*

.PHONY: cleandep
cleandep:
	@echo " Cleaning dependencies..."
	$(RM) $(DEPS)
