/** -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

 The above line is usefulin Emacs-like editors
 */

/*
 Template for creating a new representation in EO
 ================================================
 */

#ifndef _eoSAKe_h
#define _eoSAKe_h
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Ym.h"

using namespace std;
template<class FitT>
class eoSAKe: public EO<FitT>{
public:

    eoSAKe() {
    }

    eoSAKe(int _size){
        size = _size;
        //Fi = NULL;
        number =0;
        dYcr=0;
        momentoDelPrimoOrdine=0;
        AUC =0;
    }

    virtual ~eoSAKe() {
    }

    virtual string className() const{
        return "eoSAKe";
    }

    /** printing... */
    void printOn(ostream& _os) const{
        _os << size << ' ';
        for (unsigned i = 0; i < size; i++)
            _os << Fi[i] << ' ';
    }

    void setSize(int _size){
        this->size = _size;
    }

    int getSizeConst() const{
        return this->size;
    }

    int getSize() {
        return this->size;
    }

    void setFi(std::vector<double> _Fi){
        Fi =  _Fi;
    }

    void setdYcr(double _dYcr){
        dYcr =  _dYcr;
    }
    double getdYcr()  {
        return dYcr;
    }
    double getdYcrConst() const{
        return dYcr;
    }

    void setMomentoDelPrimoOrdine(double _momentoDelPrimoOrdine){
        momentoDelPrimoOrdine =  _momentoDelPrimoOrdine;
    }
    double getMomentoDelPrimoOrdine()  {
        return momentoDelPrimoOrdine;
    }
    double getMomentoDelPrimoOrdineConst() const{
        return momentoDelPrimoOrdine;
    }
    void setYmMin(Ym _YmMin){
        min =  _YmMin;
    }
    Ym getYmMin(){
        return min;
    }
    Ym getYmMinConst() const{
        return min;
    }

    void setYmMin2(Ym _YmMin2){
        min2 =  _YmMin2;
    }
    Ym getYmMin2(){
        return min2;
    }
    Ym getYmMin2Const() const{
        return min2;
    }

    void setFiIndex(int _i, double value){
        Fi[_i] = value;
    }

    void setBests(std::vector<Ym> a){
        bests = a;
    }

    std::vector<Ym> getBests(){
        return bests;
    }

    std::vector<Ym> getBestsConst() const{
        return bests;
    }

    double getFiIndex(int _i){
        return Fi[_i];
    }

    double getFiConstIndex(int _i) const{
        return Fi[_i];
    }

//    double*& getFi(){
//        return Fi;
//    }
    std::vector<double> getFi(){
        return Fi;
    }

    //    double* getFiConst() const{
    //        return Fi;
    //    }

    std::vector<double> getFiConst() const{
        return Fi;
    }

    //    void deleteFi(){
    //        //delete []Fi;
    //        free(Fi);
    //    }

    int number;


    std::vector<int> getTP() const{
        return TP;
    }
    void setTP(std::vector<int> &value){
        TP = value;
    }

    std::vector<int> getFN() const{
        return FN;
    }
    void setFN(std::vector<int> &value){
        FN = value;
    }

    std::vector<int> getFP() const{
        return FP;
    }
    void setFP(std::vector<int> &value){
        FP = value;
    }

    std::vector<int> getTN() const{
        return TN;
    }
    void setTN(std::vector<int> &value){
        TN = value;
    }

    std::vector<double> getTPR() const{
        return TPR;
    }
    void setTPR(std::vector<double> &value){
        TPR = value;
    }

    std::vector<double> getFPR() const{
        return FPR;
    }
    void setFPR(std::vector<double> &value){
        FPR = value;
    }

    double getAUC() const{
        return AUC;
    }
    void setAUC(double value){
        AUC = value;
    }

private:

    //double* Fi;	// kernel function
    std::vector<double> Fi;
    int size;

    double dYcr;
    Ym min;
    Ym min2;
    double momentoDelPrimoOrdine;
    std::vector<Ym> bests;

    //For ROC Fitness
    std::vector<int> TP;// true positive
    std::vector<int> FN;// false negative

    //outside the activation range
    std::vector<int> FP;// false positive
    std::vector<int> TN;// true negative

    std::vector<double> TPR;// true positive rate
    std::vector<double> FPR;// False positive rate

    double AUC;


};

#endif

