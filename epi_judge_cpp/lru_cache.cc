#include <vector>
#include <unordered_map>
#include <list>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"

class LruCache {
public:
    LruCache(size_t capacity) : capacity_(capacity) {}

    int Lookup(int isbn) {
        auto it = isbnPrice.find(isbn);
        if (it != isbnPrice.end()) {
            // already exist
            MoveToFront(isbn, it);
            return it->second.second;
        }
        return -1;
    }

    void Insert(int isbn, int price) {
        auto it = isbnPrice.find(isbn);
        if (it != isbnPrice.end()) {
            // already exist
            MoveToFront(isbn, it);
        } else {
            if (isbnPrice.size() == capacity_) {
                isbnPrice.erase(lruQueue.back());
                lruQueue.pop_back();
            }
            lruQueue.emplace_front(isbn);
            isbnPrice[isbn] = {lruQueue.begin(), price};
        }
    }

    bool Erase(int isbn) {
        auto it = isbnPrice.find(isbn);
        if (it == isbnPrice.end()) return false;

        lruQueue.erase(it->second.first);
        isbnPrice.erase(isbn);
        return true;
    }

private:
    typedef std::unordered_map<int, std::pair<std::list<int>::iterator, int>> Table;

    void MoveToFront(int isbn, const Table::iterator &it) {
        lruQueue.erase(it->second.first);
        lruQueue.emplace_front(isbn);
        it->second.first = lruQueue.begin();
    }

    size_t capacity_;
    Table isbnPrice;
    std::list<int> lruQueue;
};

struct Op {
  std::string code;
  int arg1;
  int arg2;
};

namespace test_framework {
template <>
struct SerializationTrait<Op> : UserSerTrait<Op, std::string, int, int> {};
}  // namespace test_framework

void LruCacheTester(const std::vector<Op>& commands) {
  if (commands.empty() || commands[0].code != "LruCache") {
    throw std::runtime_error("Expected LruCache as first command");
  }
  LruCache cache(commands[0].arg1);

  for (int i = 1; i < commands.size(); i++) {
    auto& cmd = commands[i];
    if (cmd.code == "lookup") {
      int result = cache.Lookup(cmd.arg1);
      if (result != cmd.arg2) {
        throw TestFailure("Lookup: expected " + std::to_string(cmd.arg2) +
                          ", got " + std::to_string(result));
      }
    } else if (cmd.code == "insert") {
      cache.Insert(cmd.arg1, cmd.arg2);
    } else if (cmd.code == "erase") {
      bool result = cache.Erase(cmd.arg1);
      if (result != cmd.arg2) {
        throw TestFailure("Erase: expected " + std::to_string(cmd.arg2) +
                          ", got " + std::to_string(result));
      }
    } else {
      throw std::runtime_error("Unexpected command " + cmd.code);
    }
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"commands"};
  return GenericTestMain(args, "lru_cache.cc", "lru_cache.tsv", &LruCacheTester,
                         DefaultComparator{}, param_names);
}
