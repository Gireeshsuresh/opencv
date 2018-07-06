#include <iostream>
using namespace std;

class Human
{
  private:
    int age;

  public:
    void SetAge(int inputAge)
    {
        age = inputAge;
    }
    int GetAge()
    {
        if (age > 30)
            return (age - 3);
        else
            return age;
    }
};

int main(int argc, char const *argv[])
{
    Human eve;
    eve.SetAge(20);
    Human steve;

    steve.SetAge(40);
    cout << "Age of First Object: " << eve.GetAge() << endl;
    cout << "Age of First Object: " << steve.GetAge() << endl;
    return 0;
}
