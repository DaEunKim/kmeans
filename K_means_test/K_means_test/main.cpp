//
//  main.cpp
//  K_means_test
//
//  Created by 김다은 on 2016. 10. 30..
//  Copyright © 2016년 김다은. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;
#define K_COUNT 2
#define DATA_COUNT 1000

class pos{
public:
    double x;
    double y;
};

int main(){
    pos* k = new pos[K_COUNT];
    pos* center = new pos[K_COUNT];
    
    double count_Group[K_COUNT]={0,};
    
    vector< pos > datas;
    vector< double > distance[K_COUNT];
    
    //data
    for(int i=0;i<DATA_COUNT;i++){
        pos tmp;
        tmp.x = (double)(rand()%100);
        tmp.y = (double)(rand()%100);
        cout<<"("<<tmp.x<<","<<tmp.y<<")"<<endl;
        datas.push_back(tmp);
    }//Randomly
    
    //random k, init
    for(int i=0; i<K_COUNT; i++)
    {
        k[i] = datas[i];
        center[i].x = datas[i].x;
        center[i].y = datas[i].y;
        distance[i].resize( DATA_COUNT );
    }
    bool loop = true;
    while(loop){ //when the k-positions are all same with next position.
        //center init
        for(int i=0;i<K_COUNT; i++){
            center[i].x = 0;
            center[i].y = 0;
            count_Group[i] = 0;
        }
        
        // distance
        for(int i=0;i<datas.size(); i++){
            for(int j=0;j<K_COUNT; j++){
                double tmp_distance = sqrt(pow(k[j].x - datas[i].x, 2) + pow(k[j].y - datas[i].y, 2));
                distance[j][i] = tmp_distance;
            }
        }
        
        //get center
        for(int i=0;i<datas.size(); i++){
            double min = distance[0][i];
            int min_j = 0;
            
            for(int j=1;j<K_COUNT; j++){
                if(min > distance[j][i]){
                    min = distance[j][i];
                    min_j = j;
                }
            }
            center[ min_j ].x += datas[i].x;
            center[ min_j ].y += datas[i].y;
            count_Group[min_j]++;
        }
        //change K
        int same_count = 0;
        for(int i=0;i<K_COUNT; i++){
            if(count_Group[i] != 0){
                if((center[i].x / count_Group[i]) == k[i].x
                   && (center[i].y / count_Group[i]  == k[i].y))
                same_count ++;
                k[i].x = center[i].x / count_Group[i];
                k[i].y = center[i].y / count_Group[i];
            }
            
            if(same_count == K_COUNT){
                loop=false;
            }
            cout<<fixed<<setprecision(2);
            cout<<"("<<k[i].x<<","<<k[i].y<<") ";
        }cout<<endl;
    }//end of loop
    
    
    for(int i=0;i<datas.size(); i++){
        double min = distance[0][i];
        int min_j = 0;
        for(int j=1;j<K_COUNT; j++){
            if(min > distance[j][i]){
                min = distance[j][i];
                min_j = j;
            }
        }
        cout<<min_j<<" ";
    }cout<<endl;
}
