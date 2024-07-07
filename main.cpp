/*
 * @Author: shihan
 * @Date: 2024-07-05 11:11:53
 * @version: 1.0
 * @description: 
 */
#include "GeoParser.h"


using namespace std;

int main(){
    GeoParser parser;

    // 读取和解析 example.geo 文件
    parser.readGeoFile("/Users/shihan/Desktop/t106a.geo");

    // 获取解析后的 CADData
    // std::shared_ptr<CADData> cadData = parser.getCADData();
    return 0;
}

