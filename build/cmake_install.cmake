# Install script for directory: /Applications/CRPropa/CRPYTHIAxDecaysOpt/CRPYTHIAxDecays

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/Applications/CRPropa/CRPYTHIAxDecaysOpt/CRPYTHIAxDecays/build")
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
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Applications/CRPropa/CRPYTHIAxDecaysOpt/CRPYTHIAxDecays/build/lib/python3.11/site-packages/Decays")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/Applications/CRPropa/CRPYTHIAxDecaysOpt/CRPYTHIAxDecays/build/lib/python3.11/site-packages" TYPE DIRECTORY FILES "/Applications/CRPropa/CRPYTHIAxDecaysOpt/CRPYTHIAxDecays/python/Decays")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Applications/CRPropa/CRPYTHIAxDecaysOpt/CRPYTHIAxDecays/build/lib/python3.11/site-packages/Decays/Decays.py")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/Applications/CRPropa/CRPYTHIAxDecaysOpt/CRPYTHIAxDecays/build/lib/python3.11/site-packages/Decays" TYPE FILE FILES "/Applications/CRPropa/CRPYTHIAxDecaysOpt/CRPYTHIAxDecays/build/Decays.py")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Applications/CRPropa/CRPYTHIAxDecaysOpt/CRPYTHIAxDecays/build/lib/python3.11/site-packages/Decays/_Decays.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/Applications/CRPropa/CRPYTHIAxDecaysOpt/CRPYTHIAxDecays/build/lib/python3.11/site-packages/Decays" TYPE MODULE FILES "/Applications/CRPropa/CRPYTHIAxDecaysOpt/CRPYTHIAxDecays/build/_Decays.so")
  if(EXISTS "$ENV{DESTDIR}/Applications/CRPropa/CRPYTHIAxDecaysOpt/CRPYTHIAxDecays/build/lib/python3.11/site-packages/Decays/_Decays.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/Applications/CRPropa/CRPYTHIAxDecaysOpt/CRPYTHIAxDecays/build/lib/python3.11/site-packages/Decays/_Decays.so")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Applications/CRPropa/PositionDependentPhotonField/CRPropa3/build/lib"
      -delete_rpath "/Applications/PYTHIA/pythia8311/lib"
      "$ENV{DESTDIR}/Applications/CRPropa/CRPYTHIAxDecaysOpt/CRPYTHIAxDecays/build/lib/python3.11/site-packages/Decays/_Decays.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "$ENV{DESTDIR}/Applications/CRPropa/CRPYTHIAxDecaysOpt/CRPYTHIAxDecays/build/lib/python3.11/site-packages/Decays/_Decays.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Applications/CRPropa/CRPYTHIAxDecaysOpt/CRPYTHIAxDecays/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
