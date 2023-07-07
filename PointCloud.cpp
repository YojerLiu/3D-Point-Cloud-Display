#include "PointCloud.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <array>

PointCloud::PointCloud(const std::string& path) {
  std::vector<double> xCoords, yCoords, zCoords;
  std::ifstream inf{path};
  if (!inf) {
    std::cerr << "Failed to open the file!\n";
  }
  std::string line;
  while (std::getline(inf, line)) {
    if (line.empty()) {
      continue;
    }
    std::istringstream iss{line};
    double x, y, z;
    iss >> x >> y >> z;
    xCoords.push_back(x);
    yCoords.push_back(y);
    zCoords.push_back(z);
  }
  double sumX{std::accumulate(xCoords.begin(), xCoords.end(), 0.0)};
  double sumY{std::accumulate(yCoords.begin(), yCoords.end(), 0.0)};
  double sumZ{std::accumulate(zCoords.begin(), zCoords.end(), 0.0)};
  double length{static_cast<double>(xCoords.size())};
  double avrX{sumX / length};
  double avrY{sumY / length};
  double avrZ{sumZ / length};
  // translate the coordinates
  std::for_each(xCoords.begin(), xCoords.end(), [avrX](auto& e) { e -= avrX; });
  std::for_each(yCoords.begin(), yCoords.end(), [avrY](auto& e) { e -= avrY; });
  std::for_each(zCoords.begin(), zCoords.end(), [avrZ](auto& e) { e -= avrZ; });

  auto absCompare{[](double a, double b) { return std::abs(a) < std::abs(b); }};
  auto absMaxX{std::max_element(xCoords.begin(), xCoords.end(), absCompare)};
  auto absMaxY{std::max_element(yCoords.begin(), yCoords.end(), absCompare)};
  auto absMaxZ{std::max_element(zCoords.begin(), zCoords.end(), absCompare)};
  std::array<double, 3> potentialGammas{*absMaxX, *absMaxY, *absMaxZ};
  // find the maximum absolute value of all coordinates
  auto maxGammaIter{std::max_element(potentialGammas.begin(),
                                     potentialGammas.end(), absCompare)};
  double gamma{std::abs(*maxGammaIter)};
  // ensure all coordinates are in the valid range (aka., -1 to 1)
  auto division{[gamma](double& e) { e = e / gamma; }};
  std::for_each(xCoords.begin(), xCoords.end(), division);
  std::for_each(yCoords.begin(), yCoords.end(), division);
  std::for_each(zCoords.begin(), zCoords.end(), division);
  for (std::size_t i = 0; i < xCoords.size(); i++) {
    points.push_back(Point{xCoords[i], yCoords[i], zCoords[i]});
  }
}
