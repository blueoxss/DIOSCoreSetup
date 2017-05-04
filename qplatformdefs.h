#
# qmake configuration for the A20_OlinuxinO boards
# http://www.olimex.com/

MAKEFILE_GENERATOR      = UNIX
CONFIG                 += incremental gdb_dwarf_index
QMAKE_INCREMENTAL_STYLE = sublib

include(../../common/linux.conf)
include(../../common/gcc-base-unix.conf)
include(../../common/g++-unix.conf)

load(device_config)

QT_QPA_DEFAULT_PLATFORM = eglfs
#EGLFS_PLATFORM_HOOKS_SOURCES = $$PWD/qeglfshooks_a20.cpp
# modifications to g++.conf
QMAKE_CC                = $${CROSS_COMPILE}gcc
QMAKE_CXX               = $${CROSS_COMPILE}g++
QMAKE_LINK              = $${QMAKE_CXX}
QMAKE_LINK_SHLIB        = $${QMAKE_CXX}

# modifications to linux.conf
QMAKE_AR                = $${CROSS_COMPILE}ar cqs
QMAKE_OBJCOPY           = $${CROSS_COMPILE}objcopy
QMAKE_NM                = $${CROSS_COMPILE}nm -P
QMAKE_STRIP             = $${CROSS_COMPILE}strip

COMPILER_FLAGS          = -march=armv7-a -mtune=cortex-a7 -mfpu=neon -DLINUX=1 -DEGL_API_FB=1 -mfloat-abi=hard

#modifications to gcc-base.conf
QMAKE_CFLAGS           += $${COMPILER_FLAGS}
QMAKE_CXXFLAGS         += $${COMPILER_FLAGS}
QMAKE_CXXFLAGS_RELEASE += -O3

QMAKE_LIBS             += -lrt -lpthread -ldl

# Extra stuff (OpenGL, DirectFB, ...)
QMAKE_INCDIR_EGL        = /mnt/a20/usr/include/EGL
QMAKE_LIBDIR_EGL        = /mnt/a20/usr/lib
QMAKE_INCDIR_OPENGL_ES2 = /mnt/a20/usr/include/GLES2
QMAKE_LIBDIR_OPENGL_ES2 = /mnt/a20/usr/lib
#QMAKE_INCDIR_OPENVG     = $${QMAKE_INCDIR_EGL}
#QMAKE_LIBDIR_OPENVG     = $${QMAKE_LIBDIR_EGL}

QMAKE_LIBS_EGL          = -lEGL
QMAKE_LIBS_OPENGL_ES2   = -lGLESv2 $${QMAKE_LIBS_EGL}
#QMAKE_LIBS_OPENVG       = -lOpenVG $${QMAKE_LIBS_EGL}

# Sanity check
deviceSanityCheckCompiler()

load(qt_config)
