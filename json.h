#ifndef JSON_H
#define JSON_H

#include <vector>
#include <string>
#include <unordered_map>

void convertToJson(std::vector<std::vector<int>> & frqis, 
        std::vector<int> & frq,
        std::vector<std::string> & label);


void getNodeEdge(std::vector<std::vector<int>> & frqis, 
        std::vector<int> & frq,
        std::unordered_map<int, int> & mapnodesize, 
        std::unordered_map<std::string, int> & mapedgesize, 
        std::unordered_map<std::string, std::pair<int, int>> & edgesourtar);

#endif
