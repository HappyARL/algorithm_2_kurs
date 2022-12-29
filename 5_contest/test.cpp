#include <iostream>

struct Point {
  int x;
  int y;
};

bool MakeTurn(Point a, Point b, const Point& c) {
  bool right = false;
  bool left = false;
  int s = (c.x - a.x) * (c.y - b.y) - (c.y - a.y) * (c.x - b.x);
  right = right || s < 0;
  left = left || s > 0;
  a = b;
  b = c;
  return right && left;
}

bool ConvexPolygon(Point a, Point b, int n) {
  Point c;
  for (int i = 2; i < n; ++i) {
    std::cin >> c.x >> c.y;
    if (MakeTurn(a, b, c)) {
      return false;
    }
  }
  if (MakeTurn(a, b, a)) {
    return false;
  }
  if (MakeTurn(a, b, b)) {
    return false;
  }
  return true;
}

int main() {
  int n;
  std::cin >> n;
  Point a;
  Point b;
  std::cin >> a.x >> a.y;
  std::cin >> b.x >> b.y;
  std::cout << (ConvexPolygon(a, b, n) ? "YES" : "NO");
  return 0;
}

/*
#include <iostream>

struct Point {
    int x;
    int y;
};

class Clock {
 public:
  Clock(const Point& p1, const Point& p2) : a(a), b(b), right(false), left(false) {}
  bool MakeTurn(const Point& c) {
    int s = (c.x - a.x) * (c.y - b.y) - (c.y - a.y) * (c.x - b.x);
    right = right || s < 0;
    left = left || s > 0;
    a = b;
    b = c;
    return right && left;
  }
 private:
  Point a;
  Point b;
  bool right;
  bool left;
};

bool is_convex(Point a, Point b, int n) {
  Clock d(a, b);
  Point c;
  for (int i = 2; i < n; ++i) {
    std::cin >> c.x >> c.y;
    if (d.MakeTurn(c)) {
      return false;
    }
  }
  if (d.MakeTurn(a)) {
    return false;
  }
  if (d.MakeTurn(b)) {
    return false;
  }
  return true;
}

int main() {
  int n;
  std::cin >> n;
  Point a;
  Point b;
  std::cin >> a.x >> a.y;
  std::cin >> b.x >> b.y;
  std::cout << (is_convex(a, b, n) ? "YES" : "NO");
  return 0;
}
*/