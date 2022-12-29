#include <iostream>
#include <vector>

bool InOut(std::vector<std::pair<long long, long long>> points, int x, int y) {
  bool result = false;
  int j = (int)points.size() - 1;
  for (int i = 0; i < (int)points.size(); ++i) {
    if ((points.at(i).first == x) && (points.at(i).second == y)) {
      return true;
    }
  }
  for (int i = 0; i < (int)points.size(); ++i) {
    if ((points.at(i).first != x) && (points.at(i).second != y) && (((points.at(j).first - x) / (points.at(i).first - x)) == ((points.at(j).second - y) / (points.at(i).second - y)))) {
      return false;
    }
    j = i;
  }
  j = (int)points.size() - 1;
  for (int i = 0; i < (int)points.size(); ++i) {
    if ( (((points.at(i).second < y) && (points.at(j).second >= y)) || ((points.at(j).second < y) && (points.at(i).second >= y))) &&
         ((points.at(i).first + (y - points.at(i).second) / (points.at(j).second - points.at(i).second) * (points.at(j).first - points.at(i).first) < x)) ) {
      result = !result;
    }
    j = i;
  }
  return result;
}

int main() {
  int n;
  long long x, y;
  std::cin >> n >> x >> y;
  std::vector<std::pair<long long, long long>> points;
  while (n != 0) {
    long long cor1, cor2;
    std::cin >> cor1 >> cor2;
    points.push_back(std::pair(cor1, cor2));
    --n;
  }
  std::string ans = InOut(points, x ,y) ? "YES" : "NO";
  std::cout << ans << std::endl;
  return 0;
}


/*

#include <iostream>
#include <vector>

struct Point {
  int x;
  int y;
};

bool InOut(std::vector<Point> points, Point p) {
  bool result = false;
  for (int i = 0, j = (int)points.size() - 1; i < (int)points.size(); j = ++i) {
    if ((((points.at(i).y <= p.y) && (p.y < points.at(j).y)) || ((points.at(j).y <= p.y) && (p.y < points.at(i).y))) &&
        (((points.at(j).y - points.at(i).y) != 0) && (p.x > ((points.at(j).x - points.at(i).x) * (p.y - points.at(i).y) / (points.at(j).y - points.at(i).y) + points.at(j).x)))) {
      result = !result;
    }
  }
  return result;
}

int main() {
  Point p;
  int n;
  std::cin >> n >> p.x >> p.y;
  std::vector<Point> points;
  while (n != 0) {
    Point m;
    std::cin >> m.x >> m.y;
    points.push_back(m);
  }
  for (int i = 0; i < n; ++i) {
    std::cout << points.at(i).x << points.at(i).x << std::endl;
  }
  std::string ans = InOut(points, p) ? "YES" : "NO";
  std::cout << ans << std::endl;
  return 0;
}

=========================================================================
#include <iostream>
#include <vector>

bool InOut(std::vector<std::pair<int, int>> points, int x, int y) {
  bool result = false;
  int j = (int)points.size() - 1;
  for (int i = 0; i < (int)points.size(); ++i) {
    if ((points.at(i).first == x) && (points.at(i).second == y)) {
      return true;
    }
  }
  for (int i = 0; i < (int)points.size(); ++i) {
    if ((points.at(j).second != y) && (points.at(j).first != x) && ((points.at(i).first - x) / (points.at(j).first - x) == (points.at(i).second - y) / (points.at(j).second - y))) {
      return true;
    }
    j = i;
  }
  j = (int)points.size() - 1;
  for (int i = 0; i < (int)points.size(); ++i) {
    if ( (((points.at(i).second < y) && (points.at(j).second >= y)) || ((points.at(j).second < y) && (points.at(i).second >= y))) &&
         ((points.at(i).first + (y - points.at(i).second) / (points.at(j).second - points.at(i).second) * (points.at(j).first - points.at(i).first) < x)) ) {
      result = !result;
    }
    j = i;
  }
  return result;
}

int main() {
  int n, x, y;
  std::cin >> n >> x >> y;
  std::vector<std::pair<int, int>> points;
  while (n != 0) {
    int cor1, cor2;
    std::cin >> cor1 >> cor2;
    points.push_back(std::pair(cor1, cor2));
    --n;
  }
  std::string ans = InOut(points, x ,y) ? "YES" : "NO";
  std::cout << ans << std::endl;
  return 0;
}

====================================================================================================================

if ( (vec[i].Y < point.Y && vec[j].Y >= point.Y || vec[j].Y < point.Y && vec[i].Y >= point.Y) &&
     (vec[i].X + (point.Y - vec[i].Y) / (vec[j].Y - vec[i].Y) * (vec[j].X - vec[i].X) < point.X) )
*/