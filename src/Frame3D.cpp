#include "Frame3D.hpp"
#include <type_traits>
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

// -------------------------------------- FRAME --------------------------------------------
// constructor
template <typename T, int n>
Frame<T, n>::Frame(){
};

// copy constructor
template <typename T, int n>
Frame<T,n>::Frame(const Frame& frameACopier){
    this->vectorsOfFrame=frameACopier.vectorsOfFrame;
}

// destructor
template <typename T, int n>
Frame<T,n>::~Frame(){
};

// surcharge
template <typename T, int n>
Frame<T,n>& Frame<T,n>::operator=(const Frame& frameACopier){
    // vérification que ca ne soit pas la mm variable
    if(this != &frameACopier){
        this->vectorsOfFrame=frameACopier.vectorsOfFrame;
    }
    return *this;
}

template <typename T, int n>
Frame<T,n> Frame<T,n>::operator+(const Frame& frameAAdditionner) const{
    Frame sumFrame;
    if(this->vectorsOfFrame.size()>=frameAAdditionner.vectorsOfFrame.size()){
        for (size_t i = 0; i < this->vectorsOfFrame.size(); i++)
        {
            if(i<frameAAdditionner.vectorsOfFrame.size()){
                for(int i=0;i<n;i++){
                    sumFrame.vectorsOfFrame.push_back({
                    frameAAdditionner.vectorsOfFrame[i][n],
                    });
                }
            }
            for(int i=0;i<n;i++){
                sumFrame.vectorsOfFrame.push_back({
                    this->vectorsOfFrame[i][n],
                });
            }
        }
    }
    if(this->vectorsOfFrame.size()<frameAAdditionner.vectorsOfFrame.size()){
        for (size_t i = 0; i < frameAAdditionner.vectorsOfFrame.size(); i++)
        {
            if(i < vectorsOfFrame.size()){
                for(int i=0;i<n;i++){
                    sumFrame.vectorsOfFrame.push_back({
                        this->vectorsOfFrame[i][n],
                    });
                }
            }
            for(int i=0;i<n;i++){
                sumFrame.vectorsOfFrame.push_back({
                frameAAdditionner.vectorsOfFrame[i][n],
                });
            }
        }
    }
    return sumFrame;
}

// METHODE
template <typename T, int n>
void Frame<T,n>::size(){
    std::cout<<"Le nombre de vecteur contenu dans frame est "<<this->vectorsOfFrame.size()<<std::endl;
}

template <typename T, int n>
void Frame<T,n>::add(std::vector<T> & v){
    assert(v.size()==n);
    std::array<T,n> tab_temp;
    for (int i = 0; i < n; i++){
        tab_temp[i]=v[i];
    }
    this->vectorsOfFrame.push_back(tab_temp);
}

template <typename T, int n>
double Frame<T,n>::quality_measure(const std::vector<T> & v) const{
    
    int intersection{};
    int unionSize{};
    double bestValue{};
    assert(v.size()==n);
    // on vérifie que T est de type bool
    if constexpr (std::is_same_v<T, bool>) {
        for (size_t i = 0; i < this->vectorsOfFrame.size(); i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                if(v[j]==true && this->vectorsOfFrame[i][j]==true){
                    intersection++;
                }
                if(v[j]==true||this->vectorsOfFrame[i][j]==true){
                    unionSize++;
                }
            }
            // on vérifie le nombre d'union pour ne pas diviser par zéro
            assert(unionSize!=0);
            if (bestValue < static_cast<double>(intersection)/ static_cast<double>(unionSize))
            {
                bestValue=static_cast<double>(intersection)/ static_cast<double>(unionSize);
            } 
            intersection=0;
            unionSize=0;           
        }   
        return bestValue;
    }
    // sinon on retourne 0
    else {
        assert(v.size()==n);
        
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
}