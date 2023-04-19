#include <iostream>
#include <algorithm>
using namespace std;

struct Matrix {
    int start, end;
};

bool compare(Matrix a, Matrix b) {
    return a.start < b.start;
}

int main() {
    int n;
    cin >> n;
    Matrix matrices[n];
    for (int i = 0; i < n; i++) {
        cin >> matrices[i].start >> matrices[i].end;
    }
    sort(matrices, matrices + n, compare);
    int count = 0, open = 0;
    for (int i = 0; i < n; i++) {
        if (matrices[i].start >= matrices[i - 1].end) {
            open++;
        }
        count += open - 1;
    }
    cout << count << endl;
    return 0;
}
