#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <filesystem>
#define N 10
using namespace std;

int main()
{
    srand(time(NULL));
    
	int grid[N][N] = {};
    int playerPos[N][N] = {};
    int enemyPos[N][N] = {};
    string typeRoom = "5;5";
    int x = 1, y = 1;
    int xDoor = 0, yDoor = 0;
    int xRoom = 5, yRoom = 5;
    int xEnemy = 5, yEnemy = 3;
    int rndType = 0;
    int vita = 100;
    int vitaEnemy = 0;
    int damage, saveVita, damageME = 0;
    char input = ' ';
    bool firstRead = false;
    string roomCont = "";
    string saveCont = "";
    string line = "";
    string msg = "Input atteso: ";
    string msgAtt = "";
    
    bool sconfitti = true;
    
    
    char room[N][N] = {};
    
    
    grid[N/2][N/2] = (rand() % 8) + 1;
    while(vita > 0){
        
        system("cls");
        line = "";
        roomCont = "";
        saveCont = "";
        ifstream read("rooms/room" + typeRoom + ".txt");
        
        if(!read){
            
            read.open("rooms/type/type" + to_string(rndType) + ".txt");
            for(int i = 0; i < N; i++){
                getline(read, line);
                saveCont += line;

            }
            grid[yRoom][xRoom] = (rand() % 8) + 1;
            
            saveCont[yDoor*N + xDoor] = 'U';
            ofstream write("rooms/room" + typeRoom + ".txt");
            write << saveCont;
            write.close();
            read.open("rooms/room" + typeRoom + ".txt");
            vitaEnemy = rand() % 50;
            do{
                yEnemy = rand() % N;
                xEnemy = rand() % N;
            }while(room[yEnemy][xEnemy] == '#');
            
        }
        
        
        
        roomCont = "";
        for(int i = 0; i < N; i++){
            getline(read, line);
            roomCont += line;

        }

        read.close();
        
        
        firstRead = true;
        //DEBUG
        /*cout << "ROOM: " << typeRoom << " | RND: " << "rooms/type/type" <<  to_string(rndType) << ".txt"  <<endl << endl;
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){

                    cout << grid[i][j];
                    
            }
            cout << endl;
        }*/
            
        cout << endl;    
        int k = 0;
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                
                if(i == yEnemy && j == xEnemy && vitaEnemy > 0){
                    room[i][j] = 'E';
                }else if(i == y && j == x){
                    room[i][j] = '@';
                }else{
                    room[i][j] = roomCont[k];
                    
                }

                if(typeRoom != "5;5") room[yDoor][xDoor] = 'U';
                switch(grid[yRoom][xRoom]){
                    case 1:
                        if(i == 0 && j == N/2) room[0][N/2] = 'U';
                        break;
                    case 2:
                        if(i == N/2 && j == N-1) room[N/2][N-1] = 'U';                    
                        break;
                    case 3:
                        if(i == N-1 && j == N/2) room[N-1][N/2] = 'U';
                        break;
                    case 4:
                        if(i == N/2 && j == 0) room[N/2][0] = 'U';
                        break;
                    case 5:
                        if(i == 0 && j == N/2) room[0][N/2] = 'U';
                        if(i == N/2 && j == N-1) room[N/2][N-1] = 'U';  
                        break;
                    case 6:
                        if(i == N/2 && j == N-1) room[N/2][N-1] = 'U';
                        if(i == N-1 && j == N/2) room[N-1][N/2] = 'U';  
                        break;
                    case 7:
                        if(i == N-1 && j == N/2) room[N-1][N/2] = 'U';
                        if(i == N/2 && j == 0) room[N/2][0] = 'U';
                        break;
                    case 8:
                        if(i == 0 && j == N/2) room[0][N/2] = 'U';
                        if(i == N/2 && j == 0) room[N/2][0] = 'U';
                        break;
                        
                }
                
                
                k++;
                
                cout << room[i][j];

            }
            
            cout << endl;
        }
        
        cout << endl;
        cout << msg << endl;
        cout << msgAtt;
        cin >> input;
        
        switch(input){
            case 'w':
                if(y > 0 && room[y-1][x] != '#') y--;
                break;
            case 's':
                if(y < N-1 && room[y+1][x] != '#') y++;
                break;
            case 'd':
                if(x < N-1 && room[y][x+1] != '#') x++;
                break;
            case 'a':
                if(x > 0 && room[y][x-1] != '#') x--;
                break;
            case 'x':
                
                if(room[y][x] == 'E'){ 
                    damage = rand() % 9;
                    damageME = rand() % 7;
                    vitaEnemy -= damage;
                    vita -= damageME;
                    msgAtt = "hai tolto " + to_string(damage) + " su " + to_string(saveVita) + "\nTi ha tolto " + to_string(damageME) + "di vita (" + to_string(vita) + "):";

                }else{
                    msgAtt = "Non c'e' nessuno da attaccare!";
                }
                
                
        }
        
        if(room[y][x] == 'U' && sconfitti){
            
            if(y == 0 && x == N/2){
                yRoom--;
                y = N-2;
                xDoor = N/2;
                yDoor = y+1;
            }else if(y == N/2 && x == N-1){
                xRoom++;
                x = 1;
                yDoor = N/2;
                xDoor = x-1;
            }else if(y == N-1 && x == N/2){
                yRoom++;
                y = 1;
                xDoor = N/2;
                yDoor = y-1;
            }else if(y == N/2 && x == 0){
                xRoom--;
                x = N-2;
                yDoor = N/2;
                xDoor = x+1;
            }
            
            
            
            rndType = rand() % 30;
            typeRoom = to_string(yRoom) + ";" + to_string(xRoom);
                

        }
        
        if(room[y][x] == 'E'){ 
            msg = "Premi X per attaccare...\n ";
            saveVita = vitaEnemy;

        }else{
            msg = "Input atteso: ";
        }
  
        
    }
    
    cout << "GAME OVER!";
    
    
    
	return 0;
}