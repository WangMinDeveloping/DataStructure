CXX=g++
AR=ar
OUT_NAME=DoublyList.a
OUT_PATH=../lib/
SRC_PATH=./
OBJ_PATH=../obj/
INCLUDE_PATH=../include/

DEBUG_PATH=debug/
RELEASE_PATH=release/
SRC_FILE=$(wildcard $(SRC_PATH)*.cpp)
ALL_FILE=$(notdir $(SRC_FILE))
OBJ_FILE=$(patsubst %.cpp,%.o,$(ALL_FILE))

DEBUG_FLAGS=-g -ggdb3 -Wall -fPIC -Wl,-rpath='./' --std=c++11
RELEASE_FLAGS=-O2 -fPIC -Wl,-rpath='./' --std=c++11

DEBUG_ARFLAGS=cqs
RELEASE_ARFLAGS=cqs

OUT_DEBUG_FILE=$(OUT_PATH)$(DEBUG_PATH)$(OUT_NAME)
OUT_RELEASE_FILE=$(OUT_PATH)$(RELEASE_PATH)$(OUT_NAME)

OBJ_RELEASE_FILE=$(addprefix $(OBJ_PATH)$(RELEASE_PATH),$(notdir $(OBJ_FILE)))
OBJ_DEBUG_FILE=$(addprefix $(OBJ_PATH)$(DEBUG_PATH),$(notdir $(OBJ_FILE)))

INC_PATH=
LIB_DEBUG_FILE=
LIB_RELEASE_FILE=

all: debug release publish

debug: pre_debug

release: pre_release

$(OUT_DEBUG_FILE) : $(OBJ_DEBUG_FILE)
	$(AR) $(DEBUG_ARFLAGS) $(addprefix $(OBJ_PATH)$(DEBUG_PATH),$(notdir $^)) $@

$(OUT_RELEASE_FILE) : $(OBJ_RELEASE_FILE)
	$(AR) $(RELEASE_ARFLAGS) $(addprefix $(OBJ_PATH)$(RELEASE_PATH),$(notdir $^)) $@

$(OBJ_PATH)$(DEBUG_PATH)%.o : %.cpp
	$(CXX) -c $(DEBUG_FLAGS) $(INC_PATH) $(SRC_PATH)$< -o $@
$(OBJ_PATH)$(RELEASE_PATH)%.o : $(SRC_PATH)%.cpp
	$(CXX) -c $(RELEASE_FLAGS) $(INC_PATH) $(SRC_PATH)$< -o $@

pre_debug:
	-$(shell mkdir $(OBJ_PATH) -p)
	-$(shell mkdir $(OBJ_PATH)$(DEBUG_PATH) -p)
	-$(shell mkdir $(OUT_PATH) -p)
	-$(shell mkdir $(INCLUDE_PATH) -p)
	-$(shell mkdir $(OUT_PATH)$(DEBUG_PATH) -p)

pre_release:
	-$(shell mkdir $(OBJ_PATH) -p)
	-$(shell mkdir $(OBJ_PATH)$(RELEASE_PATH) -p)
	-$(shell mkdir $(OUT_PATH) -p)
	-$(shell mkdir $(OUT_PATH)$(RELEASE_PATH) -p)

publish:
	-$(shell mkdir $(INCLUDE_PATH) -p)
	-$(shell cp ./doublyList.h $(INCLUDE_PATH) -p)
	-$(shell cp ./doublyListNode.h $(INCLUDE_PATH) -p)
	-$(shell cp ./doublyListIterator.h $(INCLUDE_PATH) -p)
clean:
	@echo " "
	@echo "make clean"
	@echo " "
	$(shell rm $(OBJ_PATH) -rf)
	$(shell rm $(OUT_PATH)$(DEBUG_PATH)$(OUT_NAME) -f)
	$(shell rm $(OUT_PATH)$(RELEASE_PATH)$(OUT_NAME) -f)
