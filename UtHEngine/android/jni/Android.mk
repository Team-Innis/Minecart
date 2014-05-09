# Copyright (C) 2010 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := openal
LOCAL_SRC_FILES := ../libs/libopenal.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := uthengine
LOCAL_SRC_FILES := ../libs/libuthengine.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := freetype
LOCAL_SRC_FILES := ../libs/libfreetype.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libfreetypegl
LOCAL_SRC_FILES := ../libs/libfreetypegl_static.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libbox2d
LOCAL_SRC_FILES := ../libs/libbox2d_static.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := uthgame
LOCAL_SRC_FILES := main.cpp
LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv2 -lOpenSLES
LOCAL_STATIC_LIBRARIES := android_native_app_glue uthengine libbox2d libfreetypegl freetype 
LOCAL_SHARED_LIBRARIES := openal 

include $(LOCAL_PATH)/../../../sources.mk

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../include/
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../extinclude/

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)
