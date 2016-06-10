#include "controlpoints.h"

ControlPoints::ControlPoints()
{

}


double getHMed(double *kernel, int SIZE){
    double sum=0;
    for (int i = 0; i < SIZE; i++) {
        sum+=kernel[i];
    }
    return sum/SIZE;

}

double getHMax(double *kernel, int SIZE){
    double max=-1;
    for (int i = 0; i < SIZE; i++) {
        if(max< kernel[i])
            max = kernel[i];
    }
    return max;

}

void initAlreadyConsidered(double *&alreadyConsidered, int SIZE){
    for (int i = 0; i < SIZE; i++) {
        alreadyConsidered[i]=-1;
    }
}

void stampa(double *kernel, int SIZE){
    for (int i = 0; i < SIZE; i++) {
        cout << kernel[i] << " ";
    }
    cout << endl;
}
int getInterset(double *kernel,double *&alreadyConsidered,double *&alreadyConsideredTemp,double boundary, int SIZE){
    int count=0;
    for (int i = 0; i < SIZE; i++) {
        if(alreadyConsidered[i]==-1  && kernel[i] >= boundary){
            alreadyConsideredTemp[i]=kernel[i];
            alreadyConsidered[i]=kernel[i];
            count++;
        }
    }
    return count;
}

void getPoints(double *&a,std::vector< double> &xVec,std::vector< double> &yVec, int SIZE){


    double sum=0;
    double x=0;
    int count=0;
    for (int i = 0; i < SIZE-1; i++) {
        if(i==168){
         cout << "CIAO" << endl;
        }
        if(a[i]!=-1){
            if(a[i+1]==-1 && a[i-1] ==-1){
                //write << i+1 << "; " << a[i] << "; " << endl;
                xVec.push_back(i+1);
                yVec.push_back(a[i]);
                cout << " x = " << i+1 << " y = " << a[i] << endl;
            }else{

                sum+=a[i];
                x+=i;
                count++;
                if(a[i+1]==-1){
                    //write << (x/count)+1 << "; " << sum/count << "; " << endl;
                    xVec.push_back((x/count)+1);
                    yVec.push_back(sum/count);
                    cout << " x = " << (x/count)+1 << " y = " << sum/count << endl;
                    sum=0;
                    count=0;
                    x=0;
                }else{
                    if(a[i+1]!=-1 && i==SIZE-2){
                        sum+=a[i+1];
                        x+=i+1;
                        count++;
                        xVec.push_back((x/count)+1);
                        yVec.push_back(sum/count);
                        cout << " x = " << (x/count)+1 << " y = " << sum/count << endl;
                        sum=0;
                        count=0;
                        x=0;
                    }
                }
            }
        }
    }


}

 void ControlPoints::calculateControlPoints(double * kernel, int size_kernel){

     double hmed= getHMed(kernel,size_kernel);
     double hmax = getHMax(kernel,size_kernel);
     double hmed2= hmed/2;
     double hmedmax= (hmed+hmax)/2;
     double hzero = 0;

     cout << "hmax = " << hmax << endl;
     cout << "hmedmax = " << hmedmax << endl;
     cout << "hmed = "<< hmed << endl;
     cout << "hmed2 = " << hmed2 <<endl;

     //    double alreadyConsideredHMax[size_kernel];
     //    double alreadyConsideredHMedMax[size_kernel];
     //    double alreadyConsideredHMed[size_kernel];
     //    double alreadyConsideredHMed2[size_kernel];
     //    double alreadyConsidered[size_kernel];
     double *alreadyConsideredHMax = new double[size_kernel];
     double *alreadyConsideredHMedMax= new double[size_kernel];
     double *alreadyConsideredHMed= new double[size_kernel];
     double *alreadyConsideredHMed2= new double[size_kernel];
     double *alreadyConsidered= new double[size_kernel];
     double *alreadyConsideredZero= new double[size_kernel];
     initAlreadyConsidered(alreadyConsidered,size_kernel);
     initAlreadyConsidered(alreadyConsideredHMax,size_kernel);
     initAlreadyConsidered(alreadyConsideredHMedMax,size_kernel);
     initAlreadyConsidered(alreadyConsideredHMed,size_kernel);
     initAlreadyConsidered(alreadyConsideredHMed2,size_kernel);
     initAlreadyConsidered(alreadyConsideredZero,size_kernel);
     int count = getInterset(kernel,alreadyConsidered,alreadyConsideredHMax,hmax,size_kernel);
     cout << "ho trovato " << count << " barre superiori a " << hmax << endl;
     count=getInterset(kernel,alreadyConsidered,alreadyConsideredHMedMax,hmedmax,size_kernel);
     cout << "ho trovato " << count << " barre superiori a " << hmedmax << endl;
     count=getInterset(kernel,alreadyConsidered,alreadyConsideredHMed,hmed,size_kernel);
     cout << "ho trovato " << count << " barre superiori a " << hmed << endl;
     count=getInterset(kernel,alreadyConsidered,alreadyConsideredHMed2,hmed2,size_kernel);
     cout << "ho trovato " << count << " barre superiori a " << hmed2 << endl;
     count=getInterset(kernel,alreadyConsidered,alreadyConsideredHMed2,hmed2,size_kernel);
     cout << "ho trovato " << count << " barre superiori a " << hmed2 << endl;
     count=getInterset(kernel,alreadyConsidered,alreadyConsideredZero,hzero,size_kernel);
     cout << "ho trovato " << count << " barre superiori a " << hzero << endl;
     //stampa(alreadyConsideredHMax);
     //stampa(alreadyConsideredHMedMax);
     //stampa(alreadyConsideredHMed);
     //stampa(alreadyConsideredHMed2);
     cout << " points from hmax" << endl;
     getPoints(alreadyConsideredHMax,x,y,size_kernel);
     cout << " points from hmedhmax" << endl;
     getPoints(alreadyConsideredHMedMax,x,y,size_kernel);
     cout << " points from hmed" << endl;
     getPoints(alreadyConsideredHMed,x,y,size_kernel);
     cout << " points from hmed2" << endl;
     getPoints(alreadyConsideredHMed2,x,y,size_kernel);
     cout << " points from zero" << endl;
     getPoints(alreadyConsideredZero,x,y,size_kernel);
//     for (int i = 0; i < x.size(); i++) {
//         cout << x[i] <<" " << y[i] << endl;
//     }


     int alto;
     for (alto = x.size() - 1; alto > 0; alto-- )
     {
         for (int i=0; i<alto; i++)
         {
             if (x[i]>x[i+1]) /* sostituire ">" con "<" per avere un ordinamento decrescente */
             {
                 double tmp = x[i];
                 x[i] = x[i+1];
                 x[i+1] = tmp;
                 double tmp2 = y[i];
                 y[i] = y[i+1];
                 y[i+1] = tmp2;

             }
         }
     }

     delete [] alreadyConsideredHMax;
     delete [] alreadyConsideredHMedMax;
     delete [] alreadyConsideredHMed;
     delete [] alreadyConsideredHMed2;
     delete [] alreadyConsidered;

     for (int i = 0; i < x.size(); i++) {
         cout << x[i] <<" " << y[i] << endl;
     }
 }

 std::vector<double> ControlPoints::getX() const
 {
     return x;
 }

 void ControlPoints::setX(const std::vector<double> &value)
 {
     x = value;
 }

 std::vector<double> ControlPoints::getY() const
 {
     return y;
 }

 void ControlPoints::setY(const std::vector<double> &value)
 {
     y = value;
 }

 void ControlPoints::getSubdividePointsFromKernel( double *kernel,int size_kernel,int n,std::vector<double> &x, std::vector<double> &y){

     double sumx=0;
     double sumy=0;
     int end = ((size_kernel%n)==0) ? size_kernel : (size_kernel-n);
     for (int i = 0; i < end; i+=n) {
         sumx=0;
         sumy=0;
         for (int j = 0; j < n; j++) {
             sumx+=j+(i+1);
             sumy+=kernel[j+i];
         }
         x.push_back(sumx/n);
         y.push_back(sumy/n);
     }
     if(size_kernel%n !=0){
         sumx=0;
         sumy=0;
         int count=0;
         for (int i = (size_kernel-(n-1)); i < size_kernel; i++) {
             sumx+=(i+1);
             sumy+=kernel[i];
              count++;
         }
         x.push_back(sumx/count);
         y.push_back(sumy/count);
     }
 }

 void ControlPoints::getSubdividePointsFromControlPoints(std::vector< double> x, std::vector< double> y, int n, std::vector<double> &xOutput, std::vector<double> &yOutput){
     double sumx=0;
     double sumy=0;
     int end = ((y.size()%n)==0) ? y.size() : (y.size()-n);
     for (int i = 0; i < end; i+=n) {
         sumx=0;
         sumy=0;
         for (int j = 0; j < n; j++) {
             sumx+=x[j+i];
             sumy+=y[j+i];
         }
         xOutput.push_back(sumx/n);
         yOutput.push_back(sumy/n);
     }

     if(y.size()%n !=0){
         sumx=0;
         sumy=0;
         int count=0;
         for (int i = (y.size()-(n-1)); i < y.size(); i++) {
             sumx+=x[i];
             sumy+=y[i];
             count++;
         }
         xOutput.push_back(sumx/count);
         yOutput.push_back(sumy/count);
     }


 }
