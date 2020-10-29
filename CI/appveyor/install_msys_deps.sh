#!/usr/bin/bash.exe

SCOPY_MINGW_BUILD_DEPS_FORK=analogdevicesinc
SCOPY_MINGW_BUILD_DEPS_BRANCH=master

echo "Download and install pre-compiled libraries ... "
wget "https://ci.appveyor.com/api/projects/$SCOPY_MINGW_BUILD_DEPS_FORK/scopy-mingw-build-deps/artifacts/scopy-$MINGW_VERSION-build-deps-pacman.txt?branch=$SCOPY_MINGW_BUILD_DEPS_BRANCH&job=Environment: MINGW_VERSION=$MINGW_VERSION, ARCH=$ARCH" -O /tmp/scopy-$MINGW_VERSION-build-deps-pacman.txt
wget "https://ci.appveyor.com/api/projects/$SCOPY_MINGW_BUILD_DEPS_FORK/scopy-mingw-build-deps/artifacts/scopy-$MINGW_VERSION-build-deps.tar.xz?branch=$SCOPY_MINGW_BUILD_DEPS_BRANCH&job=Environment: MINGW_VERSION=$MINGW_VERSION, ARCH=$ARCH" -O /tmp/scopy-$MINGW_VERSION-build-deps.tar.xz

cd /c/old_msys_deps_mingw64
wget "https://repo.msys2.org/mingw/x86_64/mingw-w64-x86_64-libusb-1.0.23-1-any.pkg.tar.xz"

cd /c
tar xJf /tmp/scopy-$MINGW_VERSION-build-deps.tar.xz


SCOPY_MINGW_BUILD_DEPS_PACMAN=$(</tmp/scopy-$MINGW_VERSION-build-deps-pacman.txt)
PACMAN_SYNC_DEPS="
	$SCOPY_MINGW_BUILD_DEPS_PACMAN\
	mingw-w64-$ARCH-matio \
"

PACMAN_REPO_DEPS="
	/c/old_msys_deps_$MINGW_VERSION/mingw-w64-$ARCH-breakpad-git-r1680.70914b2d-1-any.pkg.tar.xz \
	/c/old_msys_deps_$MINGW_VERSION/mingw-w64-$ARCH-libusb-1.0.23-1-any.pkg.tar.xz \
	/c/old_msys_deps_$MINGW_VERSION/mingw-w64-$ARCH-boost-1.72.0-3-any.pkg.tar.zst \
	/c/old_msys_deps_$MINGW_VERSION/mingw-w64-$ARCH-qt5-5.14.2-3-any.pkg.tar.zst \
"

PATH=/c/msys64/$MINGW_VERSION/bin:$PATH
echo "### Installing the dependencies"
pacman --noconfirm -Sy $PACMAN_SYNC_DEPS
pacman --noconfirm -U  $PACMAN_REPO_DEPS

# Hack: Qt5Qml CMake script throws errors when loading its plugins. So let's just drop those plugins.
rm -f /$MINGW_VERSION/lib/cmake/Qt5Qml/*Factory.cmake

