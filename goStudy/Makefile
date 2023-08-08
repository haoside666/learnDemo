TARGET			= main
DEBUG_TARGET	= $(TARGET).debug
RELEASE_TARGET	= $(TARGET).release
SRC 			= $(wildcard *.go)
GO             ?= go
BUILD_DEBUG_FLAGS    := -gcflags=all="-N -l" -ldflags "-s -w -compressdwarf=false"
BUILD_RElEASE_FLAGS  :=


## build: build the target
build: $(TARGET)
$(TARGET):$(SRC)
	$(GO) build $(BUILD_RElEASE_FLAGS) -o $@ $^

## release: build release version of the target,strip symbol table and debug information
release: $(RELEASE_TARGET)
$(RELEASE_TARGET):$(TARGET)
	strip -o $@ $^

## debug: build debug version of the target
debug: $(DEBUG_TARGET)
$(DEBUG_TARGET):$(SRC)
	$(GO) build $(BUILD_DEBUG_FLAGS) -o $@ $^

## all: build debug and release and default version of the target
all:$(RELEASE_TARGET) $(DEBUG_TARGET)

## clean: clean the intermediate file
clean:
	rm -rf $(TARGET) $(TARGET).release $(TARGET).debug


## help: print this help message
help: ./Makefile
	@echo -e "\nUsage: make <TARGETS> ...\n\nTargets:"
	@sed -n 's/^##//p' $< | column -t -s ':' | sed -e 's/^/ /'
	@echo

.PHONY: build release debug all clean help
