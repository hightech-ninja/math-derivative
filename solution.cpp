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

string remove_places(const string& s) {
  string res;
  for (int i = 0; i < (int)s.size(); ++i)
    if (s[i] != ' ')
      res.push_back(s[i]);
  return res;
}

bool isNumber(const string& s) {
  for (int i = 0; i < (int)s.size(); ++i) {
    if (!(s[i] >= '0' && s[i] <= '9'))
      return false;
  }
  return true;
}

string derivative(string s) {
  cout << ":\t" << s << endl;
  s = remove_outer_brackets(s);
  int min_b = 100500, cur_b = 0;
  for (int i = 0; i < (int)s.size(); ++i) {
    if ((s[i] == '+' || s[i] == '-') && cur_b == 0 && min_b >= 0) { // (f +- g)' = f' +- g'
      string plus = "+", minus = "-";
      return derivative(s.substr(0, i)) + (s[i] == '+' ? plus : minus) + derivative(s.substr(i + 1, s.size() - i - 1));
    }
    if (s[i] == '(' && i > 0 && 'a' <= s[i - 1] && s[i - 1] <= 'z') {
      ++i;
      for (int new_b = 1; i < (int)s.size() && new_b; ++i) {
        new_b += (s[i] == '(' ? 1 : (s[i] == ')' ? -1 : 0));
      }
      --i;
      continue;
    }
    if (s[i] == '(' || s[i] == ')') {
      cur_b += (s[i] == '(' ? 1 : -1);
      min_b = min(min_b, cur_b);
    }
  }
  min_b = 100500, cur_b = 0;
  for (int i = 0; i < (int)s.size(); ++i) {
    if ((s[i] == '*' || s[i] == '/') && cur_b == 0 && min_b >= 0) {
      string f = s.substr(0, i), g = s.substr(i + 1, s.size() - i - 1);
      if (s[i] == '*') { // (fg)' = f'g + fg'
        return "(" + derivative(f) + ")" + "*" + g + "+" + f + "*(" + derivative(g) + ")";
      }
      else { // (f/g)' = (f'g - fg')/(g^2)
        return "(" + derivative(f) + ")* " + g + "-" + f + "*(" + derivative(g) + ")) / " + g + "^2";
      }
    }
    if (s[i] == '(' && i > 0 && 'a' <= s[i - 1] && s[i - 1] <= 'z') {
      ++i;
      for (int new_b = 1; i < (int)s.size() && new_b; ++i) {
        new_b += (s[i] == '(' ? 1 : (s[i] == ')' ? -1 : 0));
      }
      --i;
      continue;
    }
    cur_b += (s[i] == '(' ? 1 : (s[i] == ')' ? -1 : 0));
    min_b = min(min_b, cur_b);
  }
  min_b = 100500, cur_b = 0;
  for (int i = 0; i < (int)s.size(); ++i) {
    if (s[i] == '^') { // (f^g) = f^g * (g * ln(f))'
      string f = s.substr(0, i), g = s.substr(i + 1, s.size() - i - 1);
      return f + "^" + g + "*(" + derivative(g + "*ln(" + f + ")") + ")";
    }
    if (s[i] == '(' && i > 0 && 'a' <= s[i - 1] && s[i - 1] <= 'z') {
      ++i;
      for (int new_b = 1; i < (int)s.size() && new_b; ++i) {
        new_b += (s[i] == '(' ? 1 : (s[i] == ')' ? -1 : 0));
      }
      --i;
      continue;
    }
  }
  if (isNumber(s))
    return "0";
  if (s == "x")
    return "1";
  if (s.size() >= 2 && s.substr(0, 2) == "ln") {
    string f = s.substr(2, s.size() - 2);
    cout << "f:\t" << f << endl;
    return f + "^(-1)*" + "(" + derivative(f) + ")";
  }
  return "(" + s + ")'";
}

int main() {
  //freopen("deriv.in", "r", stdin);
  //freopen("deriv.out", "w", stdout);
  string s;
  while (!cin.eof()) {
    getline(cin, s);
    s = python_pow_to_math_pow(remove_places(s));
    cout << derivative(s) << endl;
  }
  return 0;
}
