############################################################
## This needs to be updated for building Android version. ##
############################################################
LOCAL_PATH3 := $(CURDIR)/../..

#Include location ie. Project/include.
LOCAL_C_INCLUDES += $(LOCAL_PATH3)/Project/include/

#Source location ie. Project/src.
SRC_LOC := $(LOCAL_PATH3)/Project/source/

#Source files ie. $(SRC_LOC)HelloScene.cpp
LOCAL_SRC_FILES += \
$(SRC_LOC)MenuScene.cpp