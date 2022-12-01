#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
const int MAX = 63000;
vector<double> vertices[MAX];
vector<double> vns[MAX];
vector<double> fs[MAX];
int vacc = 0;

int main()
{

  ifstream myfile("deer.obj");
  if (myfile.is_open())
  {

    string mystring;
    while (myfile >> mystring)
    {
      if (mystring == "v")
      {
        for (int i = 0; i < 3; i++)
        {
          myfile >> mystring;
          double local = stod(mystring);

          vertices[vacc].push_back(local);
        }
        // cout << vertices[vacc][0] << vertices[vacc][1] << vertices[vacc][2] << endl;
        // vacc++;
        // cout << vacc << endl;
      }
      else if (mystring == "vn")
      {
        for (int i = 0; i < 3; i++)
        {
          myfile >> mystring;
          double local = stod(mystring);

          vns[vacc].push_back(local);
        }
        // cout << vns[vacc][0] << vns[vacc][1] << vns[vacc][2] << endl;
        // vacc++;
        // cout << vacc << endl;
      }
      else if (mystring == "f")
      {
        for (int i = 0; i < 3; i++)
        {
          myfile >> mystring;
          int endIdx = mystring.rfind('/');
          mystring = mystring.substr(0, endIdx - 1);
          double local = stoi(mystring);

          fs[vacc].push_back(local);
        }
        // cout << fs[vacc][0] << fs[vacc][1] << fs[vacc][2] << endl;
        // vacc++;
        // cout << vacc << endl;
      }
    }
  }
  return 0;
}