#pragma once

#include <concepts>
#include <utility>

namespace cango {
    /// @brief 对于提供的基类，将其转换为模板中的扩展类
    /// @tparam extension_type 扩展类，必须继承基类的同时，拥有一个 base_type 成员类型，大小与基类一致
    /// @tparam base_type 默认为由 extension_type::base_type 定义的类型
    /// @param base 基类引用
    /// @return 指向基类的扩展类引用
    template<typename extension_type, typename base_type = typename extension_type::base_type>
        requires std::is_base_of_v<base_type, extension_type> && (sizeof(extension_type) == sizeof(base_type))
    extension_type &extend_cast(base_type &base) noexcept { return reinterpret_cast<extension_type &>(base); }

    /// @brief 对于提供的基类，将其转换为模板中的扩展类
    /// @tparam extension_type 扩展类，必须继承基类的同时，拥有一个 base_type 成员类型，大小与基类一致
    /// @tparam base_type 默认为由 extension_type::base_type 定义的类型
    /// @param base 基类引用
    /// @return 指向基类的扩展类引用
    template<typename extension_type, typename base_type = typename extension_type::base_type>
        requires std::is_base_of_v<base_type, extension_type> && (sizeof(extension_type) == sizeof(base_type))
    const extension_type &extend_cast(const base_type &base) { return reinterpret_cast<const extension_type &>(base); }

    /// @brief 指明类提供对于基类的方法扩展，常用于因为方法名称不匹配而无法在接口使用的对象，如果需要扩展属性，禁止使用此类
    /// @tparam TBase 基类，已经在此类中继承
    template<typename TBase>
    class provide_extension : public TBase {
        /// @brief 防止构造扩展类
        provide_extension() = default;

    public:
        /// @brief 基类类型
        using base_type = TBase;
    };
}
