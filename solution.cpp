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
    if (!((s[i] >= '0' && s[i] <= '9') || s[i] == '.'))
      return false;
  }
  return true;
}

bool isLetter(char c) {
  return 'a' <= c && c <= 'z';
}

string derivative(string s) {
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
        return "((" + derivative(f) + ")*" + g + "-" + f + "*(" + derivative(g) + "))/" + g + "^2";
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
  for (int i = (int)s.size() - 1; i >= 0; --i) {
    if (s[i] == '^') {
      string f = s.substr(0, i), g = s.substr(i + 1, s.size() - i - 1);
      bool mark = false;
      for (int i = 0; i < (int)g.size(); ++i) {
        if ((i == 0 || !isLetter(i - 1)) && (i + 1 == (int)g.size() || !isLetter(i + 1)) && g[i] == 'x') {
          mark = true;
          break;
        }
      }
      if (mark)
        return f + "^" + g + "*(" + derivative(g + "*ln(" + f + ")") + ")";
      return g + "*" + f + "^(" + g + "-1)" + "*(" + derivative(f) + ")";
    }
    if (s[i] == ')') {
      int j, new_b;
      for (j = i - 1, new_b = 1; j >= 0 && new_b; --j) {
        if (s[j] == ')') ++new_b;
        else if (s[j] == '(') --new_b;
      }
      if (isLetter(s[j])) {
        while (j >= 0 && isLetter(s[j]))
          --j;
        i = j + 1;
      }
    }
  }
  if (isNumber(s))
    return "0";
  if (s == "x")
    return "1";
  if (s.size() >= 2 && s.substr(0, 2) == "ln") {
    string f = s.substr(2, s.size() - 2);
    return f + "^(-1)*" + "(" + derivative(f) + ")";
  }
  if (s.size() >= 3 && s.substr(0, 3) == "sin") {
    string f = s.substr(3, s.size() - 3);
    return "cos" + f + "*(" + derivative(f) + ")";
  }
  if (s.size() >= 3 && s.substr(0, 3) == "cos") {
    string f = s.substr(3, s.size() - 3);
    return "(-sin" + f + "*(" + derivative(f) + "))";
  }
  if (s.size() >= 2 && s.substr(0, 2) == "tg") {
    string f = s.substr(2, s.size() - 2);
    return "cos" + f + "^(-2)*(" + derivative(f) + ")";
  }
  if (s.size() >= 3 && s.substr(0, 3) == "ctg") {
    string f = s.substr(3, s.size() - 3);
    return "(-sin" + f + "^(-2)*(" + derivative(f) + "))";
  }
  if (s.size() >= 6 && s.substr(0, 6) == "arcsin")  {
    string f = s.substr(6, s.size() - 6);
    return "(1-" + f + "^2)^(-1/2)*(" + derivative(f) + ")";
  }
  if (s.size() >= 6 && s.substr(0, 6) == "arccos") {
    string f = s.substr(6, s.size() - 6);
    return "(-(1-" + f + "^2)^(-1/2))*(" + derivative(f) + ")";
  }
  if (s.size() >= 5 && s.substr(0, 5) == "arctg") {
    string f = s.substr(5, s.size() - 5);
    return "(1+" + f + "^2)^(-1)*(" + derivative(f) + ")";
  }
  if (s.size() >= 6 && s.substr(0, 6) == "arcctg") {
    string f = s.substr(6, s.size() - 6);
    return "(-(1+" + f + "^2)^(-1))*(" + derivative(f) + ")";
  }
  return "(" + s + ")";
}

int main() {
  freopen("deriv.in", "r", stdin);
  freopen("deriv.out", "w", stdout);
  string s;
  while (!cin.eof()) {
    getline(cin, s);
    s = python_pow_to_math_pow(remove_places(s));
    cout << math_pow_to_python_pow(derivative(s)) << endl;
  }
  return 0;
}
