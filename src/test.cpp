#include "inc/test.h"

bool ColourVectorTest();

void test(string test, bool result);

int main() {

  test("Colour(vector<Colour> &colour)", ColourVectorTest());

  return 0;
}

bool ColourVectorTest() {
  vector<Colour> colours;

  colours.push_back(Colour(50,  110, 100));
  colours.push_back(Colour(200, 120, 100));

  if (Colour(colours) == Colour(125, 115, 100)) {
    return true;
  }

  return false;
}

void test(string test, bool pass)
{
  cout << test << ": " << (pass ? "pass" : "fail") << endl;
}

