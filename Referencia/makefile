PROJECT_MAIN := Scheduler
CXX := g++

SRC_DIR := src
INC_DIR := inc
OBJ_DIR := obj

FLAGS := -I./$(INC_DIR)/

SRC := $(wildcard $(SRC_DIR)/*.cpp)
INC := $(wildcard $(INC_DIR)/*.h $(INC_DIR)/*.hpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

all: $(PROJECT_MAIN)

$(PROJECT_MAIN): $(OBJ)
	$(CXX) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INC) $(OBJ_DIR)
	$(CXX) -o $@ -c $< $(FLAGS)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)
	rm $(PROJECT_MAIN)