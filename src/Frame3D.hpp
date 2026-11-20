#pragma once
#include <vector>
#include <array>
#include <iostream>
#include <cmath>
#include <cassert>
#include <exception>
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

class AddFrameException : public std::exception {
    public:
        const char* what() const noexcept override {
            return "Erreur : La dimension du vecteur n'est pas correcte";
        }
};

template <typename T,int n>
class Frame{
    protected:
        std::vector<std::array<T,n>> vectorsOfFrame;
    public:
        // constructor
        Frame();
        // copy constructor
        Frame(const Frame& frameACopier);
        // destructor
        ~Frame();
        // surcharge
        Frame& operator=(const Frame& frameACopier);
        Frame operator+(const Frame& frameAAdditionner) const;
        // METHODE
        void size();
        void add(const std::vector<T>& v);
        void add(const std::array<T,n>& v);
        double quality_measure(const std::vector<T> & v) const;
        std::size_t sizeOfFrame()const{
            return this->vectorsOfFrame.size();
        }
         const std::array<T,n>& getVector(std::size_t i) const {
            return vectorsOfFrame.at(i);
        }
};

template <typename T, int n>
class MinimalFrame : public Frame<T,n>{
    public:
        MinimalFrame(const Frame<T,n>& frame);
};



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
    // sumFrame.vectorsOfFrame = this->vectorsOfFrame;
    // sumFrame.vectorsOfFrame.insert(sumFrame.vectorsOfFrame.end(),
    //                                frameAAdditionner.vectorsOfFrame.begin(),
    //                                frameAAdditionner.vectorsOfFrame.end());
    if(this->vectorsOfFrame.size()>=frameAAdditionner.vectorsOfFrame.size()){
        for (size_t i = 0; i < this->vectorsOfFrame.size(); i++)
        {
            if(i<frameAAdditionner.vectorsOfFrame.size()){
                sumFrame.vectorsOfFrame.push_back(frameAAdditionner.vectorsOfFrame[i]);
            }
            sumFrame.vectorsOfFrame.push_back(this->vectorsOfFrame[i]);
        }
    }
    if(this->vectorsOfFrame.size()<frameAAdditionner.vectorsOfFrame.size()){
        for (size_t i = 0; i < frameAAdditionner.vectorsOfFrame.size(); i++)
        {
            if(i < vectorsOfFrame.size()){
                sumFrame.vectorsOfFrame.push_back(this->vectorsOfFrame[i]);
            }
            sumFrame.vectorsOfFrame.push_back(frameAAdditionner.vectorsOfFrame[i]);
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
void Frame<T,n>::add(const std::vector<T>& v){
    if(v.size()!=n){
        throw AddFrameException();
    }
    std::array<T,n> tab_temp;
    for (int i = 0; i < n; i++){
        tab_temp[i]=v[i];
    }
    this->vectorsOfFrame.push_back(tab_temp);
}


template <typename T, int n>
void Frame<T,n>::add(const std::array<T,n>& v){
    if(v.size()!=n){
        throw AddFrameException();
    }
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
        std::cout<<"La meilleur qualité est "<<bestValue<<std::endl;
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

template <typename T, int n>
MinimalFrame<T,n>::MinimalFrame(const Frame<T,n>& frame){
    int compteurN{};
    bool ajouter=true;
    for (size_t i = 0; i < frame.sizeOfFrame(); i++)
    {
        for (size_t j = 0; j < this->vectorsOfFrame.size(); j++)
        {
            for (size_t z = 0; z < n; z++)
            {
                // si le nombre existe dans le tableau de minimalframe
                if(frame.getVector(i)[z]==this->vectorsOfFrame[j][z]){
                    compteurN++;
                }
            }
            if(compteurN==n){
                ajouter=false;
            }
            compteurN=0;
            
        }
        if(ajouter){
            this->add(frame.getVector(i));
        }
        ajouter=true;
    }
};