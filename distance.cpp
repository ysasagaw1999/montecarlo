#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>

int main()
{
    double d = 112.33;      // shortest distance
    double ang = M_PI * 49.6 / 180; // angle of center
    double target[3] = { d / tan(ang), 0, d};
    double length_start = 35.036;
    double each_length = 6.399375;
    double angle_start = -1 * M_PI / 6;
    double each_angle = M_PI / 24;
    double distance[16][8];
    for (int f_ch=0; f_ch < 16; f_ch++)
    {
        double center_r = length_start + (f_ch + 0.5) * each_length;
        for (int r_ch=0; r_ch<8; r_ch++)
        {
            double center_th = angle_start + (r_ch + 0.5) * each_angle;
            double center[3] = {center_r * cos(center_th), center_r * sin(center_th), 0};
            double dis[3] = {target[0] - center[0], target[1] - center[1], target[2] - center[2]};
            distance[f_ch][r_ch] = sqrt(dis[0]*dis[0] + dis[1]*dis[1] + dis[2]*dis[2]);
        }
    }

    std::ofstream opfile("distance.txt");
    for (int f_ch=0; f_ch < 16; f_ch++)
    {
        for (int r_ch=0; r_ch<8; r_ch++)
        {
            opfile << distance[f_ch][r_ch] << ", ";
        }

        opfile << "\n";
    }

    return 0;
}