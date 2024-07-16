// RSA.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<vector>
#include<set>
#include<string>
using namespace std;
set<int>primes;
int gcd(int a, int h) {
    int temp;
    while (1) {
        temp = a % h;
        if (temp == 0)return h;
        a = h;
        h = temp;
    }
}

int public_key;
int private_key;
int n;

void prime_filler() {
    vector<bool>seive(250, true);
    seive[0] = false;
    seive[1] = false;
    for (int i = 2; i < 250; i++) {
        for (int j = i * 2; j < 250; j += i) {
            seive[j] = false;
        }
    }
    for (int i = 0; i < 250; i++) {
        if (seive[i]) {
            primes.insert(i);
        }
    }
}

int pick_random_prime() {
    int k = rand() % primes.size();
    auto it = primes.begin();
    while (k--) {
        it++;
    }
    int ret = *it;
    primes.erase(it);
    return ret;
}

void set_keys() {
    
    int prime1 = pick_random_prime();
    int prime2 = pick_random_prime();
    n = prime1 * prime2;
    int phi = (prime1 - 1) * (prime2 - 2);
    int e = 2;
    while (1) {
        if (gcd(e, phi) == 1)break;
        else
            e++;
    }//d = (k*phi+1)/e

    //d stands for decryption
    public_key = e;
    int d = 2;
    while (1) {
        if ((d * e) % phi == 1)break;
        else
            d++;
    }
    private_key = d;
}

long long int encrypt(double message) {
    int e = public_key;
    long long int encrypted_text = 1;
    while (e--) {
        encrypted_text *= message;
        encrypted_text %= n;
    }
    return encrypted_text;
}

long long int decrypt(int encrpyted_text) {
    int d = private_key;
    long long decrypted_text = 1;
    while (d--) {
        decrypted_text *= encrpyted_text;
        decrypted_text %= n;
    }
    return decrypted_text;
}

vector<int>encoder(string message) {
    vector<int>arr;
    for (auto& a : message) {
        arr.push_back(encrypt(static_cast<int>(a)));
    }
    return arr;
}

string decoder(vector<int>encoded) {
    string s;
    for (auto& a : encoded) {
        s += decrypt(a);
    }
    return s;
}
int main()
{
    prime_filler();
    set_keys();
    string message = "Hello this is secret informationn\n";
    vector<int>coded = encoder(message);
    for (auto& p : coded)cout << p;
    cout << "=============================\n";
    
    cout << decoder(coded)<<endl;
    return 0;
}