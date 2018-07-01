#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

int main(int argc, char *argv[]){
    json j, k;
    int i, jsize, ksize, start;
    double offset, tmpD, invTempo;
    ifstream ifile0,ifile1;
    ofstream ofile;
    string fileName;

    if(argc<5||argc>6) exit(1);

    if(*argv[1]=='m'){
        //Merge

        // Open the files passed in as arguments
        ifile0.open(argv[2]);
        if(!ifile0.is_open()){
            cout<<"Illegal input file.\n";
            exit(1);
        }

        ifile1.open(argv[3]);
        if(!ifile1.is_open()){
            cout<<"Illegal input file.\n";
            exit(1);
        }

        ofile.open(argv[5]);
        if(!ofile.is_open()){
            cout<<"Illegal output file.\n";
            exit(1);
        }

        // Load the json data from the input files into j and k
        ifile0>>j;
        ifile1>>k;

        cout<<"Number of notes in k: "<<k["_notes"].size()<<endl;

        start=atoi(argv[4]);

        offset=((double)start*175)/60;
        cout<<"Start: "<<start<<". Offset (in beats): "<<offset<<"."<<endl;

        // Iterate through k's notes and add them to j
        jsize=j["_notes"].size();
        ksize=k["_notes"].size();
        for (i=0;i<ksize;i++){
            j["_notes"][jsize+i]=k["_notes"][i];
            tmpD=(double)j["_notes"][jsize+i]["_time"]+offset;
            cout<<"New time: "<<tmpD<<endl;
            j["_notes"][jsize+i]["_time"]=tmpD;
            cout<<"Actual set time: "<<j["_notes"][jsize+i]["_time"]<<endl;
        }

        //save the new j
        //cout<<setw(2)<<k["_notes"];
        ofile<<j;
    }else if(*argv[1]=='s'){
        //Set

        // Open the files passed in as arguments
        ifile0.open(argv[2]);
        if(!ifile0.is_open()){
            cout<<"Illegal input file.\n";
            exit(1);
        }

        ofile.open(argv[3]);
        if(!ofile.is_open()){
            cout<<"Illegal output file.\n";
            exit(1);
        }

        fileName=argv[4];

        // Load the json data from the input files into j
        ifile0>>j;

        j["difficultyLevels"][0]["offset"]=0;
        j["difficultyLevels"][0]["oldOffset"]=0;
        j["difficultyLevels"][0]["audioPath"]=fileName;
        ofile<<j;
    }else if(*argv[1]=='a'){
        //Activate

        // Open the files passed in as arguments
        ifile0.open(argv[2]);
        if(!ifile0.is_open()){
            cout<<"Illegal input file.\n";
            exit(1);
        }

        start=atoi(argv[3]);

        ofile.open(argv[4]);
        if(!ofile.is_open()){
            cout<<"Illegal output file.\n";
            exit(1);
        }

        fileName=argv[5];

        //cout<<"Activating segment starting at timestamp: "<<start<<" seconds. "<<fileName<<endl;

        // Load the json data from the input files into j
        ifile0>>j;

        invTempo=60.f/175.f;

        cout<<"invTempo: "<<invTempo<<". fmod: "<<fmod((double)start,invTempo)<<".\n";

        j["difficultyLevels"][0]["offset"]=fmod((double)start,invTempo)*-1000;
        j["difficultyLevels"][0]["oldOffset"]=fmod((double)start,invTempo)*-1000;
        //cout<<"Offset: "<<j["difficultyLevels"][0]["offset"]<<endl;
        j["difficultyLevels"][0]["audioPath"]=fileName;
        //cout<<"Offset: "<<j["difficultyLevels"][0]["audioPath"]<<endl;
        //cout<<j.dump(2)<<endl;
        ofile<<j;
    }
    
    return 0;
}
