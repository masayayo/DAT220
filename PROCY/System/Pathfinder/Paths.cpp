//
// Created by Admin on 16.11.2017.
//

#include "Paths.h"

void Paths::setPaths(Settings &json) {

    setSpawnNodes(json);
    setDividerNodes(json);
    setTeleportNodes(json);

}

std::vector<int> Paths::getPath(int bit_type, sf::Vector2i position) {

    try{
        switch(bit_type){
            case 3:
                return getDirectionSpawn(position);
            case 4:
                return std::vector<int>();
            case 5:
                return getTeleportPosition(position);
            case 6:
                return getDirectionDivider(position);
            case 7:
                return std::vector<int>();
            case 10:
                return getDirectionTeleport(position);
            default:
                return std::vector<int>();
        }
    }
    catch (std::exception& e){
        lFatal("Map loading failed");
        std::cerr << "Tried to find path, got error: \n" << e.what() << std::endl;
    }
}
