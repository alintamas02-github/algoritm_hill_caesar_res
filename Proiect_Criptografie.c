#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

class hill
{
public:
  string msg, k;
  int *enc;
  int key[3][3], inv[3][3];
  hill(string a, string b)
  {
    msg = a;
    k = b;
    int i, j, l = 0;
    cout << "\nMatricea Cheie : " << endl;
    for (i = 0; i < 3; i++)
    {
      for (j = 0; j < 3; j++)
      {
        if (l >= k.size())
        {
          key[i][j] = 'x' - 'a' + 1;
        }
        else
        {
          key[i][j] = k[l] - 'a' + 1;
        }
        cout << key[i][j] << " ";
        l++;
      }
      cout << endl;
    }
    cout << endl;
    while (msg.size() % 3 != 0)
    {
      msg = msg + 'x';
    }
    cout << "Mesajul extins : ";
    cout << msg << endl;
    enc = new int[msg.size()];
  }

  void encrypt()
  {
    int i, l, m;
    for (l = 0; l < msg.size();)
    {
      m = l;
      for (i = 0; i < 3; i++)
      {
        enc[l] = (key[i][0] * (msg[m] - 'a' + 1) + key[i][1] * (msg[m + 1] - 'a' + 1) + key[i][2] * (msg[m + 2] - 'a' + 1)) % 26 + 'a' - 1;
        cout << (char)enc[l];
        l++;
      }
    }
  }

  void decrypt()
  {
    int det = key[0][0] * (key[1][1] * key[2][2] - key[1][2] * key[2][1]) -
              key[0][1] * (key[1][0] * key[2][2] - key[1][2] * key[2][0]) +
              key[0][2] * (key[1][0] * key[2][1] - key[1][1] * key[2][0]);

    det %= 26;
    if (det < 0)
      det += 26;

    int det_inv = -1;
    for (int i = 0; i < 26; ++i)
    {
      if ((det * i) % 26 == 1)
      {
        det_inv = i;
        break;
      }
    }

    if (det_inv == -1)
    {
      cout << "Nu se poate decripta, determinantul nu are invers modular!" << endl;
      return;
    }

    for (int i = 0; i < 3; ++i)
    {
      for (int j = 0; j < 3; ++j)
      {
        inv[j][i] = ((key[(i + 1) % 3][(j + 1) % 3] * key[(i + 2) % 3][(j + 2) % 3]) -
                     (key[(i + 1) % 3][(j + 2) % 3] * key[(i + 2) % 3][(j + 1) % 3]));
        inv[j][i] %= 26;
        if (inv[j][i] < 0)
          inv[j][i] += 26;

        inv[j][i] *= det_inv;
        inv[j][i] %= 26;
        if (inv[j][i] < 0)
          inv[j][i] += 26;
      }
    }

    cout << "Matricea inversă a cheii: " << endl;
    for (int i = 0; i < 3; ++i)
    {
      for (int j = 0; j < 3; ++j)
      {
        cout << inv[i][j] << " ";
      }
      cout << endl;
    }

    cout << "Mesajul decriptat: ";
    for (int l = 0; l < msg.size();)
    {
      for (int i = 0; i < 3; ++i)
      {
        int sum = 0;
        for (int j = 0; j < 3; ++j)
        {
          sum += inv[i][j] * (enc[l + j] - 'a' + 1);
        }
        sum %= 26;
        if (sum < 0)
          sum += 26;

        cout << (char)(sum + 'a' - 1);
      }
      l += 3;
    }
    cout << endl;
  }
};


class Caesar {
public:
    static string encrypt(const string& message, int shift) {
        string result = "";
        for (char c : message) {
            if (isalpha(c)) {
                char base = isupper(c) ? 'A' : 'a';
                result += static_cast<char>((c - base + shift) % 26 + base);
            } else {
                result += c; 
            }
        }
        return result;
    }

    static string decrypt(const string& message, int shift) {
        return encrypt(message, 26 - shift); 
    }
};

class RES {
public:
    static string encrypt(const string& message) {
        string result = "";
        for (char c : message) {
            if (isalpha(c)) {
                char base = isupper(c) ? 'A' : 'a';
                result += static_cast<char>('Z' - (c - base));
            } else {
                result += c; // Caracterele care nu sunt litere rămân neschimbate
            }
        }
        return result;
    }

    static string decrypt(const string& message) {
        return encrypt(message); // Decriptarea este identică cu criptarea în algoritmul RES
    }
};

int main()
{
  int choice;
  string s, k, opt;

  cout << "Meniu:" << endl;
  cout << "1. Sistemul Hill" << endl;
  cout << "2. Caesar algoritm" << endl;
  cout << "3. Algoritmul RES" << endl;
  cout << "Alege o opțiune: ";
  cin >> choice;

  switch (choice)
  {
  case 1:
    cout << "Introduceti mesajul de criptat: ";
    cin.ignore();
    getline(cin, s);
    cout << "Introduceti cheia de criptare: ";
    getline(cin, k);
    {
      hill h(s, k);
      cout << endl;
      cout << "Mesajul criptat este: ";
      h.encrypt();
      cout << endl;

      cout << "Decriptare? (da/nu): ";
      cin >> opt;
      if (opt == "da")
      {
        h.decrypt();
      }
    }
    break;

    case 2:
    cout << "Introduceti mesajul de criptat: ";
    cin.ignore();
    getline(cin, s);
    cout << "Introduceti deplasarea (shift-ul): ";
    cin >> k;
    {
        int shift = stoi(k);
        string encrypted = Caesar::encrypt(s, shift);
        cout << "Mesajul criptat este: " << encrypted << endl;

        cout << "Decriptare? (da/nu): ";
        cin >> opt;
        if (opt == "da") {
            string decrypted = Caesar::decrypt(encrypted, shift);
            cout << "Mesajul decriptat este: " << decrypted << endl;
        }
    }
    break;

    case 3:
    cout << "Introduceti mesajul de criptat: ";
    cin.ignore();
    getline(cin, s);
    {
        string encrypted = RES::encrypt(s);
        cout << "Mesajul criptat este: " << encrypted << endl;

        cout << "Decriptare? (da/nu): ";
        cin >> opt;
        if (opt == "da") {
            string decrypted = RES::decrypt(encrypted);
            cout << "Mesajul decriptat este: " << decrypted << endl;
        }
    }
    break;

  default:
    cout << "Opțiune invalidă!";
    break;
  }

  return 0;
}
