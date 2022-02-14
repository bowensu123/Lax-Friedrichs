//
//  main.cpp
//  Lax-Friedriches
//
//  Created by Su Bowen on 2022/2/13.
//

#include <iostream>
#include <cmath>
double g( double x){
    return pow(x,2);
}
double exact(double x, double t){
    return pow(t-x,2);
}
int main(int argc, const char * argv[]) {
    int N, M;   //N: mesh number of domain; M:mesh number of time
    std::cout<<"input N: mesh number of domain"<<std::endl;
    std::cin>> N;
    std::cout<<"input M: mesh number of time"<<std::endl;
    std::cin>> M;
    double dx = 1/(double)N;
    double dt = 1/(double)N;
    double lambda = dx/dt*0.5;
    if(fabs(lambda)>1){
        throw "Reinput N and M such that stability condion is satisfied ";
    }
    double **array = new double* [N+1];
    for (int i= 0;i<N+1;i++)
    {
        array[i] = new double[N+1];
    }
    for(int n = 0; n<N+1;n++ )
    { if (n == 0)
        {
        for (int j=0;j<N+1;j++)
        {
            array[j][0] = g(j*dx);
          
        }
        }
      else {
            for(int j= 0; j<N+1;j++)
            {
             if(j==0)
               {
                array[0][n] = pow(n*dt,2);
               }
               else
              {
                array[j][n] = (0.5-lambda)*array[j+1][n-1]+ (0.5+lambda)*array[j-1][n-1];
              }
            }
        }
        
    }
    double error = 0;
    for(int i=0;i<N+1;i++){
        for (int j= 0;j<N+1;j++){
            error += pow(array[i][j]-exact(i*dx,j*dt),2);
        }
    }
 
   std::cout<<error<<std::endl;
   
    for( int indx = 0; indx < N+1; ++indx )
      {
        delete array[indx];
      }    
    delete [] array;
    
    return 0;
}
