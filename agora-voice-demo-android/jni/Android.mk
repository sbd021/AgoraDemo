########################## 加载So文件 ##########################
include $(CLEAR_VARS)
LOCAL_MODULE := CrasheyeNDK
LOCAL_SRC_FILES := prebuild/libCrasheyeNDK.so
include $(PREBUILT_SHARED_LIBRARY)
########################## 加载So文件 ##########################

LOCAL_CXXFLAGS  := -gstabs
