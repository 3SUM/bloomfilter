<br><br>

<p align="center">
<a href="https://github.com/LuisMaya"><img width="420" src="./logo/kitana.png" alt="kitana logo"></a>
</p>

<br><br>

# Kitana

Kitana is a Bloom filter implementation in C++. It makes use of the non-cryptographic
hash function `MurmurHash3`. Currently, Kitana uses `std::bitset` which does not allow for
dynamic sizing of the bitset. Future updates will include using `boost::dynamic_bitset` for
dynamic sizing and a parallel implementation of a Bloom filter.

## Installation & Usage

Kitana can be found in a single header [here](./src/bloomfilter.h). All you need to do is drop 
the file somewhere reachable from your project - either in some central location you can set 
your header search path to find, or directly into your project tree itself! Make sure the
`MurmurHash3` files are also reachable from your project.

Below, is a really simple example on how to use Kitana with various data types.

```c++
#include "bloomfilter.h"
#include <string>

int main(int argc, char *argv[])
{
    kitana::bloomfilter<int> b1;
    kitana::bloomfilter<std::string> b2;

    for(int i = 0; i < 100; i++) {
        b1.add(i);
        b2.add(std::to_string(i));
    }

    for(int i = 0; i < 100; i++) {
        b1.query(i);
        b2.query(std::to_string(i));
    }

    return 0;
}
```

## License

&copy; [Luis Maya Aranda](https://github.com/LuisMaya). All rights reserved.

Licensed under the MIT License.