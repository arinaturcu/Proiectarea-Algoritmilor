#include <iostream>
#include <math.h>

using namespace std;

class Point 
{
  private:
    double x, y;

  public:

    Point(double x, double y)
    {
      this->x = x;
      this->y = y;
    }

    double distance_to(Point point) {
      return sqrt((this->x - point.x) * (this->x - point.x) 
        + (this->x - point.x) * (this->x - point.x));
    }
};

int main() 
{
  Point p1(0, 1);
  Point p2(1, 0);

  cout << p1.distance_to(p2) << endl;

  return 0;
}