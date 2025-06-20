#include <chrono>
#include "omp.h"
#include "polygon.h"
#include "generators.h"

using std::string, std::cout, std::cerr, std::endl, std::stoi;
using namespace std::chrono;

// Checks for intersections between all pairs of polygons.
bool checkForIntersections(const vector<Polygon>& polys) {
    int n = polys.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (polys[i].polyline.intersects(polys[j].polyline)()) {
                return false;
            }
        }
    }

    // We made it here, so no intersections were found.
    return true;
}

// Sets the collided flag for polygons that intersect with one another.
void markCollisions(vector<Polygon>& polys) {
    int n = polys.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (polys[i].polyline.intersects(polys[j].polyline)()) {
                polys[i].collided = true;
                polys[j].collided = true;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    // Deal with command-line arguments.  There must be four, in addition to the program name.
    if (argc != 5) {
        cout << "Usage: " << argv[0] << " NUM_POLYGONS VARIANT NUM_THREADS RANDOM_SEED" << endl;
        cout << "  NUM_POLYGONS: The number of polygons to place." << endl;
        cout << "  VARIANT: 0 for sequential version without break" << endl;
        cout << "           1 for sequential version with break" << endl;
        cout << "           2 for OpenMP" << endl;
        cout << "  NUM_THREADS: The number threads to use when VARIANT >= 2." << endl;
        cout << "  RANDOM_SEED: The seed for the random number generator." << endl;
        exit(0);
    }

    int numPolys = stoi(argv[1]);
    int variant = stoi(argv[2]);
    int numThreads = stoi(argv[3]);
    int randomSeed = stoi(argv[4]);

    PolygonConfig config;
    config.minX = 0;
    config.maxX = 800;
    config.minY = 0;
    config.maxY = 600;
    config.minSides = 3;
    config.maxSides = 6;
    config.minRadius = 5;
    config.maxRadius = 50;

    // Seed the random number generator
    srand(randomSeed);

    // Check time before generating polygons
    auto beforeTime = high_resolution_clock::now();

    vector<Polygon> polys;
    if (variant == 0) {
        polys = generateNonIntersectingPolygonsSeq(config, numPolys, false);
    } else if (variant == 1) {
        polys = generateNonIntersectingPolygonsSeq(config, numPolys, true);
    } else {
        omp_set_num_threads(numThreads);
        polys = generateNonIntersectingPolygonsOMP(config, numPolys);
    }

    // Compute the duration
    auto afterTime = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(afterTime - beforeTime);
    int durationInt = static_cast<int>(duration.count());

    // Check that there were actually no intersections
    if (!checkForIntersections(polys)) {
        cerr << "Error: Intersections found!" << endl;
        markCollisions(polys);
        renderToSVG(config, "polygons.svg", polys);
        return 1; // Return 1 to indicate an error.
    }

    // No errors were found.  Print runtime, render, and exit.
    cout << durationInt << endl;
    renderToSVG(config, "polygons.svg", polys);
    return 0;
}