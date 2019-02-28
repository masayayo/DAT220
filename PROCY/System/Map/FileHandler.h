//
// Created by Admin on 19.10.2017.
//

#ifndef PROCY_SAVEMAP_H
#define PROCY_SAVEMAP_H

#ifdef _WIN32
#include <Windows.h>
#endif

#include <vector>
#include <string>
#include "Map.h"

class FileHandler {
public:
    FileHandler() = default;

  //  void checkAfterExistingMaps();

    void saveMap(std::string &fileName, Settings &json, tgui::Gui &gui);

    void loadMap(std::string guiListName, std::string guiChildWindow, Settings &json, tgui::Gui &gui);

    void controlName(std::string &name, bool &correct);


    void refectorJsonInto2DArray(Settings &json);

    void getFiles(std::string file_path, std::string list_name, std::string childWindow, tgui::Gui &gui);

    static std::vector<std::string> get_all_files_names_within_folder(std::string &folder);

};

#endif //PROCY_SAVEMAP_H
