#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include "geometry.h"

void randomPointOnHalfSphere(double *dx, double *dy, double *dz)
{
    double phi = (static_cast<double>(std::rand()) / RAND_MAX) * 2 * M_PI; // 0~2π
    *dz = (static_cast<double>(std::rand()) / RAND_MAX) - 1;               // -1~0
    double theta = std::acos(*dz);
    *dx = std::sin(theta) * std::cos(phi);
    *dy = std::sin(theta) * std::sin(phi);
}

bool Touch(double length, double theta)
{
    bool for_length = false;
    bool for_angle = false;
    if (length <= max_length && length > min_length)
    {
        for_length = true;
    }
    if (theta <= max_angle && theta > min_angle)
    {
        for_angle = true;
    }
    return for_angle && for_length;
}

int frontWhichChannel(double length)
{
    double length_start = min_length;
    double width = (max_length - min_length)/f_ch;
    int front_ch = f_ch; // 初期化

    for (int i = 0; i < f_ch; i++)
    {
        double start_length = i * width + length_start;
        double finish_length = (i + 1) * width + length_start;
        if (length > start_length && length <= finish_length)
        {
            front_ch = i;
            break;
        }
    }
    return front_ch; // ペアを返す
}

int rearWhichChannel(double theta)
{
    double each_angle = (max_angle - min_angle)/r_ch;
    int rear_ch = r_ch; // 初期化

    for (int i = 0; i < r_ch; i++)
    {
        double start_angle = i * each_angle - max_angle;
        double finish_angle = (i + 1) * each_angle - max_angle;
        if (theta > start_angle && theta <= finish_angle)
        {
            rear_ch = i;
            break;
        }
    }
    return rear_ch; // ペアを返す
}

int main()
{
    const int trials = 10000000; // number of attempts
    std::srand(std::time(0));     // 乱数のシードを設定
    double front_count[17] = {0}, rear_count[9] = {0};
    std::vector<double> onSakraX;
    std::vector<double> onSakraY;
    std::vector<double> outSakraX;
    std::vector<double> outSakraY;
    for (int i = 0; i < trials; ++i)
    {
        double dx, dy, dz;
        randomPointOnHalfSphere(&dx, &dy, &dz);
        double x_center = distance / std::tan(ang);
        if (dz != 0)
        {
            double r = distance / dz;
            double x = dx * r;
            double y = dy * r;
            double z = dz * r;

            double length, theta;

            double x_r = x - x_center;
            length = std::sqrt(x_r * x_r + y * y);
            theta = std::atan(y / x_r);
            bool touch = Touch(length, theta);
            if (touch)
            {
                int frontchannel = frontWhichChannel(length);
                int rearchannel = rearWhichChannel(theta);
                front_count[frontchannel] += 1;
                rear_count[rearchannel] += 1;

                onSakraX.push_back(x);
                onSakraY.push_back(y);
            }else{
                outSakraX.push_back(x);
                outSakraY.push_back(y);
            }
        }
    }

    std::ofstream opfile("onSakra.dat");
    for (size_t i = 0; i < onSakraX.size(); ++i)
    {
        opfile << onSakraX[i] << " , " << onSakraY[i] << "\n";
    }
    opfile.close();

    std::ofstream opfile2("outSakra.dat");
    for (size_t i = 0; i < outSakraX.size(); ++i)
    {
        opfile2 << outSakraX[i] << " , " << outSakraY[i] << "\n";
    }
    opfile2.close();

    int all_count[2] = {0,0};
    std::ofstream opfile3("output.txt");

    opfile3 << "trials__" << trials << "\n";

    for (int i = 0; i < f_ch; i++)
    {
        opfile3 << "front_ch" << i << "__" << front_count[i] << "\n";
        all_count[0] += front_count[i];
    }

    for (int i = 0; i < r_ch; i++)
    {
        opfile3 << "rear_ch" << i << "__" << rear_count[i] << "\n";
        all_count[1] += rear_count[i];
    }

    if (all_count[0]!=all_count[1])
    {
        std::cout << "error happened" << std::endl;
    }

    opfile3 << "all__" << all_count[0] << "\n";

    opfile3.close();

    return 0;

}
