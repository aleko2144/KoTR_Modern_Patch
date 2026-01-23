#include <cmath>

#include "CVector.h"

CVector::CVector(){
	x = 0;
	y = 0;
	z = 0;
};
	
void CVector::setFromArgs(float _x, float _y, float _z){
	x = _x;
	y = _y;
	z = _z;
};

void CVector::setFromPtr(float* ptr){
	x = ptr[0];
	y = ptr[1];
	z = ptr[2];
};
	
long double CVector::getLength(){
	return sqrt(x * x + y * y + z * z);
};
	
CVector CVector::normalize(){
	CVector result;
	float coeff = (1.0 / sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2)));
	result.x = this->x * coeff;
	result.y = this->y * coeff;
	result.z = this->z * coeff;
	return result;
};
	
CVector CVector::operator+ (const CVector& rhs){
	CVector result;
	result.x = this->x + rhs.x;
	result.y = this->y + rhs.y;
	result.z = this->z + rhs.z;
	return result;
};

CVector CVector::operator- (const CVector& rhs){
	CVector result;
	result.x = this->x - rhs.x;
	result.y = this->y - rhs.y;
	result.z = this->z - rhs.z;
	return result;
};

CVector CVector::operator* (const long double& rhs){
	CVector result;
	result.x = this->x * rhs;
	result.y = this->y * rhs;
	result.z = this->z * rhs;
	return result;
};
	
CVector CVector::operator* (const CVector& rhs){
	CVector result;
	result.x = this->x * rhs.x;
	result.y = this->y * rhs.y;
	result.z = this->z * rhs.z;
	return result;
};

CVector CVector::CrossProduct(CVector a1, CVector a2){
	CVector result;
	result.x = a1.y * a2.z - a1.z * a2.y;
	result.y = -(a1.x * a2.z - a1.z * a2.x);
	result.z = a1.x * a2.y - a1.y * a2.x;
	return result;
}

CVector* CVector::CrossProduct(CVector *a1, CVector *a2, CVector *a3){
	float v3; // ST00_4
	float v4; // ST04_4
	CVector *result; // eax
	double v6; // st7
	float v7; // ST08_4

	v3 = a3->z * a2->y - a2->z * a3->y;
	v4 = a2->z * a3->x - a3->z * a2->x;
	result = a1;
	v6 = a3->y * a2->x - a3->x * a2->y;
	a1->x = v3;
	v7 = v6;
	a1->y = v4;
	a1->z = v7;
	return result;
}

CVector * CVector::GetNormalized(CVector *out, CVector *in){
	CVector *v2; // ecx
	CVector *result; // eax
	double v4; // st7
	double v5; // st6
	float len; // [esp+8h] [ebp+8h]

	v2 = in;
	len = sqrt(in->x * in->x + in->y * in->y + in->z * in->z);
	if ( len >= 0.00001 ){
		v4 = v2->z / len;
		result = out;
		v5 = v2->y / len;
		out->x = v2->x / len;
		out->y = v5;
		out->z = v4;
	} else {
		result = out;
		out->x = 0;
		out->y = 0;
		out->z = 0;
	}
	return result;
}

CVector * CVector::GetScaled(CVector *in, float scale){
	CVector *result;

	result = in;
	in->x = in->x * scale;
	in->y = in->y * scale;
	in->z = in->z * scale;

	return result;
}

CVector * CVector::GetScaled(CVector *in, CVector *out, float scale){
	CVector *result;

	result = out;
	out->x = in->x * scale;
	out->y = in->y * scale;
	out->z = in->z * scale;

	return result;
}

CVector * CVector::sub_4BDF60(CVector *a1, CVector *a2, CVector *a3){
	float v3; // ST00_4
	float v4; // ST04_4
	CVector *result; // eax
	double v6; // st7
	float v7; // ST08_4

	v3 = a3->z * a2->y - a2->z * a3->y;
	v4 = a2->z * a3->x - a3->z * a2->x;
	result = a1;
	v6 = a3->y * a2->x - a3->x * a2->y;
	a1->x = v3;
	v7 = v6;
	a1->y = v4;
	a1->z = v7;
	return result;
}

CVector * CVector::FloatDivide(CVector *a1, CVector *divisible, float divider){
	a1->x = divisible->x / divider;
	a1->y = divisible->y / divider;
	a1->z = divisible->z / divider;

	//CVector* result = a1;
	//return result;

	return a1;
}

CVector * CVector::FloatDivide(CVector *a1, float *divisible, float divider){
	a1->x = divisible[0] / divider;
	a1->y = divisible[1] / divider;
	a1->z = divisible[2] / divider;

	//CVector* result = a1;
	//return result;

	return a1;
}

CVector * CVector::LinearDivide(CVector *a1, CVector *a2, CVector *a3){
	a1->x = a2->x / a3->x;
	a1->y = a2->y / a3->y;
	a1->z = a2->z / a3->z;

	return a1;
}

CVector * CVector::LinearAdd(CVector *a1, CVector *a3){
	CVector *result;

	a1->x = a3->x + a1->x;
	a1->y = a3->y + a1->y;
	a1->z = a3->z + a1->z;

	result = a1;
	
	return result;
}

CVector * CVector::LinearAdd(CVector *a1, CVector *a2, CVector *a3){
	CVector *result;

	a1->x = a3->x + a1->x;
	a1->y = a3->y + a1->y;
	result = a2;
	a1->z = a3->z + a1->z;
	*a2 = *a1;
	
	return result;
}

/*
	static CVector MultiplyOnMatrix(CVector a1, const CMatrix& mtx);
	static CVector * MulMatrix_(CVector *out, CVector *a2, CMatrix *a3);

CVector CVector::MultiplyOnMatrix(CVector a1, const CMatrix& mtx){
	CVector result; 

	result.x = mtx.right.x * a1.x + mtx.right.y * a1.y + mtx.right.z * a1.z;
	result.y = mtx.top.x * a1.x + mtx.top.y * a1.y + mtx.top.z * a1.z;
	result.z = mtx.at.x * a1.x + mtx.at.y * a1.y + mtx.at.z * a1.z;

	return result;	
}

CVector * CVector::MulMatrix_(CVector *out, CVector *a2, CMatrix *a3){
	CVector *v3; // eax
	double v4; // st7
	double v5; // st6
	double v6; // st5
	CVector *result; // eax
	float v8; // [esp+8h] [ebp+8h]

	v3 = a2;
	v4 = a3->at.y * a2->z + a3->top.y * a2->y + a3->right.y * a2->x;
	v8 = a3->at.z * a2->z + a3->top.z * a2->y + a3->right.z * a2->x;
	v5 = a3->at.x * v3->z + a3->top.x * v3->y;
	v6 = v3->x * a3->right.x;
	result = out;
	out->z = v8;
	out->x = v5 + v6;
	out->y = v4;
	return result;
}
*/