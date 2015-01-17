# Copyright 2015 Egor Kovetskiy
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 2.6) 
project(editor C) 
set(PROJECT_VERSION "2.1")

find_package(PkgConfig REQUIRED) 
pkg_check_modules(GLIB REQUIRED glib-2.0) 
pkg_check_modules(MCABBER REQUIRED mcabber)
include(CheckSymbolExists)
set(CMAKE_REQUIRED_INCLUDES ${MCABBER_INCLUDE_DIRS})
set(CMAKE_REQUIRED_LIBRARIES ${MCABBER_LIBRARIES})
set(CMAKE_REQUIRED_FLAGS ${MCABBER_LDFLAGS} ${MCABBER_CFLAGS})
check_symbol_exists(MCABBER_API_HAVE_editor_ID mcabber/api.h HAVE_MCABBER_editor_ID)
link_directories(${GLIB_LIBRARY_DIRS}
				 ${MCABBER_LIBRARY_DIRS})

add_library(editor MODULE editor.c) 

configure_file(config.h.in config.h)
include_directories(SYSTEM ${GLIB_INCLUDE_DIRS} 
                    ${MCABBER_INCLUDE_DIRS})
target_link_libraries(editor ${GLIB_LIBRARIES} 
					  ${MCABBER_LIBRARIES})
include_directories(${editor_SOURCE_DIR} 
                    ${editor_BINARY_DIR})
set_target_properties(editor PROPERTIES COMPILE_FLAGS "-Wall")

## Packaging information
set(CPACK_PACKAGE_NAME mcabber-mod-editor)
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_VENDOR "kovetskiy")
set(CPACK_PACKAGE_CONTACT "Egor Kovetskiy <e.kovetskiy@office.ngs.ru>")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Mcabber module for sending messages using your editor")
set(CPACK_SOURCE_GENERATOR TBZ2)
set(CPACK_GENERATOR DEB CACHE STRING "Binary package generator, eg DEB, RPM, TGZ, NSIS...")
set(CPACK_DEBIAN_PACKAGE_SECTION libs)
find_program(DPKG_EXECUTABLE dpkg)
if(DPKG_EXECUTABLE)
	execute_process(COMMAND ${DPKG_EXECUTABLE} --print-architecture OUTPUT_VARIABLE CPACK_DEBIAN_PACKAGE_ARCHITECTURE OUTPUT_STRIP_TRAILING_WHITESPACE)
else()
	set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE i386 CACHE STRING "Architecture of package")
endif()
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}_${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}")
set(CPACK_SOURCE_IGNORE_FILES "/\\\\..*;\\\\.swp;~$;/build/;\\\\.tar\\\\.;\\\\.deb;\\\\.so")
include(CPack)

configure_file(editor.avv.in editor.avv)

## Installation
install(TARGETS editor DESTINATION lib/mcabber) 
install(FILES ${PROJECT_BINARY_DIR}/editor.avv DESTINATION share/mcabber/avv/modules RENAME editor)
## The End ## vim: se ts=4: ##
