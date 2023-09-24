#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

class Model {
public:
vector<int8_t> values;
};

void test_for_issue() {
auto model = json::parse("{"values":[1,2,3]}").get<Model>();
assert(!model.values.empty());
assert(model.values.size() == 3);
assert(typeid(model.values[0]) == typeid(int8_t));
assert(typeid(model.values[1]) == typeid(int8_t));
assert(typeid(model.values[2]) == typeid(int8_t));
}

int main() {
test_for_issue();
return 0;
}