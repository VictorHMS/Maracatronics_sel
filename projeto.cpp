#include<bits/stdc++.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<termios.h>
#include<thread>
#include<chrono>
#define Port 8889
#define all(x) x.begin(),x.end()
using namespace std;

int junta[40] = {0};
int mov = 5;
char sdcat[10];
int pausa = 0;
int quit = 0;

void itos(int val){
    strcpy(sdcat,"0");
    if(!val)return;
    string a = "";
    while(val){
        a += (val%10) + '0';
        val /= 10;
    }
    reverse(all(a));
    int pos;
    for(pos = 0; pos < a.size(); pos++){
        sdcat[pos] = a[pos];
    }
    sdcat[pos]=0;
}

int getch(){
    struct termios oldt, newt;
    int ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}

int decidir(int val){
    if((360-val) < val)return 5;
    return -5;
}

void reset(){
    for(int i=0; i<6; i++){
        mov = decidir(junta[i]);
        while(junta[i]){
            junta[i] = (junta[i]+mov+360)%360;
            this_thread::sleep_for(chrono::milliseconds(10));
        }
    }
    mov = 5;
}

void passo1(){
    while(junta[1] < 80 | junta[2] < 120){
        if(junta[1] < 80) junta[1] = (junta[1]+2+360)%360;
        if(junta[2] < 120) junta[2] = (junta[2]+3+360)%360;
        this_thread::sleep_for(chrono::milliseconds(5));
    }
    this_thread::sleep_for(chrono::milliseconds(300));
    while(junta[1] > 0 | junta[2] > 0){
        if(junta[1] > 0) junta[1] = (junta[1]-2+360)%360;
        if(junta[2] > 0) junta[2] = (junta[2]-3+360)%360;
        this_thread::sleep_for(chrono::milliseconds(5));
    }
    //10 300 10
}

void passo2(){
    while(junta[2] != 320){
        junta[2] = (junta[2]-mov+360)%360;
        this_thread::sleep_for(chrono::milliseconds(10));
    }
    while(junta[2] != 125){
        junta[2] = (junta[2]+mov+360)%360;
        this_thread::sleep_for(chrono::milliseconds(7));   
    }
    this_thread::sleep_for(chrono::milliseconds(700));
    while(junta[2] != 0){
        junta[2] = (junta[2]-mov+360)%360;
        this_thread::sleep_for(chrono::milliseconds(15));
    }
}

void passo3(){
    while(junta[2] != 60){
        junta[2] = (junta[2]+mov+360)%360;
        junta[4] = (junta[4]+mov+360)%360;
        junta[5] = (junta[5]+mov+360)%360;
        this_thread::sleep_for(chrono::milliseconds(15));
    }
    for(int i=0; i<1*72; i++){
        junta[4] = (junta[4]+mov+360)%360;
        junta[3] = (junta[3]+mov+360)%360;
        this_thread::sleep_for(chrono::milliseconds(15));
    }
    while(junta[2] != 0){
        junta[2] = (junta[2]-mov+360)%360;
        junta[4] = (junta[4]+mov+360)%360;
        junta[3] = (junta[3]+mov+360)%360;
        this_thread::sleep_for(chrono::milliseconds(15));
    }
    while(junta[4] != 0 || junta[3] != 0){
        if(junta[4] != 0)junta[4] = (junta[4]+mov+360)%360;
        if(junta[3] != 0)junta[3] = (junta[3]+mov+360)%360;
        this_thread::sleep_for(chrono::milliseconds(15));
    }
}

void headb(){
    for(int i=0; i<3; i++){
        while(junta[2] != 320){
            junta[2] = (junta[2]-mov+360)%360;
            this_thread::sleep_for(chrono::milliseconds(10));
        }
        while(junta[2] != 125){
            junta[2] = (junta[2]+mov+360)%360;
            this_thread::sleep_for(chrono::milliseconds(5));   
        }
        while(junta[2] != 0){
            junta[2] = (junta[2]-mov+360)%360;
            this_thread::sleep_for(chrono::milliseconds(10));
        }
    }
}

void parar(){
    char c = getch();
    pausa = 1;
}

void girar(){
    while(!pausa){
        junta[0] = (junta[0]+mov+360)%360;
        this_thread::sleep_for(chrono::milliseconds(50));
    }
}

void dance(){
    reset();
    thread para(parar);
    thread gira(girar);
    para.detach();
    gira.detach();
    while(!pausa){
        passo1();
        if(pausa)break;
        this_thread::sleep_for(chrono::milliseconds(100));
        if(pausa)break;
        passo1();
        this_thread::sleep_for(chrono::milliseconds(500));
        if(pausa)break;
        passo2();
        passo3();
    }
    pausa = 0;
    reset();
}

void testar(){
    while(1){
        char c = getch();
        if(c == 'q') junta[0] = (junta[0]+mov+360)%360;//junta 1
        if(c == 'a') junta[0] = (junta[0]-mov+360)%360;//junta 1
        if(c == 'w') junta[1] = (junta[1]+mov+360)%360;//junta 2
        if(c == 's') junta[1] = (junta[1]-mov+360)%360;//junta 2
        if(c == 'e') junta[2] = (junta[2]+mov+360)%360;//junta 3
        if(c == 'd') junta[2] = (junta[2]-mov+360)%360;//junta 3
        if(c == 'r') junta[3] = (junta[3]+mov+360)%360;//junta 4
        if(c == 'f') junta[3] = (junta[3]-mov+360)%360;//junta 4
        if(c == 't') junta[4] = (junta[4]+mov+360)%360;//junta 5
        if(c == 'g') junta[4] = (junta[4]-mov+360)%360;//junta 5
        if(c == 'y') junta[5] = (junta[5]+mov+360)%360;//junta 6
        if(c == 'h') junta[5] = (junta[5]-mov+360)%360;//junta 6
        if(c == 'l') reset();
        if(c == 'z') passo1();
        if(c == 'x') passo2();
        if(c == 'c') passo3();
        if(c == 'v') dance();
        if(c == 'm') quit = 1;
        this_thread::sleep_for(chrono::milliseconds(1));
    }
}

int main(){
    thread aqui(testar);
    aqui.detach();
    int sockf, socks, valread;
    int opt = 1;
    struct sockaddr_in endereco;
    int tamend = sizeof(endereco);
    char buffer[1024] = {0}, msg[1024];

    sockf = socket(AF_INET, SOCK_STREAM, 0);
    if(!sockf){
        cout << "O socket falhou\n";
        return 0;
    }


    if (setsockopt(sockf, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){ 
        cout << "Falha no setsockopt\n";
        return 0;
    }
    endereco.sin_family = AF_INET;
    endereco.sin_addr.s_addr = INADDR_ANY;
    endereco.sin_port = htons (Port);

    if(bind(sockf,(struct sockaddr *)&endereco, sizeof(endereco)) < 0){
        cout << "Falha no bind\n";
        return 0;
    }

    if(listen(sockf,3) < 0){
        cout << "Falha no listen\n";
        return 0;
    }
    cout << "Olá esperando conexão\n";
    if((socks = accept(sockf, (struct sockaddr *)&endereco,(socklen_t *)&tamend)) < 0){
        cout << "Erro no accept\n";
        return 0;
    }
    valread = read(socks, buffer, 1024);
    string aux;
    
    while(valread){
        aux = "";
        for(int i=1; i<strlen(buffer); i++){
            if(buffer[i] == '>')break;
            aux += buffer[i];
        }
        if(aux == "CONNECTION_OPEN"){
            cout << "conectado" << endl;
            cout << "v para dançar, qualquer tecla para parar;\nl para voltar a posicao inicial;\nm para sair;\na,q,s,w,d,e,f,r,g,t,h,y para movimentar;\nz,x,c passos individuais.\n";
            strcpy(msg,"CONNECTION_OPEN;;");
            send(socks,/*string*/ msg,/*tamstring*/ strlen(msg),0);
        }
        if(aux == "GET_NUM_ARMS"){
            strcpy(msg,"GET_NUM_ARMS;1;");
            send(socks, msg, strlen(msg), 0);
        }
        if(aux == "GET_ARM_CODNAME;1"){
            strcpy(msg,"GET_ARM_CODNAME;1;NS_00101");
            send(socks, msg, strlen(msg), 0);
        }
        if(aux == "GET_ARM_AXES;1"){
            strcpy(msg,"GET_ARM_AXES;1;111111----");
            send(socks, msg, strlen(msg), 0);
        }
        if(aux == "GET_ARM_AUX;1"){
            strcpy(msg,"GET_ARM_AUX;1;----------;");
            send(socks, msg, strlen(msg), 0);
        }
        if(aux == "GET_ARM_BASE;1"){
            strcpy(msg,"GET_ARM_BASE;1;0;0;0;0;0;0");
            send(socks, msg, strlen(msg), 0);
        }
        if(aux == "GET_TOOL_RMT;1"){
            strcpy(msg,"GET_TOOL_RMT;1;False");
            send(socks, msg, strlen(msg), 0);
        }
        if(aux == "GET_ARM_ALL_FRAMES;1"){
            strcpy(msg,"GET_ARM_ALL_FRAMES;1;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0");
            send(socks, msg, strlen(msg), 0);
        }
        if(aux == "GET_AUX_BASE;1"){
            strcpy(msg,"GET_AUX_BASE;1;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0");
            send(socks, msg, strlen(msg), 0);
        }
        //aqui que está a brincadeira
        if(aux == "GET_ALL_JNT"){
            //strcpy(msg, "GET_ALL_JNT;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0");
            strcpy(msg, "GET_ALL_JNT");
            for(int i=0; i<40; i++){
                itos(junta[i]);
                strcat(msg,";");
                strcat(msg,sdcat);
            }
            //printf("%s\n",msg);
            //printf("%d\n",junta[0] );
            //strcpy(msg, "GET_ALL_JNT;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0");
            //printf("%s\n",msg);
            send(socks, msg, strlen(msg), 0);
        }
        //end brincadeira
        if(aux == "GET_IR_TYPES"){
            strcpy(msg,"GET_IR_TYPES;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0");
            send(socks, msg, strlen(msg), 0);
        }
        valread = read(socks, buffer, 1024);
        if(quit)break;
    }
    cout << "Ate um outro dia\n";
    return 0;
}

