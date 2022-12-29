 #include <iostream>
#include <vector>

bool VecMultiplication(std::vector<std::pair<int64_t, int64_t>> points, int64_t i, int64_t a, int64_t b, bool sign) {
  int64_t x1 = points.at(i).first - points.at(a).first;
  int64_t y1 = points.at(i).second - points.at(a).second;
  int64_t x2 = points.at(b).first - points.at(i).first;
  int64_t y2 = points.at(b).second - points.at(i).second;
  if (!sign) {
    return (x1 * y2 - y1 * x2) <= 0 ? false : true;
  }
  return (x1 * y2 - y1 * x2) >= 0 ? true : false;
}

bool ConvexPolygon(std::vector<std::pair<int64_t, int64_t>> points) {
  int64_t size = points.size();
  bool flag = true;
  bool sign = VecMultiplication(points, 1, 0, 2, flag);
  for (int64_t i = 1; i < size - 2; ++i) {
    if (VecMultiplication(points, i + 1, i, i + 2, sign) != sign) {
      return false;
    }
  }
  return true;
}

int main() {
  int64_t n;
  std::cin >> n;
  std::vector<std::pair<int64_t, int64_t>> points;
  while (n != 0) {
    int x, y;
    std::cin >> x >> y;
    points.push_back(std::pair(x, y));
    --n;
  }
  points.push_back(points.at(0));
  points.push_back(points.at(1));
  points.push_back(points.at(2));
  std::string ans = ConvexPolygon(points) ? "YES" : "NO";
  std::cout << ans << std::endl;
  return 0;
}
