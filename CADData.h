/*
 * @Author: shihan
 * @Date: 2024-07-05 11:09:35
 * @version: 1.0
 * @description: 
 */
#ifndef CADDATA_H
#define CADDATA_H

#include <unordered_map>
#include <memory>

struct Point {
    double x, y, z, lc;
};

struct Line {
    int start, end; // 使用点的索引
};

class CADData {
public:
    std::unordered_map<int, std::shared_ptr<Point> > points;
    std::unordered_map<int, std::shared_ptr<Line> > lines;
};

#endif // CADDATA_H
