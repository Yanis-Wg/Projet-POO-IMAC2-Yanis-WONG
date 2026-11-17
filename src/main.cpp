#include "Frame3D.hpp"

int main(){
    // vec de f1
    std::vector<double> f1_1{1,0,0};
    std::vector<double> f1_2{-1,0,0};
    std::vector<double> f1_3{0,1,0};
    std::vector<double> f1_4{0,-1,0};
    std::vector<double> f1_5{0,0,1};
    std::vector<double> f1_6{0,0,-1};

    // vec de f2 
    std::vector<double> f2_1{1,0,0};
    std::vector<double> f2_2{0,1,0};
    std::vector<double> f2_3{0,0,1};
    std::vector<double> f2_4{-1/sqrt(3),-1/sqrt(3),-1/sqrt(3)};

    
    Frame3D F1;
    Frame3D F2;
    Frame3D F3;
    
    F1.add(f1_1);
    F1.add(f1_2);
    F1.add(f1_3);
    F1.add(f1_4);
    F1.add(f1_5);
    F1.add(f1_6);

    F1.size();

    F2.add(f2_1);
    F2.add(f2_2);
    F2.add(f2_3);
    F2.add(f2_4);

    F2.size();
    
    // vec de f3
    F3=F1+F2;

    F3.size();

    std::vector<double> v1{1/sqrt(3),1/sqrt(3),1/sqrt(3)};
    std::vector<double> v2{1-(1/sqrt(3)),-1/sqrt(3),-1/sqrt(3)};

    std::cout<<"La meilleur qualite pour F1, F2 et F3 avec le vecteur 1 est respectivement : "<<std::endl;
    F1.quality_measure(v1);
    F2.quality_measure(v1);
    F3.quality_measure(v1);

    std::cout<<"La meilleur qualite pour F1, F2 et F3 avec le vecteur 2 est respectivement : "<<std::endl;
    F1.quality_measure(v2);
    F2.quality_measure(v2);
    F3.quality_measure(v2);
    return 0;
}