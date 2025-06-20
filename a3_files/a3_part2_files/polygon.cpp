#include "polygon.h"
using namespace h2d;
using namespace std;

int randInt(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

double randDouble(double min, double max)
{
    return (max - min) * ((double)rand() / RAND_MAX) + min;
}

void renderToSVG(PolygonConfig config, string filename, vector<Polygon> &gons) {
    int width = config.maxX - config.minX + 1;
    int height = config.maxY - config.minY + 1;
    img::Image<img::SvgImage> image(width, height);
    for (int i = 0; i < gons.size(); i++) {
        img::DrawParams params;
        if (gons[i].collided) {
            params.setColor(img::Color(255, 0, 0));
        } else {
            params.setColor(img::Color(0, 0, 0));
        }
        gons[i].polyline.draw(image, params);
    }
    image.write(filename);
}