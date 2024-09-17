cmake_minimum_required(VERSION 2.8.12)

# Change name of the library to something meaningful!
set(PLUGINNAME "CRPYTHIAxDecays")
project(${PLUGINNAME} C CXX)

find_package(PythonInterp)
find_package(PythonLibs)
find_package(SWIG REQUIRED)
#find_package(Pythia8 REQUIRED)

# get information on crpropa
execute_process(COMMAND ${PYTHON_EXECUTABLE} "${CMAKE_CURRENT_SOURCE_DIR}/findCRPropa.py" swig_interface OUTPUT_VARIABLE crpropaSwigPath)
execute_process(COMMAND ${PYTHON_EXECUTABLE} "${CMAKE_CURRENT_SOURCE_DIR}/findCRPropa.py" install_prefix OUTPUT_VARIABLE crpropaInstallPrefix)
message(STATUS "CRPropa includes : ${crpropaInstallPrefix}")

find_path(CRPROPA_SWIG_INTERFACE_FILES
  crpropa.i
  HINTS crpropa/ share/crpropa python/ ${crpropaSwigPath} 
  )

find_path(CRPROPA_INCLUDES
  CRPropa.h
  HINTS crpropa/ include/crpropa ${crpropaInstallPrefix}/include/
  )

#find_path(PYTHIA8_INCLUDES
#  Pythia.h
#  HINTS pythia8311/ include/Pythia8 ${PYTHIA8_INCLUDE_DIR}
#  )

find_library(CRPROPA_LIB NAMES crpropa libcrpropa HINTS crpropa/ lib/crpropa crpropa/lib ${crpropaInstallPrefix}/lib/)

#find_library(PYTHIA8_LIB NAMES pythia8 libpythia8 HINTS pythia8311/ pythia8311/lib/ ${PYTHIA8_LIBRARIES})

# Add Pythia8 include directory manually
include_directories("/Applications/PYTHIA/pythia8311/include/") # Pythia8/

# Link Pythia8 libraries manually
link_directories("/Applications/PYTHIA/pythia8311/lib/")

message(STATUS "CRPropa SWIG interface files: ${CRPROPA_SWIG_INTERFACE_FILES}")
message(STATUS "CRPropa includes : ${CRPROPA_INCLUDES}")
message(STATUS "CRPropa lib: ${CRPROPA_LIB}")
message(STATUS "Pythia8 includes : ${PYTHIA8_INCLUDE_DIR}") 
message(STATUS "Pythia8 lib : ${PYTHIA8_LIBRARIES}")

# swig plugin
set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/${PLUGINNAME}_wrap.cxx PROPERTIES GENERATED true )
add_custom_command( OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${PLUGINNAME}_wrap.cxx
  COMMAND swig -builtin -c++ -python ${PY3} -I${CRPROPA_SWIG_INTERFACE_FILES} -I${CRPROPA_INCLUDES} -I${CMAKE_SOURCE_DIR}/include -I${PYTHON_INCLUDE_DIRS} -I${PYTHIA8_INCLUDE_DIR} ${CRPROPA_SWIG_DEFINES} -dirprot -o ${CMAKE_CURRENT_BINARY_DIR}/${PLUGINNAME}_wrap.cxx -outdir ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${PLUGINNAME}.i)

include_directories(include ${CMAKE_CURRENT_BINARY_DIR}/include ${CRPROPA_INCLUDES} ${PYTHON_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR})

# build interface and source in one library
add_library(${PLUGINNAME} MODULE 
  ${CMAKE_CURRENT_BINARY_DIR}/${PLUGINNAME}_wrap.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/Decays.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/PythiaDecay.cc
)

target_link_libraries(${PLUGINNAME} ${CRPROPA_LIB} ${PYTHON_LIBRARIES})

add_definitions(/Applications/PYTHIA/pythia8311/bin/pythia8-config --cxxflags)
target_link_libraries(${PLUGINNAME} "/Applications/PYTHIA/pythia8311/lib/libpythia8.dylib" /Applications/PYTHIA/pythia8311/bin/pythia8-config --ldflags)

set_target_properties(${PLUGINNAME} PROPERTIES PREFIX "")
set_target_properties(${PLUGINNAME} PROPERTIES OUTPUT_NAME "_${PLUGINNAME}")

execute_process(
        COMMAND ${PYTHON_EXECUTABLE} -c "import sys; from distutils import sysconfig; sys.stdout.write(
sysconfig.get_python_lib(1,0,prefix='${CMAKE_INSTALL_PREFIX}'))"
        OUTPUT_VARIABLE PYTHON_SITE_PACKAGES
        OUTPUT_STRIP_TRAILING_WHITESPACE
        )

# installation 
install(DIRECTORY "${CMAKE_SOURCE_DIR}/python/${PLUGINNAME}" DESTINATION "${PYTHON_SITE_PACKAGES}")
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PLUGINNAME}.py" DESTINATION "${PYTHON_SITE_PACKAGES}/${PLUGINNAME}")
install(TARGETS ${PLUGINNAME} LIBRARY DESTINATION "${PYTHON_SITE_PACKAGES}/${PLUGINNAME}")


