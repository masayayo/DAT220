//
// Created by Chrim14 on 16.11.2017.
//

#include "Direction.h"


std::vector<int> Direction::setDirection(int direction, sf::Vector2i position, Settings &json) {

    std::vector<int> vector;
    int count = 0;

    do{
        if(direction == 0){
            if(position.y > 0 && json.bitTileValue[position.x*Bits_To_Tiles][(position.y-1)*Bits_To_Tiles] == 1){
                count++;
                position.y--;
            }
            else{
                vector.push_back(direction);
                vector.push_back(count);
                count = 0;
                if(position.x > 0 && json.bitTileValue[(position.x-1)*Bits_To_Tiles][position.y*Bits_To_Tiles] == 1) direction = 3;
                else if(position.x < json.map["width"] && json.bitTileValue[(position.x+1)*Bits_To_Tiles][position.y*Bits_To_Tiles] == 1) direction = 1;
                else{
                    //get the next node value;
                    int value = json.bitTileValue[position.x*Bits_To_Tiles][(position.y-1)*Bits_To_Tiles];
                    if(value != 0 && value != 2 && value != 8){
                        position.y--;
                        count = value;
                    }
                    else
                        count = -1;
                    break;
                };
            }
        }
        else if(direction == 1){
            if(position.x < json.map["width"] && json.bitTileValue[(position.x+1)*Bits_To_Tiles][position.y*Bits_To_Tiles] == 1){
                count++;
                position.x++;
            }
            else{
                vector.push_back(direction);
                vector.push_back(count);
                count = 0;
                if(position.y > 0 && json.bitTileValue[position.x*Bits_To_Tiles][(position.y-1)*Bits_To_Tiles] == 1) direction = 0;
                else if(position.y < json.map["height"] && json.bitTileValue[position.x*Bits_To_Tiles][(position.y+1)*Bits_To_Tiles] == 1) direction = 2;
                else{
                    //get the next node value;
                    int value = json.bitTileValue[(position.x+1)*Bits_To_Tiles][position.y*Bits_To_Tiles];
                    if(value != 0 && value != 2 && value != 8){
                        count = value;
                        position.x++;
                    }
                    else
                        count = -1;
                    break;
                };
            }
        }
        else if(direction == 2){
            if(position.y < json.map["height"] && json.bitTileValue[position.x*Bits_To_Tiles][(position.y+1)*Bits_To_Tiles] == 1){
                count++;
                position.y++;
            }
            else{
                vector.push_back(direction);
                vector.push_back(count);
                count = 0;
                if(position.x > 0 && json.bitTileValue[(position.x-1)*Bits_To_Tiles][position.y*Bits_To_Tiles] == 1) direction = 3;
                else if(position.x < json.map["width"] && json.bitTileValue[(position.x+1)*Bits_To_Tiles][position.y*Bits_To_Tiles] == 1) direction = 1;
                else{
                    //get the next node value;
                    int value = json.bitTileValue[position.x*Bits_To_Tiles][(position.y+1)*Bits_To_Tiles];
                    if(value != 0 && value != 2 && value != 8){
                        position.y++;
                        count = value;
                    }
                    else
                        count = -1;
                    break;
                };
            }
        }
        else if(direction == 3){
            if(position.x > 0 && json.bitTileValue[(position.x-1)*Bits_To_Tiles][position.y*Bits_To_Tiles] == 1){
                count++;
                position.x--;
            }
            else{
                vector.push_back(direction);
                vector.push_back(count);
                count = 0;
                if(position.y > 0 && json.bitTileValue[position.x*Bits_To_Tiles][(position.y-1)*Bits_To_Tiles] == 1) direction = 0;
                else if(position.y < json.map["height"] && json.bitTileValue[position.x*Bits_To_Tiles][(position.y+1)*Bits_To_Tiles] == 1) direction = 2;
                else{
                    //get the next node value;
                    int value = json.bitTileValue[(position.x-1)*Bits_To_Tiles][position.y*Bits_To_Tiles];
                    if(value != 0 && value != 2 && value != 8){
                        position.x--;
                        count = value;
                    }
                    else
                        count = -1;
                    break;
                };
            }
        }
        else break;

    }while(count < Layer_One_Size);
    //IF vector not empty take last value and increase by one;
    if(!vector.empty()){
        vector[vector.size()-1] = vector[vector.size()-1]+1;
    }
    vector.push_back(position.y);
    vector.push_back(position.x);
    vector.push_back(count);

    //std::cout << "next node: " << count << std::endl;
    //std::cout << "Destination: " << position.x << ", " << position.y << std::endl;

    std::vector<int> vector2;

    for (int i = (unsigned int) vector.size()-1; i >= 0; --i) {
        vector2.push_back(vector[i]);
    }
/*
    for(auto& temp : vector2){
        std::cout << temp << ", ";
    }
    std::cout << std::endl;
*/
    return vector2;
}

int Direction::giveDirection(std::vector<int> directions, std::vector<int> weighs) {

    //Getting all weights
    int north = weighs.at(0);
    int east = weighs.at(1);
    int south = weighs.at(2);
    int west = weighs.at(3);

    //If no direction set to 0;
    if(directions.at(0) == 0) north = 0;
    if(directions.at(1) == 0) east = 0;
    if(directions.at(2) == 0) south = 0;
    if(directions.at(3) == 0) west = 0;

    if(directions.at(0) == 0 && directions.at(1) == 0 && directions.at(2) == 0 && directions.at(3) == 0) return -1; //No direction

    int d[] = {north,east,south,west};//Stores value before changed

    if(directions.at(1) == 1) east = d[0] + d[1];
    if(directions.at(2) == 1) south = d[0] + d[1] + d[2];
    if(directions.at(3) == 1) west = d[0] + d[1] + d[2] + d[3];

    int iSecret = rand() % 101;
    if(north > 0 && iSecret < north) return 0;
    if(east > 0 && iSecret < east) return 1;
    if(south > 0 && iSecret < south) return 2;
    if(west > 0 && iSecret < west) return 3;

    do {
        iSecret = rand() % 4;
        if(directions[iSecret] == 1) return iSecret;
    }while(true);
}
