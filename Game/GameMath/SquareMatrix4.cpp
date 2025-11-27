#include "SquareMatrix4.h"

SquareMatrix4::SquareMatrix4()
{
	*this = Identity();
}

SquareMatrix4::SquareMatrix4(
	  float m00, float m01, float m02, float m03
	, float m10, float m11, float m12, float m13
	, float m20, float m21, float m22, float m23
	, float m30, float m31, float m32, float m33)
		: m_matrix{
		  m00, m01, m02, m03
		, m10, m11, m12, m13
		, m20, m21, m22, m23
		, m30, m31, m32, m33
		}
{
}

SquareMatrix4 SquareMatrix4::Identity()
{
	return SquareMatrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
}

SquareMatrix4 SquareMatrix4::Translation(float x, float y, float z)
{
	return SquareMatrix4(
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1
	);
}

SquareMatrix4 SquareMatrix4::Rotation(float thetaX, float thetaY, float thetaZ)
{
	return RotationZ(thetaZ) * RotationX(thetaX) * RotationY(thetaY);
}

SquareMatrix4 SquareMatrix4::InverseRotation(float thetaX, float thetaY, float thetaZ)
{
    return RotationY(thetaY) * RotationX(thetaX) * RotationZ(thetaZ);
}

// Xé≤âÒì]çsóÒ
SquareMatrix4 SquareMatrix4::RotationX(float thetaX)
{
	return SquareMatrix4(
		1, 0,			  0,			 0,
		0, cosf(thetaX),  sinf(thetaX),  0,
		0, -sinf(thetaX), cosf(thetaX),  0,
		0, 0,			  0,			 1
	);
}

// Yé≤âÒì]çsóÒ
SquareMatrix4 SquareMatrix4::RotationY(float thetaY)
{
	return SquareMatrix4(
		cosf(thetaY), 0, -sinf(thetaY),0,
		0,			  1, 0,			   0,
		sinf(thetaY), 0, cosf(thetaY), 0,
		0,			  0, 0,			   1
	);
}

// Zé≤âÒì]çsóÒ
SquareMatrix4 SquareMatrix4::RotationZ(float thetaZ)
{
	return SquareMatrix4(
		cosf(thetaZ),	sinf(thetaZ),	0, 0,
		-sinf(thetaZ),	cosf(thetaZ),	0, 0,
		0,				0,				1, 0,
		0,				0,				0, 1
	);
}

SquareMatrix4 SquareMatrix4::Scale(float x, float y, float z)
{
	return SquareMatrix4(
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1
	);
}

SquareMatrix4 SquareMatrix4::Projection(float ViewAngleY, float farZ, float nearZ, float aspect)
{
    return SquareMatrix4(
        1 / (tanf(ViewAngleY / 2) * aspect), 0, 0, 0,
        0, 1 / (tanf(ViewAngleY / 2)), 0, 0,
        0, 0, -(farZ + nearZ) / (farZ - nearZ), -(2 * farZ * nearZ) / (farZ - nearZ),
        0, 0, -1, 0
    );
}

SquareMatrix4 operator*(SquareMatrix4 m1, SquareMatrix4 m2)
{
	// ï‘Ç∑çsóÒÇçÏê¨
	SquareMatrix4 result;

    for (int i = 0; i < 4; ++i) {
        const float* a = m1.m_matrix[i];
        for (int j = 0; j < 4; ++j) {
            result.m_matrix[i][j] =
                a[0] * m2.m_matrix[0][j] +
                a[1] * m2.m_matrix[1][j] +
                a[2] * m2.m_matrix[2][j] +
                a[3] * m2.m_matrix[3][j];
        }
    }

	return result;
}

Vector4D operator*(SquareMatrix4 m, Vector4D v)
{
    Vector4D r;
    r.x = m.m_matrix[0][0] * v.x + m.m_matrix[0][1] * v.y + m.m_matrix[0][2] * v.z + m.m_matrix[0][3] * v.w;
    r.y = m.m_matrix[1][0] * v.x + m.m_matrix[1][1] * v.y + m.m_matrix[1][2] * v.z + m.m_matrix[1][3] * v.w;
    r.z = m.m_matrix[2][0] * v.x + m.m_matrix[2][1] * v.y + m.m_matrix[2][2] * v.z + m.m_matrix[2][3] * v.w;
    r.w = m.m_matrix[3][0] * v.x + m.m_matrix[3][1] * v.y + m.m_matrix[3][2] * v.z + m.m_matrix[3][3] * v.w;
    return r;
}

Vector4D operator*(Vector4D v, SquareMatrix4 m)
{
    return m * v;
}

SquareMatrix4 operator*(const SquareMatrix4 m, float s)
{
    return SquareMatrix4(
        m.m_matrix[0][0] * s, m.m_matrix[0][1] * s, m.m_matrix[0][2] * s, m.m_matrix[0][3],
        m.m_matrix[1][0] * s, m.m_matrix[1][1] * s, m.m_matrix[1][2] * s, m.m_matrix[1][3],
        m.m_matrix[2][0] * s, m.m_matrix[2][1] * s, m.m_matrix[2][2] * s, m.m_matrix[2][3], 
        m.m_matrix[3][0] * s, m.m_matrix[3][1] * s, m.m_matrix[3][2] * s, m.m_matrix[3][3]
        );
}

SquareMatrix4 operator*(float s, const SquareMatrix4 m)
{
    return m * s;
}
