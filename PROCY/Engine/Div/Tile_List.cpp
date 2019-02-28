//
// Created by Chrim14 on 09.11.2017.
//

#include "Tile_List.h"

///From: Settings::Settings
///Function: Adding all tiles that want to be used in a json object
void Tile_List::setTileList(json &tiles) {

    tiles["road"] = {
            "2","Bricks-Gray",
            "105", "Bricks-Red light",
            "106", "Bricks-Red medium",
            "107", "Bricks-Red dark",
            "141","Bricks-Yellow light",
            "142","Bricks-Yellow medium",
            "143","Bricks-Yellow dark",
            "10","Bricks-White light",
            "11","Bricks-White medium",
            "12","Bricks-White dark",
            "148","Bricks-Blue light",
            "149","Bricks-Blue medium",
            "150","Bricks-Blue dark",
            "67", "Bricks-Pink light",
            "69", "Bricks-Pink medium",
            "70", "Bricks-Pink dark",
            "64", "Wood-Floor light",
            "65", "Wood-Floor light",
            "66", "Wood-Floor light",
            "28", "Stoneroad-White light",
            "29", "Stoneroad-White medium",
            "30", "Stoneroad-White dark",
            "41", "Stoneroad-Gray light",
            "42", "Stoneroad-Gray medium",
            "43", "Stoneroad-Gray dark",
            "44", "Stoneroad-Old light",
            "45", "Stoneroad-Old medium",
            "47", "Stoneroad-Old dark",
            "48", "Stoneroad-Blood light",
            "49", "Stoneroad-Blood medium",
            "50", "Stoneroad-Blood dark",
            "4", "Lava-Red light",
            "5", "Lava-Red medium",
            "6", "Lava-Red dark",
            "7", "Lava-yellow light",
            "8", "Lava-yellow medium",
            "9", "Lava-yellow dark",
            "94", "Lava-Green light",
            "95", "Lava-Green medium",
            "96", "Lava-Green dark",
    };


    tiles["ground"] = {
            "1","Grass light",
            "238", "Grass medium",
            "239", "Grass dark",
            "3", "Sand Lightbrown",
            "23", "Sand Darkbrown",
            "27", "Sand White",
            "46", "Sand Gray",
            "70", "Bricks Red",
            "97", "Carpet Light Red",
            "99", "Carpet Dark Red",
            "111", "Gray Light",
            "114", "Gray Dark",
            "134", "Snow White",
            "137", "Snow Gray",
            "174","Grass uneven light",
            "175", "Grass uneven medium",
            "176", "Grass uneven dark"
    };

    tiles["spawn"] = {
            "308","Stone opening",
            "310", "Stone dark opening",
            "313", "Stone bloody opening",
            "346", "Broken door",
            "108", "Stone-Brics-Red light",
            "109", "Stone-Brics-Red medium",
            "110", "Stone-Brics-Red dark"
    };
    tiles["destination"] = {
            "184", "House light brown",
            "185", "House brown",
            "186", "House dark brown",
            "187", "House white",
            "188", "House light gray",
            "189", "House dark gray",
            "190", "Entrench death"
    };

    tiles["decorate"] = {
            "24","Oak light grass",
            "443", "Oak light grass2",
            "25","Oak medium grass",
            "444","Oak medium grass2",
            "26","Oak dark grass",
            "445", "Oak dark grass2",
            "440", "Oak light stone",
            "441", "Oak medium stone",
            "442", "Oak dark stone",
            "447", "Spruce light",
            "448", "Spruce medium",
            "449", "Spruce dark",
            "277","Castel left top",
            "278", "Castel right top",
            "280", "Castel left bot",
            "281", "Castel right bot",
            "283", "House grass",
            "284", "Fountain grass"
    };
    tiles["teleport"] = {
            "13", "Stairs stone",
            "16","Tunnel wood frame",
            "17", "Tunnel wood frame deep"
    };

}
