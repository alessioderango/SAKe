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

  std::vector<double>  getFunctionTypeConst() const{
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


  /** printing... */
//     void printOn(ostream& _os) const
//     {
//       // First write the fitness
//       EO<FitT>::printOn(_os);
//       _os << " pesi ";
//     // START Code of default output

//       for (int i = 0; i < w.size(); i++) {
//           _os << w[i]<< ' ';
//       }
//        _os << endl;

//       for (int i = 0; i < functionType.size(); i++) {
//          _os << "Function type " << functionType[i]<< ' ';
//          _os << endl;

//          if(functionType[i]==0){
//                 _os << "linear primo a  = " <<par[i].getParametersConst()[0] << ' ' << endl;
//                 _os << "linear primo b = " <<par[i].getParametersConst()[1] << ' ' << endl;
//          }
//          else
//          if(functionType[i]==1)
//                 _os << "espo primo a  = "  <<par[i].getParametersConst()[0] << ' ' << endl;
//          else
//          {
//              if(functionType[i]==2){
//               _os << "gamma alfa = "<<par[i].getParametersConst()[0]<< ' ' << endl;
//               _os << "gamma beta = "<< par[i].getParametersConst()[1]<< ' ' << endl;
//              }
//          }
//       }
//       _os << endl;
     // END   Code of default output
//     }




private:			   // put all data here
    // START Private data of an eoOneMax object
    std::vector<double> w;
    std::vector<Parameters> par;
    std::vector<int> functionType;
    QVector<double> yCombinata;
    // END   Private data of an eoOneMax object
};

#endif
