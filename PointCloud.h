#pragma once

#include <vector>
#include <string>
#include <iostream>

struct Point {
	double x;
	double y;
	double z;
};

class PointCloud {
 public:
	std::vector<Point> points{};

	PointCloud(const std::string& path);

	void printPoint(const std::size_t& index) {
		if (index <= points.size() && index >= 0) {
			Point point{points[index]};
      std::cout << "x: " << point.x << ", y: " << point.y
                << ", z: " << point.z << '\n';
		} else {
			std::cout << "Index is out of range!" << '\n';
		}
	}
};

