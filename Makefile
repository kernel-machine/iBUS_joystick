CC=gcc #Compilatore da utilizzare
OPT = -Wall -O1
SRC_DIR := src
OBJ_DIR := obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
EXEC = iBUS_js

$(EXEC): $(OBJ_FILES)
	$(CC) -o $@ $^ $(OPT)

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) -c -o $@ $< $(OPT)

clean:
	rm -rfv $(OBJ_DIR) $(EXEC)