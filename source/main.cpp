/*
TestFriends
(c) 2016
original authors: David I. Schwartz
Written under the supervision of David I. Schwartz, Ph.D., and
supported by a professional development seed grant from the B. Thomas
Golisano College of Computing & Information Sciences
(https://www.rit.edu/gccis) at the Rochester Institute of Technology.
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.
This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*	This tutorial illustrates the concept of friend with an example 
	of different ways to access to private number of an object.
*	It also covers issues such as constructor and keyword new/delete.
*/

// friend: see https://msdn.microsoft.com/en-us/library/465sdshe.aspx

#include <iostream>  // for cout
using namespace std; // for cout

class A;      // declare class A

class C {     // declare class C
public:
	C();      
	C(A& o);  // declare constructor
};

class A {                  // define class A
public:
	friend class B;        // class B has access to all members of A
	friend void test(A&);  // funtion test has the access
	friend C::C(A& o);     // constructor C::C(A& o) has the access
	A(int v) : x(v) {}     // constructor
	int getX() const { return x; }  // define member function getX | inline function
private:
	int x;                 // private member x
};

class B {                           // define class B
public:
	void test(A& o) {               // define member function test
		cout << o.getX() << endl;   // output the value of x of the parameter
	}
};

void test(A& o) { o.x = 200; }      // define global function test | make x of an A type object 200
C::C() {}                           // define constructor
C::C(A &o) { o.x = 100; }           // define constructor of class C

int main() {
	A* a = new A(10);           // allocate memory for a pointer "a" to an A object; put 10 as its argument
	cout << a->getX() << endl;  // output: 10
	B* b = new B();             // allocate memory for a pointer "b" to a B object
	b->test(*a);                // output: 10
	C* c = new C();             // allocate memory for a pointer "c" to a C object
	test(*a);                   // call the global function test which changes the x's value to 200
	cout << a->getX() << endl;  // output: 200
	C* d = new C(*a);           // allocate the memory for a pointer "d" to an C object; pass *a as its argument
	cout << a->getX() << endl;  // output: 100 | call the second construct of C object; change the value of x to 100
	delete a;
	delete b;
	delete c;
	delete d;                   // deallocate the memory
}