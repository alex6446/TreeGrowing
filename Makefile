# Alternative GNU Make workspace makefile autogenerated by Premake

ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug)
  TreeGrowing_config = debug

else ifeq ($(config),release)
  TreeGrowing_config = release

else
  $(error "invalid configuration $(config)")
endif

PROJECTS := TreeGrowing

.PHONY: all clean help $(PROJECTS) 

all: $(PROJECTS)

TreeGrowing:
ifneq (,$(TreeGrowing_config))
	@echo "==== Building TreeGrowing ($(TreeGrowing_config)) ===="
	@${MAKE} --no-print-directory -C . -f TreeGrowing.make config=$(TreeGrowing_config)
endif

clean:
	@${MAKE} --no-print-directory -C . -f TreeGrowing.make clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug"
	@echo "  release"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   TreeGrowing"
	@echo ""
	@echo "For more information, see https://github.com/premake/premake-core/wiki"