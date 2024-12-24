#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>

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
    bool for_distance = false;
    bool for_angle = false;
    if (length <= 137.426 && length > 35.036)
    {
        for_distance = true;
    }
    if (theta <= M_PI / 6 && theta > (-1) * M_PI / 6)
    {
        for_angle = true;
    }
    return for_angle && for_distance;
}

int frontWhichChannel(double length)
{
    double length_start = 35.036;
    double width = 6.399375;
    int front_ch = 16; // 初期化

    for (int i = 0; i < 16; i++)
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
    double each_angle = M_PI / 24;
    int rear_ch = 8; // 初期化

    for (int i = 0; i < 8; i++)
    {
        double start_angle = i * each_angle - 1 * M_PI / 6;
        double finish_angle = (i + 1) * each_angle - 1 * M_PI / 6;
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
        double distance = -112.33;      // shortest distance
        double ang = M_PI * 49.6 / 180; // angle of center
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

    for (int i = 0; i < 16; i++)
    {
        opfile3 << "front_ch" << i << "__" << front_count[i] << "\n";
        all_count[0] += front_count[i];
    }

    for (int i = 0; i < 8; i++)
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
