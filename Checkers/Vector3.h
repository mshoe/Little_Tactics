#pragma once

template <typename T>
class Vector3 {
public:
	Vector3();
	Vector3(T X, T Y);
	Vector3(T X, T Y, T Z);
	~Vector3();
	void changeVector(T X, T Y);
	void changeVector(T X, T Y, T Z);
	void translateVector(T X, T Y, T Z);
	bool compareVector(Vector3<T> *comparisonVec);
	bool compareVectorWithPrecision(Vector3<T> *comparisonVec, T precision);
	T x;
	T y;
	T z;
};

template <typename T>
Vector3<T>::Vector3()
{
	x = (T)0; y = (T)0; z = (T)0;
}

template <typename T>
Vector3<T>::Vector3(T X, T Y)
{
	x = X;
	y = Y;
	z = (T)0;
}

template <typename T>
Vector3<T>::Vector3(T X, T Y, T Z)
{
	x = X;
	y = Y;
	z = Z;
}

template <typename T>
Vector3<T>::~Vector3()
{
}

template <typename T>
void Vector3<T>::changeVector(T X, T Y)
{
	x = X;
	y = Y;
}

template <typename T>
void Vector3<T>::changeVector(T X, T Y, T Z)
{
	x = X;
	y = Y;
	z = Z;
}

template <typename T>
void Vector3<T>::translateVector(T X, T Y, T Z)
{
	x += X;
	y += Y;
	z += Z;
}

template <typename T>
bool Vector3<T>::compareVector(Vector3<T> * comparisonVec)
{
	if (comparisonVec->x == x
		&& comparisonVec->y == y
		&& comparisonVec->z == z)
		return true;
	return false;
}

template<typename T>
bool Vector3<T>::compareVectorWithPrecision(Vector3<T>* comparisonVec, T precision)
{
	if (comparisonVec->x + precision > x && x > comparisonVec->x - precision
		&& comparisonVec->y + precision > y && y > comparisonVec->y - precision
		&& comparisonVec->z + precision > z && z > comparisonVec->z - precision)
		return true;
	return false;
}
