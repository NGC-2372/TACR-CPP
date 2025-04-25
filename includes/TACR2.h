// TACR-CPP.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。

#ifndef TACR_H
#define TACR_H

#pragma once

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <commonmath.h>
#include <convexoptimization.h>
#include <numericalpde.h>
#include <timemanagement.h>
using namespace ContinuumRobotLibrary;

class TACR {
public:
    TACR();
    void initialize();
    void step(double dt);
    double getEndPosition() const;
    double getReferencePosition() const;

private:
    // 参数
    double L = 0.4;
    int N = 80;
    double E = 208e9;
    double rho = 8000;
    double dt = 0.05;

    // 状态变量
    Eigen::Vector3d p_end;
    double current_time = 0.0;

    // 控制参数
    const double T = 10.0;
    const double xd0_a = 0.07;
    const double xd0_b = M_PI / 10;
    const double xd0_c = 0.11;

    void solveStaticIVP();
    void solveDynamicIVP();
    void controlAlgorithm();
};

#endif // TACR_H