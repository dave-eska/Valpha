# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-src")
  file(MAKE_DIRECTORY "/home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-src")
endif()
file(MAKE_DIRECTORY
  "/home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-build"
  "/home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-subbuild/asio-cmake-populate-prefix"
  "/home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-subbuild/asio-cmake-populate-prefix/tmp"
  "/home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-subbuild/asio-cmake-populate-prefix/src/asio-cmake-populate-stamp"
  "/home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-subbuild/asio-cmake-populate-prefix/src"
  "/home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-subbuild/asio-cmake-populate-prefix/src/asio-cmake-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-subbuild/asio-cmake-populate-prefix/src/asio-cmake-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/dave/Documents/c++/Valpha/build/_deps/asio-cmake-subbuild/asio-cmake-populate-prefix/src/asio-cmake-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()