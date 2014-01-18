# Install script for directory: C:/mysqlbuildtemp/cppconn

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/MySQL/ConnectorCPP")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/cppconn" TYPE FILE FILES
    "C:/mysqlbuildtemp/cppconn/build_config.h"
    "C:/mysqlbuildtemp/cppconn/config.h"
    "C:/mysqlbuildtemp/cppconn/connection.h"
    "C:/mysqlbuildtemp/cppconn/datatype.h"
    "C:/mysqlbuildtemp/cppconn/driver.h"
    "C:/mysqlbuildtemp/cppconn/exception.h"
    "C:/mysqlbuildtemp/cppconn/metadata.h"
    "C:/mysqlbuildtemp/cppconn/parameter_metadata.h"
    "C:/mysqlbuildtemp/cppconn/prepared_statement.h"
    "C:/mysqlbuildtemp/cppconn/resultset.h"
    "C:/mysqlbuildtemp/cppconn/resultset_metadata.h"
    "C:/mysqlbuildtemp/cppconn/statement.h"
    "C:/mysqlbuildtemp/cppconn/sqlstring.h"
    "C:/mysqlbuildtemp/cppconn/warning.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

