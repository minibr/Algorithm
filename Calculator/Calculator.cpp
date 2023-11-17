#include <iostream>
#include <string>
#include <stack>

using namespace std;

//연산자 우선순위 (클수록 우선) , 연산자를 담는 구조체
struct oper {
   int p;
   string o;
};

//숫자 , oper 구조체를 담는 스택
stack<double> num;
stack<oper> op;


//후위계산법을 통한 계산을 진행하는 함수
//계산 결과는 num 스택 top에 저장된다
void cal() {
   double a, b, result;

   b = num.top();
   num.pop();
   a = num.top();
   num.pop();
   
   string oper = op.top().o;
   op.pop();

   //cout << "계산 : " << a << ' ' << oper << ' ' << b << '\n';
   
   
   if (oper == "*") {
      result = a * b;
      num.push(result);
      //cout << "num 스택으로 : " << result << '\n';
   }
   else if (oper == "/")
      if (b == 0) {
         throw b;
      }
      else {
         result = a / b;
         num.push(result);
         //cout << "num 스택으로 : " << result << '\n';
      }

   else if (oper == "+") {
      result = a + b;
      num.push(result);
      //cout << "num 스택으로 : " << result << '\n';
   }
   else if (oper == "-") {
      result = a - b;
      num.push(result);
      //cout << "num 스택으로 : " << result << '\n';
   }
   //괄호 예외처리
   else if (oper == "(" || oper == "{" || oper == "[" || oper == ")" || oper == "}" || oper == "]") {
      char x = 'x';
      throw x;
   }
      
   
}
int main() {
   while (1) {
      try {
         string input;
         cin >> input;

         if (input == "EOI") break;

         int n = 0;

         for (int i = 0; i < input.length(); i++) {
            
            //열린 소,중,대 괄호 일 경우 연산자 스택에 push
            if (input[i] == '(') {
               string tmp;
               tmp = input[i];
               op.push({ 0,tmp });
               //cout << tmp << '\n';
            }

            //닫힌 소,중,대 괄호 일 경우 열린 괄호를 만날때까지 cal 함수 호출
            else if (input[i] == ')') {
               while (op.top().o != "(") {
                  cal();
                  //괄호 예외처리
                  if (op.empty()) {
                     char x = 'x';
                     throw x;
                  }
               }
               op.pop();
            }

            else if (input[i] == '{') {
               string tmp;
               tmp = input[i];
               op.push({ 0,tmp });
               //cout << tmp << '\n';
            }

            else if (input[i] == '}') {
               while (op.top().o != "{") {
                  cal();
                  if (op.empty()) {
                     char x = 'x';
                     throw x;
                  }
               }
               op.pop();
            }

            else if (input[i] == '[') {
               string tmp;
               tmp = input[i];
               op.push({ 0,tmp });
               //cout << tmp << '\n';
            }

            else if (input[i] == ']') {
               while (op.top().o != "[") {
                  cal();
                  if (op.empty()) {
                     char x = 'x';
                     throw x;
                  }
               }
               op.pop();
            }

            //연산자일 경우 우선 순위 부여 후 cal 함수 호출
            else if (input[i] == '*' || input[i] == '/' || input[i] == '+' || input[i] == '-') {
               int priority = 0;
               n = 0;
               if (input[i] == '*' || input[i] == '/')
                  priority = 2;
               else if (input[i] == '+' || input[i] == '-')
                  priority = 1;

               while (!op.empty() && priority <= op.top().p)
                  cal();
               string tmp;
               tmp = input[i];
               op.push({ priority, tmp });
               //cout << tmp << '\n';
            }

            //숫자 일 경우 num 스택에 push
            else if (isdigit(input[i])) {
               if (n == 0) {
                  string tmp_str = input.substr(i);
                  double tmp_int;
                  tmp_int = atof(tmp_str.c_str());
                  num.push(tmp_int);
                  //cout << tmp_int << '\n';
                  n = 1;
               }
            }
         }

         while (!op.empty())
            cal();

         cout << fixed;
         cout.precision(3);
         cout << num.top() << "\n";
      }

      catch (double except){
         cout << "Error!: divide by zero" << "\n";
      }

      catch (char except2) {
         cout << "Error!: unbalanced parentheses" << "\n";
      }
   }
   
   return 0;
}