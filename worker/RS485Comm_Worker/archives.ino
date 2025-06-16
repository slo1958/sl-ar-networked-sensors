/******************************************************************************
 
void hexacout(char v){
    int c; 
    c = v / 16;
    std::cout<< (c < 10 ? c + '0' : c - 10 + 'A');
    c = v % 16;
    std::cout<< (c < 10 ? c + '0' : c - 10 + 'A');
}

void hexacharcout(char v){
    char b[3];
    char c; 
    c = v / 16;
    b[0] =  (c < 10 ? c + '0' : c - 10 + 'A');
    c = v % 16;
    b[1] =  (c < 10 ? c + '0' : c - 10 + 'A');
    b[2] = 0;
    std::cout<< b;
}


void hexabufcout(const char v[], int len){
    for (int i = 0; i<len; i++) hexacharcout(v[i]);    
}





                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.



#include <iostream>
int calcxor(char b[], int len) {
    int r = 0;
    for (int i = 0; i<len;i++) { r = r ^ b[i];}
    return r & 0xFF;
    
}

int hextoint(char c){
    return   (('0' <= c) && (c <= '9') ? c-'0' : (('A' <= c) && (c <= 'F') ? c - 'A' + 10 : -1));
}

int calcxor2(char b[], int len) {
    int r = 0;
    int k = 0;
    int i;
    for (i = 0; ((i<len) && (b[i]!=':'));i++) { r = r ^ b[i];}
    if (b[i] != ':') return r & 0xFF;
    if (i+2 > len) return r & 0xFF;
    
    i++;
    k = hextoint(b[i]) * 16 + hextoint(b[i+1]);
    
//    std::cout<< (r & 0xFF);
//    std::cout<<'/';
//    std::cout<<k;
//    std::cout<<'/';  
    return (r & 0xFF) - k;
}

void hexacharcout(char v){
    char b[3];
    char c; 
    c = v / 16;
    b[0] =  (c < 10 ? c + '0' : c - 10 + 'A');
    c = v % 16;
    b[1] =  (c < 10 ? c + '0' : c - 10 + 'A');
    b[2] = 0;
    std::cout<< b;
}

void hexabufcout(const char v[], int len){
    for (int i = 0; i<len; i++) hexacharcout(v[i]);    
}

int main()
{
    char k[20] = "[Hello World";
    
    k[16] = ':';
    k[17] = '7';
    k[18] = 'B';
    k[19] = ']';
    
    
    std::cout<<"start:";
    hexacharcout(calcxor2(k, 20));

    return 0;
}

*******************************************************************************/
