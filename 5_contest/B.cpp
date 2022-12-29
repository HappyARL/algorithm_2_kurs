#include <iostream>
#include <vector>

std::pair<int64_t, int64_t> Vector(std::pair<int64_t, int64_t> a, std::pair<int64_t, int64_t> b) {
  std::pair<int64_t, int64_t> ab;
  ab.first = b.first - a.first;
  ab.second = b.second - a.second;
  return ab;
}

int64_t VecMultiplication(std::pair<int64_t, int64_t> a, std::pair<int64_t, int64_t> b) {
  return (a.first * b.second - a.second * b.first);
}

bool ConvexPolygon(std::vector<std::pair<int64_t, int64_t>> points) {
  int64_t size = (int64_t)points.size();
  int64_t j = size - 1;
  for (int64_t i = 0; i < size - 2; ++i) {
    if ((VecMultiplication(Vector(points.at(j), points.at(i)), Vector(points.at(i), points.at(i + 1))) % size) * (VecMultiplication(Vector(points.at(i), points.at(i + 1)), Vector(points.at(i + 1), points.at(i + 2))) % size) < 0) {
      return false;
    }
    j = i;
  }
  return true;
}

int main() {
  int64_t n;
  std::cin >> n;
  std::vector<std::pair<int64_t, int64_t>> points;
  while (n != 0) {
    int64_t x, y;
    std::cin >> x >> y;
    points.push_back(std::pair(x, y));
    --n;
  }
  points.push_back(points.at(0));
  points.push_back(points.at(1));
  std::string ans = ConvexPolygon(points) ? "YES" : "NO";
  std::cout << ans << std::endl;
  return 0;
}

 /*
 #include <iostream>
#include <vector>

bool VecMultiplication(std::vector<std::pair<int, int>> points, int i, int a, int b, bool sign) {
  int x1 = points.at(i).first - points.at(a).first;
  int y1 = points.at(i).second - points.at(a).second;
  int x2 = points.at(b).first - points.at(i).first;
  int y2 = points.at(b).second - points.at(i).second;
  if (!sign) {
    return (x1 * y2 - y1 * x2) <= 0 ? false : true;
  }
  return (x1 * y2 - y1 * x2) >= 0 ? true : false;
}

bool ConvexPolygon(std::vector<std::pair<int, int>> points) {
  int size = (int)points.size();
  int j = size - 1;
  bool flag = true;
  bool sign = VecMultiplication(points, 0, j, 1, flag);
  for (int i = 1; i < size - 1; ++i) {
    if (VecMultiplication(points, i, i - 1, i + 1, sign) != sign) {
      return false;
    }
  }
  if (VecMultiplication(points, j, j - 1, 0, sign) != sign) {
    return false;
  }
  return true;
}

int main() {
  int n;
  std::cin >> n;
  std::vector<std::pair<int, int>> points;
  while (n != 0) {
    int x, y;
    std::cin >> x >> y;
    points.push_back(std::pair(x, y));
    --n;
  }
  std::string ans = ConvexPolygon(points) ? "YES" : "NO";
  std::cout << ans << std::endl;
  return 0;
}

 */