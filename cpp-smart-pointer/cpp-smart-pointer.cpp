#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;

class point {
	public:
		static int instance_count;
		char * desc;
		point(int x, int y, char * desc_) : x(x), y(y) {
			instance_count++;
			desc = desc_;
			cout << "Creating: " << desc << endl;
		}
		void print(void) {
			printf("%s: x = %i, y = %i\n", desc,x,y);
		}

		string toString() {
			return "hi cliff";
		}

		~point() {
			cout << desc << " :point was destroyed, count = " << instance_count << endl;
			instance_count--;
		}

			
	private:
		int x;
		int y;
		int z;
//		point (const point &);
//		void operator= (const point &);

};

int point::instance_count = 0;

main()
{
	cout << "starting program" << endl;

	point a(1,2, "a");
	point b(3,4, "b");
	point c(5,6, "c");
	point d(5,6, "d");

	point a_[] = {a,b,c};

	vector<point> points(a_, a_ + sizeof(a_)/sizeof(a_[0]));
	vector<point*> points_;
	//(new point(1,2), new point(3,4));
	
	printf("sizeof a = %ld, sizeof(a_) = %ld, sizeof(points) = %ld\n", sizeof(a), sizeof(a_), sizeof(points));

	points.push_back(c);
	points.push_back(c);
	points_.push_back(&c);

	// print all points
	cout << "Loop by index, copy in vector" << endl;
	int i;
	for (i=0; i < points.size(); i++) {
		points[i].print();
		//printf("point = %i, %i\n", points[i]);
	}

	// print all points
	cout << "Loop by index, pointer in vector" << endl;
	for (i=0; i < points_.size(); i++) {
		points_[i]->print();
		//printf("point = %i, %i\n", points[i]);
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
	cout << "ending program" << endl;
}

