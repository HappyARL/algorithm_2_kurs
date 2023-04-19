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

bool ConvexPolygon(std::vector<std::pair<int64_t, int64_t> > points) {
  int64_t size = points.size();
  for (int64_t i = 0; i < size; ++i) {
    int64_t j = (i + 1) % size;
    int64_t k = (i + 2) % size;
    int64_t cross_product = VecMultiplication(Vector(points[j], points[i]), Vector(points[k], points[j]));
    if (cross_product < 0) {
      return false;
    }
  }
  return true;
}

int main() {
  int64_t n;
  std::cin >> n;
  std::vector<std::pair<int64_t, int64_t> > points;
  while (n != 0) {
    int64_t x, y;
    std::cin >> x >> y;
    points.push_back(std::pair<int64_t, int64_t> (x, y));
    --n;
  }
  if (points[0] != points[points.size() - 1]) {
    points.push_back(points[0]);
  }
  std::string ans = ConvexPolygon(points) ? "YES" : "NO";
  std::cout << ans << std::endl;
  return 0;
}
