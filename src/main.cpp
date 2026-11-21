#include "Frame3D.hpp"
int main(){
    // Partie 1
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

    // Partie 2
    try {
        // frame.add(v);
    }
    catch (const AddFrameException& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    // vec de f1
    std::vector<float> ff1_1{1,0,0};
    std::vector<float> ff1_2{-1,0,0};
    std::vector<float> ff1_3{0,1,0};
    std::vector<float> ff1_4{0,-1,0};
    std::vector<float> ff1_5{0,0,1};
    std::vector<float> ff1_6{0,0,-1};

    // vec de f2 
    std::vector<float> ff2_1{1,0,0};
    std::vector<float> ff2_2{0,1,0};
    std::vector<float> ff2_3{0,0,1};
    std::vector<float> ff2_4{-1/sqrt(3),-1/sqrt(3),-1/sqrt(3)};

    std::vector<float> vf1{1/sqrt(3),1/sqrt(3),1/sqrt(3)};
    std::vector<float> vf2{1-(1/sqrt(3)),-1/sqrt(3),-1/sqrt(3)};
    
    Frame<float,3> FR1;
    Frame<float,3> FR2;
    Frame<float,3> FR3;

    FR1.add(ff1_1);
    FR1.add(ff1_2);
    FR1.add(ff1_3);
    FR1.add(ff1_4);
    FR1.add(ff1_5);
    FR1.add(ff1_6);

    FR1.size();

    FR2.add(ff2_1);
    FR2.add(ff2_2);
    FR2.add(ff2_3);
    FR2.add(ff2_4);

    FR2.size();

    // vec de f3
    FR3=FR1+FR2;

    FR3.size();
    MinimalFrame<float, 3> MF1(FR1);
    MF1.size();
    MinimalFrame<float, 3> MF2(FR2);
    MF2.size();
    MinimalFrame<float, 3> MF3(FR3);
    MF3.size();

    // meme qualité lorsque les frames sont en double
    std::cout<<"La meilleur qualite pour FR1, FR2 et FR3 avec le vecteur 1 est respectivement : "<<std::endl;
    FR1.quality_measure(vf1);
    FR2.quality_measure(vf1);
    FR3.quality_measure(vf1);

    // meme qualité mm lorsque c'est des floats
    std::cout<<"La meilleur qualite pour FR1, FR2 et FR3 avec le vecteur 2 est respectivement : "<<std::endl;
    FR1.quality_measure(vf2);
    FR2.quality_measure(vf2);
    FR3.quality_measure(vf2);

    // vec de f4
    std::vector<bool> boolF4_1{true,false,false,false};
    std::vector<bool> boolF4_2{false,true,false,false};
    std::vector<bool> boolF4_3{false,false,true,false};
    std::vector<bool> boolF4_4{false,false,false,true};

    // vec de f5
    std::vector<bool> boolF5_1{true,false,true,false};
    std::vector<bool> boolF5_2{false,true,false,true};

    Frame<bool,4> F4;
    Frame<bool,4> F5;

    F4.add(boolF4_1);
    F4.add(boolF4_2);
    F4.add(boolF4_3);
    F4.add(boolF4_4);

    F5.add(boolF5_1);
    F5.add(boolF5_2);

    std::cout<<"Qualite de F4 & F5"<<std::endl;

    std::vector<bool> vb1{true, true, false, false};
    F4.quality_measure(vb1);
    F5.quality_measure(vb1);

    // PARTIE 3
    std::vector<int> p1{1,0};
    std::vector<int> p2{-1,0};
    std::vector<int> p3{0,1};
    std::vector<int> p4{0,-1};

    PrimitiveFrame<2> PF(3);

    for (int x = -3; x <= 3; x++) {
        for (int y = -3; y <= 3; y++) {
            if (std::gcd(std::abs(x), std::abs(y)) == 1) {
                std::vector<int> v = {x, y};
                PF.add(v);
            }
        }
    }

    std::vector<int> PF2v{-2,2};
    std::cout<<"Qualite de PF avec vecteur -2,2"<<std::endl;
    PF.quality_measure(PF2v);
    PrimitiveFrame<2> F6(1);
    F6.add(p1);
    F6.add(p2);
    F6.add(p3);
    F6.add(p4);
    F6.quality_measure(PF2v);
    return 0;
}