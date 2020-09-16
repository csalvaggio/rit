#include <iostream>
#include <string>

#include "imgs/ipcv/key_encryption/KeyEncryption.h"

using namespace std;

int main() {
  string key = "buffalo";
  string str = "This is a test of the key encryption system";
  // string key = "imgs";
  // string str = "Hello World!!!";
  // string key = "Salvaggio";
  // string str = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

  auto encrypted_str = ipcv::Encrypt(key, str);
  auto decrypted_str = ipcv::Decrypt(key, encrypted_str);

  cout << "Encryption Key:   " << endl << key << endl;
  cout << endl;
  cout << "Original String:  " << endl << str << endl;
  cout << endl;
  cout << "Encrypted String: " << endl << encrypted_str << endl;
  cout << endl;
  cout << "Decrypted String: " << endl << decrypted_str << endl;
  cout << endl;
}
