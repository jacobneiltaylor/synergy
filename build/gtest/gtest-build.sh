#!/bin/sh

# Set variables
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
GTEST_DIR="${SCRIPT_DIR}/googletest/"
GTEST_URL="https://github.com/google/googletest/archive/release-1.7.0.zip"
GTEST_ZIP="/tmp/release-1.7.0.zip"

# Download googletest source if nessesary
if [ -d "$GTEST_DIR" ]
then
	echo "GoogleTest source present, skipping download."
else
	echo "GoogleTest source missing, downloading."
	curl -L "$GTEST_URL" > "$GTEST_ZIP"
	unzip -d "$SCRIPT_DIR" "$GTEST_ZIP"
	rm "$GTEST_ZIP"
	mv "${SCRIPT_DIR}/googletest-release-1.7.0" "$GTEST_DIR"
fi

# Prepare build directories
cd "${GTEST_DIR}"

rm -rf "x86"
rm -rf "x64"

mkdir "x86"
mkdir "x64"

# 32-bit build
echo "Beginning build: GoogleTest (32bit)"

cd "x86"
if [ "$OSTYPE" = "darwin"* ]
then
	cmake -DCMAKE_OSX_ARCHITECTURES=i386 -G "Unix Makefiles" ../
else
	export CFLAGS="-m32"
	export CXXFLAGS="-m32"
	export LDFLAGS="-m32"
	cmake -G "Unix Makefiles" ../
fi

make clean
make

if [ $? -eq 0 ]
then
	echo "Build succeeded for GoogleTest (32bit)"
else
	echo "Build failed for GoogleTest (32bit)"
fi

cd ..

# 64-bit build
echo "Beginning build: GoogleTest (64bit)"

cd "x64"
if [ "$OSTYPE" = "darwin"* ]
then
	cmake -DCMAKE_OSX_ARCHITECTURES=x86_64 -G "Unix Makefiles" ../
else
	export CFLAGS="-m64"
	export CXXFLAGS="-m64"
	export LDFLAGS="-m64"
	cmake -G "Unix Makefiles" ../
fi

make clean
make

if [ $? -eq 0 ]
then
	echo "Build succeeded for GoogleTest (64bit)"
else
	echo "Build failed for GoogleTest (64bit)"
fi

cd ..

cd ..
