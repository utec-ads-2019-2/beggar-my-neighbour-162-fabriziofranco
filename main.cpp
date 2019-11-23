#include <queue>
#include <iostream>
#include <iomanip>

using namespace std;

void FillTurns(const int *card, int iterator, queue<int> &A, queue<int> &B);

void Pop(queue<int> &A, queue<int> &B, queue<int> &H, int turn);

int LastValue(const queue<int> &A, const queue<int> &B, int dealer);

int cValue(int card_temp);

void PlayingCard(queue<int> &A, queue<int> &B, queue<int> &H, int &turn, int &card_temp, int &ended);

int getCardValue(char card) {
    if(card == 'A')
        return 1;
    else if(card == 'J')
        return 11;
    else if(card == 'Q')
        return 12;
    else if(card == 'K')
        return 13;
    else if(card == 'T')
        return 10;

    else
        return card-'0';
}

int main() {
    char input[50];
    int Stack[52], iterator;
    while(true) {
        for(iterator = 0; iterator < 52; iterator++) {
            cin>>input;
            if(input[0] == '#')
                return 0;
            Stack[iterator] = getCardValue(input[1]);
        }
        queue<int> A, B, H;
        FillTurns(Stack, iterator, A, B);
        int turn = 1, dealer = -1;
        while(true) {
            if(turn == 0 and A.empty()) {
                dealer = 0;
                break;
            }
            if(turn == 1 and B.empty()) {
                dealer = 1;
                break;
            }
            int card_temp;
            int ended;
            PlayingCard(A, B, H, turn, card_temp, ended);
            while(card_temp >= 11 or card_temp == 1) {
                ended = 0;
                int c=0;
                c = cValue(card_temp);
                for(iterator = 0; iterator < c; iterator++) {
                    if(turn == 0 and A.empty()) {
                        dealer = 0;
                        break;
                    }
                    if(turn == 1 and B.empty()) {
                        dealer = 1;
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
                if(dealer >= 0)
                    break;
                turn = 1-turn;
            }
            if(dealer >= 0)
                break;
            if(ended == 0)
                Pop(A, B, H, turn);
        }
        int decision;
        decision = LastValue(A, B, dealer);
        cout << 2-dealer << std::setw(3) << decision << endl;
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

int cValue(int card_temp) {
    int c=0;
    if(card_temp == 1)
        c = 4;
    else if(card_temp == 11)
        c = 1;
    else if(card_temp == 12)
        c = 2;
    else if(card_temp == 13)
        c = 3;
    return c;
}

int LastValue(const queue<int> &A, const queue<int> &B, int dealer) {
    int z;
    if(dealer)
        z= A.size();
    else
        z = B.size();
    return z;
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

void FillTurns(const int *card, int iterator, queue<int> &A, queue<int> &B) {
    for(iterator = 51; iterator >= 0; iterator--) {
        if(iterator%2)
            A.push(card[iterator]);
        else
            B.push(card[iterator]);
    }
}
