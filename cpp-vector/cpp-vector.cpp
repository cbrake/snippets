#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

class point {
	public:
		point(int x, int y) : x(x), y(y) {}
		void print(void) {
			printf("x = %i, y = %i\n", x,y);
		}

		string toString() {
			return "hi cliff";
		}
			
		int x;
		int y;
		int z;
};

main()
{

	point a(1,2);
	point b(3,4);
	point c(5,6);

	point a_[] = {a,b,c};

	vector<point> points(a_, a_ + sizeof(a_)/sizeof(a_[0]));
	vector<point*> points_;
	//(new point(1,2), new point(3,4));
	
	printf("sizeof a = %ld, sizeof(a_) = %ld, sizeof(points) = %ld\n", sizeof(a), sizeof(a_), sizeof(points));

	points.push_back(c);
	points.push_back(c);
	points_.push_back(&c);

	printf("last point, x = %i\n", points.back().x);

	// print all points
	cout << "Loop by index, copy in vector" << endl;
	for (int i=0; i < points.size(); i++) {
		points[i].print();
		//printf("point = %i, %i\n", points[i]);
	}

	// print all points
	cout << "Loop by index, pointer in vector" << endl;
	for (int i=0; i < points_.size(); i++) {
		points_[i]->print();
		//printf("point = %i, %i\n", points[i]);
	}

	// try to copy vector by assignment
	vector<point> points_copy;

	points_copy = points;

	cout << "print copy" << endl;
	for (int i=0; i < points_copy.size(); i++) {
		points_copy[i].print();
	}


	cout << "Loop by itr" << endl;

#if 0
	vector<point*>::const_iterator ci;
	for (ci=points.begin(); ci!=points.end(); ci++)
	{
		ci->print();
		//printf("point = %i\n", *ci);
	}
#endif

}

