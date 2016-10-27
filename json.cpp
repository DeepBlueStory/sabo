#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include "json.h"

void convertToJson(std::vector<std::vector<int>> & frqis, 
        std::vector<int> & frq,
        std::vector<std::string> & label) {
    std::ofstream jsondat("sample.json");
        std::unordered_map<int, int> mapnodesize; 
        std::unordered_map<std::string, int> mapedgesize;
        std::unordered_map<std::string, std::pair<int, int>> edgesourtar;
        getNodeEdge(frqis, frq, mapnodesize, mapedgesize, edgesourtar);
        jsondat << "{";
        jsondat << "\"edges\":[";
        for(auto edge : mapedgesize) {
            jsondat << "{";
            jsondat << "\"source\":\"";
            jsondat << edgesourtar[edge.first].first;
            jsondat << "\",\"target\":\"";
            jsondat << edgesourtar[edge.first].second;
            jsondat << "\",\"size\":\"";
            jsondat << edge.second;
            jsondat << "\",\"id\":\"";
            jsondat << edge.first;
            jsondat << "\"},";
        }
        jsondat.seekp(-1, std::ios::cur);
        jsondat << "],\"nodes\":[";
        for(auto node : mapnodesize) {
            jsondat << "{";
            jsondat << "\"id\":\"";
            jsondat << node.first;
            jsondat << "\",\"label\":\"";
            jsondat << label[node.first];
            jsondat << "\",\"size\":\"";
            jsondat << node.second;
            jsondat << "\"},";
        }
        jsondat.seekp(-1, std::ios::cur);
        jsondat << "]}";
        jsondat.close();
}

void getNodeEdge(std::vector<std::vector<int>> & frqis, 
        std::vector<int> & frq,
        std::unordered_map<int, int> & mapnodesize, 
        std::unordered_map<std::string, int> & mapedgesize, 
        std::unordered_map<std::string, std::pair<int, int>> & edgesourtar) {
    for(int i = 0; i < frqis.size(); i++) {
        if(frqis[i].size() > 1) 
        for(int j = 0; j < frqis[i].size(); j++) {
            for(int k = j+1; k < frqis[i].size(); k++) {
                std::pair<int, int> edge;
                edge.first = frqis[i][j];
                edge.second = frqis[i][k];
                std::string id = std::to_string(edge.first) + std::to_string(edge.second);
                std::string idc = std::to_string(edge.second) + std::to_string(edge.first);
                if(mapedgesize.find(id) == mapedgesize.end()) {
                    if(mapedgesize.find(idc) == mapedgesize.end()) {
                        mapedgesize[id] = frq[i];
                        edgesourtar[id] = edge;
                    } else {
                        mapedgesize[idc] += frq[i];
                    }
                } else {
                    mapedgesize[id] += frq[i];
                }
            }
            if(mapnodesize.find(frqis[i][j]) == mapnodesize.end()) 
                mapnodesize[frqis[i][j]] = frq[i];
            else 
                mapnodesize[frqis[i][j]] += frq[i];
        }
    }
}
