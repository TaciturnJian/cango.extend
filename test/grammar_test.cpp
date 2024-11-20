#include <iostream>
#include <sstream>

#include <cango/extend.hpp>

// 这里是某些不可更改的库
namespace lib {
    struct context {
        int id;
        float value;
    };
}

// 接下来是我们的代码逻辑，我们需要将库中的内容嵌入到我们的逻辑中
namespace {
    /// @brief 对于 context 类的扩展，提供了 output 方法
    struct context_extension : cango::provide_extension<lib::context> {
        void output(std::ostream& stream) const {
            stream << id << ": " << value;
        }
    };

    /// @brief 对于任何支持 output 方法的对象，将其输出到两个流中
    template<typename object_type>
    concept streamable = requires(const object_type& object, std::ostream& stream) {
        { object.output(stream) };
    };

    /// @brief 对于任何支持 output 方法的对象，先输入到 @c std::ostringstream 中，再输出到第二个流中
    void double_streaming(const streamable auto& object, std::ostream& second_stream) {
        std::ostringstream first_stream;
        object.output(first_stream);
        second_stream << first_stream.str();
    }
}

int main() {
    lib::context ctx{1, 2.0f};

    using namespace cango;

    //double_streaming(ctx, std::cout); 错误： ctx 不支持 output 方法
    double_streaming(extend_cast<context_extension>(ctx), std::cout);
    // 在没有额外运行时开销（没有额外构造、析构）的情况下，我们获得了需要的 ctx

    std::cout << std::endl;
}
