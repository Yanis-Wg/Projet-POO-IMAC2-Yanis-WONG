#include "Frame3D.hpp"

// constructor
Frame3D::Frame3D() = default;

// copy constructor
Frame3D::Frame3D(const Frame3D& frameACopier){
    this->vectorsOfFrame=frameACopier.vectorsOfFrame;
}

// destructor
Frame3D::~Frame3D() = default;

// surcharge
Frame3D& Frame3D::operator=(const Frame3D& frameACopier){
    // vérification que ca ne soit pas la mm variable
    if(this != &frameACopier){
        this->vectorsOfFrame=frameACopier.vectorsOfFrame;
    }
    return *this;
}

Frame3D Frame3D::operator+(const Frame3D& frameAAdditionner) const{
    Frame3D sumFrame;
    if(this->vectorsOfFrame.size()>=frameAAdditionner.vectorsOfFrame.size()){
        for (size_t i = 0; i < this->vectorsOfFrame.size(); i++)
        {
            if(i<frameAAdditionner.vectorsOfFrame.size()){
                sumFrame.vectorsOfFrame.push_back({
                    frameAAdditionner.vectorsOfFrame[i][0],
                    frameAAdditionner.vectorsOfFrame[i][1],
                    frameAAdditionner.vectorsOfFrame[i][2]
                });
            }
            sumFrame.vectorsOfFrame.push_back({
                this->vectorsOfFrame[i][0],
                this->vectorsOfFrame[i][1],
                this->vectorsOfFrame[i][2]
            });
        }
    }
    if(this->vectorsOfFrame.size()<frameAAdditionner.vectorsOfFrame.size()){
        for (size_t i = 0; i < frameAAdditionner.vectorsOfFrame.size(); i++)
        {
            if(i < vectorsOfFrame.size()){
                sumFrame.vectorsOfFrame.push_back({
                    this->vectorsOfFrame[i][0],
                    this->vectorsOfFrame[i][1],
                    this->vectorsOfFrame[i][2]
                });
            }
            sumFrame.vectorsOfFrame.push_back({
                frameAAdditionner.vectorsOfFrame[i][0],
                frameAAdditionner.vectorsOfFrame[i][1],
                frameAAdditionner.vectorsOfFrame[i][2]
            });
        }
    }
    return sumFrame;
}

// METHODE
void Frame3D::size(){
    std::cout<<"Le nombre de vecteur contenu dans frame est "<<this->vectorsOfFrame.size()<<std::endl;
}

void Frame3D::add(std::vector<double> & v){
    this->vectorsOfFrame.push_back({v[0],v[1],v[2]});
}

double Frame3D::quality_measure(const std::vector<double> & v) const{
    // comme le résultat est compris entre -1 et 1 alors je décide que si on retourne -3 alors ca veut dire que le vecteur ne faisait pas la bonne taille, si je retourne -2 c'est que la frame est vide ou vecteur nul
    if (v.size()!=3)
    {
        return -3;
    }    
    
    double maxQuality{-2};
    double produitScalaire{};
    double produitNorme{};
    double normeVect=sqrt(pow(v[0],2)+pow(v[1],2)+pow(v[2],2));
    double normeVecOfFrame{};

    // on vérifie pas assertion que le vecteur v est non nul
    assert(normeVect!=0);

    size_t tailleFrame3D= this->vectorsOfFrame.size();
    for (size_t i = 0; i < tailleFrame3D; i++)
    {
        produitScalaire=v[0]*this->vectorsOfFrame[i][0]+v[1]*this->vectorsOfFrame[i][1]+v[2]*this->vectorsOfFrame[i][2];
        normeVecOfFrame=sqrt(pow(this->vectorsOfFrame[i][0],2)+pow(this->vectorsOfFrame[i][1],2)+pow(this->vectorsOfFrame[i][2],2));
        assert(normeVecOfFrame!=0);
        produitNorme=normeVect*normeVecOfFrame;
        if((produitScalaire/produitNorme)>maxQuality){
            maxQuality=produitScalaire/produitNorme;
        }
    }
    std::cout<<"La meilleur qualité est "<<maxQuality<<std::endl;
    return maxQuality;
}

void turn_primitive(std::vector<int>& v){
    assert(!v.empty());
    int pgcd=v[0];
    for (size_t i = 1; i < v.size(); i++)
    {
        pgcd=std::gcd(pgcd,v[i]);
    }
    assert(pgcd!=0);
    for (size_t i = 0; i < v.size(); i++)
    {
        v[i]=v[i]/pgcd;
    }
}