PROGRAM_NAME = GachaKelompok
PROJECT_DIR = .
BUILD_DIR = $(PROJECT_DIR)/build
HOMEDIR = ${HOME}
INSTALL_DIR = $(HOME)/bin
MODE_BUILD = Debug

all:

pre_debug:
	@mkdir -p $(BUILD_DIR)
	cmake -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE \
		-DCMAKE_BUILD_TYPE:STRING=$(MODE_BUILD) \
		-DCMAKE_C_COMPILER:FILEPATH=/usr/bin/clang \
		-DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/clang++ \
		-S$(PROJECT_DIR) \
		-B$(BUILD_DIR) -G "Unix Makefiles"

build: pre_debug
	@echo Building $(PROGRAM_NAME)
	@echo Build dir $(BUILD_DIR)
	cmake --build $(BUILD_DIR) --config $(MODE_BUILD) --target all --

release:
	cmake --build $(BUILD_DIR) --config Release --target all --

install:
	@mkdir -p $(INSTALL_DIR)
	@cp -r $(PROJECT_DIR) $(INSTALL_DIR)

debug:
	gdb -tui -args $(BUILD_DIR)/$(GachaKelompok) -h

run:
	$(BUILD_DIR)/$(PROGRAM_NAME) -h

clean:
	rm -rf $(BUILD_DIR)
