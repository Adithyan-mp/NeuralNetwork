#include<iostream>
#include<random>
using namespace std;

class Perceptron{
    private:
        //weight of the Perceptron
        float w[2];
        
        //bias
        float thetha;
        
        //for getting random variable
        int random();
        float getRandom();
        
        //check where the point exist in hyperplane
        float check(float x[]);
        
        //function to translate the given range to dissired output
        int unit_func(float x);
      
    public:
        Perceptron();
        //for traning and finding the best fit hyperplane
        void fit(float x[][2],float y[]);
        
        //prediction
        int predict(float x,float y);
};

int Perceptron :: random(){
    static bool first=true;
    if(first){
        srand(time(0));
        first=false;
    }
    return (rand()%10)+1;
}

float Perceptron :: getRandom(){
    return random();
}

float Perceptron::check(float x[]){
    float sum=0;
    for(int i=0;i<2;i++){
        sum+=w[i]*x[i];
    }
    return sum-thetha;
}

int Perceptron :: unit_func(float x){
    if(x<0)
        return 0;
    return 1;
}

Perceptron::Perceptron(){
   for(int i=0;i<2;i++){
       w[i]=getRandom();
   }
    thetha=getRandom();
}

void Perceptron::fit(float x[][2],float y[]){
    int size=4;
    int i=0;
    while(true){
        float yPread=check(x[i]); //hyperplane w*x-thetha
        if(yPread>0 && y[i]==0){
            for(int j=0;j<2;j++){
                //changing the hyper plane to fit the value upwards
                w[j]-=x[i][j];
            }
        }
        else if(yPread<0 && y[i]==1){
            for(int j=0;j<2;j++){
                // changing the hyper plane to fit the value downwards
                w[j]+=x[i][j];
            }
        }
        else{
            i++;
        }
        if(i==size){
            break; //converge
        }
        
    }
}


int Perceptron::predict(float x,float y){
    float input[]={x,y};
    float yPread=check(input);
    return unit_func(yPread);
    
}


int main(){
    //0r gate
    float x[][2]={
        {0,0},
        {0,1},
        {1,0},
        {1,1}
    };
    
    //ans
    float y[]={0,1,1,1};
    
    Perceptron p;
    
    //training
    p.fit(x,y);
    
    //prediction
    cout<<p.predict(1,0);
    return 0;
}