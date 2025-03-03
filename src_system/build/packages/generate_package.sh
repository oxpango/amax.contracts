#! /bin/bash

VARIANT=$1

VERSION_NO_SUFFIX="2.0.0"
VERSION_SUFFIX="alpha"
VERSION="2.0.0-alpha"

# Using CMAKE_BINARY_DIR uses an absolute path and will break cross-vm building/download/make functionality
BUILD_DIR="../../build"

VENDOR=""
PROJECT="amax_contracts"
DESC=""
URL=""
EMAIL=""

export BUILD_DIR
export VERSION_NO_SUFFIX
export VERSION_SUFFIX
export VERSION
export VENDOR
export PROJECT
export DESC
export URL
export EMAIL

. ./generate_tarball.sh

