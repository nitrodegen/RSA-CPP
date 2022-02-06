
/* 
*       RSA Implementation 
*           by suibex (nitrodegen)
*               https://cyfly.rs
*           
*       Date of last changes : Feb 5 22.
*/
#include <fstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <boost/multiprecision/cpp_int.hpp>
#include <sstream>

#define ll long long int 
namespace mp = boost::multiprecision;
using namespace std;

ll findD(ll e, ll fn) {
    int k = 0;
    int d = 0;

    while (true) {
        float res = 1 + (k * fn);
        float fin = res / e;
       
        if (fin > 0 && fin == (int)fin) {
            d += fin;
            break;
        }
        k += 1;
    }
    return d;


}
long long int coprime(ll fn) {
    ll hcf = 0;
    vector<ll>nums;
    //check if i is coprime with fn

    for (int i = 2; i < fn; i++) {
        for (int j = 1; j <= fn; j++) {
            if (i % j == 0 && fn % j == 0) {
                hcf = j;
            }
        }
        if (hcf == 1) {
            nums.push_back(i);
        }
    }
    ll min = 0, max = nums.size();
    ll range = max - min + 1;
    ll random = rand() % range + min;


    return nums[random];
}
long long int Prime() {
    ll x = 30;
    ll y = 100;
    vector<ll>primes;
    bool p = false;
    for (int i = x; i < y; i++) {
        p = true;

        for (int num = 2; num < i; num++) {

            if (i % num == 0) {
                p = false;
            }

        }
        if (p) {
            primes.push_back(i);
        }


    }


    ll min = 0;
    ll max = primes.size();
    ll range = max - min + 1;
    ll random = rand() % range + min;

    return primes[random];
}
mp::cpp_int powed(long long firstnum, long long powi) {
    return mp::pow(mp::cpp_int(firstnum), powi);
}
vector<pair<ll,ll>>KeyPair() {
    long long p, q, e, d, fn, n;
    vector<pair<ll, ll> > pairs;
    p = Prime();
    q = Prime();
    n = p * q;
    fn = (p - 1) * (q - 1);
    e = coprime(fn);
    d = findD(e, fn);

   
    pairs.push_back(make_pair(e, n));
    pairs.push_back(make_pair(d, n));
    return pairs;

}

vector<string> Encrypt(vector<ll>pub, string host) {
    ll mod = pub[1];
    ll powi = pub[0];

    vector<string>fina;
    for (int i = 0; i < host.length(); i++) {
        int ch =(int) host[i];
        string inp;
       
        mp::cpp_int powing = powed(ch, powi);
        mp::cpp_int t = powing % mod;
        
       
        stringstream ss;
        ss << t;
       
        ss >> inp;
        fina.push_back(inp);

        
         
    }
  
   
    return fina;
   
}
string Decrypt(vector<ll>priv, vector<string> encrypted) {
    ll mod = priv[1];
    ll powi = priv[0];
    string fina;
    vector<int>shit;
    for (int i = 0; i < encrypted.size(); i++) {
        stringstream ss;
        int t;
        ss << encrypted[i];
        ss >> t;
        shit.push_back(t);
    }
    for (int i = 0; i < shit.size(); i++) {
        int num = shit[i];
        mp::cpp_int sh = powed(num, powi) % mod;
        fina += (int)sh;
    }
    
    return fina;
}

int main(int argc, char *argv[])
{
    cout << "RSA Encryption started." << endl;
    vector<pair<ll, ll> > pairs = KeyPair();
    vector<ll> test, pub, priv;
    string arg = argv[1];
    string str = argv[2];
    if (arg == "-e") {
        for (auto const& th : pairs) {
            test.push_back(th.first);
            test.push_back(th.second);

        }
        pub.push_back(test[0]);
        pub.push_back(test[1]);
        priv.push_back(test[2]);
        priv.push_back(test[3]);


        vector<string>  encr = Encrypt(pub, argv[2]);



        string decr = Decrypt(priv, encr);

        stringstream ss;
        string s;

        for (int i = 0; i < encr.size(); i++) {
            stringstream ss;
            int z;
            ss << encr[i];
            ss >> z;
            ss.clear();
            ss << hex << z;
            string inp;
            ss >> inp;
            s += inp;

        }

        cout << "*********************** ENCRYPTED *************************" << endl;
        cout << s << endl;
        cout << "*********************** DECRYPTED *************************" << endl;
        cout << decr << endl;
        ofstream z("key.pub");
        z << pub[0] + ":" + pub[1];
        z.close();
        ofstream z1("key.private");
        z1 << priv[0] + ":" + priv[1];
        z1.close();

    }
    
    

}