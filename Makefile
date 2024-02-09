CC = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Wpedantic -Werror -g
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

APP_NAME = chess
EXT = .cpp

SRC_DIR = src
OBJ_DIR = obj
DEP_DIR = dep

SRC = $(shell find $(SRC_DIR) -name *$(EXT))
OBJ = $(SRC:$(SRC_DIR)/%$(EXT)=$(OBJ_DIR)/%.o)
DEP = $(OBJ:$(OBJ_DIR)/%.o=$(DEP_DIR)/%.d)

all: $(APP_NAME)

$(APP_NAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%$(EXT)
	@mkdir -p $(@D)
	$(CC) $(CXXFLAGS) -o $@ -c $<

$(DEP_DIR)/%.d: $(SRC_DIR)/%$(EXT)
	@mkdir -p $(@D)
	$(CC) $(CXXFLAGS) -MM -MT $(@:$(DEP_DIR)/%.d=$(OBJ_DIR)/%.o) $< > $@

-include $(DEP)

clean:
	rm -rf $(OBJ_DIR) $(DEP_DIR)

fclean: clean
	rm -f $(APP_NAME)

.PHONY: all fclean clean

SRC_MODIFIED = $(shell git status --porcelain $(SRC_DIR) | grep -E '^(M| M)' | awk '{print $$2}')
OBJ_MODIFIED = $(SRC_MODIFIED:$(SRC_DIR)/%$(EXT)=$(OBJ_DIR)/%.o)
DEP_MODIFIED = $(OBJ_MODIFIED:$(OBJ_DIR)/%.o=$(DEP_DIR)/%.d)

ifneq ($(strip $(SRC_MODIFIED)),)
$(APP_NAME): $(OBJ_MODIFIED)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_MODIFIED): $(SRC_MODIFIED)
	@mkdir -p $(@D)
	$(CC) $(CXXFLAGS) -o $@ -c $<

$(DEP_MODIFIED): $(SRC_MODIFIED)
	@mkdir -p $(@D)
	$(CC) $(CXXFLAGS) -MM -MT $(@:$(DEP_DIR)/%.d=$(OBJ_DIR)/%.o) $< > $@

-include $(DEP_MODIFIED)
endif
