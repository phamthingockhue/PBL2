#include "Vi.h"
#include "MyVector.h"

class QuanLyVi 
{
private:
	MyVector<Vi> dsVi;
public:

	Vi* TimVi(int);
	void setVi(MyVector<Vi> vi)
	{
		dsVi = vi;
	}
	MyVector<Vi> getVi()
	{
		return dsVi;
	}
};