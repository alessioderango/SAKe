/** -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

The above line is usefulin Emacs-like editors
 */

/*
Template for creating a new representation in EO
================================================
*/

#ifndef _eoOneMax_h
#define _eoOneMax_h

#include "parameters.h"
#include <QVector>
/**
 *  Always write a comment in this format before class definition
 *  if you want the class to be documented by Doxygen

 * Note that you MUST derive your structure from EO<fitT>
 * but you MAY use some other already prepared class in the hierarchy
 * like eoVector for instance, if you handle a vector of something....

 * If you create a structure from scratch,
 * the only thing you need to provide are
 *        a default constructor
 *        IO routines printOn and readFrom
 *
 * Note that operator<< and operator>> are defined at EO level
 * using these routines
 */
template< class FitT>
class eoOneMax: public EO<FitT> {
public:
  /** Ctor: you MUST provide a default ctor.
   * though such individuals will generally be processed
   * by some eoInit object
   */
  eoOneMax()
  {
    // START Code of default Ctor of an eoOneMax object
    yCombinata.resize(0);
    w.resize(0);
    par.resize(0);
    functionType.resize(0);
    percentageVariationWeight.resize(0);
    percentageVariationLinearA.resize(0);
    percentageVariationLinearB.resize(0);
    percentageVariationGammaA.resize(0);
    percentageVariationGammaB.resize(0);
    translation.resize(0);
    // END   Code of default Ctor of an eoOneMax object
  }

  virtual ~eoOneMax()
  {
    // START Code of Destructor of an eoEASEAGenome object
    // END   Code of Destructor of an eoEASEAGenome object
  }

  virtual string className() const { return "eoOneMax"; }



  // FUNCTION W

  std::vector<double>  getWConst() const{
      return w;
  }

  std::vector<double>  getW() {
      return w;
  }

  double  getW(int i){
      return w[i];
  }

  double  getWConst(int i) const{
      return w[i];
  }

  void  setW(int i,double value){
      w[i]=value;
  }

  void  addW(double value){
      w.push_back(value);
  }

  // FUNCTION PARAMETERS

  std::vector<Parameters>  getParConst() const{
      return par;
  }

  std::vector<Parameters>  getPar() {
      return par;
  }

  Parameters  getPar(int i){
      return par[i];
  }

  Parameters  getParConst(int i) const{
      return par[i];
  }

  void  setParameters(int i,int j,double value){
      par[i].setParameters(j,value);
  }


  void  setPar(int i,Parameters value){
      par[i]=value;
  }

  void  addPar(Parameters value){
      par.push_back(value);
  }

  // FUNCTION FUNCTIONTYPE

  std::vector<int>  getFunctionTypeConst() const{
      return functionType;
  }

  std::vector<int>  getFunctionType() {
      return functionType;
  }

  int  getFunctionType(int i){
      return functionType[i];
  }

  int  getFunctionTypeConst(int i) const{
      return functionType[i];
  }

  void  setFunctionType(int i,int value){
      functionType[i]=value;
  }

  void  addFunctionType(int value){
      functionType.push_back(value);
  }

   QVector<double>  getYCombinata(){
      return yCombinata;
  }
   QVector<double>  getYCombinataConst() const{
       return yCombinata;
   }

  double  getYCombinata(int i){
      return yCombinata[i];
  }

  double  getYCombinataConst(int i) const{
      return yCombinata[i];
  }

  void  setYCombinata(int i,double value){
      yCombinata[i]=value;
  }

  void  addYCombinata(double value){
      yCombinata.push_back(value);
  }

  void  clearYCombinata(){
      yCombinata.clear();
  }

  void setWFromNew(std::vector<double> _w){
      w=_w;
  }
  void setParFromNew(std::vector<Parameters> _w){
      par=_w;
  }
  void setFunctionTypeFromNew(std::vector<int> _w){
      functionType=_w;
  }
  void setYcombinataFromNew(QVector<double> _w){
      yCombinata=_w;
  }

   std::vector<double> getPercentageVariationWeight(){
       return percentageVariationWeight;
   }
   std::vector<double> getPercentageVariationLinearA(){
       return percentageVariationLinearA;
   }
   std::vector<double> getPercentageVariationLinearB(){
       return percentageVariationLinearB;
   }
   std::vector<double> getPercentageVariationGammaA(){
       return percentageVariationGammaA;
   }
   std::vector<double> getPercentageVariationGammaB(){
       return percentageVariationGammaB;
   }


   std::vector<double> getPercentageVariationWeightConst() const{
       return percentageVariationWeight;
   }
   std::vector<double> getPercentageVariationLinearAConst() const{
       return percentageVariationLinearA;
   }
   std::vector<double> getPercentageVariationLinearBConst() const{
       return percentageVariationLinearB;
   }
   std::vector<double> getPercentageVariationGammaAConst() const{
       return percentageVariationGammaA;
   }
   std::vector<double> getPercentageVariationGammaBConst() const{
       return percentageVariationGammaB;
   }


   void setPercentageVariationWeight(std::vector<double> a){
       percentageVariationWeight = a;
   }
   void setPercentageVariationLinearA(std::vector<double> a){
       percentageVariationLinearA = a;
   }
   void setPercentageVariationLinearB(std::vector<double> a){
       percentageVariationLinearB = a;
   }
   void setPercentageVariationGammaA(std::vector<double> a){
       percentageVariationGammaA = a;
   }
   void setPercentageVariationGammaB(std::vector<double> a){
       percentageVariationGammaB = a;
   }
   void setTranslation(std::vector<double> a){
       translation = a;
   }

   double getPercentageVariationWeight(int i){
       return percentageVariationWeight[i];
   }
   double getPercentageVariationLinearA(int i){
       return percentageVariationLinearA[i];
   }
   double getPercentageVariationLinearB(int i){
       return percentageVariationLinearB[i];
   }
   double getPercentageVariationGammaA(int i){
       return percentageVariationGammaA[i];
   }
   double getPercentageVariationGammaB(int i){
       return percentageVariationGammaB[i];
   }

   void setPercentageVariationWeight(int i,double a){
       percentageVariationWeight[i] = a;
   }
   void setPercentageVariationLinearA(int i,double a){
       percentageVariationLinearA[i] = a;
   }
   void setPercentageVariationLinearB(int i,double a){
       percentageVariationLinearB[i] = a;
   }
   void setPercentageVariationGammaA(int i,double a){
       percentageVariationGammaA[i] = a;
   }
   void setPercentageVariationGammaB(int i,double a){
       percentageVariationGammaB[i] = a;
   }
   void setTranslation(int i,double a){
       translation[i] = a;
   }



   void addPercentageVariationWeight(double a){
       percentageVariationWeight.push_back(a);
   }
   void addPercentageVariationLinearA(double a){
       percentageVariationLinearA.push_back(a);
   }
   void addPercentageVariationLinearB(double a){
       percentageVariationLinearB.push_back(a);
   }
   void addPercentageVariationGammaA(double a){
       percentageVariationGammaA.push_back(a);
   }
   void addPercentageVariationGammaB(double a){
       percentageVariationGammaB.push_back(a);
   }

   void addTranslation(double a){
       translation.push_back(a);
   }

   void newVariationWeight(double a){
      percentageVariationWeight = new vector<double>(a);
   }
   void newVariationLinearA(double a){
       percentageVariationLinearA= new vector<double>(a);
   }
   void newVariationLinearB(double a){
       percentageVariationLinearB= new vector<double>(a);
   }
   void newVariationGammaA(double a){
       percentageVariationGammaA= new vector<double>(a);
   }
   void newVariationGammaB(double a){
       percentageVariationGammaB= new vector<double>(a);
   }


   std::vector<double>  getTranslationConst() const{
       return translation;
   }

   std::vector<double>  getTranslation() {
       return translation;
   }

   double  getTranslation(int i){
       return translation[i];
   }

   double  getTranslationConst(int i) const{
       return translation[i];
   }

private:			   // put all data here

    std::vector<double> w;
    std::vector<Parameters> par;
    std::vector<int> functionType;
    std::vector<double> percentageVariationWeight;
    std::vector<double> percentageVariationLinearA;
    std::vector<double> percentageVariationLinearB;
    std::vector<double> percentageVariationGammaA;
    std::vector<double> percentageVariationGammaB;
    std::vector<double> translation;
    QVector<double> yCombinata;
};

#endif
