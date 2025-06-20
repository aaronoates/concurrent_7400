#pragma once
#include <string>
#include "homog2d.hpp"
using namespace h2d;
using namespace std;

int randInt(int min, int max);

double randDouble(double min, double max);

struct PolygonConfig {
    double minX;
    double maxX;
    double minY;
    double maxY;
    int minSides;
    int maxSides;
    double minRadius;
    double maxRadius;
};

struct Polygon
{
    CPolyline polyline;
    bool collided = false;

    Polygon() {}

    Polygon(PolygonConfig config) {
        int numSides = randInt(config.minSides, config.maxSides);

        // Choose a random centre point from which to generate the actual
        // points for this polygon.
        double centreX = randDouble(config.minX + config.maxRadius, config.maxX - config.maxRadius);
        double centreY = randDouble(config.minY + config.maxRadius, config.maxY - config.maxRadius);

        vector<Point2d> pts;
        for (int j = 0; j < numSides; j++) {
            double radius = randDouble(config.minRadius, config.maxRadius);
            double angle = 2 * M_PI * j / numSides;
            double x = centreX + radius * cos(angle);
            double y = centreY + radius * sin(angle);
            pts.push_back(Point2d(x, y));
        }
        polyline = CPolyline(pts);
    }

    // Overload the << operator to print the polygon.
    friend ostream& operator<<(ostream& os, const Polygon& polygon) {
        os << "Polygon: ";
        for (const Point2d& point : polygon.polyline.getPts()) {
            os << "(" << point.getX() << ", " << point.getY() << ") ";
        }
        return os;
    }
};

void renderToSVG(PolygonConfig config, string filename, vector<Polygon> &gons);