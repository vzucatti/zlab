
#include <iostream>
#include "core.hpp"
#include "math.hpp"

int main(){
    using namespace std;
    
    cout << "Hello bibi!\n";
    
    zlab::scalarType a{10};
    
    zlab::pow(2.0,2.0);

    zlab::Bump rbf1{10};
    auto tmp = rbf1.evaluate(2.0);
    cout << tmp << endl;
    
    return 0;
}
