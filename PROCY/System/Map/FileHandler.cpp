//
// Created by Chrim14 on 19.10.2017.
//

#include "FileHandler.h"


///From: EditorSetup::getSaveChildWindow
///Function: Store all map information in a Json file
void FileHandler::saveMap(std::string &fileName, Settings &json, tgui::Gui &gui) {

    std::string filePath = "Texture/Maps/";
    std::string fileType = ".json";

    tgui::ChildWindow::Ptr childWindow = gui.get<tgui::ChildWindow>("saveChildMenu");

    tgui::Label::Ptr label = childWindow->get<tgui::Label>("fileMessage");

    lDebug("Saving map: " + fileName);

    bool correctName; //True if save entery is correct after what happens in controllName function
    bool error = false; //True if a error occurs
    bool overwrite = true;
    std::string message = fileName;

    controlName(message, correctName);

    if (correctName) {

        tgui::Button::Ptr bSave = childWindow->get<tgui::Button>("bSave");

        //Overwrite protection
        if (bSave != nullptr) {
            std::string bSaveString = bSave->getText();
            std::string yes = json.language["yes"];
            if (bSave->getText() != yes) {
                if (fileName != json.map["name"]) {
                    std::vector<std::string> allFiles = get_all_files_names_within_folder(filePath);

                    for (const auto &temp : allFiles) {
                        if (fileName + fileType == temp) {
                            bSave->setText(sf::String::fromUtf8(yes.begin(),yes.end()));
                            message = "file exist, will you overwrite?";
                            correctName = false;
                            overwrite = false;
                            break;
                        }
                    }
                }
            }

            else{
                std::string bSaveString2 = json.language["saveFile"];
                bSave->setText(sf::String::fromUtf8(bSaveString2.begin(),bSaveString2.end()));
            }

        }
        if (overwrite) {

            std::string savePath = filePath + fileName + fileType;

            try {
                std::ofstream file(savePath);

                if (!file) {
                    lError("Could not save file to path: " + savePath);
                    message = "ERROR Could not save file";
                    error = true;
                    goto label;
                }

                const unsigned int x = json.map["width"];
                const unsigned int y = json.map["height"];

                //clearing old data
                json.map["map"] = {};
                json.map["bmap"] = {};

                for (int i = 0; i < y; ++i) {
                    for (int j = 0; j < x; ++j) {
                        json.map["map"] += json.tileValue[j][i];
                    }
                }

                for (int i = 0; i < y * Bits_To_Tiles; ++i) {
                    for (int j = 0; j < x * Bits_To_Tiles; ++j) {
                        json.map["bmap"] += json.bitTileValue[j][i];
                    }
                }

                file << std::setw(4) << json.map << std::endl;

                message = "File saved";
            }
            catch (...) {
                lError("Could not write to file path: " + savePath);
                message = "ERROR Could not write to file path";
                error = true;
            }
        }
    }
    label:
    if (label != nullptr) {
        if (!correctName) {
            label->setTextColor(sf::Color(255, 200, 0));
        } else if (error) {
            label->setTextColor(sf::Color(255, 0, 0));
        } else {
            label->setTextColor(sf::Color(0, 255, 0));
        }
        label->setText(message);
    }
}

///From: EditorSetup::getEditorSetupMenu
///Function: Get all map information from a Json file
void FileHandler::loadMap(std::string guiListName, std::string guiChildWindow, Settings &json, tgui::Gui &gui) {

    std::string filePath = "Texture/Maps/";
    std::string fileType = ".json";
    std::string fileName;
    std::string errorMessage;
    bool correctName;

    if(guiChildWindow.empty()){
    fileName = gui.get<tgui::ListBox>(guiListName)->getSelectedItem();

    }
    else{
        if(guiChildWindow == "pGames"){
            fileName = gui.get<tgui::Panel>(guiChildWindow)->get<tgui::ListBox>(guiListName)->getSelectedItem();
        }else{
            fileName = gui.get<tgui::ChildWindow>(guiChildWindow)->get<tgui::ListBox>(guiListName)->getSelectedItem();
        }
    }

    if(fileName.empty()){
        errorMessage = "Did not find file";
        goto label;
    }

    errorMessage = fileName;
    controlName(errorMessage,correctName);
    if(!correctName){
        errorMessage = "This file has not a legit file name";
    }
    try {
        if (std::ifstream(filePath + fileName + fileType)) {
            lInfo("Loading file: " + fileName);

            std::ifstream file(filePath + fileName + fileType);

            file >> json.map;
            unsigned int x = json.map["width"];
            unsigned int y = json.map["height"];

            if (x > Layer_One_Size || x < Layer_One_Size_Min || y > Layer_One_Size || y < Layer_One_Size_Min) {
                errorMessage = "Corrupted file, size";
                goto label;
            }

            unsigned int counter = 0;
            for (const auto &size : json.map["map"]) {
                counter++;
            }

            if (counter != x * y) {
                errorMessage = "Corrupted file, tile map";
                goto label;
            }

            counter = 0;

            for (const auto &size : json.map["bmap"]) {
                counter++;
            }
            if (counter != x * y * Bits_To_Tiles * Bits_To_Tiles) {
                errorMessage = "Corrupted file, bit map";
                goto label;
            }

            errorMessage = "";
        }
        else{
            errorMessage = "File could not open";
        }
    } catch (...){
        errorMessage = "Corruption in map file";
    }

    label:

    if(!errorMessage.empty()){
        lWarning(errorMessage);
    }

    tgui::Label::Ptr errorLabel;

        if(guiChildWindow.empty())
            errorLabel = gui.get<tgui::Label>("fileMessage");

        else{
            if(guiChildWindow == "pGames"){
                errorLabel = gui.get<tgui::Panel>(guiChildWindow)->get<tgui::Label>("fileMessage");
            }else{
                errorLabel = gui.get<tgui::ChildWindow>(guiChildWindow)->get<tgui::Label>("fileMessage");
            }
        }

    if(errorLabel == nullptr){
        lError("Did not find label fileMessage");
        return;
    }

    errorLabel->setTextColor(sf::Color(255, 200, 0));
    errorLabel->setText(errorMessage);
}

///From: FileHandler::saveMap and FileHandler::loadMap
///Function: restricting file names in characters and length
void FileHandler::controlName(std::string &name, bool &correct) {

    correct = true;

    if(name.empty()){
        name = "name empty";
        correct = false;
    }
    else if(name.length() > 20){
        name = "Name size to large, max 20 character";
        correct = false;
    }
    else if(name.length() < 3){
        name = "Name size to small, min 3 characters";
        correct = false;
    }
    else{
        for(auto character : name){

            if (character > 122 || (character > 90 && character < 97) || (character > 57 && character < 65) || (character > 32 && character < 48) || character < 32){
                name = "Special symbol not allowed";
                correct = false;
                return;
            }
            else if(name[0] < 65){
                name = "First character invalid";
                correct = false;
                return;
            }
        }
    }
}

///From: EditorSetup::getEditorSetupMenu
///Function: Refactor Json array to 2D array
void FileHandler::refectorJsonInto2DArray(Settings &json) {

    const unsigned int width = json.map["width"];

    int tempX = 0;
    int tempY = 0;

    for (const auto& counter : json.map["map"]){
        json.tileValue[tempX][tempY] = counter;
        tempX++;
        if(tempX >= width){
            tempY++;
            tempX = 0;
        }
    }
    tempX = 0, tempY = 0;
    json.map["map"] = {};
    for (const auto& counter : json.map["bmap"]){
        json.bitTileValue[tempX][tempY] = counter;
        tempX++;
        //std::cout << counter << " ";
        if(tempX >= width*Bits_To_Tiles){
            //std::cout << std::endl;
            tempY++;
            tempX = 0;
        }
    }
    json.map["bmap"] = {};
}

///Used: EditorSetup::getEditorSetupMenu
///Function: Adding file names to list
void FileHandler::getFiles(std::string file_path, std::string list_name, std::string childWindow, tgui::Gui &gui) {

    std::vector<std::string> files = get_all_files_names_within_folder(file_path);

    tgui::ListBox::Ptr list;
    if(childWindow.empty())
        list = gui.get<tgui::ListBox>(list_name);
    else{
        if(childWindow == "pGames"){
            list = gui.get<tgui::Panel>(childWindow)->get<tgui::ListBox>(list_name);
        }
        else{
            list = gui.get<tgui::ChildWindow>(childWindow)->get<tgui::ListBox>(list_name);
        }
    }


    if(list != nullptr) {
        int counter = 0;
        for (auto &temp : files) {
            temp = temp.substr(0, temp.size() - 5);
            list->addItem(temp,std::to_string(counter));
            counter++;
        }
    }
    else{
        lError("Tried to add files to list, but got null pointer");
    }
}


///############################### PRIVATE ##########################################################///


///Used: FileHandler::getFiles
///Function: Finding file names in directory
std::vector<std::string> FileHandler::get_all_files_names_within_folder(std::string &folder)
{

#ifdef _WIN32
    std::vector<std::string> names;
    std::string search_path = folder + "/*.json";
    WIN32_FIND_DATA fd{};
    HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
    if(hFind != INVALID_HANDLE_VALUE) {
        do {
            // read all (real) files in current folder
            // , delete '!' read other 2 default folder . and ..
            if(! (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ) {
                names.push_back((std::string) fd.cFileName);
            }
        }while(::FindNextFile(hFind, &fd));
        ::FindClose(hFind);
    }
    return names;
#endif
}
