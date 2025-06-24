#include "generators.h"
#include <omp.h>
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

#include <omp.h>

vector<Polygon> generateNonIntersectingPolygonsOMP(PolygonConfig config, int numPolys) {
    vector<Polygon> polys; //creates a vector of Polygon objects
    omp_lock_t lock; // A type that holds the status of a lock, whether the lock is available or if a thread owns a lock.
    omp_init_lock(&lock); // initializes a lock at the address of the "lock" object.

    #pragma omp parallel // compiler directive to create a parallel region where multiple threads are executed in parallel.
    {
        while (true) {
            // Early exit: check if we've already added enough polygons
            omp_set_lock(&lock); // locks the lock
            if ((int)polys.size() >= numPolys) { //if the size of the polygons vector is greater than or equal to numPolys
                omp_unset_lock(&lock); //unlock the lock and break the loop
                break;
            }
            omp_unset_lock(&lock); //unlock the lock

            // Generate candidate polygon
            Polygon candidate(config);

            // Check for intersection with existing polygons (read-only, under lock)
            bool intersects = false;
            omp_set_lock(&lock);
            for (const Polygon& existing : polys) {
                if (candidate.polyline.intersects(existing.polyline)()) {
                    intersects = true;
                    break; // Early break on first intersection
                }
            }
            omp_unset_lock(&lock);

            // If no intersection, add it to the shared list (under lock)
            if (!intersects) {
                omp_set_lock(&lock);
                if ((int)polys.size() < numPolys) { // Recheck size in case it changed
                    polys.push_back(candidate);
                }
                omp_unset_lock(&lock);
            }
        }
    }

    omp_destroy_lock(&lock);
    return polys;
}
