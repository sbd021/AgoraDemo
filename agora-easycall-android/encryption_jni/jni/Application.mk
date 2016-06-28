STLPORT_FORCE_REBUILD := false
APP_STL := gnustl_static
#APP_STL := gnustl_shared
APP_CPPFLAGS += -std=c++11
APP_CPPFLAGS += -fno-exceptions
#APP_CPPFLAGS += -fexceptions
APP_CPPFLAGS += -fno-rtti -fPIC -fpic
APP_CPPFLAGS += -fvisibility=hidden
APP_CFLAGS += -fvisibility=hidden

APP_CPPFLAGS += -DBUILTIN_ENCRYPTION
APP_CFLAGS += -DBUILTIN_ENCRYPTION

LDFLAGS += -Wl,--gc-sections
ifneq ($(TARGET_ARCH),mips)
  LDFLAGS += -Wl,--icf=safe
endif
TARGET_arm_release_CFLAGS := -Os
HAVEVIDEO = 1
ENABLE_EAAC_ENC = 0
ENABLE_MP3_DEC = 1
ENABLE_SLES_PLAYER = 0
AGORARTC_HAS_EXCEPTION = 0
APP_ABI := armeabi-v7a x86
APP_PLATFORM := android-9
NDK_TOOLCHAIN_VERSION=4.8
