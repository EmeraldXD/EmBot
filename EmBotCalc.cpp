// Revised to c++
#include <iostream>
#include <cmath>

std::string calculateDirection(double x1, double z1, double x2, double z2) {
    double xChange = x2 - x1;
    double zChange = z2 - z1;

    if (xChange >= 0 && zChange >= 0) {
        return "southeast";
    } else if (xChange >= 0 && zChange < 0) {
        return "southwest";
    } else if (xChange < 0 && zChange >= 0) {
        return "northeast";
    } else {
        return "northwest";
    }
}

void calculateNewCoordinates(double x, double z, double slope, std::string direction,
                             double distance, std::string significantCoordinate,
                             double &newX, double &newZ) {
    double signX, signZ;
    if (direction == "southeast") {
        signX = 1;
        signZ = 1;
    } else if (direction == "southwest") {
        signX = 1;
        signZ = -1;
    } else if (direction == "northeast") {
        signX = -1;
        signZ = 1;
    } else {
        signX = -1;
        signZ = -1;
    }

    double distSignificant, distNonsignificant;

    if (slope <= 2) {
        distSignificant = distance * 0.7 * signX;
        distNonsignificant = distance * 0.3 * signZ;
    } else if (slope <= 4) {
        distSignificant = distance * 0.8 * signX;
        distNonsignificant = distance * 0.2 * signZ;
    } else if (slope <= 8) {
        distSignificant = distance * 0.87 * signX;
        distNonsignificant = distance * 0.13 * signZ;
    } else if (slope <= 16) {
        distSignificant = distance * 0.95 * signX;
        distNonsignificant = distance * 0.05 * signZ;
    } else {
        distSignificant = distance * signX;
        distNonsignificant = 0;
    }

    if (significantCoordinate == "x") {
        newX = x + distSignificant;
        newZ = z + distNonsignificant;
    } else {
        newX = x + distNonsignificant;
        newZ = z + distSignificant;
    }

    if (newX < 0) {
        newX -= 4;
    }

    if (newZ < 0 && significantCoordinate == "z" && (direction == "southeast" || direction == "northeast")) {
        newZ += 4;
    }
}

int main() {
    double offset, distance, x1, z1, x2, z2, slope;
    std::string direction, significantCoordinate;
    
    std::cout << "Enter the offset: ";
    std::cin >> offset;
    distance = 3636 / offset;

    std::cout << "Enter the x coordinate of the first point: ";
    std::cin >> x1;
    std::cout << "Enter the z coordinate of the first point: ";
    std::cin >> z1;

    std::cout << "Enter the x coordinate of the second point: ";
    std::cin >> x2;
    std::cout << "Enter the z coordinate of the second point: ";
    std::cin >> z2;

    slope = (z2 - z1) / (x2 - x1);

    direction = calculateDirection(x1, z1, x2, z2);

    if (std::abs(x2 - x1) > std::abs(z2 - z1)) {
        significantCoordinate = "x";
    } else {
        significantCoordinate = "z";
    }

    double newX, newZ;
    calculateNewCoordinates(x1, z1, slope, direction, distance, significantCoordinate, newX, newZ);

    double netherX = newX / 8;
    double netherZ = newZ / 8;

    std::cout << "Stronghold Coordinates: (" << newX << ", " << newZ << ")\n";
    std::cout << "Nether Coordinates: (" << netherX << ", " << netherZ << ")\n";

    return 0;
}
