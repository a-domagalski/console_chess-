#ifndef VECTOR2_H
#define VECTOR2_H
#include <iostream>
class vector2
{
private:

public:
	short x;
	short y;

	vector2();
	vector2(const short&, const short&);

	vector2& operator=(const vector2&);
	friend bool operator==(const vector2&, const vector2&);

	friend std::ostream& operator<<(std::ostream&,const vector2&);
};
#endif