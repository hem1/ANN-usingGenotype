//
//  main.cpp
//  Artificial Neural Network
//
//  Created by Hemanta Pun on 10/06/2017.
//  Copyright © 2017 Hemanta Pun. All rights reserved.
//

#include <iostream>
#include <fstream>

#include "Genotype.hpp"
#include "ANN.hpp"


void train_xor_fm_file(Network &mynetwork);
void train_xor_rand_input(Network &mynetwork);
void test_xor(Network &mynetwork);

void train_xor_fm_file(Network &mynetwork){
    
    int ite = 100;
    while(--ite>0)
    {
        ifstream infile("xor_test.txt");
        string s;
        int pass = 0;
        
        while(getline(infile, s))
        {
            int index = 0;
            while(s[index] != ':') index++;
            
            if(s.substr(0,index).compare( "in" ) == 0)
            {
//                cout<<"xxxx-------------------------line "<< ++pass<<endl;

                string ss = s.substr(index+2);
                int i = 0;
                while(ss[i] != ' ') i++;
                double x = stod(ss.substr(0,i));
                double y = stod(ss.substr(i));
                
//                cout<<x<<" and "<<y<<endl;
                mynetwork.setInputForANN({x,y});
                mynetwork.forwardPropagation();
            }
            
            else if(s.substr(0,index).compare( "out" ) == 0)
            {
                double z = stod(s.substr(index+2));
//                cout<<"out is "<<z<<endl;
                mynetwork.setTargetForANN({z});
                mynetwork.backPropagation();
//                double o = mynetwork.getNWOutput()[0];
                
//                mynetwork.printOutput();
            }
        }
//        mynetwork.printOutput();
        infile.close();
    }
    mynetwork.printOutput();
    test_xor(mynetwork);
    
}


void train_xor_rand_input(Network &mynetwork){
    
    vector<double> inputs;
    
    int i = 0;
    cout<<"processing......\n";
    while(1)
    {
        
        int x = rand() % 2;
        int y = rand() % 2;
        int z = (x xor y);
        
        vector<double> inputs;
        inputs.push_back(double (x));
        inputs.push_back(double (y));
        
        mynetwork.setInputForANN(inputs);
        mynetwork.forwardPropagation();
        inputs.clear();
        
        
        mynetwork.setTargetForANN({(double)z});
        mynetwork.backPropagation();
        
        cout << "pass "<<i<<endl;
        cout<<"\nx y : "<<x<<" "<<y<<endl;
        cout<<"ACTUAL is   "<< z<<endl;
        double o = mynetwork.getOutputFromANN()[0];
        cout<<"from n/w : "<<o;
        cout<<"\n---------------------------------\n";
        
        if(i++ >100000 && abs(o-z) <0.05 )
        {
            break;
        }
    }
    cout<<"\nepoch is \n"<<i<<endl;
    test_xor(mynetwork);
    
}

void test_xor(Network &mynetwork){
    cout<<"enter two numbers ";
    int a, b;
    while(cin)
    {
        cin>> a;
        cin>>b;
        mynetwork.setInputForANN({(double)a,(double)b});
        mynetwork.forwardPropagation();
        cout<< " actual is "<<(a xor b)<<endl;
        cout<<"result is "<<mynetwork.getOutputFromANN()[0]<<endl;
        
        cout<<"enter two numbers ";
        
    }
}

int main(int argc, const char * argv[]) {
    Network mynetwork;
    Genotype g;
    //construct 2x3x1 n/w
    
    
    g.addGeneNode(g.createGeneNode(1, INPUT));
    g.addGeneNode(g.createGeneNode(2, INPUT));
    g.addGeneNode(g.createGeneNode(3, HIDDEN));
    g.addGeneNode(g.createGeneNode(4, HIDDEN));
    g.addGeneNode(g.createGeneNode(5, HIDDEN));
    g.addGeneNode(g.createGeneNode(6, OUTPUT));

    g.addConnection(g.createGeneConnection(1, 3, 0.8, ENABLED, 1));
    g.addConnection(g.createGeneConnection(1, 4, 0.4, ENABLED, 1));
    g.addConnection(g.createGeneConnection(1, 5, 0.3, ENABLED, 1));
    g.addConnection(g.createGeneConnection(2, 3, 0.2, ENABLED, 1));
    g.addConnection(g.createGeneConnection(2, 4, 0.9, ENABLED, 1));
    g.addConnection(g.createGeneConnection(2, 5, 0.5, ENABLED, 1));
    g.addConnection(g.createGeneConnection(3, 6, 0.3, ENABLED, 1));
    g.addConnection(g.createGeneConnection(4, 6, 0.5, ENABLED, 1));
    g.addConnection(g.createGeneConnection(5, 6, 0.9, ENABLED, 1));
    vector<double> in {1.0,1.0};
    vector<double> out {0.0};
    
    mynetwork.constructNetwork(g);
    mynetwork.setInputForANN(in);
    mynetwork.setTargetForANN(out);
    mynetwork.forwardPropagation();
    mynetwork.backPropagation();
    
//    mynetwork.printOutput();
//    train_xor_rand_input(mynetwork);
    train_xor_fm_file(mynetwork);
    
}

//int main(int argc, const char * argv[]) {
//    // insert code here...
//    
//    Genotype genom;
//    
//    
//    //solution at https://stevenmiller888.github.io/mind-how-to-build-a-neural-network/
//    
////    
////    genom.addGeneNode(genom.createGeneNode(1, INPUT));
////    genom.addGeneNode(genom.createGeneNode(2, INPUT));
////    genom.addGeneNode(genom.createGeneNode(3, HIDDEN));
////    genom.addGeneNode(genom.createGeneNode(4, HIDDEN));
////    genom.addGeneNode(genom.createGeneNode(5, HIDDEN));
////    genom.addGeneNode(genom.createGeneNode(6, OUTPUT));
////
////    genom.addConnection(genom.createGeneConnection(1, 3, 0.8, ENABLED, 1));
////    genom.addConnection(genom.createGeneConnection(1, 4, 0.4, ENABLED, 1));
////    genom.addConnection(genom.createGeneConnection(1, 5, 0.3, ENABLED, 1));
////    genom.addConnection(genom.createGeneConnection(2, 3, 0.2, ENABLED, 1));
////    genom.addConnection(genom.createGeneConnection(2, 4, 0.9, ENABLED, 1));
////    genom.addConnection(genom.createGeneConnection(2, 5, 0.5, ENABLED, 1));
////    genom.addConnection(genom.createGeneConnection(3, 6, 0.3, ENABLED, 1));
////    genom.addConnection(genom.createGeneConnection(4, 6, 0.5, ENABLED, 1));
////    genom.addConnection(genom.createGeneConnection(5, 6, 0.9, ENABLED, 1));
////    vector<double> in {1.0,1.0};
////    vector<double> out {0.0};
//    
//    
//    
//    genom.addGeneNode(genom.createGeneNode(1, INPUT));
//    genom.addGeneNode(genom.createGeneNode(2, INPUT));
//    genom.addGeneNode(genom.createGeneNode(3, OUTPUT));
//    genom.addGeneNode(genom.createGeneNode(4, HIDDEN));
//    genom.addGeneNode(genom.createGeneNode(5, HIDDEN));
//    genom.addGeneNode(genom.createGeneNode(6, HIDDEN));
//    
//    genom.addConnection(genom.createGeneConnection(1, 4, 0.8, ENABLED, 1));
//    genom.addConnection(genom.createGeneConnection(1, 5, 0.4, ENABLED, 1));
//    genom.addConnection(genom.createGeneConnection(1, 6, 0.3, ENABLED, 1));
//    genom.addConnection(genom.createGeneConnection(2, 4, 0.2, ENABLED, 1));
//    genom.addConnection(genom.createGeneConnection(2, 5, 0.9, ENABLED, 1));
//    genom.addConnection(genom.createGeneConnection(2, 6, 0.5, ENABLED, 1));
//    genom.addConnection(genom.createGeneConnection(4, 3, 0.3, ENABLED, 1));
//    genom.addConnection(genom.createGeneConnection(5, 3, 0.5, ENABLED, 1));
//    genom.addConnection(genom.createGeneConnection(6, 3, 0.9, ENABLED, 1));
//    vector<double> in {1.0,1.0};
//    vector<double> out {0.0};
//    
////    genom.addGeneNode(genom.createGeneNode(1, INPUT));
////    genom.addGeneNode(genom.createGeneNode(2, INPUT));
////    genom.addGeneNode(genom.createGeneNode(3, INPUT));
////    genom.addGeneNode(genom.createGeneNode(4, INPUT));
////    genom.addGeneNode(genom.createGeneNode(5, HIDDEN));
////    genom.addGeneNode(genom.createGeneNode(6, HIDDEN));
////    genom.addGeneNode(genom.createGeneNode(7, OUTPUT));
////    
////    genom.addConnection(genom.createGeneConnection(1, 5, 0.1, ENABLED, 1));
////    genom.addConnection(genom.createGeneConnection(1, 6, 0.1, ENABLED, 1));
////    genom.addConnection(genom.createGeneConnection(2, 5, -0.2, ENABLED, 1));
////    genom.addConnection(genom.createGeneConnection(2, 6, -0.1, ENABLED, 1));
////    genom.addConnection(genom.createGeneConnection(3, 5, 0.1, ENABLED, 1));
////    genom.addConnection(genom.createGeneConnection(3, 6, 0.3, ENABLED, 1));
////    genom.addConnection(genom.createGeneConnection(4, 7, 0.2, ENABLED, 1));
////    genom.addConnection(genom.createGeneConnection(5, 7, 0.2, ENABLED, 1));
////    genom.addConnection(genom.createGeneConnection(6, 7, 0.3, ENABLED, 1));
////    vector<double> in {1.0,0.1,0.9, 1.0};
////    vector<double> out {0.9};
//    
//    
////    genom.addGene(genom.createGeneNode(1, INPUT));
////    genom.addGene(genom.createGeneNode(2, INPUT));
////    genom.addGene(genom.createGeneNode(3, INPUT));
////    genom.addGene(genom.createGeneNode(4, HIDDEN));
////    genom.addGene(genom.createGeneNode(5, OUTPUT));
////
////    genom.addConnection(genom.createGeneConnection(1, 4, 0.7, ENABLED, ++Inn));
////    genom.addConnection(genom.createGeneConnection(2, 4, -0.5, ENABLED, ++Inn));
////    genom.addConnection(genom.createGeneConnection(2, 5, 0.5, DISABLED, ++Inn));
////    genom.addConnection(genom.createGeneConnection(3, 5, 0.2, ENABLED, ++Inn));
////    genom.addConnection(genom.createGeneConnection(4, 5, 0.4, ENABLED, ++Inn));
//    
//    
//    
//    Network network;
//    network.constructNetwork(genom);
//    network.setInput(in);
//    network.setTarget(out);
//    
//    network.forwardPropagation();
//    network.backPropagation();
//    network.backPropagation();
//    network.printOutput();
//    
//    //    genom.printGene();
//    return 0;
//}
