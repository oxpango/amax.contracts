# Install script for directory: /home/gitpod/contracts/amax.contracts/src_system/contracts/amax.system

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/gitpod/contracts/amax.contracts/src_system/build/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "1")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/gitpod/contracts/amax.contracts/src_system/build/install/contracts/amax.system/amax.system.wasm;/home/gitpod/contracts/amax.contracts/src_system/build/install/contracts/amax.system/amax.system.abi")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/gitpod/contracts/amax.contracts/src_system/build/install/contracts/amax.system" TYPE FILE FILES
    "/home/gitpod/contracts/amax.contracts/src_system/build/contracts/amax.system/amax.system.wasm"
    "/home/gitpod/contracts/amax.contracts/src_system/build/contracts/amax.system/amax.system.abi"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/gitpod/contracts/amax.contracts/src_system/build/install/contracts/rex.results/rex.results.wasm;/home/gitpod/contracts/amax.contracts/src_system/build/install/contracts/rex.results/rex.results.abi")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/gitpod/contracts/amax.contracts/src_system/build/install/contracts/rex.results" TYPE FILE FILES
    "/home/gitpod/contracts/amax.contracts/src_system/build/contracts/amax.system/.rex/rex.results.wasm"
    "/home/gitpod/contracts/amax.contracts/src_system/build/contracts/amax.system/.rex/rex.results.abi"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/gitpod/contracts/amax.contracts/src_system/build/install/contracts/powup.results/powup.results.wasm;/home/gitpod/contracts/amax.contracts/src_system/build/install/contracts/powup.results/powup.results.abi")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/gitpod/contracts/amax.contracts/src_system/build/install/contracts/powup.results" TYPE FILE FILES
    "/home/gitpod/contracts/amax.contracts/src_system/build/contracts/amax.system/.powerup/powup.results.wasm"
    "/home/gitpod/contracts/amax.contracts/src_system/build/contracts/amax.system/.powerup/powup.results.abi"
    )
endif()

