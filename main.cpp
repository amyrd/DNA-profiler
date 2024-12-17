//  Creative component: "find" function, used to locate a particular sequence in the loaded dna and 
//  makes it visible by using a marker which the user also inputs
//  must load DNA before it can be used
//  input "find" to run.

//  Project 1 - DNA Profiling
//  Lewis Dayrit
//  This program takes data of people's str counts and sequences of DNA and tries to find a match
//  
//

#include "ourvector.h"
#include <fstream>
#include <sstream> // for line parsing
#include <string>
using namespace std;

struct person
{
    string name;
    ourvector<int> strCounts;
};


// takes file, and parses comma seperate values into a struct and puts each struct into everyonesData vector
void load_db(string file, ourvector<person> &everyonesData, ourvector<ourvector<char> > &firstLine){
    string fileLine;
    string csv; 
    ifstream infile(file);
    everyonesData.clear();
    firstLine.clear();

    cout << "Loading database..." << endl;

    if (!infile.is_open()){
        cout << "Error: unable to open '" << file << "'" << endl;
    }
    else{
        // getting the first line and streaming it
        getline(infile, fileLine); 
        stringstream line(fileLine);
    
        ourvector<char> singleWord;

        // making a vector for each word and then putting each vector into a 2D vector that will consist of the first line
        while(!line.eof()){
            singleWord.clear();
            getline(line, csv, ',');
        
            for (int i = 0; i < csv.size(); i++){
                singleWord.push_back(csv[i]);
            }
            firstLine.push_back(singleWord);
        }

        // getting a line from the file, seperating the values and assigning it to person struct
        while(!infile.eof()){
            person personDataHolder;

            // first gets one line
            getline(infile, fileLine);
            stringstream line(fileLine);


            // getting one word from the line seperate by a comma
            getline(line, csv, ',');
            personDataHolder.name = csv;

            // continure to collect the words and store them in the vector of people
            while (!line.eof()){
                getline(line, csv, ',');
                personDataHolder.strCounts.push_back(stoi(csv));
            }
            everyonesData.push_back(personDataHolder);
        }
        infile.close();
    }
}

// takes all vectors that hold data and displays them if they have any data
void display(ourvector<person> everyonesData, ourvector<char> dna, ourvector<ourvector<char> > firstLine, ourvector<int> strCountStorage){
    bool tempBool = false;

    // checking if this vector is empty
    if (everyonesData.size() != 0){
        cout << "Database loaded: " << endl;

        for (int i = 0; i < everyonesData.size(); i++){
            cout << everyonesData[i].name << " ";
            for (int j = 0; j < everyonesData[i].strCounts.size(); j++){
                cout << everyonesData[i].strCounts[j] << " ";
            }
            cout << endl;
        }
    }
    // if it is empty
    else{
        cout << "No database loaded." << endl;
    }

    if(dna.size() != 0){
        cout << "DNA loaded: " << endl;
        for (int i = 0; i < dna.size(); i++){
            cout << dna[i];
        }
        cout << endl;
    }
    else{
        cout << "No DNA loaded." << endl << endl;
    }

    if (strCountStorage.size() != 0){
        cout << "DNA processed, STR counts: " << endl;
        for (int i = 1; i < firstLine.size(); i++){
            for (int j = 0; j < firstLine[i].size(); j++){
                cout << firstLine[i][j];
            }
            cout << ": " << strCountStorage[i - 1] << endl;
        }
    }
    else {
        cout << "No DNA has been processed." << endl;
    }  
}

// allows user to load a dna file and store each char into a vector, both being the parameters
void load_dna(string file, ourvector<char> &dna){
    dna.clear();
    string line;
    char base;
    ifstream infile(file); 
    getline(infile, line);
    cout << "Loading DNA..." << endl;
    // checking if file is properly opened
    if (!infile.is_open()){
        cout << "Error: unable to open " << "'" << file << "'" << endl;
    }
    else{ 
        for (int i = 0; i < line.size(); i++){
        dna.push_back(line[i]);
        }
    }
    infile.close();
}

// checks if the current dna sequence being compared does not match the str, takes in the vectors being comapred 
// and the loop variables in order to access the vectors being comapred
void notMatchedChecker(ourvector<ourvector<char> > firstLine, ourvector<char> dna, int &i, int &j, int &n){
    for (n = 0; n < firstLine[i].size(); n++){
        // + n is the loop variable for the str we are checking for, this allows
        // the current element we are checking in the dna file to check if the following bases are matches as well
        if(dna[j + n] != firstLine[i][n]){ 
        break;
        }
    }
}
// takes dna vector and the first line which contains each type of str that was loaded in the data base
// then finds the longest sequence of each str and counts how long
void process(ourvector<char> dna, ourvector<ourvector<char> > firstLine, ourvector<int> &strCountStorage){
    if (firstLine.size() == 0){
        cout << "No database loaded." << endl;
    }
    else if (dna.size() == 0){
        cout << "No DNA loaded." << endl;
    }
    else{
        cout << "Processing DNA..." << endl;
        int i,j,n = 0;

        // looping for each type of str
        for (i = 1; i < firstLine.size(); i++){ 
            int counter = 0;
            int maxSeq = 0;

            // subtracting the size of the str to find to prevent the loop going beyond the dna vector size
            for (j = 0; j <= (dna.size() - firstLine[i].size()); j){

                // looping through elements of the current str type
                notMatchedChecker(firstLine, dna, i, j, n);
                
                // increments counter if character sequence matched perfectly with the current str we are trying to match
                if (n == firstLine[i].size()){
                    counter++;
                    // since the current block of sequence was just counted for, we can skip the elements that were just checked
                    j = j + firstLine[i].size();
                }
                else {
                    if (counter >= maxSeq){
                        j += 1;
                        maxSeq = counter;
                        counter = 0;
                    }
                    else{
                        j++;
                    }
                }
            }
            strCountStorage.push_back(maxSeq);
        }

    }
    
}

// takes everyones str count data as well as the processed data in order to check if one of the people
// have mathcing str counts as the procesed data
// also takes dna vector to check if dna was processed
void search(ourvector<person> everyonesData, ourvector<int> strCountStorage, ourvector<char> dna){
    int i,j;
    string match;
    bool matched = false;
    if (everyonesData.size() == 0){
        cout << "No database loaded." << endl;
    }
    else if (dna.size() == 0){
        cout << "No DNA loaded." << endl;
    }
    else if (strCountStorage.size() == 0){
        cout << "No DNA processed." << endl;
    }
    else{
        cout << "Searching database..." << endl;
        // - 1 becasue there is a black spot at the end of the people vector
        for(i = 0; i < everyonesData.size() - 1; i++){
            // looping through each str count for each person
            for (j = 0; j < strCountStorage.size(); j++){
                if (everyonesData[i].strCounts[j] != strCountStorage[j]){
                    break;
                }
            }

            // j being the same size as the storage means it matched with every single str
            if (j == strCountStorage.size() ){
                match = everyonesData[i].name;
                matched = true;
            }
        }
        if (matched){
            cout << "Found in database!  DNA matches: " << match << endl;
        }
        else{
            cout << "Not found in database." << endl;
        }
    }
}

// creative component, takes dna vector and looks for user inputted sequence
void findSequence(ourvector<char> dna){
    string seqToFind;
    int location;
    string marker;
    bool found = false;
    int i,j;
    if (dna.size() == 0){
        cout <<  "No DNA loaded" << endl;
    }
    else{
        cout << "enter the DNA sequence you would like to find: ";
        cin >> seqToFind;
        cout << endl << "Choose a character to mark the beggining and end of the desired sequence: ";
        cin >> marker;
        // subtracting the size of the words we want to find to prevent the loop going beyond the dna vector size
        for (i = 0; i <= (dna.size() - seqToFind.size() - 1); i++){

            for (j = 0; j < seqToFind.size(); j++){

                // if the current base we are looking at does not match the desired sequence
                if (dna[i + j] != seqToFind[j]){ 
                   break;
               }

            }
            // save the location of where the sequence is found
            if (j == seqToFind.size()){
                location = i;
                cout << "sequence found and marked" << endl;
                found = true;
                break;
            }
        }

        if (found == false){
        cout << "sorry, the sequene you entered could not be found" << endl;
        }
        else{
            // displays the dna vector but adds the user's marker at both ends of the found sequence
            for (int n = 0; n < dna.size(); n++){
                if (n == i){
                    cout << marker << "   ";
                }
            // add size of seq to get element of the end of the sequence
            else if(n == i + seqToFind.size()){
                cout << "   " << marker;
            }
                cout << dna[n];
            }
        }
    }  
}

int main() {
    string userChoice = "-1";
    string file;
    ourvector<person> everyonesData; 
    ourvector<char> dna;
    ourvector<int> strCountStorage; // holds processed data
    ourvector<ourvector<char> > firstLine; // holds the first line of large and small txt files

    cout << "Welcome to the DNA Profiling Application." << endl;
    while (userChoice != "#"){
        cout << "Enter command or # to exit: ";
        cin >> userChoice;
        
        if (userChoice == "load_db"){
            cin >> file;
            load_db(file, everyonesData, firstLine);
        }
        else if (userChoice == "display"){
            display(everyonesData, dna, firstLine, strCountStorage);
        }
        else if (userChoice == "load_dna"){
            cin >> file;
            load_dna(file, dna);
        }
        else if (userChoice == "process"){
            process(dna, firstLine, strCountStorage);
        }
        else if (userChoice == "search"){
            search(everyonesData, strCountStorage, dna);
        }
        else if (userChoice ==  "find"){
            findSequence(dna);
        }
    }
    return 0;
}