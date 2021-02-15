/*
 * [2019] Signet Lab - Programming for ICT
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
*/

#include <iostream>
#include <memory>
#include "my-int.h"

/**
 * Method that takes a unique ptr of MyInt and multiplies it by two
 * @param up_int unique ptr to MyInt passed by value
 * @return the unique pointer to MyInt passed as input
 */
std::unique_ptr<MyInt> multiplyByTwoUp(std::unique_ptr<MyInt> up_int) {
  up_int->setVal(up_int->getVal()*2);
  return up_int; // equivalent to std::move(up_int)

}

/**
 * Method that takes a unique ptr reference  of MyInt and multiplies it by two
 * @param up_int unique ptr to MyInt passed by reference
 */
void multiplyByTwoUpRef(std::unique_ptr<MyInt>& up_int) {
  up_int->setVal(up_int->getVal()*2);

}

/**
 * Method that takes a shared ptr of MyInt and multiplies it by two
 * @param sp_int shared ptr to MyInt passed by value
 */
void multiplyByTwoSp(std::shared_ptr<MyInt> sp_int) {
  std::cout << "sp_int counter = " << sp_int.use_count() << std::endl;
  sp_int->setVal(sp_int->getVal()*2);
}

int
main(int argc, char const *argv[])
{
  
  std::unique_ptr<MyInt> up(new MyInt(4));
  std::cout << "up val = " << *up << std::endl;
  //multiplyByTwoUp(up); // does not even compile: up copy constructor is deleted
  //multiplyByTwoUp(std::move(up)); it was causing the sigfault
  up = multiplyByTwoUp(std::move(up)); // SOL1: move and get it back
  // We moved it! So the next line is a sigfault: 
  // TODO (you need to do this): comment it to move next
  std::cout << "up new val (SOL1)= " << *up << std::endl; 
  multiplyByTwoUpRef(up); // SOL2: const reference
  std::cout << "up new val (SOL2)= " << *up << std::endl; 

  up.reset(new MyInt(4));
  std::cout << "up val = " << *up << std::endl;
  up = multiplyByTwoUp(std::move(up));
  std::cout << "up new val = " << *up << std::endl; 


  // a shared ptr can be passed by value instead
  std::shared_ptr<MyInt> sp(std::make_shared<MyInt>(4));
  std::cout << "sp val = " << *sp << " sp counter = " << sp.use_count() << std::endl;
  multiplyByTwoSp(sp);
  std::cout << "sp new val = " << *sp << " sp counter = " << sp.use_count() << std::endl;

  return 0;
}
