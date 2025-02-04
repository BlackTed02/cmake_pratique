# CMakeList.txt : projet CMake pour cmake_pratique, incluez la source et définissez
# la logique spécifique au projet ici.
#

file(GLOB ALL_SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Ajoutez une source à l'exécutable de ce projet.
add_executable (${PROJECT_NAME} ${ALL_SRC})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/../include)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE 
	sfml-audio
	sfml-system
	sfml-graphics
	sfml-window
	sfml-network
	Lib
)

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
