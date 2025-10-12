
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <random>
#include <iomanip>
#include <limits>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
using namespace std;

//PTR1 WILL BE USED TO PASS PLAYER 2'S GRID INTO THE FUNCTION
//PTR2 WILL BE USED TO PASS PLAYER 1'S GRID INTO THE FUNCTION
void grids(char (*ptr1)[4],char (*ptr2)[4],int rows);
void gameplay(char (*ptr1)[4],char (*ptr2)[4],int rows, int mode, string name1, string name2);
bool isAHit(char (*ptr)[4],int rows,int selection);
void storeProgress(char (*ptr)[4],int rows,string fileName);
void displayProgress(string fileName);
int computerGuesses(char (*ptr)[4], int rows);
void showResult(string name1, string name2, int shipsDestroyed1, int shipsDestroyed2);
void displayFinalGrids(char (*ptr)[4],int rows,string fileName,string playerName);

int main(){
    srand(time(0));
    char compGrid[4][4], userGrid[4][4];
    char (*cPtr)[4] = compGrid;//WILL BE USED TO HOST PLAYER 2'S GRID, PLAYER 1 WILL WORK TO DESTROY BATTLESHIPS IN THIS GRID
    char (*uPtr)[4] = userGrid;//WILL BE USED TO HOST PLAYER 1'S GRID, PLAYER 2 WILL WORK TO DESTROY BATTLESHIPS IN THIS GRID
    char response, gridResponse;
    int modeOption;
    string uName1, uName2;
    
    do{
        computerGuesses(nullptr, 0);
        cout<<"\nWELCOME TO NAVAL CLASH\n";
        grids(cPtr,uPtr,4);
        
        do{
            cout<<"MODES:\n";
            cout<<"1. PLAYER VS PLAYER\n";
            cout<<"2. PLAYER VS COMPUTER\n";
            cout<<"PICK THE MODE WOULD YOU LIKE TO PLAY: ";
            cin>>modeOption;
            if(cin.fail() || (modeOption != 1 && modeOption != 2)){
                cout<<"Wrong input. Try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else{
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }while(true);

        if(modeOption == 1){
            cout<<"Enter player 1's name: ";
            getline(cin, uName1);
            cout<<"Enter player 2's name: ";
            getline(cin, uName2);
        }
        else if(modeOption == 2){
            cout<<"Enter player 1's name: ";
            getline(cin, uName1);
            uName2 = "COMPUTER";
        }
        gameplay(cPtr,uPtr,4, modeOption, uName1, uName2);

        do{
            cout<<"Review final grids?(Y/N):";
            cin>>gridResponse;
            if(cin.fail() || (toupper(gridResponse) != 'Y' && toupper(gridResponse) != 'N')){
                cout<<"Wrong input. Try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else{
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }while(true);

        if(toupper(gridResponse) == 'Y'){
            cout<<"FINAL GRIDS:\n";
            displayFinalGrids(uPtr,4,"player1_final_grid.txt",uName1);
            displayFinalGrids(cPtr,4,"player2_final_grid.txt",uName2);
            
        }
        do{
            cout<<"Play again?(Y/N): ";
            cin>>response;
            if(cin.fail() || (toupper(response) != 'Y' && toupper(response) != 'N')){
                cout<<"Wrong input. Try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else{
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }while(true);
    }while(toupper(response) == 'Y');

    cout<<"\nThank you for playing!\n";

    return 0;
}


void grids(char (*ptr1)[4],char (*ptr2)[4],int rows){
    
    int randIndex;

    //CREATE GRID 1
    for(int i=0;i<4;i++){
        randIndex = rand() % 4;
        for(int k=0;k<4;k++){
            //randIndex = rand() % 4;
            if(k == randIndex){
                ptr1[i][k] = 'S';
            }
            else{
                ptr1[i][k] = '~';
            }
        }
    }
    //CREATE GRID 2
    for(int i=0;i<4;i++){
        randIndex = rand() % 4;
        for(int k=0;k<4;k++){
            if(k == randIndex){
                ptr2[i][k] = 'S';
            }
            else{
                ptr2[i][k] = '~';
            }
        }
    }
}
bool isAHit(char (*ptr)[4],int rows,int selection){
    
    int theRow = (selection - 1) / 4;
    int theCol = (selection - 1) % 4;

    return (ptr[theRow][theCol] == 'S');
}
void gameplay(char (*ptr1)[4],char (*ptr2)[4],int rows, int mode, string name1, string name2){
    
    int userOption, gridRow, gridCol;
    bool userTurn = true;
    int result;
    int chances1 = 5,chances2 = 5;
    int destroyed1 = 0, destroyed2 = 0;
    //string uName, uName2;

    switch (mode){
        case 1:
            
            while(chances1 > 0 || chances2 > 0){
                if(userTurn){
                    cout<<endl<<name1<<"'s TURN: \n";
                    storeProgress(ptr1,4,"player2_grid.txt");
                    displayProgress("player2_grid.txt");
                    
                    do{
                        cout<<"SELECT OPTION: "; 
                        cin>>userOption;
                        if(cin.fail() || (userOption < 1 || userOption >16)){
                            cout<<"Wrong input. Try again.\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        else{
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            gridRow = (userOption - 1) / 4;
                            gridCol = (userOption - 1) % 4;
                            if(ptr1[gridRow][gridCol] == 'X' || ptr1[gridRow][gridCol] == 'H'){
                                cout<<"Block already selected. Try again.\n";
                            }
                            else{
                                break;
                            }
                            
                        }
                    }while(true);
                    gridRow = (userOption - 1) / 4;
                    gridCol = (userOption - 1) % 4;
                    result = isAHit(ptr1,rows,userOption);

                    if(result){
                        cout<<"HIT!!! SHIP DESTROYED!!!\n";
                        ptr1[gridRow][gridCol] = 'H';
                        destroyed1++;
                    }
                    else{
                        cout<<"MISS!!!\n";
                        ptr1[gridRow][gridCol] = 'X';
                    }
                    storeProgress(ptr1,4,"player2_grid.txt");
                    cout<<chances1 - 1<<" chance(s) remaining"<<endl;
                    chances1--;
                }
                else{
                    cout<<endl<<name2<<"'s TURN: \n";
                    storeProgress(ptr2,4,"player1_grid.txt");
                    displayProgress("player1_grid.txt");
                    
                    do{
                        cout<<"SELECT OPTION: "; 
                        cin>>userOption;
                        if(cin.fail() || (userOption < 1 || userOption >16)){
                            cout<<"Wrong input. Try again.\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        else{
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            gridRow = (userOption - 1) / 4;
                            gridCol = (userOption - 1) % 4;
                            if(ptr2[gridRow][gridCol] == 'X' || ptr2[gridRow][gridCol] == 'H'){
                                cout<<"Block already selected. Try again.\n";
                            }
                            else{
                                break;
                            }
                            
                        }
                    }while(true);
                    
                    result = isAHit(ptr2,rows,userOption);

                    if(result){
                        cout<<"HIT!!! SHIP DESTROYED!!!\n";
                        ptr2[gridRow][gridCol] = 'H';
                        destroyed2++;
                    }
                    else{
                        cout<<"MISS!!!\n";
                        ptr2[gridRow][gridCol] = 'X';
                    }
                    storeProgress(ptr2,4,"player1_grid.txt");
                    cout<<chances2 - 1<<" chance(s) remaining"<<endl;
                    chances2--;
                }
                if(destroyed1 == 4 || destroyed2 == 4){
                    break;
                }
                
                userTurn = !userTurn; //FLIPS THROUGH THE PLAYER TURNS, PLAYER 1 IS TRUE AND PLAYER 2 IS FALSE

            }
            showResult(name1,name2, destroyed1, destroyed2);
            break;
        case 2:
            while(chances1 > 0 || chances2 > 0){
                if(userTurn){
                    cout<<endl<<name1<<"'s TURN: \n";
                    storeProgress(ptr1,4,"player2_grid.txt");
                    displayProgress("player2_grid.txt");
                    
                    do{
                        cout<<"SELECT OPTION: "; 
                        cin>>userOption;
                        if(cin.fail() || (userOption < 1 || userOption >16)){
                            cout<<"Wrong input. Try again.\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        else{
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            gridRow = (userOption - 1) / 4;
                            gridCol = (userOption - 1) % 4;
                            if(ptr1[gridRow][gridCol] == 'X' || ptr1[gridRow][gridCol] == 'H'){
                                cout<<"Block already selected. Try again.\n";
                            }
                            else{
                                break;
                            }
                            
                        }
                    }while(true);
                    gridRow = (userOption - 1) / 4;
                    gridCol = (userOption - 1) % 4;
                    result = isAHit(ptr1,rows,userOption);

                    if(result){
                        cout<<"HIT!!! SHIP DESTROYED!!!\n";
                        ptr1[gridRow][gridCol] = 'H';
                        destroyed1++;
                    }
                    else{
                        cout<<"MISS!!!\n";
                        ptr1[gridRow][gridCol] = 'X';
                    }
                    storeProgress(ptr1,4,"player2_grid.txt");
                    cout<<chances1 - 1<<" chance(s) remaining"<<endl;
                    chances1--;
                }
                else{
                    cout<<endl<<name2<<"'s TURN\n";
                    storeProgress(ptr2,4,"player1_grid.txt");
                    displayProgress("player1_grid.txt");
                    
                    cout<<"SELECT OPTION: "; 

                    for(int i=0;i<3;++i){
                        this_thread::sleep_for(100ms);
                    }
                    this_thread::sleep_for(100ms);
                    userOption = computerGuesses(ptr2, 4);
                    cout<<userOption<<endl;
                    
                    gridRow = (userOption - 1) / 4;
                    gridCol = (userOption - 1) % 4;

                    result = isAHit(ptr2,rows,userOption);
                    if(result){
                        cout<<"HIT!!! SHIP DESTROYED!!!\n";
                        ptr2[gridRow][gridCol] = 'H';
                        destroyed2++;
                    }
                    else{
                        cout<<"MISS!!!\n";
                        ptr2[gridRow][gridCol] = 'X';
                    }
                    storeProgress(ptr2,4,"player1_grid.txt");
                    cout<<chances2 - 1<<" chance(s) remaining"<<endl;
                    chances2--;
                }
                if(destroyed1 == 4 || destroyed2 == 4){
                    break;
                }
                
                userTurn = !userTurn; //FLIPS THROUGH THE PLAYER TURNS, PLAYER 1 IS TRUE AND PLAYER 2 IS FALSE

            }
            showResult(name1,name2, destroyed1, destroyed2);
            break;
        default:
            break;
    }
    
}
//SAVING THE MOST RECENT GRIDS USING FILE READING
void storeProgress(char (*ptr)[4],int rows,string fileName){
    //PLAYER 1 GETS TO SEE PLAYER 2'S GRID
    //PLAYER 2 GETS TO SEE PLAYER 1'S GRID
    ofstream outFile(fileName);

    int count = 1; // FOR NUMBERING THE BLOCKS (1-16)
    if(outFile.is_open()){
        for(int i = 0;i<rows;i++){
            outFile<<"+";
            for(int k=0;k<4;k++){
                outFile<<"----+";
            }
            outFile<<"\n|";
            for(int k=0;k<4;k++){
                //state = ptr[i][k];
                if(ptr[i][k] == 'H'){
                    outFile<<setw(3)<<"H"<<" |";
                }
                else if(ptr[i][k] == 'X'){
                    outFile<<setw(3)<<"X"<<" |";
                }
                else{
                    outFile<<setw(3)<<count<<" |";
                    
                }
                count++;
                
            }
            outFile<<"\n";
        }
        outFile<<"+";
        for(int j=0;j<4;j++){
            outFile<<"----+";
        }
        outFile<<"\n";
        outFile.close();
    }
    else{
        cout<<"Error opening file!\n";
    }
}
void displayProgress(string fileName){
    ifstream inFile(fileName);

    string line;
    if(inFile.is_open()){
        while(getline(inFile, line)){
            cout<<line<<endl;
        }
        inFile.close();
    }
    else{
        cout<<"Error opening file!\n";
    }
}
int computerGuesses(char (*ptr)[4], int rows){
    static vector<int> usedValues;
    //RESET VECTOR FOR NEW GAME
    if(ptr == nullptr){
        usedValues.clear();
        return 0;
    }
    int guess;
    bool alreadyExists;

    do{
        guess = (rand() % 16) + 1;
        alreadyExists = false;
        for(int i=0;i<usedValues.size();i++){
            if(usedValues[i] == guess){
                alreadyExists = true;
                break;
            }
        }
    }while(alreadyExists);

    usedValues.push_back(guess);
    
    return guess;
}
void showResult(string name1, string name2, int shipsDestroyed1, int shipsDestroyed2){
    cout<<"\n=============SCORES=============\n";
    cout<<setw(15)<<left<<"PLAYER"<<setw(20)<<"SHIPS DESTROYED"<<endl;
    cout<<"--------------------------------\n";
    cout<<setw(15)<<left<<name1<<setw(20)<<shipsDestroyed1<<endl;
    cout<<setw(15)<<left<<name2<<setw(20)<<shipsDestroyed2<<endl;
            
    if(shipsDestroyed1 > shipsDestroyed2){
        cout<<name1<<" wins!!\n";    
    }
    else if(shipsDestroyed1 < shipsDestroyed2){
        cout<<name2<<" wins!!\n";
    }
    else{
        cout<<"Draw!!\n";
    } 
}
void displayFinalGrids(char (*ptr)[4],int rows,string fileName,string playerName){
    ofstream theOutFile(fileName);

    if(theOutFile.is_open()){
        for(int i = 0;i<rows;i++){
            theOutFile<<"+";
            for(int k=0;k<4;k++){
                theOutFile<<"----+";
            }
            theOutFile<<"\n|";
            for(int k=0;k<4;k++){
                //state = ptr[i][k];
                if(ptr[i][k] == 'H'){
                    theOutFile<<setw(3)<<"H"<<" |";
                }
                else if(ptr[i][k] == 'X'){
                    theOutFile<<setw(3)<<"X"<<" |";
                }
                else if(ptr[i][k] == 'S'){
                    theOutFile<<setw(3)<<"S"<<" |";
                    
                }
                else{
                    theOutFile<<setw(3)<<"~"<<" |";
                }
                
            }
            theOutFile<<"\n";
        }
        theOutFile<<"+";
        for(int j=0;j<4;j++){
            theOutFile<<"----+";
        }
        theOutFile<<"\n";
        theOutFile.close();
    }
    else{
        cout<<"Error opening file!\n";
    }

    cout<<endl<<playerName<<"'s final grid:\n";
    displayProgress(fileName);
}


