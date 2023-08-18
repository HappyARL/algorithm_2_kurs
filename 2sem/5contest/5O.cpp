#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

const double PI = acos(-1.0);

void FFT(std::vector<std::complex<double> >& polynom, bool invert) {
  int64_t n = polynom.size();
  if (n == 1) {
    return;
  }

  std::vector<std::complex<double> > a0(n / 2), a1(n / 2);
  for (int64_t i = 0; 2 * i < n; ++i) {
    a0[i] = polynom[2 * i];
    a1[i] = polynom[2 * i + 1];
  }

  FFT(a0, invert);
  FFT(a1, invert);

  double angle = 2 * PI / n * (invert ? -1 : 1);
  std::complex<double> w(1), wn(cos(angle), sin(angle));

  for (int64_t i = 0; 2 * i < n; ++i) {
    polynom[i] = a0[i] + w * a1[i];
    polynom[i + n / 2] = a0[i] - w * a1[i];
    if (invert) {
      polynom[i] /= 2;
      polynom[i + n / 2] /= 2;
    }
    w *= wn;
  }
}

int main() {
  int64_t a_size, b_size;
  std::cin >> a_size;
  std::vector<std::complex<double> > A(a_size + 1);

  for (int64_t i = 0; i <= a_size; ++i) {
    std::cin >> A[i];
  }

  std::cin >> b_size;
  std::vector<std::complex<double>> B(b_size + 1);

  for (int64_t i = 0; i <= b_size; ++i) {
    std::cin >> B[i];
  }

  int64_t size = 1;
  while (size < a_size + b_size + 1) {
    size *= 2;
  }

  A.resize(size);
  B.resize(size);

  FFT(A, false);
  FFT(B, false);

  for (int64_t i = 0; i < size; ++i) {
    A[i] *= B[i];
  }

  FFT(A, true);

  std::cout << a_size + b_size << " ";
  for (int64_t i = 0; i <= a_size + b_size; ++i) {
    std::cout << (int)round(A[i].real()) << " ";
  }

  return 0;
}

//#include <std::complex>
//#include <cmath>
//#include <iostream>
//#include <std::vector>
//
//const double pi_num = 2 * acos(0.0);
//
//std::std::vector<std::std::complex<double> > FFT(std::std::vector<std::std::complex<double> >& polynom) {
//  size_t length = polynom.size();
//  if (length == 1) {
//    return polynom;
//  }
//  std::std::vector<std::std::complex<double> > even_polynom_num;
//  std::std::vector<std::std::complex<double> > odd_polynom_num;
//  for (size_t i = 0; i < polynom.size(); ++i) {
//    if (i % 2 == 0) {
//      even_polynom_num.push_back(polynom[i]);
//    } else {
//      odd_polynom_num.push_back(polynom[i]);
//    }
//  }
//  FFT(even_polynom_num);
//  FFT(odd_polynom_num);
//  double ang = 2 * pi_num / (double)length * -1;
//  std::std::complex<double> w (1);
//  std::std::complex<double> wn (cos(ang), sin(ang));
//  for (size_t i = 0; i < length / 2; ++i) {
//    polynom[i] = even_polynom_num[i] + w * odd_polynom_num[i];
//    polynom[i + length / 2] = even_polynom_num[i] - w * odd_polynom_num[i];
//    w *= wn;
//  }
//  return polynom;
//}
//
//std::std::vector<std::std::complex<double> > IFFT(std::std::vector<std::std::complex<double> >& polynom) {
//  size_t length = polynom.size();
//  if (length == 1) {
//    return polynom;
//  }
//  std::std::vector<std::std::complex<double> > even_polynom_num;
//  std::std::vector<std::std::complex<double> > odd_polynom_num;
//  for (size_t i = 0; i < polynom.size(); ++i) {
//    if (i % 2 == 0) {
//      even_polynom_num.push_back(polynom[i]);
//    } else {
//      odd_polynom_num.push_back(polynom[i]);
//    }
//  }
//  even_polynom_num = IFFT(even_polynom_num);
//  odd_polynom_num = IFFT(odd_polynom_num);
//  double ang = (2 * pi_num / (double)length);
//  std::std::complex<double> w (1);
//  std::std::complex<double> wn (cos(ang), sin(ang));
//  for (size_t i = 0; i < length / 2; ++i) {
//    polynom[i] = even_polynom_num[i] + w * odd_polynom_num[i];
//    polynom[i] /= 2;
//    polynom[i + length / 2] = even_polynom_num[i] - w * odd_polynom_num[i];
//    polynom[i + length / 2] /= 2;
//    w *= wn;
//  }
//  return polynom;
//}
//
//void Multiply(const std::std::vector<std::std::complex<double> >& polynom_a,
//              const std::std::vector<std::std::complex<double> >& polynom_b) {
//  std::std::vector<std::std::complex<double> > FFT_polynom_a = polynom_a;
//  std::std::vector<std::std::complex<double> > FFT_polynom_b = polynom_b;
//  size_t n = 1;
//  while (n < std::max(polynom_a.size(), polynom_b.size())) {
//    n <<= 1;
//  }
//  n <<= 1;
//  FFT_polynom_a.resize (n);
//  FFT_polynom_b.resize (n);
//  FFT(FFT_polynom_a);
//  FFT(FFT_polynom_b);
//  for (size_t i = 0; i < n; ++i) {
//    FFT_polynom_a[i] *= FFT_polynom_b[i];
//  }
//  IFFT(FFT_polynom_a);
//  for (size_t i = 0; i < n; ++i) {
//    if (FFT_polynom_a[i].real() != 0) {
//      std::std::cout << lround(FFT_polynom_a[i].real()) << " ";
//    }
//  }
//  std::std::cout << std::endl;
//}
//
//int64_t main() {
//  std::std::vector<std::std::complex<double> > polynom_a;
//  std::std::vector<std::std::complex<double> > polynom_b;
//  int64_t length_a;
//  std::std::cin >> length_a;
//  while (length_a + 1 != 0) {
//    std::std::complex<double> value;
//    std::std::cin >> value;
//    polynom_a.push_back(value);
//    --length_a;
//  }
//  int64_t length_b;
//  std::std::cin >> length_b;
//  while (length_b + 1 != 0) {
//    std::std::complex<double> value;
//    std::std::cin >> value;
//    polynom_b.push_back(value);
//    --length_b;
//  }
//  Multiply(polynom_a, polynom_b);
//  return 0;
//}
//
///*
//int64_t main() {
//  std::std::vector<std::std::complex<double> > a;
//  int64_t length_a;
//  std::std::cin >> length_a;
//  while (length_a + 1 != 0) {
//    std::std::complex<double> value;
//    std::std::cin >> value;
//    a.push_back(value);
//    --length_a;
//  }
//  std::std::cout << "FFT" << '\n';
//  std::std::vector<std::std::complex<double> > b = FFT(a);
//  for (int64_t i = 0; i < 4; i++)
//    std::std::cout << b[i] << std::endl;
//  std::std::cout << "IFFT" << '\n';
//  std::std::vector<std::std::complex<double> > c = IFFT(a);
//  for (int64_t i = 0; i < 4; i++)
//    std::std::cout << c[i] << std::endl;
//  return 0;
//}
//*/