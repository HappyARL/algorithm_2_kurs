#include <complex>
#include <cmath>
#include <iostream>
#include <vector>

const double pi_num = 2 * acos(0.0);

std::vector<std::complex<double> > FFT(std::vector<std::complex<double> >& polynom) {
  size_t length = polynom.size();
  if (length == 1) {
    return polynom;
  }
  std::vector<std::complex<double> > even_polynom_num;
  std::vector<std::complex<double> > odd_polynom_num;
  for (size_t i = 0; i < polynom.size(); ++i) {
    if (i % 2 == 0) {
      even_polynom_num.push_back(polynom[i]);
    } else {
      odd_polynom_num.push_back(polynom[i]);
    }
  }
  FFT(even_polynom_num);
  FFT(odd_polynom_num);
  double ang = 2 * pi_num / (double)length * -1;
  std::complex<double> w (1);
  std::complex<double> wn (cos(ang), sin(ang));
  for (size_t i = 0; i < length / 2; ++i) {
    polynom[i] = even_polynom_num[i] + w * odd_polynom_num[i];
    polynom[i + length / 2] = even_polynom_num[i] - w * odd_polynom_num[i];
    w *= wn;
  }
  return polynom;
}

std::vector<std::complex<double> > IFFT(std::vector<std::complex<double> >& polynom) {
  size_t length = polynom.size();
  if (length == 1) {
    return polynom;
  }
  std::vector<std::complex<double> > even_polynom_num;
  std::vector<std::complex<double> > odd_polynom_num;
  for (size_t i = 0; i < polynom.size(); ++i) {
    if (i % 2 == 0) {
      even_polynom_num.push_back(polynom[i]);
    } else {
      odd_polynom_num.push_back(polynom[i]);
    }
  }
  even_polynom_num = IFFT(even_polynom_num);
  odd_polynom_num = IFFT(odd_polynom_num);
  double ang = (2 * pi_num / (double)length);
  std::complex<double> w (1);
  std::complex<double> wn (cos(ang), sin(ang));
  for (size_t i = 0; i < length / 2; ++i) {
    polynom[i] = even_polynom_num[i] + w * odd_polynom_num[i];
    polynom[i] /= 2;
    polynom[i + length / 2] = even_polynom_num[i] - w * odd_polynom_num[i];
    polynom[i + length / 2] /= 2;
    w *= wn;
  }
  return polynom;
}

void Multiply(const std::vector<std::complex<double> >& polynom_a,
              const std::vector<std::complex<double> >& polynom_b) {
  std::vector<std::complex<double> > FFT_polynom_a = polynom_a;
  std::vector<std::complex<double> > FFT_polynom_b = polynom_b;
  size_t n = 1;
  while (n < std::max(polynom_a.size(), polynom_b.size())) {
    n <<= 1;
  }
  n <<= 1;
  FFT_polynom_a.resize (n);
  FFT_polynom_b.resize (n);
  FFT(FFT_polynom_a);
  FFT(FFT_polynom_b);
  for (size_t i = 0; i < n; ++i) {
    FFT_polynom_a[i] *= FFT_polynom_b[i];
  }
  IFFT(FFT_polynom_a);
  for (size_t i = 0; i < n; ++i) {
    if (FFT_polynom_a[i].real() != 0) {
      std::cout << lround(FFT_polynom_a[i].real()) << " ";
    }
  }
  std::cout << std::endl;
}

int main() {
  std::vector<std::complex<double> > polynom_a;
  std::vector<std::complex<double> > polynom_b;
  int length_a;
  std::cin >> length_a;
  while (length_a + 1 != 0) {
    std::complex<double> value;
    std::cin >> value;
    polynom_a.push_back(value);
    --length_a;
  }
  int length_b;
  std::cin >> length_b;
  while (length_b + 1 != 0) {
    std::complex<double> value;
    std::cin >> value;
    polynom_b.push_back(value);
    --length_b;
  }
  Multiply(polynom_a, polynom_b);
  return 0;
}

/*
int main() {
  std::vector<std::complex<double> > a;
  int length_a;
  std::cin >> length_a;
  while (length_a + 1 != 0) {
    std::complex<double> value;
    std::cin >> value;
    a.push_back(value);
    --length_a;
  }
  std::cout << "FFT" << '\n';
  std::vector<std::complex<double> > b = FFT(a);
  for (int i = 0; i < 4; i++)
    std::cout << b[i] << std::endl;
  std::cout << "IFFT" << '\n';
  std::vector<std::complex<double> > c = IFFT(a);
  for (int i = 0; i < 4; i++)
    std::cout << c[i] << std::endl;
  return 0;
}
*/