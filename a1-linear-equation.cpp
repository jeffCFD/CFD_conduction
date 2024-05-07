#include <stdio.h>
#include <math.h>




int main() {
    char name[50];
    sprintf(name , "data_total round off.dat");
    FILE*data = fopen( name ,"a");
    fprintf(data,"VARIABLES = \"Mesh spacing\"\"L2 norm\"\n");
    fprintf(data,"ZONE T=\"9 point\" F=POINT\n I = 4\n");
    FILE*data2 = fopen("graph.dat","w");
    fprintf(data2, "VARIABLES=\"X\",\"Y\",\"T\"\n");
    fprintf( data2, "ZONE T=\"STEP=0\" F=POINT\n");
        int g = 0;
        int iteration = 1000000;
        double ROE = 1e-18;  
        int steps = 0;  
        double c_diff;    
        int N_[4] ={11,21,41,81};
        double h_[4] ={0.1,0.05,0.025,0.0125};
        double T_exact[N_[g]][N_[g]] = {0};
    fprintf(data2, "I=%d, J=%d\n", N_[g], N_[g]);
    for (int i = 0; i < N_[g]; i++)
    {
        for (int  j = 0; j <N_[g] ; j++)
        {
            T_exact[i][j] =sin(M_PI*j*h_[g])*sinh(M_PI*i*h_[g])/sinh(M_PI);
        }     
    }
    
        
    
    
/*2nd order*/
    
    double T[N_[g]][N_[g]] = {0};
    double T_new[N_[g]][N_[g]] = {0};

    for (int i = 0; i < N_[g]; i++) {
        T[i][0] = 0;
        T[i][N_[g] - 1] = 0;
        T[0][i] = 0;
        T[N_[g] - 1][i] = sin(M_PI * i * h_[g]);
    }

    /*do {
        c_diff = 0;
        for (int i = 1; i < (N_[g] - 1); i++) {
            for (int j = 1; j < (N_[g] - 1); j++) {
                T_new[i][j] = (T[i + 1][j] + T[i - 1][j] + T[i][j + 1] + T[i][j - 1]) / 4.;
                c_diff = c_diff + fabs(T_new[i][j] - T[i][j]);
                T[i][j] = T_new[i][j];
            }
        }
        steps++;
        c_diff = c_diff/((N_[g]-2)*(N_[g]-2));
    } while ( c_diff > ROE && steps < iteration);
    double error = 0 ;
    for (int i = 0; i < N_[g]; i++)
    {
        for (int j = 0; j < N_[g]; j++)
        {
            error = error +(T_exact[i][j]-T[i][j])*(T_exact[i][j]-T[i][j]);     
    }
        
        
    }
    double L = sqrt(error)/(N_[g]*N_[g]);

    
    fprintf(data,"%lf\t%e\n",h_[g],L);*/


/*4th order*/
    
    /*T[N_[g]][N_[g]] = {0};
    T_new[N_[g]][N_[g]] = {0}; 
    for (int i = 0; i < N_[g]; i++) {
        T[i][0] = 0;
        T[i][N_[g] - 1] = 0;
        T[0][i] = 0;
        T[N_[g] - 1][i] = sin(M_PI * i * h_[g]);
    }

    
    do {
        c_diff = 0 ;
        for (int  i = 1; i < N_[g] - 1; i++)
        {
            for (int j =1; j < N_[g] - 1 ; j++)
            {
                if ((i == 1 && j < N_[g]-4) || (j == 1 && i < N_[g]-4))
                {
                    T_new[i][j] =(10*(T[i][j-1]+T[i-1][j])-4*(T[i+1][j]+T[i][j+1])+14*(T[i+2][j]+T[i][j+2])-6*(T[i+3][j]+T[i][j+3])+(T[i+4][j]+T[i][j+4]))/30.;     
                    c_diff = c_diff + fabs(T_new[i][j] - T[i][j]);                                                                                                                                                                                                      
                    T[i][j] = T_new[i][j];
                }
                else if ((i == 1 && j> N_[g]-5) || (i < N_[g]-4 && j == N_[g]-2)) 
                {
                    T_new[i][j] =(10*(T[i][j+1]+T[i-1][j])-4*(T[i][j-1]+T[i+1][j])+14*(T[i][j-2]+T[i+2][j])-6*(T[i][j-3]+T[i+3][j])+(T[i][j-4]+T[i+4][j]))/30. ;
                    c_diff = c_diff + fabs(T_new[i][j] - T[i][j]);                                                                                                                                                                                                      
                    T[i][j] = T_new[i][j];                
                }
                else if ((i == N_[g]-2 && j < N_[g]-4)||(j == 1 && i > N_[g]-5))
                {
                    T_new[i][j]=(10*(T[i][j-1]+T[i+1][j])-4*(T[i][j+1]+T[i-1][j])+14*(T[i][j+2]+T[i-2][j])-6*(T[i][j+3]+T[i-3][j])+(T[i][j+4]+T[i-4][j]))/30. ;
                    c_diff = c_diff + fabs(T_new[i][j] - T[i][j]);                                                                                                                                                                                                      
                    T[i][j] = T_new[i][j];                
                }
                else if ((i == N_[g] - 2 && j > N_[g]-5)||(i > N_[g]-5 && j == N_[g]-2 ))
                {
                    T_new[i][j] =(10*(T[i][j+1]+T[i+1][j])-4*(T[i-1][j]+T[i][j-1])+14*(T[i-2][j]+T[i][j-2])-6*(T[i-3][j]+T[i][j-3])+(T[i-4][j]+T[i][j-4]))/30. ;
                    c_diff = c_diff + fabs(T_new[i][j] - T[i][j]);                                                                                                                                                                                                      
                    T[i][j] = T_new[i][j];                
                }
                else
                {
                    T_new[i][j] = (16*(T[i+1][j]+T[i-1][j]+T[i][j+1]+T[i][j-1])-(T[i+2][j]+T[i-2][j]+T[i][j+2]+T[i][j-2]))/60.;
                    c_diff = c_diff + fabs(T_new[i][j] - T[i][j]);                                                                                                                                                                                                      
                    T[i][j] = T_new[i][j];
                }
            
            }
        }
        steps++;
        c_diff = c_diff/((N_[g]-2)*(N_[g]-2));
        
    } while ( c_diff > ROE && steps < iteration);
    double error = 0 ;
    for (int i = 0; i < N_[g]; i++)
    {
        for (int j = 0; j < N_[g]; j++)
        {
            error = error +(T_exact[i][j]-T[i][j])*(T_exact[i][j]-T[i][j]);     
    }
        
        
    }
    double L = sqrt(error)/(N_[g]*N_[g]);

    fprintf(data,"%lf\t%e\n",h_[g],L);*/
    

    /*9 point method*/
    T[N_[g]][N_[g]] = {0};
    T_new[N_[g]][N_[g]] = {0};
    for (int i = 0; i < N_[g]; i++) {
        T[i][0] = 0;
        T[i][N_[g] - 1] = 0;
        T[0][i] = 0;
        T[N_[g] - 1][i] = sin(M_PI * i * h_[g]);
        
    }
    do
    {
    c_diff = 0 ;
    for (int i = 1; i < N_[g]-1; i++)
    {
        for (int j = 1; j < N_[g]-1; j++)
        {
            T_new[i][j] = (4*(T[i+1][j]+T[i-1][j]+T[i][j+1]+T[i][j-1])+T[i+1][j+1]+T[i+1][j-1]+T[i-1][j+1]+T[i-1][j-1])/20.;
            c_diff = c_diff + fabs(T_new[i][j]-T[i][j]);
            T[i][j] = T_new[i][j] ;    
        }
        
    }
    c_diff = c_diff/((N_[g]-2)*(N_[g]-2));
    steps++;    
        
    } while (c_diff > ROE && steps< iteration);
    

    
    double error = 0 ;
    for (int i = 0; i < N_[g]; i++)
    {
        for (int j = 0; j < N_[g]; j++)
        {
            error = error +fabs(T_exact[i][j]-T[i][j]);     
    }
        
        
    }
    double L = (error)/(N_[g]*N_[g]);
            
    printf("iterations: %d\n", steps);
    printf ("%e\n",c_diff) ;
    
 
    fprintf(data,"%lf\t%e\n",h_[g],L);
    for (int i = 0; i < N_[g]; i++)
    {
        for (int j = 0; j < N_[g]; j++)
        {
            fprintf(data2,"%d\t%d\t%e\n",i,j,T[j][i]);
        }
        
    }
    
    
    
    printf("done");    
    
    fclose(data);
    fclose(data2);
}

    
