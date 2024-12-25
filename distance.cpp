#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "geometry.h"

int main()
{
    double d = -1 * distance;      // shortest distance
    double target[3] = { d / tan(ang), 0, d};
    double length_start = min_length;
    double each_length = (max_length - min_length)/f_ch;
    double each_angle = (max_angle - min_angle)/r_ch;
    double distance[f_ch][r_ch];
    for (int f=0; f < f_ch; f++)
    {
        double center_r = length_start + (f + 0.5) * each_length;
        for (int r=0; r<r_ch; r++)
        {
            double center_th = min_angle + (r + 0.5) * each_angle;
            double center[3] = {center_r * cos(center_th), center_r * sin(center_th), 0};
            double dis[3] = {target[0] - center[0], target[1] - center[1], target[2] - center[2]};
            distance[f][r] = sqrt(dis[0]*dis[0] + dis[1]*dis[1] + dis[2]*dis[2]);
        }
    }

    std::ofstream opfile("distance.txt");
    for (int f=0; f < f_ch; f++)
    {
        for (int r=0; r<r_ch; r++)
        {
            opfile << distance[f][r] << ", ";
        }

        opfile << "\n";
    }

    return 0;
}