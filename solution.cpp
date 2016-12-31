#include <bits/stdc++.h>

using namespace std;

string python_pow_to_math_pow(const string &s) {
  string res;
  for (int i = 0; i < (int)s.size(); ++i) {
    if (i + 1 < (int)s.size() && s[i] == '*' && s[i + 1] == '*')
      res.push_back('^'), ++i;
    else
      res.push_back(s[i]);
  }
  return res;
}

string math_pow_to_python_pow(const string &s) {
  string res;
  for (int i = 0; i < (int)s.size(); ++i) {
    if (s[i] == '^')
      res += "**";
    else
      res.push_back(s[i]);
  }
  return res;
}

vector<int> calc_balance_array(const string& s) {
  vector<int> b(s.size());
  for (int i = 0; i < (int)s.size(); ++i)
    b[i] = b[i - 1] + (s[i] == '(' ? 1 : (s[i] == ')' ? -1 : 0));
  return b;
}

// [l; r)
int min_balance(const vector<int>& b, int l, int r) {
  return b[(int)(min_element(b.begin() + l, b.begin() + r) - b.begin())];
}
// [l; r]
int balance(const vector<int>& b, int l, int r) {
  return (l ? b[r] - b[l] : b[r]);
}

string remove_outer_brackets(const string& s) {
  vector<int> b = calc_balance_array(s);
  int x = 0;
  for (; s[x] == '(' && s[s.size() - x - 1] == ')' && x + 1 < (int)s.size() - x - 1  && min_balance(b, x + 1, s.size() - x - 1) > x && b[s.size() - x  - 2] == x + 1; ++x) {
  }
  return s.substr(x, s.size() - 2 * x);
}

string derivative(string s) {
  s = remove_outer_brackets(s);
  return s;
}

int main() {
  //freopen("deriv.in", "r", stdin);
  //freopen("deriv.out", "w", stdout);
  string s;
  while (!cin.eof()) {
    getline(cin, s);
    cout << remove_outer_brackets(python_pow_to_math_pow(s)) << endl;
  }
  return 0;
}
