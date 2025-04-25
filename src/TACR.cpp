#include "TACR.h"
using namespace TACRnamespace;
//静态常量初始化
//独立参数
const double TACR::L = 0.4;      
const int    TACR::N = 80;        
const int    TACR::NL = N + 1;   
const double TACR::E = 208e9;    
const double TACR::radius = 0.001;     
const double TACR::rho = 8000;    
const Vector3d TACR::g = -9.81 * Vector3d::UnitX();  
const double TACR::dt = 5e-2;   
const double TACR::alpha = -0.2;  
const double TACR::T = 10;
const int TACR::STEPS = static_cast<int>(T / dt);

const DiagonalMatrix<double, 3> TACR::Bse = DiagonalMatrix<double, 3>(0, 0, 0);//对角矩阵
const DiagonalMatrix<double, 3> TACR::Bbt = DiagonalMatrix<double, 3>(5e-4, 5e-4, 5e-4);
const DiagonalMatrix<double, 3> TACR::C = DiagonalMatrix<double, 3>(1e-4, 1e-4, 1e-4);

//绳索参数
const int TACR::num_tendons = 4;
typedef Array<double, TACR::num_tendons, 1> ArrayNd;
//const ArrayNd compliance = ArrayNd::Constant(1e-4);
const double TACR::tendon_offset = 0.02;
const Vector3d TACR::ri[TACR::num_tendons] = { tendon_offset * Vector3d::UnitX() };//三行，num_tendons列 数组

//依赖参数计算
const double TACR::G = E / (2 * 1.3);
const double TACR::A = pi * pow(radius, 2);
const double TACR::I = pi * pow(radius, 4) / 4;
const DiagonalMatrix<double, 3> TACR::J = DiagonalMatrix<double, 3>(I, I, 2 * I);
const DiagonalMatrix<double, 3> TACR::Kse = DiagonalMatrix<double, 3>(G * A, G * A, E * A);
const DiagonalMatrix<double, 3> TACR::Kbt = DiagonalMatrix<double, 3>(E * I, E * I, G * 2 * I);
const Matrix3d TACR::Kse_dense = Kse.toDenseMatrix();
const Matrix3d TACR::Kbt_dense = Kbt.toDenseMatrix();
const Matrix3d TACR::Kse_c0Bse = Kse.toDenseMatrix() + c0 * Bse.toDenseMatrix();
const Matrix3d TACR::Kbt_c0Bbt = Kbt.toDenseMatrix() + c0 * Bbt.toDenseMatrix();
const Vector3d TACR::rhoAg = rho * A * g;
const double TACR::rhoA = rho * A;
const DiagonalMatrix<double, 3> TACR::rhoJ = rho * J;

//BDF - alpha coefficients
const double TACR::ds = L / N;
const double TACR::c0 = (1.5 + alpha) / (dt * (1 + alpha));
const double TACR::c1 = -2 / dt;
const double TACR::c2 = (0.5 + alpha) / (dt * (1 + alpha));
const double TACR::d1 = alpha / (1 + alpha);

// 参考轨迹参数
const double TACR::xd0_a = 0.07;
const double TACR::xd0_b = pi / T;
const double TACR::xd0_c = 0.11;


TACR::TACR() {
cout << "TACR constructor called" << endl;
cout << "rhoAg: " << rhoAg << endl;
cout << ri[0] << endl;
}

TACR::~TACR() {
cout << "TACR destructor called" << endl;
}

void TACR::initXTipValues(double T, double dt) {
	vector<double> XTipValues((int)(T / dt) + 1, 0.0);
}

double TACR::getXTipPosition(double time) const {
	return xd0_a * cos(xd0_b * time);
}

//X-Tip 参考轨迹
double TACR::getRefePosition(double time) const {
   return xd0_a * sin(xd0_b * time) + xd0_c;
}

//保存X-Tip位置
void TACR::saveXTipPosition(double xTipValue){
	XTipValues.emplace_back(xTipValue);
}