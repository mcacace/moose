###############################################################################
################### MOOSE Application Standard Makefile #######################
###############################################################################
#
# Optional Environment variables
# MOOSE_DIR     - Root directory of the MOOSE project
# MODULE_DIR       - Location of the MOOSE modules directory
# FRAMEWORK_DIR - Location of the MOOSE framework
#
###############################################################################
MODULE_DIR         ?= $(shell dirname `pwd`)
MOOSE_DIR          ?= $(shell dirname $(MODULE_DIR))
FRAMEWORK_DIR      ?= $(MOOSE_DIR)/framework
ADDITIONAL_CPPFLAGS += -Wall -Wextra
###############################################################################

# framework
include $(FRAMEWORK_DIR)/build.mk
include $(FRAMEWORK_DIR)/moose.mk

################################## MODULES ################################
#ALL_MODULES       := yes
ALL_MODULES         := no

CHEMICAL_REACTIONS  := no
CONTACT             := no
FLUID_PROPERTIES    := yes
HEAT_CONDUCTION     := no
MISC                := no
NAVIER_STOKES       := no
PHASE_FIELD         := no
RDG                 := no
RICHARDS            := no
SOLID_MECHANICS     := no
STOCHASTIC_TOOLS    := no
TENSOR_MECHANICS    := yes
WATER_STEAM_EOS     := yes
XFEM                := no
POROUS_FLOW         := yes

INCLUDE_COMBINED  := no
USE_TEST_LIBS     := yes
SKIP_LOADER       := yes
include $(MODULE_DIR)/modules.mk
###############################################################################

# Build the Module executable
APPLICATION_DIR    := $(MODULE_DIR)/combined
APPLICATION_NAME   := combined
BUILD_EXEC         := yes
GEN_REVISION       := no
include            $(FRAMEWORK_DIR)/app.mk

###############################################################################
# Additional special case targets should be added here
# gmis interface support for mfront
ADDITIONAL_CPPFLAGS += -I/home/cacace/snippets/MFrontGenericInterfaceSupport/include/
ADDITIONAL_LIBS += -L/home/cacace/snippets/MFrontGenericInterfaceSupport/build/src/ -lMFrontGenericInterface
