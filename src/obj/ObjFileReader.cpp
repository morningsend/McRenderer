//
// Created by Zaiyang Li on 08/02/2018.
//

#include "ObjFileReader.hpp"

#include <utility>
#include <sstream>
#include <iostream>


namespace McRenderFace {
    using namespace std;
    void readVertex(istream& stream, glm::vec3& vec) {
        stream >> vec.x;
        stream >> vec.y;
        stream >> vec.z;
    }
    void readTextureCoord(istream& stream, glm::vec2& vec) {
        stream >> vec.x;
        stream >> vec.y;
    }
    void readFaces(istream& stream, vector<ObjFace>& faces) {
        ObjFace face;
        int i = 0;
        char charTemp;
        int vi = 0, ti = 0, ni = 0;
        while(i < 3){
            vi = 0; ti = 0; ni = 0;
            stream >> vi;
            if(stream.peek() == '/') {
                stream.get();
                charTemp = static_cast<char>(stream.get());
                if(isdigit(charTemp)) {
                    stream.unget();
                    stream >> ti;
                }
            }
            if(stream.peek() == '/') {
                stream.get();
                stream >> ni;
            }
            face.vertex[i] = vi - 1;
            face.normal[i] = ni - 1;
            face.uvCoord[i] = ti - 1;
            i++;
        }
        faces.push_back(face);
    }
    ObjFileReader::ObjFileReader(const std::string& filePath): filePath{filePath} {

    }

    ObjFileReader::ObjFileReader(const char *filePath):filePath{filePath} {

    }

    std::unordered_map<string, ObjModel*> ObjFileReader::read() {
        ifstream inputFile(filePath, ios::in);
        if(!inputFile) {
            throw runtime_error("file not found: " +filePath);
        }

        char lineBuffer[256];
        std::unordered_map<string, ObjModel*> models;
        ObjModel* model = new ObjModel();
        glm::vec3 vec3Temp;
        glm::vec2 vec2Temp;
        string prefix;
        string stringTemp;
        int faceCount = 0;

        while(inputFile.getline(lineBuffer, 256)) {
            std::istringstream stream(lineBuffer);
            stream >> prefix;

            if(prefix == "#"){
                continue;
            }
            else if(prefix == "g") {
                stream >> stringTemp;
                if(models.find(stringTemp) == models.end()) {
                    models[stringTemp] = model;
                    model->modelName = stringTemp;
                }
            }
            else if (prefix == "v") {
                readVertex(stream, vec3Temp);
                model->vertices.push_back(vec3Temp);
            } else if(prefix == "vt") {
                readTextureCoord(stream, vec2Temp);
                (*model).uvCoords.push_back(vec2Temp);
            } else if(prefix == "usemtl") {
                stream >> stringTemp;
                (*model).materialName = stringTemp;
            } else if(prefix == "vn") {
                readVertex(stream, vec3Temp);
                (*model).normals.push_back(vec3Temp);
            } else if(prefix == "f") {
                faceCount++;
                //cout << lineBuffer << ' ' << faceCount << endl;
                readFaces(stream, (*model).faces);
            } else if(prefix == "mtllib") {
                stream >> stringTemp;
            }
            prefix = "";
            stringTemp = "";
            vec3Temp = glm::vec3(0);
            vec2Temp = glm::vec2(0);
        }

        cout<<"hello" << endl;
        return models;
    }

}
