#ifndef CMATRIX_H
#define CMATRIX_H

#include "CVector.h"

class CMatrix {
public:
	CVector right;
	CVector top;
	CVector at;
	CVector pos;
	CMatrix();
	CVector GetRadians();
	CMatrix* MatrixMultiply(CMatrix *out, CMatrix *a2, CMatrix *a3);
};

#endif