#include "generators.h"

vector<Polygon> generateNonIntersectingPolygonsSeq(PolygonConfig config, int numPolys, bool useBreak) {
    vector<Polygon> polys;

    while (polys.size() < numPolys) {
        Polygon p(config);
        bool intersects = false;
        for (const Polygon& poly : polys) {
            if (p.polyline.intersects(poly.polyline)()) {
                intersects = true;
                if (useBreak)
                    break;
            }
        }

        if (!intersects)
            polys.push_back(p);
    }

    return polys;
}

vector<Polygon> generateNonIntersectingPolygonsOMP(PolygonConfig config, int numPolys) {
    vector<Polygon> polys;

    // STUDENTS: Implement this function to fill the polys vector with numPolys 
    // non-intersecting polygons.



    return polys;
}
