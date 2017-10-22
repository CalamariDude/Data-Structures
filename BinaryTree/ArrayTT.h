//
// Created by Jad Zeineddine on 10/17/17.
//

#ifndef BINARYTREE_ARRAYTT_H
#define BINARYTREE_ARRAYTT_H


#include <iostream>

class ArrayTT{
public:
    int newlength;
    int length;
    int index;

    ArrayTT(int arr[], int lengther){
        this->length = lengther;
        this->newlength = length * 2 -1 ;
        int newarr[newlength];
        for(int i = 0; i < length;  i ++){
            newarr[i + (newlength-length)] = arr[i];
        }
        std::cout<<"newlength = "<< newlength<<std::endl;
        std::cout<<"length = " << length <<std::endl;
        index = newlength-1;
        computervector(newarr);
        printarr(newarr, newlength);
    }


    bool isOdd(int n){
        if (n % 2 == 1){
            return true;
        }
        else return false;
    }


    void computervector(int newarr[]){
        int length = this->length;
        index = newlength-length;
        int templength = length;
        std::cout<<"____________________"<<std::endl;
        int toinsertindex = index - lengthcompute(length) + 1;
        for(int count = index + 1; count >= 0, toinsertindex >= 0; count = count - length , templength = length,  toinsertindex = toinsertindex - lengthcompute(length)) {
            std::cout<<"+++++++++++++++++++++"<<std::endl;
            std::cout<<"count = "<< count<< std::endl;
            std::cout<<"toinsertindex = " << toinsertindex <<std::endl;
            std::cout<<"templength = " << templength <<std::endl;
            if(isOdd(length)) {
                for (int i = count, j = toinsertindex; i < count + templength - 1 ; i += 2, j++ ) {
                    newarr[j] = max(newarr[i], newarr[i+1]);
                }
                    newarr[toinsertindex + length - 1 ] = newarr[count + templength];
            }
             else{
                for (int i = count, j = toinsertindex; i < count + templength ; i += 2, j++ ) {
                    newarr[j] = max(newarr[i], newarr[i+1]);
                }
            }
        }
    }


    int lengthcompute(int &length){
        if(isOdd(length)){
            length = length/2 + 1;
        }
        else{
            length /= 2;
        }
        return length;
    }

    int max(int a, int b){
        return a > b ? a : b;
    }


    int printarr(int var[], int length){
        std::cout<<"__________________"<<std::endl;
        for(int i = 0; i < length; i++){
            if(i == 1)
                std::cout<<"|";
            else if(i  == 3)
                std::cout<<"|";
            else if(i == 7)
                std::cout<<"|";
            std::cout<< var[i] << " ";

        }

    }

};

#endif //BINARYTREE_ARRAYTT_H

