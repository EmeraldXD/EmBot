#include <iostream>
#include <cmath>
using namespace std;

string c(double x1, double z1, double x2, double z2) {
    string s;
    s = (x2 - x1 >= 0 ? "south" : "north");
    s += (z2 - z1 >= 0 ? "east" : "west");
    return s;
}

void n(double x, double z, double a, string d, string s, double &nx, double &nz) {
    double sx = (d[0] == 's' ? 1 : -1), sz = (d[1] == 'e' ? 1 : -1), ds, df;
    if (a <= 2) ds = a * 0.35, sz *= 0.3;
    else if (a <= 4) ds = a * 0.4, sz *= 0.2;
    else if (a <= 8) ds = a * 0.435, sz *= 0.13;
    else if (a <= 16) ds = a * 0.475, sz *= 0.05;
    else ds = a;
    df = (a < 2 ? sx * 0.3 : 0);
    nx = (s == "x" ? x + ds : x + df);
    nz = (s == "z" ? z + ds : z + df);
    nx = (nx < 0 ? nx + 4 : nx);
}

int main() {
    double o, d, x1, z1, x2, z2, a;
    string dr, s;
    cin >> o >> x1 >> z1 >> x2 >> z2;
    a = abs(z2 - z1) / abs(x2 - x1);
    dr = c(x1, z1, x2, z2);
    s = (abs(x2 - x1) > abs(z2 - z1) ? "x" : "z");
    n(x1, z1, a, dr, s, d, o);
    d /= 8;
    cout << "Stronghold Coordinates: (" << d << ", " << o << ")\n";
    cout << "Nether Coordinates: (" << d / 8 << ", " << o / 8 << ")\n";
}
