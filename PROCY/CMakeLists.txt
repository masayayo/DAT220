cmake_minimum_required(VERSION 3.8)
project(PROCY)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        main.cpp
        Engine/StateMachine.cpp
        Engine/StateMachine.h
        Engine/StateController.cpp
        Engine/StateController.h
        GUI/Menu/Menu.cpp
        GUI/Menu/Menu.h
        Game.cpp
        Game.h
        Debugger/Logging.h
        Engine/Settings.cpp
        Engine/Settings.h
        GUI/Menu/SettingButtons.cpp
        GUI/Menu/SettingButtons.h
        GUI/Sound/Sound.cpp
        GUI/Sound/Sound.h
        GUI/MapEditor/EditorSetup.cpp
        GUI/MapEditor/EditorSetup.h
        System/MapEditor/MapEditorStaticFunctions.cpp
        System/MapEditor/MapEditorStaticFunctions.h
        System/Map/Map.cpp
        System/Map/Map.h
        System/Map/FileHandler.cpp
        System/Map/FileHandler.h
        System/Map/MapEvents.cpp
        System/Map/MapEvents.h
        System/Entities/Monster.cpp
        System/Entities/Monster.h
        System/Entities/Wave.cpp
        System/Entities/Wave.h
        System/Game/HUD.cpp
        System/Game/HUD.h
        GUI/MapEditor/EditorChildWindows.cpp
        GUI/MapEditor/EditorChildWindows.h
        System/Map/MapFunctions.cpp
        System/Map/MapFunctions.h
        System/Map/MapStaticFunctions.cpp
        System/Map/MapStaticFunctions.h
        GUI/MapEditor/EditorStaticGuiFunctions.cpp
        GUI/MapEditor/EditorStaticGuiFunctions.h
        System/Game/Timer.h
        System/Game/Tower.h
        System/Game/Bullet.h
        System/Game/Bullet.cpp
        System/Game/Player.cpp
        System/Game/Player.h
        System/Game/PlayerClass.cpp
        System/Game/PlayerClass.h
        Engine/Div/Tile_List.cpp
        Engine/Div/Tile_List.h
        Engine/Div/Language.cpp
        Engine/Div/Language.h
        System/Entities/WaveManager.cpp
        System/Entities/WaveManager.h
        System/Pathfinder/Spawn.cpp
        System/Pathfinder/Spawn.h
        System/Pathfinder/Direction.cpp
        System/Pathfinder/Direction.h
        System/Pathfinder/Paths.cpp
        System/Pathfinder/Paths.h
        System/Pathfinder/Divider.cpp
        System/Pathfinder/Divider.h
        System/Pathfinder/Teleport.cpp
        System/Pathfinder/Teleport.h
        System/Game/Updater.h
        System/Game/Updater.cpp
        GUI/Menu/MenuPanels.cpp
        GUI/Menu/MenuPanels.h
        Engine/Div/KeyBinds.cpp
        Engine/Div/KeyBinds.h
        System/Entities/MonsterClass.cpp
        System/Entities/MonsterClass.h
        System/Entities/waveClass.cpp
        System/Entities/waveClass.h
        )


add_executable(PROCY ${SOURCE_FILES})


target_link_libraries(PROCY
        sfml-system
        sfml-window
        sfml-graphics
        sfml-audio
        tgui
        )
