#include <bits/stdc++.h>

using namespace std;

string python_pow_to_math_pow(string s) {
  string res;
  for (int i = 0; i < (int)s.size(); ++i) {
    if (i + 1 < (int)s.size() && s[i] == '*' && s[i + 1] == '*')
      res.push_back('^'), ++i;
    else
      res.push_back(s[i]);
  }
  return res;
}

string math_pow_to_python_pow(string s) {
  string res;
  for (int i = 0; i < (int)s.size(); ++i) {
    if (s[i] == '^')
      res += "**";
    else
      res.push_back(s[i]);
  }
  return res;
}

int main() {
  freopen("deriv.in", "r", stdin);
  freopen("deriv.out", "w", stdout);
  string s;
  while (!cin.eof()) {
    getline(cin, s);
    cout << python_pow_to_math_pow(s) << endl;
  }
  return 0;
}
