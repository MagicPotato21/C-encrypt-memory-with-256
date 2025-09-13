#include <cryptopp/aes.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/filters.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <iostream>

int main()
{
  // Generate a random 256-bit key
  CryptoPP::AutoSeededRandomPool rng;
  byte key[CryptoPP::AES::DEFAULT_KEYLENGTH];
  rng.GenerateBlock(key, sizeof(key));

  // Define the input and output buffers
  const byte* input = (const byte*)"Hello, world!";
  size_t inputLength = 13;
  byte output[inputLength];

  // Encrypt the input using the key
  CryptoPP::ECB_Mode<CryptoPP::AES>::Encryption encryptor;
  encryptor.SetKey(key, sizeof(key));
  CryptoPP::ArraySink sink(output, sizeof(output));
  CryptoPP::ArraySource source(input, inputLength, true,
    new CryptoPP::StreamTransformationFilter(encryptor, new CryptoPP::Redirector(sink)));

  // Print the encrypted output
  std::cout << "Encrypted output: " << std::endl;
  for (size_t i = 0; i < inputLength; ++i)
  {
    std::cout << std::hex << (int)output[i] << " ";
  }
  std::cout << std::endl;

  return 0;
}
