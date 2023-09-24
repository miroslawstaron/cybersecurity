#include <iostream>
#include <vector>
#include "json.hpp"
using json = nlohmann::json;

class Issue1005 {
public:
    void test_for_issue() {
        Model model = json::parse("{\"values\":[[1,2,3]]}").get<Model>();
        assert(model.values.size() == 1);
        assert(model.values[0].size() == 3);
        assert(typeid(model.values[0][0]) == typeid(int8_t));
        assert(typeid(model.values[0][1]) == typeid(int8_t));
        assert(typeid(model.values[0][2]) == typeid(int8_t));
    }

    void test_for_List() {
        Model2 model = json::parse("{\"values\":[1,2,3]}").get<Model2>();
        assert(model.values.size() == 3);
        assert(typeid(model.values[0]) == typeid(int8_t));
        assert(typeid(model.values[1]) == typeid(int8_t));
        assert(typeid(model.values[2]) == typeid(int8_t));
    }

    struct Model {
        std::vector<std::vector<int8_t>> values;
    };

    struct Model2 {
        std::vector<int8_t> values;
    };
};

int main() {
    Issue1005 test;
    test.test_for_issue();
    test.test_for_List();
    return 0;
}
