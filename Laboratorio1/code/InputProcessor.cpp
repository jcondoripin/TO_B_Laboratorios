#include "InputProcessor.h"
#include <algorithm>
#include <regex>
#include <stdexcept>

using namespace std;

vector<CalculatorCore::Token> InputProcessor::tokenize(const string &input)
{
  string s = input;
  regex number_re(R"([0-9]+(?:\.[0-9]+)?)");
  regex op_re(R"([+\-*/])");

  vector<pair<size_t, CalculatorCore::Token>> matches;

  for (sregex_iterator it(s.begin(), s.end(), number_re), end; it != end; ++it)
  {
    smatch m = *it;
    CalculatorCore::Token tk;
    tk.isNumber = true;
    tk.number = stod(m.str());
    tk.pos = m.position();
    matches.emplace_back(tk.pos, tk);
  }

  for (sregex_iterator it(s.begin(), s.end(), op_re), end; it != end; ++it)
  {
    smatch m = *it;
    CalculatorCore::Token tk;
    tk.isNumber = false;
    tk.op = m.str()[0];
    tk.pos = m.position();
    matches.emplace_back(tk.pos, tk);
  }

  sort(matches.begin(), matches.end(), [](auto &a, auto &b)
       { return a.first < b.first; });

  vector<CalculatorCore::Token> tokens;
  for (const auto &m : matches)
  {
    tokens.push_back(m.second);
  }

  vector<CalculatorCore::Token> cleaned;
  for (size_t i = 0; i < tokens.size(); ++i)
  {
    auto &t = tokens[i];

    if (!t.isNumber && (t.op == '+' || t.op == '-'))
    {
      bool isUnary = false;

      if (i == 0)
      {
        isUnary = true;
      }
      else if (!tokens[i - 1].isNumber)
      {
        isUnary = true;
      }

      if (isUnary)
      {
        if (i + 1 < tokens.size() && tokens[i + 1].isNumber)
        {
          double val = tokens[i + 1].number;
          if (t.op == '-')
            val = -val;

          CalculatorCore::Token nt;
          nt.isNumber = true;
          nt.number = val;
          nt.pos = t.pos;
          cleaned.push_back(nt);
          ++i;
          continue;
        }
        else
        {
          throw runtime_error("Signo unario mal empleado o expresión inválida");
        }
      }
    }

    cleaned.push_back(t);
  }

  size_t nums = 0;
  for (auto &tk : cleaned)
    if (tk.isNumber)
      ++nums;

  if (nums == 0)
    throw runtime_error("No se encontraron números en la expresión");

  if (nums > maxNumbers)
    throw runtime_error("La expresión supera el máximo de " + to_string(maxNumbers) + " números");

  bool expectNumber = true;
  for (auto &tk : cleaned)
  {
    if (expectNumber && !tk.isNumber)
      throw runtime_error("Formato inválido: se esperaba número");
    if (!expectNumber && tk.isNumber)
      throw runtime_error("Formato inválido: se esperaba operador");
    expectNumber = !expectNumber;
  }

  if (!cleaned.empty() && !cleaned.back().isNumber)
    throw runtime_error("Expresión termina en operador");

  return cleaned;
}
