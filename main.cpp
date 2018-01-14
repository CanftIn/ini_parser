#include <iostream>
#inlcude "test.hpp"
#include <sstream>
using namespace std;

void test()
{
    std::stringstream ss;
    ss <<
    "a=1\n"
    "b=1\n\n"
    "[e]\n"
    "ea=1\n"
    "eb=1\n\n"
    "[c]\n"
    "ca=2\n"
    "cb=2\n\n"
    "[[d]]\n"
    "da=3\n"
    "db=3\n\n"
    "[A]\n"
    "Aa=4\n"
    "Ab=4\n";

    INI::Parser p(ss);
    std::stringstream out;
    p.dump(out);
    assert(out.str() == ss.str());
    assert(p.top()["a"]=="1");

}





int main()
{
    test();
    return 0;
}
