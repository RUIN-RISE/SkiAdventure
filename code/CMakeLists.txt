
add_executable(SkiAdventure main.cpp
	common/frame.cpp
    common/Curve.cpp
    common/PhysicsEntity.cpp
    common/Angle.cpp
    common/Vector.cpp
	common/Timer.cpp
	common/Rotator.cpp
	model/Model.cpp
	viewmodel/commands/NextStepCommand.cpp
	viewmodel/commands/JumpCommand.cpp
	viewmodel/commands/StartCommand.cpp
	viewmodel/GameViewModel.cpp
	viewmodel/SpiritViewModel.cpp
	view/widgets/GameBoard.cpp
	view/MainWindow.cpp
	view/StartScreen.cpp
	app/app.cpp)

target_precompile_headers(SkiAdventure PRIVATE precomp.h)

set_target_properties(SkiAdventure PROPERTIES
	WIN32_EXECUTABLE TRUE)

target_link_libraries(SkiAdventure PRIVATE fltk fltk_images)
target_include_directories(SkiAdventure PRIVATE ${Stb_INCLUDE_DIR})

set(assets_path_list "${CMAKE_CURRENT_BINARY_DIR}/Debug/assets"
	"${CMAKE_CURRENT_BINARY_DIR}/Release/assets")
file(MAKE_DIRECTORY ${assets_path_list})
foreach(assets_path ${assets_path_list})
	file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/assets/player.png"
		"${CMAKE_CURRENT_SOURCE_DIR}/assets/snow.png"
		"${CMAKE_CURRENT_SOURCE_DIR}/assets/stone.png"
		"${CMAKE_CURRENT_SOURCE_DIR}/assets/background.png"
# 		"${CMAKE_CURRENT_SOURCE_DIR}/assets/plane_blue.png"
		DESTINATION "${assets_path}")
endforeach()
