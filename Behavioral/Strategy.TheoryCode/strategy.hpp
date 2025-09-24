#ifndef STRATEGY_HPP_
#define STRATEGY_HPP_

#include <algorithm>
#include <cctype>
#include <cstring>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

namespace Canonical
{
    // "Strategy"
    class Formatter
    {
    public:
        virtual std::string format(const std::string& data) = 0;
        virtual ~Formatter() = default;
    };

    // "ConcreteStrategyA"
    class UpperCaseFormatter : public Formatter
    {
    public:
        std::string format(const std::string& data) override
        {
            std::string transformed_data{data};

            std::transform(data.begin(), data.end(), transformed_data.begin(), [](char c) { return std::toupper(c); });

            return transformed_data;
        }
    };

    // "ConcreteStrategyB"
    class LowerCaseFormatter : public Formatter
    {
    public:
        std::string format(const std::string& data) override
        {
            std::string transformed_data{data};

            std::transform(data.begin(), data.end(), transformed_data.begin(), [](char c) { return std::tolower(c); });

            return transformed_data;
        }
    };

    // "ConcreteStrategyC"
    class CapitalizeFormatter : public Formatter
    {
    public:
        std::string format(const std::string& data) override
        {
            std::string transformed_data{data};

            if (data.size() >= 1)
            {
                transformed_data[0] = static_cast<char>(std::toupper(data.front()));

                std::transform(data.begin() + 1, data.end(), transformed_data.begin() + 1, [](char c) { return std::tolower(c); });
            }

            return transformed_data;
        }
    };

    // "Context"
    class Document
    {
        std::shared_ptr<Formatter> strategy_;
        std::string data_ = "text";

    public:
        Document(std::shared_ptr<Formatter> strategy)
            : strategy_{strategy}
        {
        }

        void set_formatter(std::shared_ptr<Formatter> new_strategy)
        {
            strategy_ = new_strategy;
        }

        void pretty_print()
        {
            std::cout << "Text: " << strategy_->format(data_) << std::endl;
        }

        std::string data() const
        {
            return data_;
        }

        void set_data(const std::string& data)
        {
            data_ = data;
        }
    };
} // namespace Canonical

namespace ModernCpp
{
    // "Strategy"
    using Formatter = std::function<std::string(const std::string&)>;

    // "ConcreteStrategyA"
    class UpperCaseFormatter
    {
    public:
        std::string operator()(const std::string& data)
        {
            std::string transformed_data{data};

            std::transform(data.begin(), data.end(), transformed_data.begin(), [](char c) { return std::toupper(c); });

            return transformed_data;
        }
    };

    // "ConcreteStrategyB"
    class LowerCaseFormatter
    {
    public:
        std::string operator()(const std::string& data)
        {
            std::string transformed_data{data};

            std::transform(data.begin(), data.end(), transformed_data.begin(), [](char c) { return std::tolower(c); });

            return transformed_data;
        }
    };

    // "ConcreteStrategyC"
    class CapitalizeFormatter
    {
    public:
        std::string operator()(const std::string& data)
        {
            std::string transformed_data{data};

            if (data.size() >= 1)
            {
                transformed_data[0] = static_cast<char>(std::toupper(data.front()));

                std::transform(data.begin() + 1, data.end(), transformed_data.begin() + 1, [](char c) { return std::tolower(c); });
            }

            return transformed_data;
        }
    };

    // "Context"
    class Document
    {
        Formatter formatter_;
        std::string data_ = "text";

    public:
        Document(Formatter strategy)
            : formatter_{strategy}
        {
        }

        void set_formatter(Formatter new_formatter)
        {
            formatter_ = new_formatter;
        }

        void pretty_print()
        {
            std::cout << "Text: " << formatter_(data_) << std::endl;
        }

        std::string data() const
        {
            return data_;
        }

        void set_data(const std::string& data)
        {
            data_ = data;
        }
    };
} // namespace ModernCpp

#endif /*STRATEGY_HPP_*/
