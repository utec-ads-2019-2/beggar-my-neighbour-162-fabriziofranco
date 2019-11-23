#include <queue>
#include <iostream>
using namespace std;

void FillTurns(const int *card, int it, queue<int> &A, queue<int> &B);

void Pop(queue<int> &A, queue<int> &B, queue<int> &H, int turn);

int LastValue(const queue<int> &A, const queue<int> &B, int judge);

int PaidValue(int card_temp);

void PlayingCard(queue<int> &A, queue<int> &B, queue<int> &H, int &turn, int &card_temp, int &ended);

int getCardValue(char card) {
    if(card == 'A'){
        return 1;}
    else if(card == 'T')
        return 10;
    else if(card == 'J')
        return 11;
    else if(card == 'Q')
        return 12;
    else if(card == 'K')
        return 13;
    else
        return card-'0';
}

int main() {
    char input[50];
    int card[52];
    int it;
    while(true) {
        for(it = 0; it < 52; it++) {
            cin>>input;
            if(input[0] == '#')
                return 0;
            card[it] = getCardValue(input[1]);
        }
        queue<int> A, B, H;
        FillTurns(card, it, A, B);
        int turn = 1, judge = -1;
        while(true) {
            if(turn == 0 and A.empty()) {
                judge = 0;
                break;
            }
            if(turn == 1 and B.empty()) {
                judge = 1;
                break;
            }
            int card_temp;
            int ended;
            PlayingCard(A, B, H, turn, card_temp, ended);
            while(card_temp >= 11 or card_temp == 1) {
                ended = 0;
                int paid=0;
                paid = PaidValue(card_temp);
                for(it = 0; it < paid; it++) {
                    if(turn == 0 and A.empty()) {
                        judge = 0;
                        break;
                    }
                    if(turn == 1 and B.empty()) {
                        judge = 1;
                        break;
                    }
                    if(turn == 0)
                        card_temp = A.front(), A.pop();
                    else
                        card_temp = B.front(), B.pop();
                    H.push(card_temp);
                    if(card_temp == 1 or card_temp >= 11)
                        break;
                }
                if(judge >= 0)  break;
                turn = 1-turn;
            }
            if(judge >= 0)
                break;
            if(ended == 0)
                Pop(A, B, H, turn);
        }
        int decision;
        decision = LastValue(A, B, judge);
        printf("%d%3d\n", 2-judge,  decision);
    }
}

void PlayingCard(queue<int> &A, queue<int> &B, queue<int> &H, int &turn, int &card_temp, int &ended) {
    ended= 1;
    if(turn == 0)
        card_temp = A.front(), A.pop();
    else
        card_temp = B.front(), B.pop();
    H.push(card_temp);
    turn = 1-turn;
}

int PaidValue(int card_temp) {
    int paid=0;
    if(card_temp == 1)
        paid = 4;
    else if(card_temp == 11)
        paid = 1;
    else if(card_temp == 12)
        paid = 2;
    else if(card_temp == 13)
        paid = 3;
    return paid;
}

int LastValue(const queue<int> &A, const queue<int> &B, int judge) {
    int a;
    if(judge)
        a= A.size();
    else
        a = B.size();
    return a;
}

void Pop(queue<int> &A, queue<int> &B, queue<int> &H, int turn) {
    if(turn == 0) {
        while(!H.empty()) {
            A.push(H.front());
            H.pop();
        }
    } else {
        while(!H.empty()) {
            B.push(H.front());
            H.pop();
        }
    }
}

void FillTurns(const int *card, int it, queue<int> &A, queue<int> &B) {
    for(it = 51; it >= 0; it--) {
        if(it%2)
            A.push(card[it]);
        else
            B.push(card[it]);
    }
}
