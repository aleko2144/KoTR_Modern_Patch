#ifndef CVECTOR_H
#define CVECTOR_H

class CVector {
public:
	float x;
	float y;
	float z;
	CVector();
	void setFromArgs(float _x, float _y, float _z);
	void setFromPtr(float* ptr);
	long double getLength();
	CVector CVector::normalize();
	CVector CVector::operator+ (const CVector& rhs);
	CVector CVector::operator- (const CVector& rhs);
	CVector CVector::operator* (const long double& rhs);
	CVector CVector::operator* (const CVector& rhs);

	static CVector CrossProduct(CVector a1, CVector a2);
	static CVector * CrossProduct(CVector *a1, CVector *a2, CVector *a3);

	static CVector * GetNormalized(CVector *out, CVector *in);
	static CVector * GetScaled(CVector *in, float scale);
	static CVector * GetScaled(CVector *in, CVector *out, float scale);
	static CVector * sub_4BDF60(CVector *a1, CVector *a2, CVector *a3);
	static CVector * FloatDivide(CVector *a1, CVector *divisible, float divider);
	static CVector * FloatDivide(CVector *a1, float *divisible, float divider);
	static CVector * LinearDivide(CVector *a1, CVector *a2, CVector *a3);
	static CVector * LinearAdd(CVector *a1, CVector *a2, CVector *a3);
	static CVector * LinearAdd(CVector *a1, CVector *a3);
};

#endif