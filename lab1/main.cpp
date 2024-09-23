#include <iostream>
#include "src/myvector.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;


    myvector<int> massive;
    massive = {123,123,123};

    std::vector<int> awdawd;
    std::cout << "READ: " << massive.read(0) << std::endl;
    massive.push_back(321);
    std::cout << "SIZE: " << massive.length() << std::endl;
    for (int i = 0; i < massive.length(); ++i) {
        std::cout << massive[i] << std::endl;
    }
    massive.clear();
    std::cout << "SIZE: " << massive.length() << std::endl;
    for(auto d = massive.begin(); d != massive.end(); ++d) {
        std::cout << *d << std::endl;
    }
    std::cout << "INSERT: " << massive.write(0, 123) << std::endl;
    std::cout << "INSERT: " << massive.write(999, 123) << std::endl;
    std::cout << "INSERT: " << massive.write(-1, 123) << std::endl;
    massive[2] = 123;
    massive.push_back(818887);
    massive.push_back(123);
    massive.push_back(8123);
    massive.push_back(81233);
    massive.push_back(8123);
    massive.push_back(123);
    massive.push_back(123);
    massive.push_back(123);
    std::cout << "SIZE: " << massive.length() << std::endl;
    for(auto d = massive.begin(); d != massive.end(); ++d) {
        std::cout << d.index << ". " << *d << std::endl;
    }
    std::cout << "FOUND: " << massive.find(818887) << std::endl;
    std::cout << "FOUND ITER: " << massive.find_iterator(818887).index << std::endl;
    std::cout << "FOUND BOOL: " << massive.have(818887) << std::endl;
    std::cout << "ERRASE: " << massive.errase(1) << std::endl;
    std::cout << "ERRASE VAL: " << massive.errase_value(123) << std::endl;

    std::cout << "REVERSE SIZE: " << massive.length() << std::endl;
    for(auto d = massive.rbegin(); d != massive.rend(); ++d) {
        std::cout << d.index << ". " << *d << std::endl;
    }

    std::cout <<"SIZE: " << massive.length() << std::endl;
    for(auto d = massive.begin(); d != massive.end(); ++d) {
        std::cout << d.index << ". " << *d << std::endl;
    }

    //std::cout << "INSERT: " << massive.insert(7, 2) << ", SIZE: " << massive.length() << std::endl;
    std::cout << "INSERT: " << massive.insert(7,2) << "SIZE: " << massive.length() << std::endl;
    for(auto d = massive.begin(); d != massive.end(); ++d) {
        std::cout << d.index << ". " << *d << std::endl;
    }


    /*std::vector<int> vec;
    for (int i = 1 ; i < 6 ; ++i )
    {
        vec.push_back ( 2 * i );
    }
    std::vector <int>::iterator vIter;
    std::cout << "The vector vec is: " << std::endl;
    for ( vIter = vec.begin( ) ; vIter != vec.end( ); vIter++)
        std::cout << "\t" << std::distance(vec.begin(), vIter) << ". " << *vIter << std::endl;
    std::vector <int>::reverse_iterator rvIter;
    std::cout << "The vector vec reversed is: " << std::endl;
    for ( rvIter = vec.rbegin( ) ; rvIter != vec.rend( ); rvIter++)
        std::cout << "\t" << std::distance(vec.rbegin(), rvIter) << ". " << *rvIter << std::endl;*/

    return 0;
}
