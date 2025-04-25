#ifndef TACR_H
#define TACR_H
#pragma once

#include <iostream>
#include <cmath>
#include <fstream>
#include <stdio.h>
#include <commonmath.h>
#include <convexoptimization.h>
#include <numericalpde.h>
#include <timemanagement.h>
using namespace ContinuumRobotLibrary;
using namespace std;

// 定义命名空间
namespace TACRnamespace {
    class TACR {
    public:
        TACR();
        ~TACR();
        void initXTipValues(double T, double dt);
        double getXTipPosition(double time) const;
        double getRefePosition(double time) const;
        void saveXTipPosition(double xTipValue);

    public:
        //独立参数
        static const double L;       // Length(before strain)
        static const int N;          // Spatial resolution
        static const int NL;        //末端节点
        static const double E;          // Young's modulus
        static const double radius; // Cross - section radius
        static const double rho;    // Density
        static const Vector3d g;    //Gravity
        static const double dt;     //Time step
        static const double alpha;  //BDF - alpha parameter
        static const double T;      //Total time
        static const int STEPS;     //Number of timesteps to completion

        static const DiagonalMatrix<double, 3> Bse;//对角矩阵
        static const DiagonalMatrix<double, 3> Bbt;
        static const DiagonalMatrix<double, 3> C;

        //绳索参数
        static const int num_tendons; // Number of tendons
        static const double tendon_offset;
        static const Vector3d ri[];

        //依赖参数计算
        static const double G;//Shear modulus
        static const double A;//Cross-sectional area
        static const double I;//Inertia
        static const DiagonalMatrix<double, 3> J;
        static const DiagonalMatrix<double, 3> Kse;
        static const DiagonalMatrix<double, 3> Kbt;
        static const Matrix3d Kse_dense;
        static const Matrix3d Kbt_dense;
        static const Matrix3d Kse_c0Bse;
        static const Matrix3d Kbt_c0Bbt;
        static const Vector3d rhoAg;
        static const double rhoA;
        static const DiagonalMatrix<double, 3> rhoJ;

        //BDF - alpha coefficients
        static const double ds; // Grid distance(before strain)  ds = L / N
        static const double c0;
        static const double c1;
        static const double c2;
        static const double d1;


        // 参考轨迹参数
        static const double xd0_a;
        static const double xd0_b;
        static const double xd0_c;


        vector<double> XTipValues;
    };
}
#endif // TACR_H