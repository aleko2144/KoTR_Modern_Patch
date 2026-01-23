#include <cmath>
#include <cfloat>

#include "CMatrix.h"


CMatrix::CMatrix(){
	right.x = 0;
	right.y = 0;
	right.z = 0;

	top.x = 0;
	top.y = 0;
	top.z = 0;

	at.x = 0;
	at.y = 0;
	at.z = 0;

	pos.x = 0;
	pos.y = 0;
	pos.z = 0;
};

CVector CMatrix::GetRadians(){
	CVector result;

	double cy = sqrt(this->at.z*this->at.z + this->at.x*this->at.x);

	if (cy > 16*FLT_EPSILON){
		result.z = (float) atan2(this->right.y, this->top.y);
		result.x = (float) atan2(- this->at.y, (float) cy);
		result.y = (float) atan2(this->at.x, this->at.z);
	} else {
		result.z = (float) atan2(- this->top.x, this->right.x);
		result.x = (float) atan2(- this->at.y, (float) cy);
		result.y = 0;
	}

	return result;

	//rot.x = ((x_d * 180) / PI);
	//rot.y = ((y_d * 180) / PI);
	//rot.z = ((z_d * 180) / PI);
	
	//return rot;
};

CMatrix* CMatrix::MatrixMultiply(CMatrix *out, CMatrix *a2, CMatrix *a3){
	typedef CMatrix* (* MatrixMultiply)(CMatrix *out, CMatrix *a2, CMatrix *a3);
	return MatrixMultiply(0x5AB9C0)(out, a2, a3);
}

