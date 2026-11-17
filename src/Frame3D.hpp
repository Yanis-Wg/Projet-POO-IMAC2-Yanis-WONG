#pragma once
#include <vector>
#include <array>
#include <iostream>
#include <cmath>
#include <cassert>

class Frame3D{
    private:
        std::vector<std::array<double,3>> vectorsOfFrame;
    public:
        // constructor
        Frame3D();
        // copy constructor
        Frame3D(const Frame3D& frameACopier);
        // destructor
        ~Frame3D();
        // surcharge
        Frame3D& operator=(const Frame3D& frameACopier);
        Frame3D operator+(const Frame3D& frameAAdditionner) const;
        // METHODE
        void size();
        void add(std::vector<double> & v);
        double quality_measure(const std::vector<double> & v) const;
};
