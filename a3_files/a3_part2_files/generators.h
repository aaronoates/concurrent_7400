#pragma once
#include <vector>
#include "polygon.h"
using namespace std;

/**
 * Generate a vector of non-intersecting polygons.  Uses a sequential algorithm.
 * 
 * @param config The configuration used to control the generation of each polygon.
 * @param numPolys The number of polygons to generate.
 * @param useBreak A flag indicating whether to use a break statement during generation.
 * @return A vector of non-intersecting polygons.
 */
vector<Polygon> generateNonIntersectingPolygonsSeq(PolygonConfig config, int numPolys, bool useBreak);

/**
 * Generate a vector of non-intersecting polygons in parallel using OpenMP.
 * 
 * @param config The configuration used to control the generation of each polygon.
 * @param numPolys The number of polygons to generate.
 * @return A vector of non-intersecting polygons.
 */
vector<Polygon> generateNonIntersectingPolygonsOMP(PolygonConfig config, int numPolys);